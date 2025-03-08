/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:22:50 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/08 02:36:25 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Crée un pipe avec pipe().*/
void	create_pipe(int pipefd[2])
{
	pipe(pipefd);
}

/* Fork le premier processus, gère les redirections et appelle execve().*/
pid_t	create_process_1(t_pipex *pipex, char *env[], int input_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		handle_error("Error: fork failed");
	if (pid == 0)
	{
		close(pipex->pipefd[0]);
		dup2(input_fd, STDIN_FILENO);
		dup2(pipex->pipefd[1], STDOUT_FILENO);
		close(pipex->pipefd[1]);
		close(input_fd);
		if (!pipex->cmd_path)
		{
			if (pipex->cmd)
				free(pipex->cmd);
			if (pipex->cmd_args)
				free_all_ptr((void **)pipex->cmd_args);
			handle_error("Error: Command path is NULL");
		}
		execve(pipex->cmd_path, pipex->cmd_args, env);
	}
	return (pid);
}

/*Fork le deuxième processus, gère les redirections et appelle execve().*/
pid_t	create_process_2(t_pipex *pipex, char *env[], int output_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		handle_error("Error: fork failed");
	if (pid == 0)
	{
		close(pipex->pipefd[1]);
		dup2(pipex->pipefd[0], STDIN_FILENO);
		dup2(output_fd, STDOUT_FILENO);
		close(pipex->pipefd[0]);
		close(output_fd);
		close(pipex->pipefd[1]);
		if (!pipex->cmd_path)
		{
			if (pipex->cmd)
				free(pipex->cmd);
			if (pipex->cmd_args)
				free_all_ptr((void **)pipex->cmd_args);
			handle_error("Error: Command path is NULL");
		}
		execve(pipex->cmd_path, pipex->cmd_args, env);
	}
	return (pid);
}

/*Attends la fin des processus enfants et récupère leur statut.*/
void	wait_for_processes(int pid1, int pid2)
{
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
