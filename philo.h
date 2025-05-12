/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:26:26 by mehdi             #+#    #+#             */
/*   Updated: 2025/01/16 11:56:02 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;
typedef struct s_philo	t_philo;
// **write_function_macro**
# define DEBUG_MODE 1

// Reset
#define RESET "\033[0m"

// Regular Colors
#define RED	"\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

typedef enum s_opcode
{
	LOCK,
	CREATE,
	UNLOCK,
	JOIN,
	DESTROY,
	DETACH,
	INIT
}	t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}		t_time_code;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}		t_fork;

typedef struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;
	long		threads_running_nbr;
	long		start_simulation;
	bool		end_simulation;
	bool		all_threads_ready;
	pthread_t	monitor;
	t_mtx		table_mutex;
	t_mtx		write_mutex;
	t_fork		*forks;
	t_philo		*philos;
}	t_table;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}		t_philo_status;

typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		philo_mutex;
	t_table		*table;
}		t_philo;

// **utils**
void	error_exit(const char *error);
long	gettime(t_time_code time_code);
void	precise_usleep(long usec, t_table *table);
void	clean(t_table *table);

// **parsing**
void	parse_input(t_table *table, char **av);

// **dinner**
void	*dinner_simulation(void *data);
void	dinner_start(t_table *table);

// **getters_setters**
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long *value);
bool	simulation_finished(t_table *table);

// **initialisation**
void	data_init(t_table *table);

// **safe_functions**
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
			void *data, t_opcode opcode);

// **synchro**
void	wait_all_threads(t_table *table);
void	increase_long(t_mtx *mutex, long *value);
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
void	thinking(t_philo *philo, bool pre_simulation);
void	de_synchro_philo(t_philo *philo);

// **write_status**
void	write_status(t_philo_status status, t_philo *philo, bool debug);

// **monitor**
void	*monitor_dinner(void *data);

#endif