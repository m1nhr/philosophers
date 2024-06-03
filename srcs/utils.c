/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:30:14 by marecarraya       #+#    #+#             */
/*   Updated: 2023/05/04 20:15:28 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long int	ft_atol(const char *str)
{
	long long int	i;
	long long int	n;
	long long int	nb;

	i = 0;
	n = 1;
	nb = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb *= 10;
		nb += str[i] - 48;
		i++;
	}
	return (nb * n);
}

void	print_action(char *str, t_philo *philo, int unlock)
{
	unsigned long int	timestamp;

	pthread_mutex_lock(&philo->rules->write);
	if (!check_finish_sim(philo, 0))
	{
		timestamp = get_time() - philo->rules->start_time;
		printf("%lu %d %s\n", timestamp, philo->pos, str);
	}
	if (unlock)
		pthread_mutex_unlock(&philo->rules->write);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

unsigned long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	ft_isint(char *str)
{
	long long int	n;
	int				i;

	n = ft_atol(str);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if (ft_strlen(str) > 10)
		return (0);
	if (n > 2147483627 || n < -2147483628)
		return (0);
	return (1);
}
