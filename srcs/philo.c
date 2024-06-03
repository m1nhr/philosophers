/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:16:19 by marecarraya       #+#    #+#             */
/*   Updated: 2023/05/04 20:14:07 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_params(t_rules *rules, int argc, char *argv[])
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!ft_isint(argv[i]))
			return (0);
		if (ft_atol(argv[i]) < 0)
			return (0);
		i++;
	}
	rules->nb_philo = ft_atol(argv[1]);
	rules->time_to_die = ft_atol(argv[2]);
	rules->time_to_eat = ft_atol(argv[3]);
	rules->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		rules->eat_count_max = ft_atol(argv[5]);
	else
		rules->eat_count_max = 0;
	if (rules->nb_philo < 1 || rules->time_to_die < 0 || rules->time_to_eat < 0
		|| rules->time_to_sleep < 0 || rules->eat_count_max < 0)
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_rules	rules;

	if (argc != 5 && argc != 6)
		return (printf("Program requires 5 or 6 arguments\n"));
	if (!check_params(&rules, argc, argv))
		return (printf("Invalid arguments\n"));
	if (!ft_init(&rules))
		return (printf("Error during initialisation\n"));
	launch_threads(&rules);
}
