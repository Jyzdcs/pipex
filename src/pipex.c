/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:22:50 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/06 18:42:46 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Crée un pipe avec pipe().*/
void	create_pipe(int pipefd[2])
{
	pipe(pipefd);
}

/*Fork un processus, gère les redirections et appelle execve().*/
void	create_process(t_cmd *cmd, char *env[], int pipefd[2], int input_fd,
		int output_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		handle_error("Error: fork failed");
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(input_fd, STDIN_FILENO);
		dup2(output_fd, STDOUT_FILENO);
		close(input_fd);
		close(output_fd);
		execve(cmd->cmd_path, cmd->cmd_args, env);
		handle_error("Error: execve failed");
	}
	else
	{
		close(pipefd[1]);
		wait(NULL);
	}
}

/*Attends la fin des processus enfants et récupère leur statut.*/
void	wait_for_processes(int pid1, int pid2)
{
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
