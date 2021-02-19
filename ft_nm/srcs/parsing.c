/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 12:40:30 by lde-batz          #+#    #+#             */
/*   Updated: 2021/01/15 14:49:03 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_lst_file	*new_file(t_nm *nm, t_lst_file *files, char *str_file)
{
	t_lst_file	*new;
	t_lst_file	*last;

	if (!(new = (t_lst_file *)malloc(sizeof(t_lst_file))))
	{
		ft_putendl_fd("Error malloc()", 2);
		return (files);
	}
	nm->lst_file_len++;
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

void		parsing(t_nm *nm, int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (ft_strcmp(argv[i], "-h") == 0)
			print_help(nm);
		else if (ft_strcmp(argv[i], "-g") == 0)
			nm->opt.g = 1;
		else if (ft_strcmp(argv[i], "-n") == 0)
			nm->opt.n = 1;
		else if (ft_strcmp(argv[i], "-o") == 0)
			nm->opt.o = 1;
		else if (ft_strcmp(argv[i], "-p") == 0)
			nm->opt.p = 1;
		else if (ft_strcmp(argv[i], "-r") == 0)
			nm->opt.r = 1;
		else if (ft_strcmp(argv[i], "-u") == 0)
			nm->opt.u = 1;
		else
			nm->files = new_file(nm, nm->files, argv[i]);
	}
	if (nm->files == NULL)
		nm->files = new_file(nm, nm->files, "a.out");
}
