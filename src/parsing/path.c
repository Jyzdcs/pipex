/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/08 15:52:28 by kclaudan         ###   ########.fr       */
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
 * @brief Handles the error when PATH is not found
 *
 * @param pipex Pipex structure with command details
 */
static void	handle_path_error(t_pipex pipex)
{
	if (pipex.cmd)
		free(pipex.cmd);
	close(pipex.pipefd[1]);
	close(pipex.pipefd[0]);
	handle_error("Error: PATH does not exist");
}

/**
 * @brief Handles the error when command is not found
 *
 * @param pipex Pipex structure with command details
 */
static void	handle_cmd_error(t_pipex pipex)
{
	if (pipex.cmd)
		free(pipex.cmd);
	close(pipex.pipefd[1]);
	close(pipex.pipefd[0]);
	handle_error("Error: Command not found");
}

/**
 * @brief Creates and checks a command path
 *
 * @param dir Directory to check
 * @param cmd Command name
 * @return char* Valid command path or NULL
 */
static char	*create_and_check_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*cmd_path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	cmd_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!cmd_path)
		return (NULL);
	if (access(cmd_path, F_OK | X_OK) == 0)
		return (cmd_path);
	free(cmd_path);
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
	char	*cmd_path;
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	if (!paths || !cmd)
		return (NULL);
	while (paths[i])
	{
		cmd_path = create_and_check_path(paths[i], cmd);
		if (cmd_path)
		{
			result = cmd_path;
			break ;
		}
		i++;
	}
	free_all_ptr((void **)paths);
	return (result);
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

	if (!env)
		return (NULL);
	path = get_path(env);
	if (!path)
	{
		handle_path_error(pipex);
		return (NULL);
	}
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	cmd_path = try_paths(paths, pipex.cmd);
	if (!cmd_path)
	{
		handle_cmd_error(pipex);
		return (NULL);
	}
	return (cmd_path);
}
