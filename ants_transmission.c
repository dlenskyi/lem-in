/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_transmission.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlenskyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 17:25:09 by dlenskyi          #+#    #+#             */
/*   Updated: 2019/02/15 17:25:10 by dlenskyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		parse_dat_way(t_lem_gen *g)
{
	int		i;
	t_room	*room_buf;
	int		valid;

	i = -1;
	room_buf = if_exists(g->room, g->end);
	valid = g->final[room_buf->id];
	if (valid == -1)
		quit("Something went wrong with transmission :(", g);
	while (++i >= 0 && valid != 0)
		valid = g->final[valid];
	if (!(g->ants_trans = (t_ants_trans *)ft_memalloc(sizeof(t_ants_trans)
			* i)))
		quit("Initialization error", g);
	g->size = i;
	valid = g->final[room_buf->id];
	g->ants_trans[--i].name = room_buf->name;
	g->ants_trans[i].id = room_buf->id;
	while (g->final[valid] != 0)
	{
		g->ants_trans[--i].name = get_curr_room(valid, g->room)->name;
		g->ants_trans[i].id = valid;
		valid = g->final[valid];
	}
}

t_room		*get_curr_room(int current, t_room *begin)
{
	t_room	*room_buf;

	room_buf = begin;
	while (room_buf)
	{
		if (room_buf->id == current)
			return (room_buf);
		room_buf = room_buf->next;
	}
	return (room_buf);
}

int			if_remains(t_lem_gen *g)
{
	int	i;

	i = -1;
	while (++i < g->size)
	{
		if (g->ants_trans[i].ants != 0)
			return (0);
	}
	return (1);
}

void		send_ants(t_lem_gen *g)
{
	int		i;
	int		curr_ant;

	curr_ant = 0;
	ft_printf("\n");
	while (++curr_ant <= g->ant)
	{
		g->ants_trans[0].ants = curr_ant;
		(g->flag.color) ? (print_if_color(g->size, g)) :
		(print_result(g->size, g));
		i = g->size;
		while (--i)
			g->ants_trans[i].ants = g->ants_trans[i - 1].ants;
		g->ants_trans[0].ants = 0;
	}
	while (!if_remains(g))
	{
		(g->flag.color) ? (print_if_color(g->size, g)) :
		(print_result(g->size, g));
		i = g->size;
		while (--i)
			g->ants_trans[i].ants = g->ants_trans[i - 1].ants;
	}
}
