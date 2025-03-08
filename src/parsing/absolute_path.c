/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/08 19:40:40 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Vérifie si la commande contient un chemin absolu
 *
 * @param cmd Chaîne de caractères contenant la commande
 * @return int TRUE si c'est un chemin absolu, FALSE sinon
 */
int	is_absolute_path(char *cmd)
{
	int	i;

	if (!cmd)
		return (FALSE);
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

/**
 * @brief Configure la commande et les arguments dans la structure pipex
 *
 * @param pipex Structure pipex à configurer
 * @param path Chemin de la commande
 * @param full_cmd Commande complète avec arguments
 * @return int TRUE si réussi, FALSE sinon
 */
static int	setup_cmd_and_args(t_pipex *pipex, char *path, char *full_cmd)
{
	if (!path || !pipex)
		return (FALSE);
	pipex->cmd_path = ft_strdup(path);
	if (!pipex->cmd_path)
		return (FALSE);
	pipex->cmd = extract_cmd_name(path);
	if (!pipex->cmd)
	{
		free(pipex->cmd_path);
		return (FALSE);
	}
	if (full_cmd)
		pipex->cmd_args = format_cmd(full_cmd);
	else
		pipex->cmd_args = format_cmd(path);
	if (!pipex->cmd_args)
	{
		free(pipex->cmd_path);
		free(pipex->cmd);
		return (FALSE);
	}
	return (TRUE);
}

/**
 * @brief Extrait le chemin et la commande d'un chemin absolu avec arguments
 *
 * @param abs_path Chaîne contenant le chemin absolu et la commande
 * @param pipex Structure où stocker les infos extraites
 * @return int TRUE si l'extraction a réussi, FALSE sinon
 */
static int	extract_path_and_cmd(char *abs_path, t_pipex *pipex)
{
	char	**parts;
	int		i;
	int		result;

	if (!abs_path || !pipex)
		return (FALSE);
	parts = ft_split(abs_path, ' ');
	if (!parts)
		return (FALSE);
	i = 0;
	while (parts[i])
		i++;
	if (i < 1)
	{
		free_all_ptr((void **)parts);
		return (FALSE);
	}
	result = setup_cmd_and_args(pipex, parts[0], abs_path);
	free_all_ptr((void **)parts);
	return (result);
}

/**
 * @brief Traite le chemin absolu pour extraire commande et arguments
 *
 * @param abs_path Chaîne contenant le chemin absolu et la commande
 * @param pipex Structure où stocker les infos extraites
 * @return int TRUE si l'extraction a réussi, FALSE sinon
 */
int	process_absolute_path(char *abs_path, t_pipex *pipex)
{
	if (!abs_path || !pipex)
		return (FALSE);
	return (extract_path_and_cmd(abs_path, pipex));
}
