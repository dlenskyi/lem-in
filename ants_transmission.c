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

int		is_optimal_road(int ants, int *weight, t_lem_gen *road)
{
	int		curr;
	int		sum;

	curr = 1;
	sum = 0;
	while (curr < road->id)
	{
		sum += road->weight - weight[curr];
		curr++;
	}
	return (ants > sum);
}

int		que_ants(t_lem_gen *g)
{
	int		qued;

	qued = 0;
	while (g->begin)
	{
		if (g->ant != 0)
		{
			qued = 1;
			if (g->begin->ant != 0)
				que_ants(g->begin);
			g->begin->ant = g->ant;
			g->ant = 0;
			return (1);
		}
		g = g->begin;
	}
	return (qued);
}

void	send_for_print(t_list_room *ways, int ant, t_util *util)
{
	t_lem_gen	*road;

	road = ways->gen;
	que_ants(road);
	road->ant = ant;
	if (util->flag.color)
		print_if_color(road, util);
	else
		print_result(road, util);
}

void	send_qued_ants(t_list_room *begin, t_util *util)
{
	int			qued;
	t_list_room	*ways;

	qued = 1;
	while (qued)
	{
		ways = begin;
		qued = 0;
		while (ways)
		{
			if (que_ants(ways->gen))
			{
				qued = 1;
				if (util->flag.color)
					print_if_color(ways->gen, util);
				else
					print_result(ways->gen, util);
			}
			ways = ways->next;
		}
		if (qued)
			putendl(util);
	}
}

void	send_ants(int ants, int *weight, t_list_room *ways, t_util *util)
{
	int			ant_nb;
	t_list_room	*begin;

	ant_nb = 0;
	begin = ways;
	while (++ant_nb <= ants)
	{
		ways = begin;
		send_for_print(ways, ant_nb, util);
		ways = ways->next;
		while (ways && is_optimal_road(ants - ant_nb, weight, ways->gen))
		{
			ant_nb += 1;
			send_for_print(ways, ant_nb, util);
			ways = ways->next;
		}
		while (ways && que_ants(ways->gen))
		{
			if (util->flag.color)
				print_if_color(ways->gen, util);
			else
				print_result(ways->gen, util);
			ways = ways->next;
		}
		putendl(util);
	}
	free(weight);
	send_qued_ants(begin, util);
}
