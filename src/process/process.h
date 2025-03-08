/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:00:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/08 15:21:19 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../utils/utils.h"
# include "../redirections/redirections.h"
# include "../pipex.h"

/**
 * @brief Creates a pipe for inter-process communication
 * 
 * @param pipefd Array to store pipe file descriptors
 */
void	create_pipe(int pipefd[2]);

/**
 * @brief Creates the first child process to execute a command
 * 
 * @param pipex Structure with command details
 * @param env Environment variables array
 * @param input_fd Input file descriptor
 * @return pid_t Process ID of the created child
 */
pid_t	create_process_1(t_pipex *pipex, char *env[], int input_fd);

/**
 * @brief Creates the second child process to execute a command
 * 
 * @param pipex Structure with command details
 * @param env Environment variables array
 * @param output_fd Output file descriptor
 * @return pid_t Process ID of the created child
 */
pid_t	create_process_2(t_pipex *pipex, char *env[], int output_fd);

/**
 * @brief Waits for child processes to complete
 * 
 * @param pid1 Process ID of the first child
 * @param pid2 Process ID of the second child
 */
void	wait_for_processes(int pid1, int pid2);

#endif 