/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/08 15:23:56 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

/**
 * @brief Formats the command into arguments array
 *
 * @param cmd Command string
 * @return char** Array of command arguments
 */
char	**format_cmd(char *cmd)
{
	char	**cmd_args;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		handle_error("Error: Failed to format command");
	return (cmd_args);
}

/**
 * @brief Extracts the command name (first word before a space)
 *
 * @param cmd Command string
 * @return char* Extracted command name
 */
char	*extract_cmd_name(char *cmd)
{
	int i;
	char *cmd_name;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	cmd_name = (char *)malloc(sizeof(char) * (i + 1));
	if (!cmd_name)
		return (NULL);
	ft_strlcpy(cmd_name, cmd, i + 1);
	return (cmd_name);
}