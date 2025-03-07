/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:17:13 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/07 18:12:24 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* ***********************************************************************  */
/*                               INCLUDES                                   */
/* ***********************************************************************  */

# include "../include/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>

/* ***********************************************************************  */
/*                                DEFINES                                   */
/* ***********************************************************************  */

# define TRUE 1
# define FALSE 0
# define ERROR -1
# define SUCCESS 0

/* Codes d'erreur */
# define ERR_ARGS 1
# define ERR_FILE 2
# define ERR_CMD 3
# define ERR_PIPE 4
# define ERR_FORK 5
# define ERR_EXEC 6
# define ERR_MEM 7

/* ***********************************************************************  */
/*                              STRUCTURES                                  */
/* ***********************************************************************  */

/**
 * @brief Structure contenant les informations d'une commande
 * 
 * @param cmd Nom de la commande
 * @param cmd_path Chemin complet vers l'exécutable
 * @param cmd_args Arguments de la commande (tableau terminé par NULL)
 */
typedef struct s_cmd
{
	char	*cmd;
	char	*cmd_path;
	char	**cmd_args;
}			t_cmd;

/**
 * @brief Structure contenant les données du programme
 * 
 * @param infile Chemin du fichier d'entrée
 * @param outfile Chemin du fichier de sortie
 * @param pipefd Descripteurs du pipe
 * @param cmd1 Première commande à exécuter
 * @param cmd2 Seconde commande à exécuter
 * @param env Environnement système
 */
typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	int		pipefd[2];
	t_cmd	cmd1;
	t_cmd	cmd2;
	char	**env;
}			t_pipex;

/* ***********************************************************************  */
/*                          FONCTION PRINCIPALES                            */
/* ***********************************************************************  */

/* main.c */
int		init_pipex(t_pipex *pipex, int argc, char *argv[], char *env[]);
void	exec_pipex(t_pipex *pipex);
void	cleanup_pipex(t_pipex *pipex);

/* ***********************************************************************  */
/*                         GESTION DES COMMANDES                            */
/* ***********************************************************************  */

/* cmd_parser.c */
char	*extract_cmd_name(char *cmd);
char	**format_cmd(char *cmd);
int		init_cmd(t_cmd *cmd, char *cmd_str, char **env);
void	free_cmd(t_cmd *cmd);

/* path_parser.c */
char	*get_path(char *env[]);
char	*find_cmd_path(char *cmd, char *env[]);

/* ***********************************************************************  */
/*                        GESTION DES PROCESSUS                             */
/* ***********************************************************************  */

/* process_manager.c */
pid_t	create_process_1(t_cmd *cmd, char *env[], int pipefd[2], int input_fd);
pid_t	create_process_2(t_cmd *cmd, char *env[], int pipefd[2], int output_fd);
void	wait_for_processes(pid_t pid1, pid_t pid2);

/* pipe_manager.c */
int		create_pipe(int pipefd[2]);
void	close_pipe(int pipefd[2]);

/* ***********************************************************************  */
/*                        GESTION DES FICHIERS                              */
/* ***********************************************************************  */

/* file_handler.c */
int		check_file(char *filename, int mode);
int		open_infile(char *filename);
int		open_outfile(char *filename);

/* redirection.c */
void	dup_and_redirect(int old_fd, int new_fd);

/* ***********************************************************************  */
/*                              UTILITAIRES                                 */
/* ***********************************************************************  */

/* error_handler.c */
void	handle_error(char *message);
int		exit_with_error(char *message, int code);
void	print_usage(void);

/* validation.c */
int		check_arguments(int argc);

#endif