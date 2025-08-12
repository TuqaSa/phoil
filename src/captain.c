/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   captain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed <tsaeed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:55:42 by tsaeed            #+#    #+#             */
/*   Updated: 2025/08/12 18:56:44 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phiol.h"

static int	starved(t_phoil *phoil)
{
	int	curr_time;
	int	died;

	curr_time = gettime(phoil->table->start_t);
	died = (curr_time - phoil->last_teat) >= phoil->table->tdead;
	return (died);
}

static int	satisfied(t_table *table)
{
	int	fulfilled;
	int	i;

	i = 0;
	fulfilled = 0;
	while (i < table->phoil_num)
	{
		if (table->phoils[i]->state == satiated)
			fulfilled++;
		i++;
	}
	return (fulfilled == table->phoil_num && table->max_meal != -1);
}

int	serve_dinner(t_table *table)
{
	int	i;

	table->flag = 1;
	while (table->flag)
	{
		i = 0;
		while (i < table->phoil_num)
		{
			if (starved(table->phoils[i]))
			{
				mtx_printf(table, "is dead", table->phoils[i], RED);
				return (table->flag = 0);
			}
			i++;
		}
		if (satisfied(table))
			return (table->flag = 0);
		usleep(1000);
	}
	return (0);
}
