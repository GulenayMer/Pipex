/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:58:04 by mgulenay          #+#    #+#             */
/*   Updated: 2022/04/27 22:22:51 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* 
./pipex file1 cmd1 cmd2 file2    == < file1 cmd1 | cmd2 > file2

./pipex infile "ls -l" "wc -l" outfile == < infile ls -l | wc -l > outfile

./pipex infile "grep a1" "wc -w" outfile == < infile grep a1 | wc -w > outfile 

*/

/* Child process */
/* Parent process */

int main(int argc, char **argv)
{
	int fds[2];
	// fd[0] -- file to be read from
	// fd[1] -- file to be written into
	
	/* Error check */
	if (argc != 5)
	{
		//"Invalid number of arguments\n"
		return (1);
	}
	
	pipe(fds);
	if (pipe(fds) == -1)
	{
		perror("Error in pipe\n");
		return (1);
	}
	
	int pid1;
	pid1 = fork();
	if (pid1 < 0)
		perror("Error occured pid1\n");
	if (pid1 == 0)
	{
		fds[0] = open(argv[1], O_RDONLY);
		if (fd[0] < 0)
		{
			perror("Error occured while reading from infile\n");
			return (1);
		}
	}

	int pid2;
	pid2 = fork();
	if (pid2 < 0)
		perror("Error occured pid2\n");
	if (pid2 == 0)
	{
		fd[1] = open(argv[4], O_CREAT | O_RDWR | O_TRUNC);
		if (fd[1] < 0)
		{
			perror("Error occured while writing into outfile\n");
			return (1);
		}
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return (0);
}
