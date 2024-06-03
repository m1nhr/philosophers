/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:21:19 by rmarecar          #+#    #+#             */
/*   Updated: 2023/05/05 14:39:35 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_finish_sim(t_philo *philo, int ok)
{
	pthread_mutex_lock(&philo->rules->finish);
	if (ok)
	{
		philo->rules->died = 1;
		pthread_mutex_unlock(&philo->rules->finish);
		return (1);
	}
	if (philo->rules->died)
	{
		pthread_mutex_unlock(&philo->rules->finish);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->finish);
	return (0);
}

void	philo_kill(t_rules *rules, t_philo *philo, int i)
{
	if (i != -120)
		print_action("died", &philo[i], 1);
	check_finish_sim(philo, 1);
	pthread_mutex_unlock(&rules->meal);
}

int	philo_check_death(t_rules *rules, t_philo *philo, int *j)
{
	int	i;

	i = -1;
	while (++i < rules->nb_philo && !check_finish_sim(philo, 0))
	{
		pthread_mutex_lock(&rules->meal);
		if ((int)(get_time() - philo[i].t_last_meal) > rules->time_to_die)
		{
			philo_kill(rules, philo, i);
			return (1);
		}
		else if (rules->eat_count_max
			&& philo[i].ate_count >= rules->eat_count_max)
		{
			*j += 1;
			if (*j == rules->nb_philo)
				philo_kill(rules, philo, -120);
			if (*j == rules->nb_philo)
				return (1);
		}
		if (philo[i].ate_count >= rules->eat_count_max)
				philo[i].ate_count = -10000;
		pthread_mutex_unlock(&rules->meal);
	}
	return (0);
}

void	philo_dead(t_rules *rules, t_philo *philo)
{
	int	j;

	j = 0;
	while (1)
	{
		if (philo_check_death(rules, philo, &j))
			return ;
	}
}

void	exit_threads(t_rules *rules)
{
	int	i;

	if (rules->nb_philo == 1)
		pthread_join(rules->philos[0].thread_id, NULL);
	else
	{
		i = 0;
		while (i < rules->nb_philo)
		{
			pthread_join(rules->philos[i].thread_id, NULL);
			i++;
		}
	}
	i = -1;
	while (++i < rules->nb_philo)
		pthread_mutex_destroy(&rules->forks[i]);
	pthread_mutex_destroy(&rules->meal);
	pthread_mutex_destroy(&rules->write);
	free(rules->philos);
	free(rules->forks);
}
