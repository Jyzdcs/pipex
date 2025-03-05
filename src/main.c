/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:21:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/03/05 16:25:15 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
- Vérification des arguments dans main() via check_arguments().
- Vérification des fichiers et des commandes avec check_file() et find_command_path().
- Création des pipes dans pipex.c avec create_pipe().
- Fork des processus enfants et redirections via create_process(), puis attente des processus avec wait_for_processes().
- Gestion des redirections et fermeture des pipes dans redirections.c.
*/

int main(int argc, char *argv[], char *env[])
{

}