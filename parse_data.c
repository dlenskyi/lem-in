/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlenskyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:28:14 by dlenskyi          #+#    #+#             */
/*   Updated: 2019/02/26 17:23:43 by dlenskyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		is_safe_ant(t_map **map, t_util *util)
{
	if (!ft_strstr((*map)->info, "##start") &&
		!ft_strstr((*map)->info, "##end"))
		push_comment(&util->comment, (*map)->info, util);
	if (!ft_strcmp((*map)->info, "##start"))
		quit("You cannot manage START with ants!", util);
	if (!ft_strcmp("##end", (*map)->info))
		quit("You cannot manage END with ants!", util);
}

int			parse_ants(t_map **map, t_util *util)
{
	int		i;
	int		ants_nb;

	i = -1;
	ants_nb = 0;
	while (*map && (*map)->info[0] == '#')
	{
		is_safe_ant(map, util);
		*map = (*map)->next;
	}
	if (*map)
	{
		while ((*map)->info[++i])
			if (!ft_isdigit((*map)->info[i]))
				quit("Invalid number of ants!", util);
		ants_nb = ft_atoi((*map)->info);
		if (!ants_nb)
			quit("Choose greater than zero number of ants!", util);
		else
			*map = (*map)->next;
	}
	return (ants_nb);
}

t_map		*parse_map(t_util *util)
{
	t_map	*map;
	t_map	*previous;
	t_map	*begin;

	begin = NULL;
	while (get_next_line(0, &util->line) > 0)
	{
		if (!begin)
		{
			begin = (t_map *)ft_memalloc(sizeof(t_map));
			begin->next = NULL;
			begin->info = util->line;
			previous = begin;
		}
		else
		{
			map = (t_map *)ft_memalloc(sizeof(t_map));
			map->next = NULL;
			map->info = util->line;
			previous->next = map;
			previous = map;
		}
	}
	return (begin);
}
