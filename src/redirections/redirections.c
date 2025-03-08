/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/08 15:52:46 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"

/**
 * @brief Redirects file descriptors using dup2
 *
 * @param old_fd Original file descriptor
 * @param new_fd New file descriptor
 */
void	dup_and_redirect(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		handle_error("Error: Failed to redirect file descriptors");
}

/**
 * @brief Closes both ends of a pipe
 *
 * @param pipefd Array of pipe file descriptors
 */
void	close_pipe(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}
