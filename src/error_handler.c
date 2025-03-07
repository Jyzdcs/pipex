/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/07 18:00:00 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Affiche un message d'erreur et termine le programme
 * 
 * Utilise perror pour afficher le message d'erreur avec le message système
 * correspondant, puis termine le programme avec un code d'erreur.
 * 
 * @param message Message d'erreur à afficher
 */
void	handle_error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

/**
 * @brief Affiche un message d'erreur et termine le programme avec un code
 * 
 * @param message Message d'erreur à afficher
 * @param code Code d'erreur à retourner
 * @return int Ne retourne jamais (le programme se termine)
 */
int	exit_with_error(char *message, int code)
{
	perror(message);
	exit(code);
	return (code);
}

/**
 * @brief Affiche l'utilisation correcte du programme
 */
void	print_usage(void)
{
	ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
	exit(ERR_ARGS);
}
