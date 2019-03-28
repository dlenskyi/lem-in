/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlenskyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:46:44 by dlenskyi          #+#    #+#             */
/*   Updated: 2019/02/25 18:46:56 by dlenskyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_result(t_lem_gen *g, t_util *util)
{
	while (g)
	{
		if (g->ant != 0)
			ft_printf("L%d-%s ", g->ant, g->name);
		if (util->end)
			g->ant = 0;
		g = g->begin;
	}
}

void	print_args(t_util *util)
{
	t_comment	*cmt_tmp;

	cmt_tmp = util->comment;
	if (util->flag.lines && util->flag.color)
		ft_printf("\n{RED}Number of lines: %d{OFF}\n", util->my_lines);
	else if (util->flag.lines)
		ft_printf("\nNumber of lines: %d\n", util->my_lines);
	if (util->flag.cmt)
	{
		ft_printf("\n{MGT}----COMMENTS----\n{OFF}");
		while (cmt_tmp)
		{
			ft_printf("{YEL}%s{OFF}\n", cmt_tmp->comment);
			cmt_tmp = cmt_tmp->next;
		}
	}
}

void	print_map(t_map *map, t_map *begin)
{
	while (begin && begin != map)
	{
		ft_printf("%s\n", begin->info);
		begin = begin->next;
	}
	ft_printf("\n");
}

void	print_color_map(t_map *map, t_map *begin)
{
	while (begin && begin != map)
	{
		ft_printf("{YEL}%s{OFF}\n", begin->info);
		begin = begin->next;
	}
	ft_printf("\n");
}

void	print_if_color(t_lem_gen *g, t_util *util)
{
	while (g)
	{
		if (g->ant != 0)
			ft_printf("{GRN}L%d-%s {OFF}", g->ant, g->name);
		if (util->end)
			g->ant = 0;
		g = g->begin;
	}
}
