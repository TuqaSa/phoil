/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed <tsaeed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 21:06:32 by tsaeed            #+#    #+#             */
/*   Updated: 2025/08/10 21:27:38 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phiol.h"

t_waiter	*init_waiter(t_table *table)
{
	t_waiter	*waiter;
	int			i;

	waiter = malloc(sizeof(t_waiter));
	if (!waiter)
		return (NULL);
	waiter->fork_set = malloc(sizeof(int) * table->phoil_num);
	if (!waiter->fork_set)
	{
		free(waiter);
		return (NULL);
	}
	i = 0;
	while (i < table->phoil_num)
		waiter->fork_set[i++] = 0;
	waiter->print_mutex_indc = 1;
	i = 0;
	while (i < table->phoil_num)
	{
		table->forks[i] = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		waiter->fork_set[i] = 1;
		i++;
	}
	return (waiter);
}

static void	declar_table(char **av, t_table *table)
{
	table->print_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	table->max_meal = -1;
	table->flag = 0;
	table->phoil_num = ft_atoi(av[1]);
	table->tdead = ft_atoi(av[2]);
	table->teat = ft_atoi(av[3]);
	table->tsleep = ft_atoi(av[4]);
	if (av[5])
		table->max_meal = ft_atoi(av[5]);
}

int	init_table(char **av, t_table *table)
{
	table->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!table->forks)
		return (0);
	table->phoils = malloc(sizeof(t_phoil *) * (ft_atoi(av[1]) + 1));
	table->phoils[ft_atoi((av[1]))] = NULL;
	if (!table->phoils)
	{
		free(table->forks);
		return (0);
	}
	declar_table(av, table);
	table->waiter = init_waiter(table);
	if (!table->waiter)
	{
		free(table->forks);
		free(table->phoils);
		return (0);
	}
	return (1);
}

int	init_phoil(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->phoil_num)
	{
		table->phoils[i] = malloc(sizeof(t_phoil));
		if (!table->phoils[i])
			return (free_array((void *)table->phoils, i));
		table->phoils[i]->seat = i;
		if (i % 2)
			table->phoils[i]->first_fork = i;
		else
			table->phoils[i]->first_fork = (i + 1) % table->phoil_num;
		if (i % 2)
			table->phoils[i]->second_fork = (i + 1) % table->phoil_num;
		else
			table->phoils[i]->second_fork = i;
		table->phoils[i]->eat_conut = 0;
		table->phoils[i]->state = hungry;
		table->phoils[i]->table = table;
		table->phoils[i]->thread_id = 0;
		table->phoils[i]->last_teat = 0;
	}
	return (1);
}

int	init_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->phoil_num)
	{
		table->phoils[i]->thread_id = (pthread_t) NULL;
		if (pthread_create(&table->phoils[i]->thread_id, NULL,
				(void *)phoil_lifecycle, (void *)table->phoils[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}
