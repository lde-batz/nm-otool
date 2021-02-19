/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 12:40:30 by lde-batz          #+#    #+#             */
/*   Updated: 2021/01/08 15:54:12 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

t_lst_file	*new_file(t_lst_file *files, char *str_file)
{
	t_lst_file	*new;
	t_lst_file	*last;

	if (!(new = (t_lst_file *)malloc(sizeof(t_lst_file))))
	{
		ft_putendl_fd("Error malloc()", 2);
		return (files);
	}
	new->file = str_file;
	new->next = NULL;
	if (files == NULL)
		return (new);
	last = files;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	return (files);
}

void		parsing(t_otool *otool, int argc, char **argv)
{
	int		i;

	i = 0;
	while (++i < argc)
		otool->files = new_file(otool->files, argv[i]);
	if (otool->files == NULL)
		otool->files = new_file(NULL, "a.out");
}
