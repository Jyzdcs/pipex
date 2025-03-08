/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/08 15:26:50 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Gets the PATH environment variable
 *
 * @param env Environment variables array
 * @return char* PATH string or NULL if not found
 */
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

/**
 * @brief Tries to find a command path in all possible directories
 *
 * @param paths Array of path directories
 * @param cmd Command name
 * @return char* Command path if found, NULL otherwise
 */
static char	*try_paths(char **paths, char *cmd)
{
	char	*tmp;
	char	*cmd_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
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
	return (NULL);
}

/**
 * @brief Finds the full path to a command
 *
 * @param pipex Pipex structure with command details
 * @param env Environment variables array
 * @return char* Full path to command or NULL if not found
 */
char	*find_cmd_path(t_pipex pipex, char *env[])
{
	char	*path;
	char	*cmd_path;
	char	**paths;

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
	cmd_path = try_paths(paths, pipex.cmd);
	if (!cmd_path)
	{
		free_all_ptr((void **)paths);
		free(pipex.cmd);
		close(pipex.pipefd[1]);
		close(pipex.pipefd[0]);
		handle_error("Error: Command not found");
		return (NULL);
	}
	return (cmd_path);
}
