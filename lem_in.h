/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlenskyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 17:04:03 by dlenskyi          #+#    #+#             */
/*   Updated: 2019/01/31 17:04:05 by dlenskyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

typedef struct			s_flag
{
	int					cmt;
	int					color;
	int					lines;
}						t_flag;

typedef struct			s_room
{
	int					id;
	char				*name;
	struct s_room		*next;
}						t_room;

typedef struct			s_chained
{
	double				weight;
	int					dest;
	int					src;
	struct s_chained	*next;
}						t_chained;

typedef struct			s_ants_trans
{
	char				*name;
	int					ants;
	int					id;
}						t_ants_trans;

typedef struct			s_comment
{
	char				*comment;
	struct s_comment	*next;
}						t_comment;

typedef struct			s_road
{
	double				weight;
	int					dest;
	struct s_road		*next;
}						t_road;

typedef struct			s_map
{
	char				*info;
	struct s_map		*next;
}						t_map;

typedef struct			s_lem_gen
{
	t_room				*room;
	t_chained			*chained;
	t_ants_trans		*ants_trans;
	t_comment			*comment;
	t_road				*delay;
	t_road				**road;
	t_flag				flag;
	t_map				*map;
	char				*line;
	int					size;
	int					*final;
	int					room_num;
	int					ant;
	char				*start;
	char				*end;
	double				*weight;
	char				*req_lines;
	int					my_lines;
}						t_lem_gen;

void					parse_ants(t_lem_gen *g);
void					parse_room(t_lem_gen *g);
void					is_safe(char **str, t_lem_gen *g);
void					find_road(t_lem_gen *g);
void					new_chain(t_chained **begin, t_chained *chain);

t_room					*push_room(char **str, t_room **begin, t_lem_gen *g);
void					push_chain(char **str, t_lem_gen *g);
void					push_comment(t_comment **begin, t_lem_gen *g);
void					push_start(t_lem_gen *g);
void					push_end(t_lem_gen *g);

t_room					*if_exists(t_room *begin, char *chain);
t_road					*new_road(t_chained *chained);
void					push_road(t_road **begin, t_road *road);
void					push_map(t_map **begin, t_lem_gen *g);

void					push_delay(double weight, int dest, t_road **begin);
void					pop_delay(t_road **begin);
void					parse_optimal_way(t_lem_gen *g);
void					get_optimal_way(t_lem_gen *g);

void					parse_dat_way(t_lem_gen *g);
t_room					*get_curr_room(int current, t_room *begin);
int						if_remains(t_lem_gen *g);
void					send_ants(t_lem_gen *g);

void					print_result(int ants, t_lem_gen *g);
void					print_if_color(int ants, t_lem_gen *g);
void					print_map(t_lem_gen *g);
void					print_color_map(t_lem_gen *g);
void					print_args(t_lem_gen *g);

void					parse_args(int ac, char **av, t_lem_gen *g);
void					quit(char *s);

#endif
