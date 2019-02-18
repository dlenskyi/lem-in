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

void	print_result(int *my_lines, int ants, t_lem_gen *g)
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
	(*my_lines)++;
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
			ft_printf("{RED}{SET:BO}Something went wrong with
						transmission :({OFF}\n");
		exit(1);
	}
	exit(0);
}

int		main(void)
{
	t_lem_gen	g;

	ft_bzero(&g, sizeof(g));
	g.room_num = 0;
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
	quit("GG!");
	return (0);
}
