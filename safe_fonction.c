/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_fonction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 11:53:44 by mehdi             #+#    #+#             */
/*   Updated: 2025/01/16 11:11:36 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret == NULL)
		error_exit("probleme de malloc");
	return (ret);
}

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (EINVAL == status && (LOCK == opcode
			|| UNLOCK == opcode || DESTROY == opcode))
		error_exit("valeur de mutex invalide");
	else if (EINVAL == status && INIT == opcode)
		error_exit("valeur de attr invalide");
	else if (EDEADLK == status)
		error_exit("erreur de mutex");
	else if (ENOMEM == status)
		error_exit("impossible d'allouer de la memoir au mutex");
	else if (EPERM == status)
		error_exit("le thread n'a pas de mutex");
	else if (EBUSY == status)
		error_exit("mutex est fermer");
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (!mutex)
		error_exit("pointeur de mutex est NULL");
	if (LOCK == opcode)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (DESTROY == opcode)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else if (INIT == opcode)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else
		error_exit("probleme avec le mutex");
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (EAGAIN == status)
		error_exit("manque de ressources pour les threads");
	else if (EPERM == status)
		error_exit("probleme avec les permissions");
	else if (EINVAL == status && CREATE == opcode)
		error_exit("la valeur du attr est invalide");
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		error_exit("la valeur n'est pas joignable");
	else if (ESRCH == status)
		error_exit("un deadlock est detecter");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode)
{
	if (!thread)
		error_exit("pointeur de thread est NULL");
	if (CREATE == opcode)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handle_thread_error(pthread_detach((*thread)), opcode);
	else
		error_exit("probleme avec les threads");
}
