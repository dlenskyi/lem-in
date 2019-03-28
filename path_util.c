/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delay_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlenskyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:12:56 by dlenskyi          #+#    #+#             */
/*   Updated: 2019/03/26 16:12:57 by dlenskyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			*get_weight(t_list_room *ways)
{
	int		*weight;

	weight = (int *)malloc(sizeof(int) * 1000);
	while (ways)
	{
		weight[ways->gen->id] = ways->gen->weight;
		ways = ways->next;
	}
	return (weight);
}

t_lem_gen	*check_head(t_list_room **head)
{
	t_lem_gen	*g;

	if (!*head)
		return (NULL);
	g = (*head)->gen;
	*head = (*head)->next;
	return (g);
}

void		is_safe_delay(t_list_room **head, t_list_room **tail, t_lem_gen *g)
{
	t_list_room	*list_room;

	list_room = new_list_room(g);
	if (*tail != NULL)
		(*tail)->next = list_room;
	*tail = list_room;
	if (!*head)
		*head = list_room;
}

void		clean_delay(t_list_room *head)
{
	t_list_room *remove;

	while (head)
	{
		remove = head;
		head = head->next;
		free(remove);
	}
}

int			args_len(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
