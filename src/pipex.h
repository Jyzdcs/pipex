/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:17:13 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/08 15:28:47 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* Include all necessary module headers */
# include "../include/libft/libft.h"
# include "cmd/command.h"
# include "parsing/parsing.h"
# include "process/process.h"
# include "redirections/redirections.h"
# include "utils/utils.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

// /**
//  * @brief Structure to hold pipeline information
//  */
// typedef struct s_pipex
// {
// 	char	*cmd;
// 	char	*cmd_path;
// 	char	**cmd_args;
// 	int		pipefd[2];
// }			t_pipex;

/* Utils.c : utils */
void	handle_error(char *message);
char	**format_cmd(char *cmd);

/* Parsing.c : parsing et vérification des arguments */
char	*extract_cmd_name(char *cmd);
int		check_arguments(int argc);
int		check_file(char *filename, int mode);
char	*find_cmd_path(t_pipex pipex, char *env[]);
char	*get_path(char *env[]);

/* pipex.c : creation du pipe, gestion des child process et exec des cmd */
void	create_pipe(int pipefd[2]);
pid_t	create_process_1(t_pipex *pipex, char *env[], int input_fd);
pid_t	create_process_2(t_pipex *pipex, char *env[], int output_fd);
void	wait_for_processes(int pid1, int pid2);

/* redirections.c : gere les redirections entrer et de sortie*/
void	dup_and_redirect(int old_fd, int new_fd);
void	close_pipe(int pipefd[2]);

#endif