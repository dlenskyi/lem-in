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

void	push_comment(t_comment **begin, char *cmt, t_util *util)
{
	t_comment	*buf;
	t_comment	*new;

	if (!(new = (t_comment *)ft_memalloc(sizeof(t_comment))))
		quit("Initialization error", util);
	new->comment = ft_strdup(cmt);
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
			util->flg.col = 1;
		else if (!ft_strcmp(av[i], "-lines"))
			util->flg.lines = 1;
		else if (!ft_strcmp(av[i], "-cmt"))
			util->flg.cmt = 1;
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
	(util.flg.col) ? (print_color_map(map, begin)) :
	(print_map(map, begin));
	send_ants(util.ants_nb, get_weight(ways), ways, &util);
	if (util.flg.cmt || util.flg.lines || util.flg.col)
		print_args(&util);
	quit(NULL, &util);
	return (0);
}
