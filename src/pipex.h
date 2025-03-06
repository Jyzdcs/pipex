/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:17:13 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/06 23:53:01 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define TRUE 1
# define FALSE 0
# include "../include/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_cmd
{
	char	*cmd;
	char	*cmd_path;
	char	**cmd_args;
}			t_cmd;

/* Utils.c : utils */
void		handle_error(char *message);
char		**format_cmd(char *cmd);

/* Parsing.c : parsing et vérification des arguments */
char		*extract_cmd_name(char *cmd);
int			check_arguments(int argc);
int			check_file(char *filename, int mode);
char		*find_cmd_path(char *cmd, char *env[]);
char		*get_path(char *env[]);

/* pipex.c : creation du pipe, gestion des child process et exec des cmd */
void		create_pipe(int pipefd[2]);
void		create_process_1(t_cmd *cmd, char *env[], int pipefd[2],
				int input_fd, int output_fd);
void		create_process_2(t_cmd *cmd, char *env[], int pipefd[2],
				int output_fd);
void		wait_for_processes(int pid1, int pid2);

/* redirections.c : gere les redirections entrer et de sortie*/
void		dup_and_redirect(int old_fd, int new_fd);
void		close_pipe(int pipefd[2]);

#endif