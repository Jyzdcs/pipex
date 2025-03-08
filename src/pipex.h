/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:17:13 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/08 01:15:51 by kclaudan         ###   ########.fr       */
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
# include <sys/wait.h>

typedef struct s_pipex
{
	char	*cmd;
	char	*cmd_path;
	char	**cmd_args;
	int		pipefd[2];
}			t_pipex;

/* Utils.c : utils */
void		handle_error(char *message);
char		**format_cmd(char *cmd);

/* Parsing.c : parsing et vérification des arguments */
char		*extract_cmd_name(char *cmd);
int			check_arguments(int argc);
int			check_file(char *filename, int mode);
char		*find_cmd_path(t_pipex pipex, char *env[]);
char		*get_path(char *env[]);

/* pipex.c : creation du pipe, gestion des child process et exec des cmd */
void		create_pipe(int pipefd[2]);
pid_t		create_process_1(t_pipex *pipex, char *env[], int input_fd);
pid_t		create_process_2(t_pipex *pipex, char *env[], int output_fd);
void		wait_for_processes(int pid1, int pid2);

/* redirections.c : gere les redirections entrer et de sortie*/
void		dup_and_redirect(int old_fd, int new_fd);
void		close_pipe(int pipefd[2]);

#endif