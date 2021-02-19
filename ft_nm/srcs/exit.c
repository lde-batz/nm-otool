/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 13:39:00 by lde-batz          #+#    #+#             */
/*   Updated: 2021/01/08 15:24:08 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		print_error(const char *error, int ret)
{
	ft_putendl_fd(error, 2);
	return (ret);
}

void	free_t_nm(t_nm *nm)
{
	t_lst_file	*free_file;

	while (nm->files)
	{
		free_file = nm->files;
		nm->files = nm->files->next;
		free(free_file);
	}
}

void	print_help(t_nm *nm)
{
	ft_putendl("Help Sreen\n");
	ft_putendl("Usage:");
	ft_putendl("ft_nm [options] <input files>\n");
	ft_putendl("Options");
	ft_putendl(" -g		- Show only external symbols");
	ft_putendl(" -h		- Print this help screen");
	ft_putendl(" -n		- Sort symbols by address");
	ft_putstr(" -o		");
	ft_putendl("- Precede each symbol with the object file it came from");
	ft_putendl(" -p		- Show symbols in order encountered");
	ft_putendl(" -r		- Sort in reverse order");
	ft_putendl(" -u		- Show only undefined symbols");
	free_t_nm(nm);
	exit(EXIT_SUCCESS);
}
