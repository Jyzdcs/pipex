/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 00:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/10 00:00:00 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../utils/utils.h"
#include <fcntl.h>

/**
 * @brief Initialise les champs de la structure pipex
 *
 * @param pipex Structure à initialiser
 */
void	init_pipex_fields(t_pipex *pipex)
{
	pipex->cmd = NULL;
	pipex->cmd_path = NULL;
	pipex->cmd_args = NULL;
}

/**
 * @brief Configure la commande avec un chemin absolu
 *
 * @param pipex Structure pipex
 * @param cmd_path Chemin de la commande
 * @return int Statut de succès (1) ou d'échec (0)
 */
int	setup_absolute_cmd(t_pipex *pipex, char *cmd_path)
{
	if (!process_absolute_path(cmd_path, pipex))
	{
		cleanup_command(pipex);
		handle_error("Error: Invalid absolute path");
	}
	if (access(pipex->cmd_path, F_OK | X_OK) == -1)
	{
		close(pipex->pipefd[1]);
		cleanup_command(pipex);
		handle_error("Error: Command not found or not executable");
	}
	return (1);
}

/**
 * @brief Configure la commande avec un chemin relatif
 *
 * @param pipex Structure pipex
 * @param cmd_str Chaîne de commande
 * @param env Variables d'environnement
 */
void	setup_relative_cmd(t_pipex *pipex, char *cmd_str, char *env[])
{
	pipex->cmd = extract_cmd_name(cmd_str);
	pipex->cmd_path = find_cmd_path(*pipex, env);
	pipex->cmd_args = format_cmd(cmd_str);
}

/**
 * @brief Ouvre un fichier d'entrée pour la redirection
 *
 * @param filename Nom du fichier à ouvrir
 * @return int Descripteur de fichier ou erreur
 */
int	open_input_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		handle_error("Error: Cannot open input file");
	return (fd);
}

/**
 * @brief Ouvre un fichier de sortie pour la redirection
 *
 * @param filename Nom du fichier à ouvrir/créer
 * @return int Descripteur de fichier ou erreur
 */
int	open_output_file(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		handle_error("Error: Cannot open or create output file");
	return (fd);
}
