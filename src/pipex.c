/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:22:50 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/05 16:38:12 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Crée un pipe avec pipe().*/
void create_pipe(int pipefd[2])
{

}

/*Fork un processus, gère les redirections et appelle execve().*/
void create_process(char *cmd_path, char **cmd_args, int pipefd[2], int input_fd, int output_fd)
{

}

/*Attends la fin des processus enfants et récupère leur statut.*/
void wait_for_processes(int pid1, int pid2)
{
	
}
