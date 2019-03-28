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

void	putendl(t_util *util)
{
	ft_printf("\n");
	util->my_lines += 1;
}

void	quit(char *s, t_util *util)
{
	if (util->line)
		ft_strdel(&util->line);
	if (s)
	{
		ft_printf("{RED}{SET:BO}%s{OFF}\n", s);
		exit(1);
	}
	exit(0);
}

void	parse_args(int ac, char **av, t_util *util)
{
	int	i;

	i = 1;
	if (ac < 1)
		quit("usage: ./lem-in [-color | -lines | -cmt] < [map]", util);
	while (av[i])
	{
		if (!ft_strcmp(av[i], "-color"))
			util->flag.color = 1;
		else if (!ft_strcmp(av[i], "-lines"))
			util->flag.lines = 1;
		else if (!ft_strcmp(av[i], "-cmt"))
			util->flag.cmt = 1;
		else
			quit("usage: ./lem-in [-color | -lines | -cmt] < [map]", util);
		i++;
	}
}

int		main(int ac, char **av)
{
	t_map			*begin;
	t_map			*map;
	t_list_room		*list_room;
	t_list_room		*ways;
	t_util			util;

	ft_bzero(&util, sizeof(util));
	parse_args(ac, av, &util);
	map = parse_map(&util);
	if (!map)
		quit("Empty map!", &util);
	begin = map;
	util.ants_nb = parse_ants(&map, &util);
	list_room = get_rooms_list(&map, &util);
	get_links(list_room, &map, &util);
	ways = find_roads(to_the_end(list_room, &util), &util);
	if (!ways)
		quit("There is no way to get end :(", &util);
	(util.flag.color) ? (print_color_map(map, begin)) :
	(print_map(map, begin));
	send_ants(util.ants_nb, get_weight(ways), ways, &util);
	if (util.flag.cmt || util.flag.lines || util.flag.color)
		print_args(&util);
	quit(NULL, &util);
	return (0);
}
