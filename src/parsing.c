/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:41:11 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/06 16:41:49 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Vérifie que le programme a bien 4 arguments*/
int	check_arguments(int argc)
{
	if (argc != 5)
	{
		handle_error("Error: Nombre d'arguments different de 5");
		return (FALSE);
	}
	return (TRUE);
}

/*Vérifie l'existence d'un fichier et qu'il est accessible en lecture ou écriture.*/
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

/*Récupère le PATH dans l'environnement.*/
char	*get_path(char *env[])
{
	char	*path;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	handle_error("Error: PATH does not exist");
	return (NULL);
}

/*Cherche le chemin d'une commande à partir du PATH.*/
char	*find_command_path(char *cmd, char *env[])
{
	char	*path;
	char	*cmd_path;
	char	**paths;
	int		i;

	path = get_path(env);
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(cmd_path, cmd);
		if (access(cmd_path, F_OK) == 0)
		{
			free_all_ptr((void **)paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_all_ptr((void **)paths);
	handle_error("Error: Command not found");
	return (NULL);
}
