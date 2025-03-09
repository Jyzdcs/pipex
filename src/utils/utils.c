/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/09 23:54:25 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../../include/libft/libft.h"
#include "../parsing/parsing.h"

/**
 * @brief Handles error messages and exits the program
 *
 * @param message Error message to display
 */
void	handle_error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

/**
 * @brief Cleans up command resources (generic function)
 *
 * @param pipex Pipex structure with command details
 */
void	cleanup_command(t_pipex *pipex)
{
	if (pipex->cmd)
		free(pipex->cmd);
	if (pipex->cmd_path)
		free(pipex->cmd_path);
	if (pipex->cmd_args)
		free_all_ptr((void **)pipex->cmd_args);
}
