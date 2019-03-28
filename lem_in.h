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

# include "libft/includes/libft.h"

typedef struct				s_flag
{
	int						cmt;
	int						col;
	int						lines;
}							t_flag;

typedef struct				s_comment
{
	char					*comment;
	struct s_comment		*next;
}							t_comment;

typedef struct				s_coord
{
	int						x;
	int						y;
}							t_coord;

typedef struct				s_map
{
	char					*info;
	struct s_map			*next;
}							t_map;

typedef struct				s_list_room
{
	struct s_lem_gen		*gen;
	struct s_list_room		*next;
}							t_list_room;

typedef struct				s_util
{
	char					*line;
	int						ants_nb;
	t_flag					flg;
	t_comment				*comment;
	int						start;
	int						end;
	int						my_lines;
}							t_util;

typedef struct				s_lem_gen
{
	t_list_room				*neighbour;
	t_coord					coord;
	struct s_lem_gen		*begin;
	int						start;
	int						end;
	char					*name;
	int						used;
	int						weight;
	int						id;
	int						ant;
}							t_lem_gen;

int							parse_ants(t_map **map, t_util *util);
t_map						*parse_map(t_util *util);
void						is_safe_ant(t_map **map, t_util *util);

t_list_room					*get_rooms_list(t_map **map, t_util *util);
void						is_safe_start(int start, t_util *util);
void						is_safe_end(int end, t_util *util);
void						push_valid_room(t_list_room *begin,
							t_list_room *new_list, t_util *util);

void						push_room(t_list_room *begin,
							t_list_room *new_list, t_util *util);
t_list_room					*new_list_room(t_lem_gen *gen);
t_lem_gen					*add_room(char **str, t_util *util);
void						get_links(t_list_room *list_room,
							t_map **map, t_util *util);

t_lem_gen					*to_the_end(t_list_room *list_room, t_util *util);
t_list_room					*find_roads(t_lem_gen *final, t_util *util);
void						push_delay(int used, t_list_room **head,
							t_list_room **tail, t_lem_gen *g);
t_lem_gen					*breadth_first_search(int used, t_lem_gen *final,
							t_util *util);
int							is_used(t_util *util, t_lem_gen *g);

int							*get_weight(t_list_room *ways);
t_lem_gen					*check_head(t_list_room **head);
void						is_safe_delay(t_list_room **head,
							t_list_room **tail, t_lem_gen *g);
void						clean_delay(t_list_room *head);
int							args_len(char **str);

int							is_optimal_road(int ants,
							int *weight, t_lem_gen *road);
void						send_for_print(t_list_room *ways,
							int ant, t_util *util);
void						send_for_print(t_list_room *ways,
							int ant, t_util *util);
void						send_qued_ants(t_list_room *begin, t_util *util);
void						send_ants(int ants, int *weight,
							t_list_room *ways, t_util *util);

void						prnt_res(t_lem_gen *g, t_util *util);
void						prnt_col(t_lem_gen *g, t_util *util);
void						print_map(t_map *map, t_map *begin);
void						print_color_map(t_map *map, t_map *begin);
void						print_args(t_util *util);

void						putendl(t_util *util);
void						push_comment(t_comment **begin,
							char *cmt, t_util *util);
void						parse_args(int ac, char **av, t_util *util);
void						quit(char *s, t_util *util);

#endif
