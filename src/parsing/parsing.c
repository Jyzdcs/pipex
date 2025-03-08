/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/08 17:26:49 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Handles the error when command is not found
 *
 * @param pipex Pipex structure with command details
 */
void	handle_cmd_error(t_pipex pipex)
{
	if (pipex.cmd)
		free(pipex.cmd);
	close(pipex.pipefd[1]);
	close(pipex.pipefd[0]);
	handle_error("Error: Command not found");
}

/**
 * @brief Checks if the program has the correct number of arguments
 *
 * @param argc Argument count
 * @return int TRUE if arguments are valid, FALSE otherwise
 */
int	check_arguments(int argc)
{
	if (argc != 5)
	{
		handle_error("Error: Nombre d'arguments incorrect");
		return (FALSE);
	}
	return (TRUE);
}

/**
 * @brief Checks if a file exists and has appropriate permissions
 *
 * @param filename File name to check
 * @param mode 1 for input file (read), 2 for output file (write)
 * @return int TRUE if file is valid, FALSE otherwise
 */
int	check_file(char *filename, int mode)
{
	int	fd;

	if (mode == 1)
	{
		if (access(filename, F_OK) == -1 || access(filename, R_OK) == -1)
		{
			handle_error("Error: infile n'existe pas ou n'est pas acccessible");
			return (FALSE);
		}
	}
	if (mode == 2)
	{
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{
			handle_error("Error: outfile ne peut pas etre creer ou ecrit");
			return (FALSE);
		}
		close(fd);
	}
	return (TRUE);
}
