/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat_32.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:11:52 by lde-batz          #+#    #+#             */
/*   Updated: 2021/02/15 16:11:57 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void		handle_fat_32(t_otool *otool, void *ptr)
{
	uint32_t			i;
	uint32_t			nfat;
	struct fat_header	*header;
	struct fat_arch		*fat_arch;

	header = (struct fat_header *)ptr;
	nfat = header->nfat_arch;
	nfat = swap_uint32(nfat);
	fat_arch = ptr + sizeof(*header);
	i = -1;
	while (++i < nfat)
	{
		otool->type.i = i;
		otool->type.is_ppc = 0;
		if (!(check_binary_memory(otool,
									ptr + swap_uint32(fat_arch[i].offset))))
			return ;
		if (nfat > 1 && !i && cpu_type(swap_uint32(fat_arch[i + 1].cputype)))
			continue ;
		if (nfat > 1 && !cpu_type(swap_uint32(fat_arch[i].cputype)))
			otool->type.is_ppc = (i) ? 2 : 1;
		ft_otool(otool, ptr + swap_uint32(fat_arch[i].offset));
		if (cpu_type(swap_uint32(fat_arch[i].cputype)))
			return ;
	}
}
