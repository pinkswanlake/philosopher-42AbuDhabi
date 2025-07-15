/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmafrid <asmafrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:26:45 by asmafrid          #+#    #+#             */
/*   Updated: 2025/02/04 16:26:46 by asmafrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_philo_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_locker[philo->r_fork]);
	pthread_mutex_lock(&philo->data->fork_locker[philo->l_fork]);
	while (philo->data->fork[philo->l_fork] == -1
		|| philo->data->fork[philo->r_fork] == -1
		|| philo->data->fork[philo->r_fork] == philo->id
		|| philo->data->fork[philo->l_fork] == philo->id)
	{
		pthread_mutex_unlock(&philo->data->fork_locker[philo->r_fork]);
		pthread_mutex_unlock(&philo->data->fork_locker[philo->l_fork]);
		usleep(100);
		pthread_mutex_lock(&philo->data->fork_locker[philo->r_fork]);
		pthread_mutex_lock(&philo->data->fork_locker[philo->l_fork]);
	}
	philo->data->fork[philo->l_fork] = -1;
	philo->data->fork[philo->r_fork] = -1;
	pthread_mutex_unlock(&philo->data->fork_locker[philo->r_fork]);
	pthread_mutex_unlock(&philo->data->fork_locker[philo->l_fork]);
	printing(philo, "\e[0;32mhas taken a fork\033[0m", time_calc(philo), 0);
	printing(philo, "\e[0;32mhas taken a fork\033[0m", time_calc(philo), 0);
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		usleep(1500);
		pthread_mutex_lock(&philo->data->fork_locker[philo->l_fork]);
		pthread_mutex_lock(&philo->data->fork_locker[philo->r_fork]);
		while (philo->data->fork[philo->l_fork] == -1
			|| philo->data->fork[philo->r_fork] == -1
			|| philo->data->fork[philo->r_fork] == philo->id
			|| philo->data->fork[philo->l_fork] == philo->id)
		{
			pthread_mutex_unlock(&philo->data->fork_locker[philo->l_fork]);
			pthread_mutex_unlock(&philo->data->fork_locker[philo->r_fork]);
			usleep(100);
			pthread_mutex_lock(&philo->data->fork_locker[philo->l_fork]);
			pthread_mutex_lock(&philo->data->fork_locker[philo->r_fork]);
		}
		philo->data->fork[philo->l_fork] = -1;
		philo->data->fork[philo->r_fork] = -1;
		pthread_mutex_unlock(&philo->data->fork_locker[philo->l_fork]);
		pthread_mutex_unlock(&philo->data->fork_locker[philo->r_fork]);
		printing(philo, "\e[0;32mhas taken a fork\033[0m", time_calc(philo), 0);
		printing(philo, "\e[0;32mhas taken a fork\033[0m", time_calc(philo), 0);
	}
	else
		take_philo_even(philo);
}

void	spend_time(t_philo *philo, long long time)
{
	long long	curr_t;

	curr_t = get_time();
	pthread_mutex_lock(&philo->data->ending);
	if (philo->data->finish != 0)
	{
		pthread_mutex_unlock(&philo->data->ending);
		return ;
	}
	pthread_mutex_unlock(&philo->data->ending);
	while ((get_time() - curr_t) < time)
		usleep(100);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->ending);
	if (philo->data->finish == 0)
	{
		pthread_mutex_unlock(&philo->data->ending);
		take_fork(philo);
		printing(philo, "\e[0;33mis eating\033[0m", time_calc(philo), 0);
		pthread_mutex_lock(&philo->data->last_meal_locker);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->data->last_meal_locker);
		pthread_mutex_lock(&philo->data->meals_no_locker);
		philo->data->meal_count++;
		pthread_mutex_unlock(&philo->data->meals_no_locker);
		spend_time(philo, philo->data->eat_t);
		pthread_mutex_lock(&philo->data->fork_locker[philo->l_fork]);
		philo->data->fork[philo->l_fork] = philo->id;
		pthread_mutex_unlock(&philo->data->fork_locker[philo->l_fork]);
		pthread_mutex_lock(&philo->data->fork_locker[philo->r_fork]);
		philo->data->fork[philo->r_fork] = philo->id;
		pthread_mutex_unlock(&philo->data->fork_locker[philo->r_fork]);
		return ;
	}
	pthread_mutex_unlock(&philo->data->ending);
}
