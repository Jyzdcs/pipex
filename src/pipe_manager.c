/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:45:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/07 17:45:00 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Crée un pipe
 * 
 * @param pipefd Tableau de deux entiers où stocker les descripteurs
 * @return int 0 en cas de succès, -1 sinon
 */
int	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
		return (ERROR);
	return (SUCCESS);
}

/**
 * @brief Ferme les deux extrémités d'un pipe
 * 
 * @param pipefd Tableau contenant les descripteurs à fermer
 */
void	close_pipe(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}
