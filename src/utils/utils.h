/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/09 23:57:43 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define TRUE 1
# define FALSE 0

/* Forward declaration pour éviter l'inclusion circulaire */
typedef struct s_pipex	t_pipex;

/**
 * @brief Handles error messages and exits the program
 *
 * @param message Error message to display
 */
void	handle_error(char *message);

/**
 * @brief Cleans up command resources (generic function)
 *
 * @param pipex Pipex structure with command details
 */
void	cleanup_command(t_pipex *pipex);

#endif