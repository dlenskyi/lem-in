/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlenskyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 17:14:24 by dlenskyi          #+#    #+#             */
/*   Updated: 2019/02/28 14:37:47 by dlenskyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	quit(char *s, t_lem_gen *g)
{
	if (g->line)
		ft_strdel(&g->line);
	if (s)
	{
		ft_printf("{RED}{SET:BO}%s{OFF}\n", s);
		exit(1);
	}
	exit(0);
}

void	parse_args(int ac, char **av, t_lem_gen *g)
{
	int	i;

	i = 1;
	if (ac < 1)
		quit("usage: ./lem-in [-help | -color | -lines | -cmt] < [map]", g);
	while (av[i])
	{
		if (!ft_strcmp(av[i], "-color"))
			g->flag.color = 1;
		else if (!ft_strcmp(av[i], "-lines"))
			g->flag.lines = 1;
		else if (!ft_strcmp(av[i], "-cmt"))
			g->flag.cmt = 1;
		else if (!ft_strcmp(av[i], "-help"))
			g->flag.help = 1;
		else
			quit("usage: ./lem-in [-help | -color | -lines | -cmt] < [map]", g);
		if (g->flag.help)
			quit("usage: ./lem-in [-help | -color | -lines | -cmt] < [map]", g);
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
		quit("Map doesn't have start or end", &g);
	find_road(&g);
	parse_optimal_way(&g);
	get_optimal_way(&g);
	if (!g.ants_trans)
		parse_dat_way(&g);
	(g.flag.color) ? (print_color_map(&g)) :
	(print_map(&g));
	send_ants(&g);
	if (g.flag.cmt || g.flag.lines || g.flag.color)
		print_args(&g);
	quit(NULL, &g);
	return (0);
}
