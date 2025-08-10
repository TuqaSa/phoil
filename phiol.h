/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phiol.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed <tsaeed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:13:02 by tsaeed            #+#    #+#             */
/*   Updated: 2025/08/10 20:52:09 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHIOL_H
#define PHIOL_H

# include <pthread.h>
# include <stdatomic.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
//t_sleep = 5000 == usleep(5000)[___________=50000] --> t_sleep = 5000 == my_usleep(5000) --> usleep(50) x 100[_x__x_x__x__x_x_]
//
typedef struct s_phoil t_phoil;

struct s_times;

//t_phoil->s_table->t_die
typedef struct s_table
{
	t_phoil	**phoils;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	struct timeval			start_t;
	long	tsleep;
	long	teat;
	long	tdead;
	long	tthink;
	long	max_meal;
	_Atomic int 	flag;// make this _Atomic later
}	t_table;
//pthread_mutex_lock(philo[1]->table->forks[left_fork]); this is how a phoil picks up a fork
//left_fork = 0,r_f = 1
//r_f = 1, l_f =2 .... *make this depend on even and odd, add slight delay fro even philos when first starting routine
t_phoil
{
//while (Flag)// read after write
};


t_table x;
#endif