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

t_room		*push_room(char **str, t_room **begin, t_lem_gen *g)
{
	t_room	*buf;
	t_room	*new;

	new = ft_memalloc(sizeof(t_room));
	new->name = ft_strdup(str[0]);
	new->id = ++g->room_num;
	ft_del_strsplit(str);
	buf = *begin;
	if (!buf)
		*begin = new;
	else
	{
		while (buf)
		{
			if (!buf->next)
			{
				buf->next = new;
				break ;
			}
			buf = buf->next;
		}
	}
	return (new);
}

void		push_chain(char **str, t_lem_gen *g)
{
	t_room		*src[2];
	t_chained	*new[2];

	src[0] = if_exists(g->room, str[0]);
	src[1] = if_exists(g->room, str[1]);
	if (!src[0] || !src[1] || str[2])
	{
		ft_del_strsplit(str);
		quit("Error in chains :/");
	}
	if (!(new[0] = (t_chained *)ft_memalloc(sizeof(t_chained))))
		quit("Initialization error");
	if (!(new[1] = (t_chained *)ft_memalloc(sizeof(t_chained))))
		quit("Initialization error");
	new[0]->src = src[0]->id;
	new[0]->dest = src[1]->id;
	new_chain(&g->chained, new[0]);
	new[1]->dest = src[0]->id;
	new[1]->src = src[1]->id;
	new_chain(&g->chained, new[1]);
	ft_del_strsplit(str);
}

void		push_comment(t_comment **begin, t_lem_gen *g)
{
	t_comment	*buf;
	t_comment	*new;

	if (!(new = (t_comment *)ft_memalloc(sizeof(t_comment))))
		quit("Initialization error");
	new->comment = ft_strdup(g->line);
	buf = *begin;
	if (!buf)
	{
		*begin = new;
		return ;
	}
	while (buf)
	{
		if (!buf->next)
		{
			buf->next = new;
			return ;
		}
		buf = buf->next;
	}
}

void		push_start(t_lem_gen *g)
{
	char	**str;

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
	str = ft_strsplit(g->line, ' ');
	g->start = ft_strdup(str[0]);
	is_safe(str, g);
}

void		push_end(t_lem_gen *g)
{
	char	**str;

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
	str = ft_strsplit(g->line, ' ');
	g->end = ft_strdup(str[0]);
	is_safe(str, g);
}
