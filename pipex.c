/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:58:04 by mgulenay          #+#    #+#             */
/*   Updated: 2022/05/09 12:18:11 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* 
./pipex file1 cmd1 cmd2 file2    == < file1 cmd1 | cmd2 > file2
./pipex infile "ls -l" "wc -l" outfile == < infile ls -l | wc -l > outfile
./pipex infile "grep a1" "wc -w" outfile == < infile grep a1 | wc -w > outfile 
*/

/* look for the path line inside the environment, 
	split and check each command path and 
	return the right one 
*/

char	*find_right_path(char *command, char **envp)
{
	char	**possible_paths;
	char	*slash_to_end;
	char	*path_with_cmd;
	int		i;
	
	possible_paths = env_path(envp);
	i = 0;
	while (possible_paths[i])
	{
		slash_to_end = ft_strjoin(possible_paths[i], "/");
		path_with_cmd = ft_strjoin(slash_to_end, command);
		free(slash_to_end);
		if (access(path_with_cmd, F_OK) == 0)
			return (path_with_cmd);
		free(path_with_cmd);
		i++;
	}
	ft_free(possible_paths);
	return (NULL);
}

/* Child process -- created by fork, takes the infile to read from,
	 puts the output inside the pipe as input;
	closes the files are done, and executes the command
*/

void	first_process(int *pipefd, int *fds, char **argv, char **envp)
{
	char	**command;
	char	*path;

	fds[0] = open(argv[1], O_RDONLY);
	if (fds[0] < 0)
	{
		perror("Error occured while reading from infile\n");
		exit(1);
	}
	close(pipefd[0]);
	dup2(fds[0], STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	command = ft_split(argv[2], ' ');
	path = find_right_path(command[0], envp);
	command_execution(command, path, envp);
}

/* takes the inout from the pipe, changes the output for the outfile; 
	closes and executed the command
*/
void	second_process(int *pipefd, int *fds, char **argv, char **envp)
{
	char	**command;
	char	*path;

	fds[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 00664);
	if (fds[1] < 0)
	{
		perror("Error occured while writing in outfile\n");
		exit(1);
	}
	close(pipefd[1]);
	dup2(fds[1], STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	command = ft_split(argv[3], ' ');
	path = find_right_path(command[0], envp);
	command_execution(command, path, envp);
}

void	pipex(int *fds, int *pipefd, char **argv, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 < 0)
	{
		perror("Error while forking\n");
		exit(1);
	}
	if (pid1 == 0)
		first_process(pipefd, fds, argv, envp);
	waitpid(pid1, NULL, 0);
	pid2 = fork();
	if (pid2 < 0)
	{
		perror("Error while forking\n");
		exit(1);
	}
	if (pid2 == 0)
		second_process(pipefd, fds, argv, envp);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid2, NULL, 0);
}

/*  create the pipe, check errors, call child processes
	pipefd[0] -- file to be read from
	pipefd[1] -- file to be written into
*/
int	main(int argc, char **argv, char **envp)
{
	int	fds[2];
	int	pipefd[2];

	error_message(argc);
	if (pipe(pipefd) < 0)
	{
		perror("Error in pipe\n");
		exit(1);
	}
	pipex(fds, pipefd, argv, envp);
	return (0);
}
