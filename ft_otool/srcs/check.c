/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:42:59 by lde-batz          #+#    #+#             */
/*   Updated: 2021/02/15 16:13:42 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

char	check_binary_memory(t_otool *otool, void *ptr)
{
	int len;

	if (ptr > otool->ptr_end)
	{
		len = ft_strlen(otool->files->file) + 20;
		while (len--)
			ft_printf("\b");
		ft_putstr_fd(otool->files->file, 2);
		ft_putstr_fd(": is a malformed object\n", 2);
		return (0);
	}
	return (1);
}

char	check_binary_cmd(t_otool *otool, size_t ncmds,
													struct load_command *lc)
{
	size_t		i;

	i = 0;
	while (i < ncmds)
	{
		if (!(check_binary_memory(otool, lc)))
			return (0);
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
	return (1);
}

char	check_binary_seg32(t_otool *otool, size_t nsects,
														struct section *sect)
{
	size_t		i;

	i = 0;
	while (i < nsects)
	{
		if (!(check_binary_memory(otool, sect)))
			return (0);
		sect = (void *)sect + sizeof(struct section);
		i++;
	}
	return (1);
}

char	check_binary_seg64(t_otool *otool, size_t nsects,
													struct section_64 *sect)
{
	size_t		i;

	i = 0;
	while (i < nsects)
	{
		if (!(check_binary_memory(otool, sect)))
			return (0);
		sect = (void *)sect + sizeof(struct section_64);
		i++;
	}
	return (1);
}
