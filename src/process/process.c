/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/08 15:30:29 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

/**
 * @brief Creates a pipe for inter-process communication
 *
 * @param pipefd Array to store pipe file descriptors
 */
void	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
		handle_error("Error: Failed to create pipe");
}

/**
 * @brief Executes a command with error handling
 *
 * @param pipex Structure with command details
 * @param env Environment variables array
 */
static void	execute_command(t_pipex *pipex, char *env[])
{
	if (!pipex->cmd_path)
	{
		if (pipex->cmd)
			free(pipex->cmd);
		if (pipex->cmd_args)
			free_all_ptr((void **)pipex->cmd_args);
		handle_error("Error: Command path is NULL");
	}
	execve(pipex->cmd_path, pipex->cmd_args, env);
	handle_error("Error: Failed to execute command");
}

/**
 * @brief Creates the first child process to execute a command
 *
 * @param pipex Structure with command details
 * @param env Environment variables array
 * @param input_fd Input file descriptor
 * @return pid_t Process ID of the created child
 */
pid_t	create_process_1(t_pipex *pipex, char *env[], int input_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		handle_error("Error: fork failed");
	if (pid == 0)
	{
		dup2(input_fd, STDIN_FILENO);
		dup2(pipex->pipefd[1], STDOUT_FILENO);
		close(pipex->pipefd[0]);
		close(input_fd);
		close(pipex->pipefd[1]);
		execute_command(pipex, env);
	}
	return (pid);
}

/**
 * @brief Creates the second child process to execute a command
 *
 * @param pipex Structure with command details
 * @param env Environment variables array
 * @param output_fd Output file descriptor
 * @return pid_t Process ID of the created child
 */
pid_t	create_process_2(t_pipex *pipex, char *env[], int output_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		handle_error("Error: fork failed");
	if (pid == 0)
	{
		dup2(pipex->pipefd[0], STDIN_FILENO);
		dup2(output_fd, STDOUT_FILENO);
		close(pipex->pipefd[0]);
		close(pipex->pipefd[1]);
		close(output_fd);
		execute_command(pipex, env);
	}
	return (pid);
}

/**
 * @brief Waits for child processes to complete
 *
 * @param pid1 Process ID of the first child
 * @param pid2 Process ID of the second child
 */
void	wait_for_processes(int pid1, int pid2)
{
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}