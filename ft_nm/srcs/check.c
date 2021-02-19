/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:02:06 by lde-batz          #+#    #+#             */
/*   Updated: 2021/02/15 15:57:54 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	check_binary_memory(t_nm *nm, void *ptr)
{
	if (ptr > nm->ptr_end)
	{
		ft_putstr_fd(nm->files->file, 2);
		ft_putstr_fd(": is a malformed object\n", 2);
		return (0);
	}
	return (1);
}

char	check_binary_cmd(t_nm *nm, size_t ncmds,
													struct load_command *lc)
{
	size_t		i;

	i = 0;
	while (i < ncmds)
	{
		if (!(check_binary_memory(nm, lc)))
			return (0);
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
	return (1);
}

char	check_binary_seg32(t_nm *nm, size_t nsects,
														struct section *sect)
{
	size_t		i;

	i = 0;
	while (i < nsects)
	{
		if (!(check_binary_memory(nm, sect)))
			return (0);
		sect = (void *)sect + sizeof(struct section);
		i++;
	}
	return (1);
}

char	check_binary_seg64(t_nm *nm, size_t nsects,
													struct section_64 *sect)
{
	size_t		i;

	i = 0;
	while (i < nsects)
	{
		if (!(check_binary_memory(nm, sect)))
			return (0);
		sect = (void *)sect + sizeof(struct section_64);
		i++;
	}
	return (1);
}
