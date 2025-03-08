/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/08 15:20:12 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "../utils/utils.h"
# include "../../include/libft/libft.h"

/**
 * @brief Extracts the command name (first word before a space)
 * 
 * @param cmd Command string
 * @return char* Extracted command name
 */
char	*extract_cmd_name(char *cmd);

/**
 * @brief Formats the command into arguments array
 * 
 * @param cmd Command string
 * @return char** Array of command arguments
 */
char	**format_cmd(char *cmd);

#endif 