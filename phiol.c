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

int set_table(char ** av , t_table * table)
{
	if(!init_table(av, table))
		return (0);
	if(!init_phiols(table))
	{
		free(table->forks);
		free(table->phoils);
		return (0);
	}
	gettimeofday(&table->start_t, NULL);
		if (!init_threads(table))
		return (cleanup(table));
	return (1);
}


int main(int ac , char ** av)
{
	t_table table;

	if((ac == 5 || ac == 6) && is_numeric(av))
	{
		if(set_table)
	}
}
