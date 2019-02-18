/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_room_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlenskyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 18:49:17 by dlenskyi          #+#    #+#             */
/*   Updated: 2019/02/15 15:54:01 by dlenskyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room		*if_exists(t_room *begin, char *chain)
{
	t_room	*buf;

	if (!chain)
		return (NULL);
	buf = begin;
	while (buf)
	{
		if (!ft_strcmp(buf->name, chain))
			return (buf);
		buf = buf->next;
	}
	return (NULL);
}

void		push_road(t_road **begin, t_road *road)
{
	t_road	*buf;

	buf = *begin;
	if (!buf)
		*begin = road;
	else
	{
		while (buf)
		{
			if (!buf->next)
			{
				buf->next = road;
				break ;
			}
			buf = buf->next;
		}
	}
}

t_road		*new_road(t_chained *chained)
{
	t_road	*new;

	if (!(new = (t_road *)ft_memalloc(sizeof(t_road))))
		quit("Initialization error");
	new->dest = chained->dest;
	new->weight = chained->weight;
	return (new);
}

double		iter_geron(double approximation, double natural)
{
	double	deviation;
	double	previous;

	previous = approximation;
	deviation = natural / previous;
	approximation = (deviation + previous) / 2;
	if (previous * 0.99 > approximation || previous * 1.01 < approximation)
		return (iter_geron(approximation, natural));
	return (approximation);
}

double		get_weight(t_room *src, t_room *dest)
{
	long	i;
	long	j;
	double	weight;

	i = src->x - dest->x;
	j = src->y - dest->y;
	weight = (double)((j * j) + (i * i));
	weight = iter_geron(weight / 2, weight);
	return (weight);
}
