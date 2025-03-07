/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:55:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/07 17:55:00 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Redirige un descripteur de fichier vers un autre
 * 
 * Remplace le descripteur new_fd par une copie de old_fd
 * 
 * @param old_fd Descripteur source
 * @param new_fd Descripteur à remplacer
 */
void	dup_and_redirect(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		exit_with_error("Error: dup2 failed", ERR_PIPE);
}
