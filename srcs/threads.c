/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:33:20 by marecarraya       #+#    #+#             */
/*   Updated: 2023/05/05 14:41:13 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_sleep(unsigned long duration, t_rules *rules)
{
	unsigned long	start;

	start = get_time();
	while (!check_finish_sim(rules->philos, 0))
	{
		if (get_time() - start >= duration)
			break ;
		usleep(rules->nb_philo * 2);
	}
}

void	eat_bis(t_philo *philo)
{
	print_action("is eating", philo, 1);
	pthread_mutex_lock(&philo->rules->meal);
	philo->t_last_meal = get_time();
	philo->ate_count++;
	pthread_mutex_unlock(&philo->rules->meal);
	philo_sleep(philo->rules->time_to_eat, philo->rules);
}

void	philo_eat(t_philo *philo)
{
	if (philo->pos % 2 == 0)
	{
		pthread_mutex_lock(&philo->rules->forks[philo->left_fork]);
		print_action("has taken a fork", philo, 1);
		pthread_mutex_lock(&philo->rules->forks[philo->right_fork]);
		print_action("has taken a fork", philo, 1);
		eat_bis(philo);
		pthread_mutex_unlock(&philo->rules->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->rules->forks[philo->left_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->rules->forks[philo->right_fork]);
		print_action("has taken a fork", philo, 1);
		if (philo->rules->nb_philo == 1)
		{
			pthread_mutex_unlock(&philo->rules->forks[philo->right_fork]);
			return ;
		}
		pthread_mutex_lock(&philo->rules->forks[philo->left_fork]);
		print_action("has taken a fork", philo, 1);
		eat_bis(philo);
		pthread_mutex_unlock(&philo->rules->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->rules->forks[philo->right_fork]);
	}
}

void	*routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	if (philo->pos % 2 && philo->rules->nb_philo > 1)
		philo_sleep(philo->rules->time_to_eat / 50, philo->rules);
	while (!check_finish_sim(philo, 0))
	{
		philo_eat(philo);
		if (philo->rules->nb_philo == 1)
			break ;
		print_action("is sleeping", philo, 1);
		philo_sleep(philo->rules->time_to_sleep, philo->rules);
		print_action("is thinking", philo, 1);
		if (philo->rules->nb_philo % 2 != 0)
			philo_sleep((philo->rules->time_to_die
					- (philo->rules->time_to_eat + philo->rules->time_to_eat))
				/ 2, philo->rules);
	}
	return (NULL);
}

int	launch_threads(t_rules *rules)
{
	int	i;

	i = 0;
	rules->died = 0;
	rules->start_time = get_time();
	while (i < rules->nb_philo)
	{
		rules->philos[i].t_last_meal = get_time();
		if (pthread_create(&rules->philos[i].thread_id,
				NULL, routine, &(rules->philos[i])))
			return (0);
		i++;
	}
	philo_dead(rules, rules->philos);
	exit_threads(rules);
	return (1);
}
