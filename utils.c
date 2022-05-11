/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 22:05:26 by mgulenay          #+#    #+#             */
/*   Updated: 2022/05/09 12:00:17 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_message(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("Invalid number of arguments\n", STDOUT_FILENO);
		exit(1);
	}
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	if (str)
		free(str);
}

void	command_execution(char **command, char *path, char **envp)
{
	if (path != NULL && command != NULL)
	{
		execve(path, command, envp);
		perror(": there is a problem with execve!\n");
		ft_free(command);
		free(path);
	}
	else
	{
		write(2, command[0], ft_strlen(*command));
		write(2, ": command not found\n", 21);
		ft_free(command);
		free(path);
		exit(1);
	}
}

char	**env_path(char **envp)
{
	char	**possible_paths;
	char	*path_in_env;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	path_in_env = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	possible_paths = ft_split(path_in_env, ':');
	free(path_in_env);
	return (possible_paths);
}
