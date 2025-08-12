/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed <tsaeed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:56:22 by tsaeed            #+#    #+#             */
/*   Updated: 2025/08/12 18:56:27 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phiol.h"

void	phoil_cleanup(t_phoil *phoil)
{
	if (phoil)
	{
		if (phoil->thread_id)
			pthread_join(phoil->thread_id, NULL);
		free(phoil);
	}
	phoil = NULL;
}

int	free_array(void **ptr, int end)
{
	int	i;

	if (!ptr)
		return (0);
	i = 0;
	while (i < end)
	{
		if (ptr[i])
			free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
	return (0);
}

int	cleanup(t_table *table)
{
	int	i;

	if (!table)
		return (0);
	i = -1;
	while (++i < table->phoil_num)
		if (table->phoils[i])
			phoil_cleanup(table->phoils[i]);
	i = -1;
	while (++i < table->phoil_num && table->phoil_num != 1)
		if (table->waiter->fork_set[i])
			pthread_mutex_destroy(&table->forks[i]);
	if (table->waiter->print_mutex_indc)
		pthread_mutex_destroy(&table->print_mutex);
	free(table->forks);
	free(table->phoils);
	free(table->waiter->fork_set);
	free(table->waiter);
	return (0);
}
