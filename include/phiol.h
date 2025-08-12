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
# define PHIOL_H

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define PURPLE "\033[0;35m"
# define BLUE "\033[0;34m"

# include <limits.h>
# include <pthread.h>
# include <stdatomic.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_phoil	t_phoil;
typedef struct s_waiter	t_waiter;

typedef enum e_state
{
	hungry,
	satiated,
	dead,
}						t_state;

typedef struct s_table
{
	t_phoil				**phoils;
	t_waiter			*waiter;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	struct timeval		start_t;
	long				tsleep;
	long				teat;
	long				tdead;
	long				tthink;
	long				max_meal;
	int					phoil_num;
	_Atomic int			flag;
}						t_table;

typedef struct s_phoil
{
	t_table				*table;
	pthread_t			thread_id;
	_Atomic long		last_teat;
	_Atomic t_state		state;
	int					seat;
	int					first_fork;
	int					second_fork;
	int					eat_conut;
}						t_phoil;

typedef struct s_waiter
{
	int					*fork_set;
	int					print_mutex_indc;
}						t_waiter;

int						init_table(char **av, t_table *table);
int						init_phoil(t_table *table);
t_waiter				*init_waiter(t_table *table);
int						init_thread(t_table *table);
int						serve_dinner(t_table *table);
void					phoil_cleanup(t_phoil *phoil);
int						free_array(void **ptr, int end);
int						cleanup(t_table *table);
void					*phoil_lifecycle(void *arg);
long					get_timestamp_in_ms(void);
long					gettime(struct timeval start);
void					ft_usleep(long time_in_ms, t_table *table);
void					mtx_printf(t_table *table, char *str, t_phoil *phoil,
							char *color);
int						ft_atoi(const char *str);
int						is_numeric(char **av);

#endif
