/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:50:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/07 17:50:00 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Vérifie l'existence et les droits d'accès d'un fichier
 * 
 * @param filename Nom du fichier à vérifier
 * @param mode 1 pour vérifier un fichier d'entrée, 2 pour un fichier de sortie
 * @return int 1 si le fichier est accessible, 0 sinon
 */
int	check_file(char *filename, int mode)
{
	int	fd;

	if (mode == 1)
	{
		if (access(filename, F_OK) == -1 || access(filename, R_OK) == -1)
		{
			exit_with_error("Error: infile n'existe pas ou inaccessible",
				ERR_FILE);
			return (FALSE);
		}
	}
	if (mode == 2)
	{
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{
			exit_with_error("Error: outfile ne peut pas être créé", ERR_FILE);
			return (FALSE);
		}
		close(fd);
	}
	return (TRUE);
}

/**
 * @brief Ouvre le fichier d'entrée pour lecture
 * 
 * @param filename Nom du fichier à ouvrir
 * @return int Descripteur du fichier ouvert
 */
int	open_infile(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_with_error("Error: Cannot open infile", ERR_FILE);
	return (fd);
}

/**
 * @brief Ouvre le fichier de sortie pour écriture
 * 
 * @param filename Nom du fichier à ouvrir ou créer
 * @return int Descripteur du fichier ouvert
 */
int	open_outfile(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit_with_error("Error: Cannot open outfile", ERR_FILE);
	return (fd);
}
