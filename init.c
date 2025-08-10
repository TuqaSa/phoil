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
static void declar_table(cha ** av , t_table *table)
{
	
}
int init_table(char ** av , t_table * table)
{
	table->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if(!table->forks)
		return (0);
	table->phoils = malloc(sizeof(t_phoil *) * (ft_atoi(av[1]) + 1));
	table->phoils[ft_atoi((av[1]))] = NULL;
	if(!table->phoils)
	{
		free(table->forks);
		return (0);
	}

}