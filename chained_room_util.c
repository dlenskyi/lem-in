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

void			push_room(t_list_room *begin,
				t_list_room *new_list, t_util *util)
{
	if (!new_list && !begin)
		return ;
	while (begin->next)
	{
		if (begin->gen->coord.y == new_list->gen->coord.y &&
			begin->gen->coord.x == new_list->gen->coord.x)
			quit("You put same coords for different rooms!", util);
		if (!ft_strcmp(new_list->gen->name, begin->gen->name))
			quit("You put same names for different rooms!", util);
		begin = begin->next;
	}
	if (!ft_strcmp(new_list->gen->name, begin->gen->name))
		quit("You put same names for different rooms!", util);
	if (begin->gen->coord.y == new_list->gen->coord.y &&
		begin->gen->coord.x == new_list->gen->coord.x)
		quit("You put same coords for different rooms!", util);
	begin->next = new_list;
}

t_list_room		*new_list_room(t_lem_gen *gen)
{
	t_list_room		*list_room;

	list_room = (t_list_room *)ft_memalloc(sizeof(t_list_room));
	list_room->gen = gen;
	list_room->next = NULL;
	return (list_room);
}

t_lem_gen		*add_room(char **str, t_util *util)
{
	int			i;
	t_lem_gen	*gen_room;

	i = -1;
	gen_room = (t_lem_gen *)ft_memalloc(sizeof(t_lem_gen));
	gen_room->name = str[0];
	gen_room->ant = 0;
	gen_room->used = 0;
	gen_room->start = util->start;
	gen_room->end = util->end;
	gen_room->begin = NULL;
	gen_room->neighbour = NULL;
	while (str[1][++i])
		if (!ft_isdigit(str[1][i]))
			quit("Invalid coords!", util);
	i = -1;
	while (str[2][++i])
		if (!ft_isdigit(str[2][i]))
			quit("Invalid coords!", util);
	gen_room->coord.x = ft_atoi(str[1]);
	gen_room->coord.y = ft_atoi(str[2]);
	free(str[1]);
	free(str[2]);
	free(str);
	return (gen_room);
}

void			push_link(t_list_room *list_room, char **str, t_util *util)
{
	t_lem_gen	*src;
	t_lem_gen	*dest;

	src = NULL;
	dest = NULL;
	while (list_room)
	{
		if (!ft_strcmp(list_room->gen->name, str[0]))
			src = list_room->gen;
		if (!ft_strcmp(list_room->gen->name, str[1]))
			dest = list_room->gen;
		list_room = list_room->next;
	}
	if (!dest || !src)
		quit("Invalid link!", util);
	if (!src->neighbour)
		src->neighbour = new_list_room(dest);
	else
		push_valid_room(src->neighbour, new_list_room(dest), util);
	if (!dest->neighbour)
		dest->neighbour = new_list_room(src);
	else
		push_valid_room(dest->neighbour, new_list_room(src), util);
}

void			get_links(t_list_room *list_room, t_map **map, t_util *util)
{
	char	**str;

	while (*map)
	{
		while (*map && (*map)->info[0] == '#')
		{
			if (!ft_strcmp((*map)->info, "##start"))
				quit("You cannot connect START with links!", util);
			if (!ft_strcmp((*map)->info, "##end"))
				quit("You cannot connect END with links!", util);
			*map = (*map)->next;
		}
		if (*map)
		{
			str = ft_strsplit((*map)->info, '-');
			if (args_len(str) != 2)
			{
				ft_del_strsplit(str);
				return ;
			}
			push_link(list_room, str, util);
			ft_del_strsplit(str);
			*map = (*map)->next;
		}
	}
}
