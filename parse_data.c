/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlenskyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:28:14 by dlenskyi          #+#    #+#             */
/*   Updated: 2019/01/31 18:28:16 by dlenskyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		is_safe(char **str, t_lem_gen *g)
{
	if ((ft_strlen(str[1]) > 18 || ft_strchr(str[0], '-')) ||
		(ft_strlen(str[2]) > 18) || !str[1] || !str[2] || str[3] ||
		str[0][0] == 'L' || g->chained)
	{
		ft_del_strsplit(str);
		quit("Invalid map");
	}
	push_room(str, &g->room, g);
}

void		parse_ants(t_lem_gen *g)
{
	while (get_next_line(0, &g->line) > 0)
	{
		if (g->line[0] == '#')
		{
			push_comment(&g->comment, g);
			ft_strdel(&g->line);
		}
		else
			break ;
	}
	if (!g->line || ft_atoi(g->line) <= 0)
		quit("Invalid number of ants");
	g->ant = ft_atoi(g->line);
	ft_printf("%d\n", g->ant);
	ft_strdel(&g->line);
}

void		parse_room(t_lem_gen *g)
{
	while (get_next_line(0, &g->line) > 0)
	{
		if (g->line[0] == '#' && !ft_strstr(g->line, "##start") &&
			!ft_strstr(g->line, "##end") && !ft_strstr(g->line,
					"#Here is the number of lines required:"))
			push_comment(&g->comment, g);
		else if (ft_strstr(g->line, "#Here is the number of lines required:"))
			g->req_lines = ft_strdup(g->line);
		else if (ft_strstr(g->line, "##start"))
			push_start(g);
		else if (ft_strchr(g->line, ' '))
			is_safe(ft_strsplit(g->line, ' '), g);
		else if (ft_strstr(g->line, "##end"))
			push_end(g);
		else if (ft_strchr(g->line, '-'))
			push_chain(ft_strsplit(g->line, '-'), g);
		else
		{
			ft_strdel(&g->line);
			quit("Invalid room");
		}
		if (!ft_strstr(g->line, "#Here is the number of lines required:"))
			ft_printf("%s\n", g->line);
		ft_strdel(&g->line);
	}
}

void		new_chain(t_chained **begin, t_chained *chain)
{
	t_chained *buf_chain;

	buf_chain = *begin;
	if (!buf_chain)
		*begin = chain;
	else
	{
		while (buf_chain)
		{
			if (!buf_chain->next)
			{
				buf_chain->next = chain;
				return ;
			}
			buf_chain = buf_chain->next;
		}
	}
}

void		find_road(t_lem_gen *g)
{
	t_road		*road;
	t_chained	*chained;

	if (!(g->road = ft_memalloc(sizeof(t_road) * (g->room_num + 2))))
		quit("Initialization error");
	chained = g->chained;
	while (chained)
	{
		road = new_road(chained);
		push_road(&g->road[chained->src], road);
		chained = chained->next;
	}
}
