/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:10:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/07 18:10:00 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Vérifie que le programme a bien 4 arguments
 * 
 * @param argc Nombre d'arguments
 * @return int 1 si le nombre d'arguments est correct, 0 sinon
 */
int	check_arguments(int argc)
{
	if (argc != 5)
	{
		print_usage();
		return (FALSE);
	}
	return (TRUE);
}
