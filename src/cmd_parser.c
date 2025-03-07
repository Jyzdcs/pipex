/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:30:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/07 17:30:00 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Extrait le nom de la commande (premier mot avant un espace)
 * 
 * @param cmd Chaîne de caractères contenant la commande
 * @return char* Nom de la commande ou NULL en cas d'erreur
 */
char	*extract_cmd_name(char *cmd)
{
	int		i;
	char	*cmd_name;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	cmd_name = (char *)malloc(sizeof(char) * (i + 1));
	if (!cmd_name)
		return (NULL);
	ft_strlcpy(cmd_name, cmd, i + 1);
	return (cmd_name);
}

/**
 * @brief Découpe la commande et ses arguments en tableau de chaînes
 * 
 * @param cmd Chaîne de caractères contenant la commande et ses arguments
 * @return char** Tableau de chaînes terminé par NULL ou NULL en cas d'erreur
 */
char	**format_cmd(char *cmd)
{
	char	**cmd_args;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		exit_with_error("Error: Failed to format command", ERR_MEM);
	return (cmd_args);
}

/**
 * @brief Initialise une structure de commande
 * 
 * @param cmd Structure à initialiser
 * @param cmd_str Chaîne de caractères contenant la commande
 * @param env Variables d'environnement
 * @return int 1 si succès, 0 si échec
 */
int	init_cmd(t_cmd *cmd, char *cmd_str, char **env)
{
	cmd->cmd = extract_cmd_name(cmd_str);
	if (!cmd->cmd)
		return (FALSE);
	cmd->cmd_path = find_cmd_path(cmd->cmd, env);
	if (!cmd->cmd_path)
	{
		free(cmd->cmd);
		return (FALSE);
	}
	cmd->cmd_args = format_cmd(cmd_str);
	return (TRUE);
}

/**
 * @brief Libère les ressources allouées pour une commande
 * 
 * @param cmd Structure de commande à nettoyer
 */
void	free_cmd(t_cmd *cmd)
{
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->cmd_path)
		free(cmd->cmd_path);
	if (cmd->cmd_args)
		free_all_ptr((void **)cmd->cmd_args);
}
