/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlenskyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:46:44 by dlenskyi          #+#    #+#             */
/*   Updated: 2019/02/28 14:34:14 by dlenskyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_result(int ants, t_lem_gen *g)
{
	while (--ants >= 0)
		if (g->ants_trans[ants].ants != 0)
			ft_printf("L%i-%s ", g->ants_trans[ants].ants,
					g->ants_trans[ants].name);
	ft_printf("\n");
	g->my_lines += 1;
}

void	print_args(t_lem_gen *g)
{
	t_comment	*cmt_tmp;

	cmt_tmp = g->comment;
	if (g->flag.lines)
	{
		ft_printf("\n%s", (g->req_lines) ? (g->req_lines) : "");
		ft_printf("%sNumber of lines: %d\n", (g->req_lines) ? "\n" : "",
				g->my_lines);
		ft_strdel(&g->req_lines);
	}
	if (g->flag.cmt)
	{
		ft_printf("\n{MGT}----COMMENTS----\n{OFF}");
		while (cmt_tmp)
		{
			ft_printf("{YEL}%s{OFF}\n", cmt_tmp->comment);
			cmt_tmp = cmt_tmp->next;
		}
	}
}

void	print_map(t_lem_gen *g)
{
	t_map	*buf_map;

	buf_map = g->map;
	while (buf_map)
	{
		ft_printf("%s\n", buf_map->info);
		buf_map = buf_map->next;
	}
}

void	print_color_map(t_lem_gen *g)
{
	t_map	*buf_map;

	buf_map = g->map;
	while (buf_map)
	{
		ft_printf("{YEL}%s{OFF}\n", buf_map->info);
		buf_map = buf_map->next;
	}
}

void	print_if_color(int ants, t_lem_gen *g)
{
	while (--ants >= 0)
		if (g->ants_trans[ants].ants != 0)
			ft_printf("{GRN}L%d-%s {OFF}",
					g->ants_trans[ants].ants, g->ants_trans[ants].name);
	ft_printf("\n");
	g->my_lines += 1;
}
