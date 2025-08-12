/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phiol_lifecycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed <tsaeed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:55:59 by tsaeed            #+#    #+#             */
/*   Updated: 2025/08/12 18:56:58 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phiol.h"

static int	pick_up_forks(t_phoil *phoil)
{
	pthread_mutex_lock(&phoil->table->forks[phoil->first_fork]);
	mtx_printf(phoil->table, "has taken a fork", phoil, GREEN);
	if (!phoil->table->flag || phoil->table->phoil_num == 1)
	{
		pthread_mutex_unlock(&phoil->table->forks[phoil->first_fork]);
		return (0);
	}
	pthread_mutex_lock(&phoil->table->forks[phoil->second_fork]);
	mtx_printf(phoil->table, "has taken a fork", phoil, GREEN);
	if (phoil->table->flag)
	{
		mtx_printf(phoil->table, "is eating", phoil, BLUE);
		phoil->last_teat = gettime(phoil->table->start_t);
		ft_usleep(phoil->table->teat, phoil->table);
	}
	pthread_mutex_unlock(&phoil->table->forks[phoil->first_fork]);
	pthread_mutex_unlock(&phoil->table->forks[phoil->second_fork]);
	phoil->eat_conut++;
	if (phoil->eat_conut >= phoil->table->max_meal)
		phoil->state = satiated;
	return (1);
}

void	*phoil_lifecycle(void *arg)
{
	t_phoil	*phoil;

	phoil = (t_phoil *)arg;
	phoil->state = hungry;
	while (!phoil->table->flag)
		usleep(50);
	if (phoil->seat % 2)
		ft_usleep(5, phoil->table);
	phoil->last_teat = gettime(phoil->table->start_t);
	while (phoil->table->flag)
	{
		if (phoil->table->flag)
			if (!pick_up_forks(phoil))
				return (NULL);
		if (phoil->table->flag)
		{
			mtx_printf(phoil->table, "is sleeping", phoil, YELLOW);
			ft_usleep(phoil->table->tsleep, phoil->table);
		}
		mtx_printf(phoil->table, "is thinking", phoil, PURPLE);
		usleep(500);
	}
	return (NULL);
}
