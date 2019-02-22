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
