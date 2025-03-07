/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:21:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/07 18:01:48 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Initialise la structure pipex avec les arguments du programme
 * 
 * Vérifie les arguments et initialise les commandes.
 * 
 * @param pipex Structure principale à initialiser
 * @param argc Nombre d'arguments
 * @param argv Tableau des arguments
 * @param env Variables d'environnement
 * @return int 1 si succès, 0 si échec
 */
int	init_pipex(t_pipex *pipex, int argc, char *argv[], char *env[])
{
	if (!check_arguments(argc))
		return (FALSE);
	pipex->infile = argv[1];
	pipex->outfile = argv[4];
	pipex->env = env;
	if (!check_file(pipex->infile, 1) || !check_file(pipex->outfile, 2))
		return (FALSE);
	if (!init_cmd(&pipex->cmd1, argv[2], env))
		return (FALSE);
	if (!init_cmd(&pipex->cmd2, argv[3], env))
	{
		free_cmd(&pipex->cmd1);
		return (FALSE);
	}
	return (TRUE);
}

/**
 * @brief Exécute le pipeline
 * 
 * Crée le pipe, lance les processus enfants et attend leur terminaison.
 * 
 * @param pipex Structure contenant toutes les données nécessaires
 */
void	exec_pipex(t_pipex *pipex)
{
	pid_t	pid1;
	pid_t	pid2;
	int		input_fd;
	int		output_fd;

	if (create_pipe(pipex->pipefd) == ERROR)
		exit_with_error("Error: pipe creation failed", ERR_PIPE);
	input_fd = open_infile(pipex->infile);
	pid1 = create_process_1(&pipex->cmd1, pipex->env, pipex->pipefd, input_fd);
	close(pipex->pipefd[1]);
	output_fd = open_outfile(pipex->outfile);
	pid2 = create_process_2(&pipex->cmd2, pipex->env, pipex->pipefd, output_fd);
	close(pipex->pipefd[0]);
	wait_for_processes(pid1, pid2);
}

/**
 * @brief Libère les ressources allouées dans la structure pipex
 * 
 * @param pipex Structure à nettoyer
 */
void	cleanup_pipex(t_pipex *pipex)
{
	free_cmd(&pipex->cmd1);
	free_cmd(&pipex->cmd2);
}

/**
 * @brief Fonction principale du programme
 * 
 * @param argc Nombre d'arguments
 * @param argv Tableau des arguments
 * @param env Variables d'environnement
 * @return int Code de retour du programme
 */
int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;

	if (!init_pipex(&pipex, argc, argv, env))
		return (EXIT_FAILURE);
	exec_pipex(&pipex);
	cleanup_pipex(&pipex);
	return (EXIT_SUCCESS);
}
