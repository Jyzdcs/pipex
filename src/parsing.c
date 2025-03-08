/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:41:11 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/08 01:34:19 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Vérifie que le programme a bien 4 arguments*/
int	check_arguments(int argc)
{
	if (argc != 5)
	{
		handle_error("Error: Nombre d'arguments incorrect");
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
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

/*Cherche le chemin d'une commande à partir du PATH.*/
char	*find_cmd_path(t_pipex pipex, char *env[])
{
	char	*path;
	char	*cmd_path;
	char	*tmp;
	char	**paths;
	int		i;

	path = get_path(env);
	if (!path)
	{
		free(pipex.cmd);
		close(pipex.pipefd[1]);
		close(pipex.pipefd[0]);
		handle_error("Error: PATH does not exist");
		return (NULL);
	}
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(tmp, pipex.cmd);
		if (access(cmd_path, F_OK) == 0)
		{
			free_all_ptr((void **)paths);
			free(tmp);
			return (cmd_path);
		}
		free(tmp);
		free(cmd_path);
		i++;
	}
	free_all_ptr((void **)paths);
	free(pipex.cmd);
	close(pipex.pipefd[1]);
	close(pipex.pipefd[0]);
	handle_error("Error: Command not found");
	return (NULL);
}

/* Extrait le nom de la commande (premier mot avant un espace) */
char	*extract_cmd_name(char *cmd)
{
	int		i;
	char	*cmd_name;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	cmd_name = (char *)malloc(sizeof(char) * (i + 1));
	if (!cmd_name)
		return (NULL);
	ft_strlcpy(cmd_name, cmd, i + 1);
	return (cmd_name);
}
