/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phiol.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed <tsaeed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 19:18:08 by tsaeed            #+#    #+#             */
/*   Updated: 2025/08/10 21:01:25 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phiol.h"

int	is_numeric(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	vaild_values(char **av, int ac)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	set_table(char **av, t_table *table)
{
	if (!init_table(av, table))
		return (0);
	if (!init_phoil(table))
	{
		free(table->forks);
		free(table->phoils);
		return (0);
	}
	gettimeofday(&table->start_t, NULL);
	if (!init_thread(table))
		return (cleanup(table));
	return (1);
}

int	main(int ac, char **av)
{
	t_table	table;

	if ((ac == 5 || ac == 6) && is_numeric(av) && vaild_values(av, ac))
	{
		if (set_table(av, &table))
			serve_dinner(&table);
		cleanup(&table);
		return (0);
	}
	printf("usage: ./philo n_philo t_die t_eat t_sleep [n_min_eat_philo]\n");
	return (1);
}
