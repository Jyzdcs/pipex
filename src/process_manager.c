/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:40:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/07 17:40:00 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Configure les redirections pour le processus enfant
 * 
 * @param in_fd Descripteur d'entrée
 * @param out_fd Descripteur de sortie
 */
static void	setup_child_redirections(int in_fd, int out_fd)
{
	dup2(in_fd, STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
	close(in_fd);
	close(out_fd);
}

/**
 * @brief Exécute la commande dans le processus enfant
 * 
 * @param cmd Structure contenant la commande à exécuter
 * @param env Variables d'environnement
 */
static void	execute_command(t_cmd *cmd, char *env[])
{
	if (!cmd->cmd_path)
	{
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->cmd_args)
			free_all_ptr((void **)cmd->cmd_args);
		exit_with_error("Error: Command path is NULL", ERR_CMD);
	}
	execve(cmd->cmd_path, cmd->cmd_args, env);
	exit_with_error("Error: execve failed", ERR_EXEC);
}

/**
 * @brief Crée le premier processus pour le pipeline
 * 
 * @param cmd Informations sur la commande à exécuter
 * @param env Variables d'environnement
 * @param pipefd Descripteurs du pipe
 * @param input_fd Descripteur du fichier d'entrée
 * @return pid_t PID du processus créé
 */
pid_t	create_process_1(t_cmd *cmd, char *env[], int pipefd[2], int input_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_with_error("Error: fork failed", ERR_FORK);
	if (pid == 0)
	{
		close(pipefd[0]);
		setup_child_redirections(input_fd, pipefd[1]);
		execute_command(cmd, env);
	}
	close(input_fd);
	return (pid);
}

/**
 * @brief Crée le deuxième processus pour le pipeline
 * 
 * @param cmd Informations sur la commande à exécuter
 * @param env Variables d'environnement
 * @param pipefd Descripteurs du pipe
 * @param output_fd Descripteur du fichier de sortie
 * @return pid_t PID du processus créé
 */
pid_t	create_process_2(t_cmd *cmd, char *env[], int pipefd[2], int output_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_with_error("Error: fork failed", ERR_FORK);
	if (pid == 0)
	{
		close(pipefd[1]);
		setup_child_redirections(pipefd[0], output_fd);
		execute_command(cmd, env);
	}
	close(output_fd);
	return (pid);
}

/**
 * @brief Attend la fin des processus enfants
 * 
 * @param pid1 PID du premier processus
 * @param pid2 PID du deuxième processus
 */
void	wait_for_processes(pid_t pid1, pid_t pid2)
{
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
