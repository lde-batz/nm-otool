/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat_64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 14:12:06 by lde-batz          #+#    #+#             */
/*   Updated: 2021/02/15 15:51:50 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	handle_fat_64(t_nm *nm, void *ptr)
{
	uint32_t			i;
	uint32_t			nfat;
	struct fat_header	*header;
	struct fat_arch		*fat_arch;

	header = (struct fat_header *)ptr;
	nfat = swap_uint32(header->nfat_arch);
	fat_arch = ptr + sizeof(struct fat_header);
	i = -1;
	while (++i < nfat)
	{
		nm->type.i = i;
		nm->type.is_ppc = 0;
		if (!(check_binary_memory(nm, ptr + swap_uint32(fat_arch[i].offset))))
			return ;
		if (nfat > 1 && !i && cpu_type(swap_uint32(fat_arch[i + 1].cputype)))
			continue ;
		if (nfat > 1 && !cpu_type(swap_uint64(fat_arch[i].cputype)))
			nm->type.is_ppc = (i) ? 2 : 1;
		ft_nm(nm, ptr + swap_uint64(fat_arch[i].offset));
		if (cpu_type(swap_uint32(fat_arch[i].cputype)))
			return ;
	}
}
