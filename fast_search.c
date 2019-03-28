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

t_lem_gen	*to_the_end(t_list_room *list_room, t_util *util)
{
	t_lem_gen	*start;
	t_lem_gen	*end;

	start = NULL;
	end = NULL;
	while (list_room)
	{
		if (list_room->gen->end)
			end = list_room->gen;
		if (list_room->gen->start)
			start = list_room->gen;
		list_room = list_room->next;
	}
	if (!end)
		quit("You didn't enter start!", util);
	if (!start)
		quit("You didn't enter end!", util);
	return (end);
}

int			is_used(t_util *util, t_lem_gen *g)
{
	g->id = g->used;
	g->used = INT_MAX;
	if (g->end)
		return (1);
	if (g->begin)
		g->weight = is_used(util, g->begin) + 1;
	return (g->weight);
}

void		push_delay(int used, t_list_room **head,
					t_list_room **tail, t_lem_gen *g)
{
	t_list_room	*tmp_neighbour;

	tmp_neighbour = g->neighbour;
	while (tmp_neighbour)
	{
		if (tmp_neighbour->gen->used != INT_MAX &&
			tmp_neighbour->gen->used != used)
		{
			tmp_neighbour->gen->used = used;
			tmp_neighbour->gen->begin = g;
			is_safe_delay(head, tail, tmp_neighbour->gen);
		}
		tmp_neighbour = tmp_neighbour->next;
	}
}

t_lem_gen	*breadth_first_search(int used, t_lem_gen *final, t_util *util)
{
	t_lem_gen	*g;
	t_list_room	*start;
	t_list_room	*head;
	t_list_room	*tail;

	head = NULL;
	tail = NULL;
	is_safe_delay(&head, &tail, final);
	start = head;
	while (head != NULL)
	{
		g = check_head(&head);
		g->used = used;
		if (g->start)
		{
			is_used(util, g->begin);
			clean_delay(start);
			return (g->begin);
		}
		push_delay(used, &head, &tail, g);
	}
	clean_delay(start);
	return (NULL);
}

t_list_room	*find_roads(t_lem_gen *final, t_util *util)
{
	t_lem_gen	*road;
	t_list_room	*ways;
	int			curr;

	curr = 1;
	ways = NULL;
	while ((road = breadth_first_search(curr, final, util)))
	{
		if (!ways)
			ways = new_list_room(road);
		else
			push_valid_room(ways, new_list_room(road), util);
		if (road->end)
			break ;
		curr++;
	}
	return (ways);
}
