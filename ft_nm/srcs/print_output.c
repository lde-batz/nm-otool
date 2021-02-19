/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 12:52:54 by lde-batz          #+#    #+#             */
/*   Updated: 2021/02/15 15:58:37 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	print_data(t_nm *nm)
{
	if (nm->lst_file_len > 1 || nm->type.type == TYPE_ARCHIVE
							|| nm->type.is_ppc > 0)
	{
		ft_printf("\n%s", nm->files->file);
		if (nm->type.type == TYPE_ARCHIVE)
			ft_printf("(%s)", nm->type.str_data);
		else if (nm->type.type == TYPE_FAT)
			ft_printf(" (for architecture %s)",
								(nm->type.is_ppc == 1) ? "ppc" : "i386");
		else if (nm->type.type == TYPE_FAT_64)
			ft_printf(" (for architecture %s)",
								(nm->type.is_ppc == 1) ? "ppc64" : "x86_64");
		ft_printf(":\n");
	}
	nm->type.first = 1;
}

void	print_line(t_nm *nm, t_data_tab *data_tab, uint8_t len)
{
	if (data_tab->type == ' ' || data_tab->type == '?'
								|| !data_tab->symname[0])
		return ;
	if (nm->type.first != 1 && nm->opt.o != 1)
		print_data(nm);
	if (nm->opt.o == 1)
		ft_printf("%s: ", nm->files->file);
	if (data_tab->type == 'U' || data_tab->type == 'I')
		write(1, "                ", len);
	else
		ft_printf("%*0lx", len, data_tab->value);
	ft_printf(" %c %s", data_tab->type, data_tab->symname);
	if (data_tab->type == 'I')
		ft_printf(" (indirect for %s)\n", data_tab->symname);
	else
		write(1, "\n", 1);
}
