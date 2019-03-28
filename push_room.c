/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlenskyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 12:10:54 by dlenskyi          #+#    #+#             */
/*   Updated: 2019/02/01 12:10:55 by dlenskyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			get_start_end(t_map **map, t_util *util)
{
	static int	start = 0;
	static int	end = 0;

	util->start = 0;
	util->end = 0;
	while (*map && (*map)->info[0] == '#')
	{
		if (!ft_strstr((*map)->info, "##start") &&
			!ft_strstr((*map)->info, "##end"))
			push_comment(&util->comment, (*map)->info, util);
		if (!ft_strcmp((*map)->info, "##start"))
		{
			is_safe_start(start, util);
			util->start = 1;
			start++;
		}
		if (!ft_strcmp((*map)->info, "##end"))
		{
			is_safe_end(end, util);
			util->end = 1;
			end++;
		}
		*map = (*map)->next;
	}
}

void			push_valid_room(t_list_room *begin,
				t_list_room *new_list, t_util *util)
{
	if (!new_list && !begin)
		return ;
	while (begin->next)
		begin = begin->next;
	begin->next = new_list;
}

t_list_room		*get_rooms_list(t_map **map, t_util *util)
{
	t_list_room		*list_room;
	char			**str;

	list_room = NULL;
	while (*map)
	{
		check_if_l(map, util);
		get_start_end(map, util);
		if (*map)
		{
			str = ft_strsplit((*map)->info, ' ');
			if (args_len(str) != 3)
			{
				ft_del_strsplit(str);
				return (list_room);
			}
			if (!list_room)
				list_room = new_list_room(add_room(str, util));
			else
				push_room(list_room, new_list_room(add_room(str, util)), util);
			*map = (*map)->next;
		}
	}
	return (list_room);
}

void			is_safe_start(int start, t_util *util)
{
	if (util->end)
		quit("It cannot be START and END in a row!", util);
	if (start)
		quit("It cannot be more than one START in map!", util);
}

void			is_safe_end(int end, t_util *util)
{
	if (util->start)
		quit("It cannot be START and END in a row!", util);
	if (end)
		quit("It cannot be more than one END in map!", util);
}
