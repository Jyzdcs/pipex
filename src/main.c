/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:21:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/08 01:41:34 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
- Vérification des arguments dans main() via check_arguments().
- Vérification des fichiers et des commandes avec check_file() et find_command_path().
- Création des pipes dans pipex.c avec create_pipe().
- Fork des processus enfants et redirections via create_process(),
	puis attente des processus avec wait_for_processes().
- Gestion des redirections et fermeture des pipes dans redirections.c.
*/

#include <stdio.h>

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
	pipex.cmd = extract_cmd_name(argv[2]);
	pipex.cmd_path = find_cmd_path(pipex, env);
	pipex.cmd_args = format_cmd(argv[2]);
	fd = open(argv[1], O_RDONLY);
	pid1 = create_process_1(&pipex, env, fd);
	close(fd);
	free(pipex.cmd);
	free(pipex.cmd_path);
	free_all_ptr((void **)pipex.cmd_args);
	close(pipex.pipefd[1]);
	pipex.cmd = extract_cmd_name(argv[3]);
	pipex.cmd_path = find_cmd_path(pipex, env);
	pipex.cmd_args = format_cmd(argv[3]);
	fd = open(argv[4], O_WRONLY | O_CREAT | O_APPEND, 0644);
	pid2 = create_process_2(&pipex, env, fd);
	close(fd);
	free(pipex.cmd);
	free(pipex.cmd_path);
	free_all_ptr((void **)pipex.cmd_args);
	close(pipex.pipefd[0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
