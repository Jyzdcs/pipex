/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/08 15:21:47 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "../utils/utils.h"

/**
 * @brief Redirects file descriptors using dup2
 * 
 * @param old_fd Original file descriptor
 * @param new_fd New file descriptor
 */
void	dup_and_redirect(int old_fd, int new_fd);

/**
 * @brief Closes both ends of a pipe
 * 
 * @param pipefd Array of pipe file descriptors
 */
void	close_pipe(int pipefd[2]);

#endif 