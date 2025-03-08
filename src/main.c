/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:21:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/08 19:31:44 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Cleans up resources for the first command
 *
 * @param pipex Pipex structure with command details
 */
static void	cleanup_first_command(t_pipex *pipex)
{
	free(pipex->cmd);
	free(pipex->cmd_path);
	free_all_ptr((void **)pipex->cmd_args);
	close(pipex->pipefd[1]);
}

/**
 * @brief Cleans up resources for the second command
 *
 * @param pipex Pipex structure with command details
 */
static void	cleanup_second_command(t_pipex *pipex)
{
	free(pipex->cmd);
	free(pipex->cmd_path);
	free_all_ptr((void **)pipex->cmd_args);
	close(pipex->pipefd[0]);
}

/**
 * @brief Sets up the first command
 *
 * @param pipex Pipex structure to hold command details
 * @param argv Command line arguments
 * @param env Environment variables
 * @return int File descriptor for input file
 */
static int	setup_first_command(t_pipex *pipex, char *argv[], char *env[])
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		handle_error("Error: Cannot open input file");
	pipex->cmd_path = NULL;
	if (is_absolute_path(argv[2]))
	{
		if (!process_absolute_path(argv[2], pipex))
			handle_error("Error: Invalid absolute path");
		if (access(pipex->cmd_path, F_OK | X_OK) == -1)
			handle_error("Error: Command not found or not executable");
	}
	else
	{
		pipex->cmd = extract_cmd_name(argv[2]);
		pipex->cmd_path = find_cmd_path(*pipex, env);
		pipex->cmd_args = format_cmd(argv[2]);
	}
	return (fd);
}

/**
 * @brief Sets up the second command
 *
 * @param pipex Pipex structure to hold command details
 * @param argv Command line arguments
 * @param env Environment variables
 * @return int File descriptor for output file
 */
static int	setup_second_command(t_pipex *pipex, char *argv[], char *env[])
{
	int	fd;

	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		handle_error("Error: Cannot open or create output file");
	pipex->cmd_path = NULL;
	if (is_absolute_path(argv[3]))
	{
		if (!process_absolute_path(argv[3], pipex))
			handle_error("Error: Invalid absolute path");
		if (access(pipex->cmd_path, F_OK | X_OK) == -1)
			handle_error("Error: Command not found or not executable");
	}
	else
	{
		pipex->cmd = extract_cmd_name(argv[3]);
		pipex->cmd_path = find_cmd_path(*pipex, env);
		pipex->cmd_args = format_cmd(argv[3]);
	}
	return (fd);
}

/**
 * @brief Main function
 *
 * @param argc Argument count
 * @param argv Arguments
 * @param env Environment variables
 * @return int Exit status
 */
int	main(int argc, char *argv[], char *env[])
{
	pid_t	pid1;
	pid_t	pid2;
	t_pipex	pipex;
	int		fd;

	if (!check_arguments(argc) || !check_file(argv[1], 1)
		|| !check_file(argv[4], 2))
		return (FALSE);
	create_pipe(pipex.pipefd);
	fd = setup_first_command(&pipex, argv, env);
	pid1 = create_process_1(&pipex, env, fd);
	close(fd);
	cleanup_first_command(&pipex);
	fd = setup_second_command(&pipex, argv, env);
	pid2 = create_process_2(&pipex, env, fd);
	close(fd);
	cleanup_second_command(&pipex);
	wait_for_processes(pid1, pid2);
	return (0);
}
