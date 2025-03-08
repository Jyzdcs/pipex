/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:21:34 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/06 18:17:07 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Separe les arguments de la commande.*/
char	**format_cmd(char *cmd)
{
	char	**cmd_args;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		handle_error("Error: Failed to format command");
	return (cmd_args);
}

/*Gère l'affichage des erreurs avec perror() et le nettoyage.*/
void	handle_error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}
