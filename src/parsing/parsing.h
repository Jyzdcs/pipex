/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/08 19:39:34 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../../include/libft/libft.h"
# include "../cmd/command.h"
# include "../utils/utils.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/**
 * @brief Structure to hold pipeline information
 */
typedef struct s_pipex
{
	char	*cmd;
	char	*cmd_path;
	char	**cmd_args;
	int		pipefd[2];
}			t_pipex;

/**
 * @brief Handles the error when command is not found
 *
 * @param pipex Pipex structure with command details
 */
void		handle_cmd_error(t_pipex pipex);

/**
 * @brief Checks if the program has the correct number of arguments
 *
 * @param argc Argument count
 * @return int TRUE if arguments are valid, FALSE otherwise
 */
int			check_arguments(int argc);

/**
 * @brief Checks if a file exists and has appropriate permissions
 *
 * @param filename File name to check
 * @param mode 1 for input file (read), 2 for output file (write)
 * @return int TRUE if file is valid, FALSE otherwise
 */
int			check_file(char *filename, int mode);

/**
 * @brief Gets the PATH environment variable
 *
 * @param env Environment variables array
 * @return char* PATH string or NULL if not found
 */
char		*get_path(char *env[]);

/**
 * @brief Finds the full path to a command
 *
 * @param pipex Pipex structure with command details
 * @param env Environment variables array
 * @return char* Full path to command or NULL if not found
 */
char		*find_cmd_path(t_pipex pipex, char *env[]);

/**
 * @brief Vérifie si la commande contient un chemin absolu
 *
 * @param cmd Chaîne de caractères contenant la commande
 * @return int TRUE si c'est un chemin absolu, FALSE sinon
 */
int			is_absolute_path(char *cmd);

/**
 * @brief Extrait le chemin et la commande d'un chemin absolu
 *
 * @param abs_path Chaîne contenant le chemin absolu et la commande
 * @param pipex Structure où stocker les infos extraites
 * @return int TRUE si l'extraction a réussi, FALSE sinon
 */
int			process_absolute_path(char *abs_path, t_pipex *pipex);

#endif