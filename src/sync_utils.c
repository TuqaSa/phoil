/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed <tsaeed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:56:10 by tsaeed            #+#    #+#             */
/*   Updated: 2025/08/12 18:57:02 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phiol.h"

long	get_timestamp_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	gettime(struct timeval start)
{
	return ((int)(get_timestamp_in_ms() - ((start.tv_sec * 1000)
			+ (start.tv_usec / 1000))));
}

void	ft_usleep(long time_in_ms, t_table *table)
{
	struct timeval	start;
	long			current_time;

	gettimeofday(&start, NULL);
	current_time = gettime(start);
	while (current_time < time_in_ms && table->flag)
	{
		usleep(100);
		current_time = gettime(start);
	}
}

void	mtx_printf(t_table *table, char *str, t_phoil *phoil, char *color)
{
	long	timestamp;

	timestamp = gettime(table->start_t);
	pthread_mutex_lock(&table->print_mutex);
	if (!table->flag)
	{
		pthread_mutex_unlock(&table->print_mutex);
		return ;
	}
	if (color[5] == '1')
		printf(RED "%ld %d %s\n", timestamp, phoil->seat + 1, str);
	else if (color[5] == '2')
		printf(GREEN "%ld %d %s\n", timestamp, phoil->seat + 1, str);
	else if (color[5] == '3')
		printf(BLUE "%ld %d %s\n", timestamp, phoil->seat + 1, str);
	else if (color[5] == '4')
		printf(YELLOW "%ld %d %s\n", timestamp, phoil->seat + 1, str);
	else if (color[5] == '5')
		printf(PURPLE "%ld %d %s\n", timestamp, phoil->seat + 1, str);
	pthread_mutex_unlock(&table->print_mutex);
}
