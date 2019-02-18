/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlenskyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:13:09 by dlenskyi          #+#    #+#             */
/*   Updated: 2019/02/01 14:13:10 by dlenskyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		push_delay(double weight, int dest, t_road **begin)
{
	t_road	*road_tmp;
	t_road	*road;

	if (!(road = (t_road *)ft_memalloc(sizeof(t_road))))
		quit("Initialization error");
	road_tmp = *begin;
	road->weight = weight;
	road->dest = dest;
	if (!road_tmp)
		*begin = road;
	else
	{
		while (road_tmp)
		{
			if (!road_tmp->next)
			{
				road_tmp->next = road;
				return ;
			}
			road_tmp = road_tmp->next;
		}
	}
}

void		pop_delay(t_road **begin)
{
	t_road	*road_tmp;

	road_tmp = (*begin)->next;
	free(*begin);
	*begin = road_tmp;
}

void		parse_optimal_way(t_lem_gen *g)
{
	int		i;
	t_room	*room_buf;

	i = -1;
	if (!(g->final = (int *)ft_memalloc(sizeof(int) * (g->room_num + 1))))
		quit("Initialization error");
	if (!(g->weight = (double *)ft_memalloc(sizeof(double) *
			(g->room_num + 1))))
		quit("Initialization error");
	while (g->room_num + 1 > ++i)
		g->final[i] = -1;
	i = -1;
	while (g->room_num + 1 > ++i)
		g->weight[i] = LONG_MAX;
	room_buf = if_exists(g->room, g->start);
	g->final[room_buf->id] = 0;
	g->weight[room_buf->id] = 0;
	push_delay(0, room_buf->id, &g->delay);
}

void		get_optimal_way(t_lem_gen *g)
{
	int		dst_buf;
	double	weight_buf;
	t_road	*r_buf;

	while (g->delay)
	{
		dst_buf = g->delay->dest;
		weight_buf = g->delay->weight;
		r_buf = g->road[dst_buf];
		pop_delay(&g->delay);
		if (g->weight[dst_buf] >= weight_buf)
		{
			while (r_buf)
			{
				if (r_buf->weight + g->weight[dst_buf] < g->weight[r_buf->dest])
				{
					g->weight[r_buf->dest] = r_buf->weight + g->weight[dst_buf];
					push_delay(g->weight[r_buf->dest], r_buf->dest, &g->delay);
					g->final[r_buf->dest] = dst_buf;
				}
				r_buf = r_buf->next;
			}
		}
	}
}
