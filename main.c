/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlenskyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 17:14:24 by dlenskyi          #+#    #+#             */
/*   Updated: 2019/01/31 17:14:25 by dlenskyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_result(int ants, t_lem_gen *g)
{
	int valid_print;

	valid_print = 0;
	while (--ants >= 0)
	{
		if (g->ants_trans[ants].ants != 0)
		{
			if (valid_print++ == 0)
				ft_printf("L%d-%s",
						g->ants_trans[ants].ants, g->ants_trans[ants].name);
			else
				ft_printf(" L%d-%s",
						g->ants_trans[ants].ants, g->ants_trans[ants].name);
		}
	}
	ft_printf("\n");
	g->my_lines += 1;
}

void	print_args(t_lem_gen *g)
{
	t_comment	*cmt_tmp;
	cmt_tmp = g->comment;
	if (g->flag.lines)
	{
		ft_printf("%s", (g->req_lines) ? (g->req_lines) : "");
		ft_printf("%sNumber of lines: %d\n", (g->req_lines) ? "\n" : "", g->my_lines);
		ft_strdel(&g->req_lines);
	}
	if (g->flag.cmt)
	{
		while (cmt_tmp)
		{
			ft_printf("{YEL}%s{OFF}\n", cmt_tmp->comment);
			cmt_tmp = cmt_tmp->next;
		}
	}
}

void	quit(char *s)
{
	if (s)
	{
		if (!ft_strcmp(s, "Invalid number of ants"))
			ft_printf("{RED}{SET:BO}Invalid number of ants{OFF}\n");
		else if (!ft_strcmp(s, "Invalid room"))
			ft_printf("{RED}{SET:BO}Invalid room{OFF}\n");
		else if (!ft_strcmp(s, "Invalid chain between rooms"))
			ft_printf("{RED}{SET:BO}Invalid chain between rooms{OFF}\n");
		else if (!ft_strcmp(s, "Map doesn't have start or end"))
			ft_printf("{RED}{SET:BO}Map doesn't have start or end{OFF}\n");
		else if (!ft_strcmp(s, "Couldn't get distance :/"))
			ft_printf("{RED}{SET:BO}Couldn't get distance :/{OFF}\n");
		else if (!ft_strcmp(s, "Initialization error"))
			ft_printf("{RED}{SET:BO}Initialization error{OFF}\n");
		else if (!ft_strcmp(s, "Error in chains :/"))
			ft_printf("{RED}{SET:BO}Error in chains :/{OFF}\n");
		else if (!ft_strcmp(s, "Something went wrong with transmission :("))
		{
			ft_printf("{RED}{SET:BO}Something went wrong with ");
			ft_printf("transmission :({OFF}\n");
		}
		else if (!ft_strcmp(s, "usage: ./lem-in < [map]"))
			ft_printf("{RED}{SET:BO}usage: ./lem-in < [map]{OFF}\n");
		exit(1);
	}
	exit(0);
}

void	parse_args(int ac, char **av, t_lem_gen *g)
{
	int	i;

	i = 1;
	if (ac < 1)
		quit("usage: ./lem-in < [map]");
	while (av[i])
	{
		if (!ft_strcmp(av[i], "-colors"))
			g->flag.color = 1;
		if (!ft_strcmp(av[i], "-lines"))
			g->flag.lines = 1;
		if (!ft_strcmp(av[i], "-cmt"))
			g->flag.cmt = 1;
		if ((ft_strcmp(av[i], "-colors") || ft_strcmp(av[i], "-") ||
			ft_strcmp(av[i], "-lines") || ft_strcmp(av[i], "-cmt")) &&
			ft_strchr(av[i], '<'))
			quit("usage: ./lem-in < [map]");
		i++;
	}
}

int		main(int ac, char **av)
{
	t_lem_gen	g;

	ft_bzero(&g, sizeof(g));
	g.room_num = 0;
	parse_args(ac, av, &g);
	parse_ants(&g);
	parse_room(&g);
	if (!g.start || !g.end)
		quit("Map doesn't have start or end");
	find_road(&g);
	parse_optimal_way(&g);
	get_optimal_way(&g);
	if (!g.ants_trans)
		parse_dat_way(&g);
	send_ants(&g);
	if (g.flag.cmt || g.flag.lines || g.flag.color)
		print_args(&g);
	quit("GG!");
	return (0);
}
