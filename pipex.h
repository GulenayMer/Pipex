/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:57:56 by mgulenay          #+#    #+#             */
/*   Updated: 2022/05/09 11:40:43 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"

void	first_process(int *pipefd, int *fds, char **argv, char **envp);
void	second_process(int *pipefd, int *fds, char **argv, char **envp);
char	*find_right_path(char *command, char **envp);
void	pipex(int *fds, int *pipefd, char **argv, char **envp);
void	ft_free(char **str);
void	error_message(int argc);
void	command_execution(char **command, char *path, char **envp);
char	**env_path(char **envp);

#endif
