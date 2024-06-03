/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:30:22 by marecarraya       #+#    #+#             */
/*   Updated: 2023/05/04 20:12:32 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_init_mutex(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&rules->meal, NULL))
		return (0);
	if (pthread_mutex_init(&rules->write, NULL))
		return (0);
	if (pthread_mutex_init(&rules->finish, NULL))
		return (0);
	return (1);
}

void	ft_init_philo(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		rules->philos[i].ate_count = 0;
		rules->philos[i].pos = i + 1;
		rules->philos[i].left_fork = i;
		rules->philos[i].right_fork = (i + 1) % rules->nb_philo;
		rules->philos[i].rules = rules;
		i++;
	}
}

int	ft_init(t_rules *rules)
{
	rules->philos = malloc(sizeof(t_philo) * rules->nb_philo);
	if (!rules->philos)
		return (0);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	if (!rules->forks)
	{
		free(rules->philos);
		return (0);
	}
	if (!ft_init_mutex(rules))
	{
		free(rules->philos);
		free(rules->forks);
		return (0);
	}
	ft_init_philo(rules);
	return (1);
}
