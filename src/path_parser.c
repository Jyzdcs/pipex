/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:35:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/07 17:35:00 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Récupère la variable PATH dans l'environnement
 * 
 * @param env Tableau des variables d'environnement
 * @return char* Pointeur vers la valeur de PATH ou NULL si non trouvé
 */
char	*get_path(char *env[])
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

/**
 * @brief Vérifie si une commande existe à un chemin donné
 * 
 * @param path_dir Répertoire du PATH à tester
 * @param cmd Nom de la commande
 * @return char* Chemin complet de la commande si trouvée, NULL sinon
 */
static char	*check_cmd_in_path(char *path_dir, char *cmd)
{
	char	*tmp;
	char	*cmd_path;

	tmp = ft_strjoin(path_dir, "/");
	if (!tmp)
		return (NULL);
	cmd_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!cmd_path)
		return (NULL);
	if (access(cmd_path, F_OK) == 0)
		return (cmd_path);
	free(cmd_path);
	return (NULL);
}

/**
 * @brief Cherche le chemin d'une commande dans les répertoires du PATH
 * 
 * @param cmd Nom de la commande
 * @param env Variables d'environnement
 * @return char* Chemin complet de la commande si trouvée, NULL sinon
 */
char	*find_cmd_path(char *cmd, char *env[])
{
	char	*path;
	char	*cmd_path;
	char	**paths;
	int		i;

	path = get_path(env);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		cmd_path = check_cmd_in_path(paths[i], cmd);
		if (cmd_path)
		{
			free_all_ptr((void **)paths);
			return (cmd_path);
		}
		i++;
	}
	free_all_ptr((void **)paths);
	return (NULL);
}
