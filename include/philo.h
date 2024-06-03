/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarecar <rmarecar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:16:55 by marecarraya       #+#    #+#             */
/*   Updated: 2023/05/05 13:45:36 by rmarecar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	int					ate_count;
	int					pos;
	int					left_fork;
	int					right_fork;
	unsigned long long	t_last_meal;
	struct s_rules		*rules;
	pthread_t			thread_id;
}						t_philo;

typedef struct s_rules
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					eat_count_max;
	unsigned long long	start_time;
	int					died;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		meal;
	pthread_mutex_t		write;
	pthread_mutex_t		finish;
}						t_rules;

/*utils.c*/
long long int	ft_atol(const char *str);
int				ft_strlen(char *str);
int				ft_isint(char *str);
unsigned long	get_time(void);
void			print_action(char *str, t_philo *philo, int unlock);

/*init.c*/
int				ft_init(t_rules *rules);
int				ft_init_mutex(t_rules *rules);
void			ft_init_philo(t_rules *rules);

/*philo.c*/
int				check_params(t_rules *rules, int argc, char *argv[]);

/*threads.c*/
void			philo_sleep(unsigned long duration, t_rules *rules);
void			eat_bis(t_philo *philo);
void			philo_eat(t_philo *philo);
void			*routine(void *void_philo);
int				launch_threads(t_rules *rules);

/*finish.c*/
int				check_finish_sim(t_philo *philo, int ok);
int				launch_threads(t_rules *rules);
void			exit_threads(t_rules *rules);
void			philo_dead(t_rules *rules, t_philo *philo);

#endif