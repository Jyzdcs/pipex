/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:21:34 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/05 19:56:35 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Vérifie que le programme a bien 4 arguments*/
int check_arguments(int argc)
{
	if (argc != 5)
	{
		handle_error("Error: Nombre d'arguments different de 5");
		return (FALSE);
	}
	return (TRUE);
}

/*Vérifie l'existence d'un fichier et qu'il est accessible en lecture ou écriture.*/
int check_file(char *filename, int mode)
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

/*Cherche le chemin d'une commande à partir du PATH.*/
char *find_command_path(char *cmd, char *env[])
{
	char *test;
	
	test = getenv("PATH");
	if (!test)
	{
		handle_error("Error: PATH does not exist");
		return (NULL);
	}
	printf("%s\n", test);
}

/*Gère l'affichage des erreurs avec perror() et le nettoyage.*/
void handle_error(char *message)
{
	perror(message);
}
