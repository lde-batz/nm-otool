/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat_64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:11:52 by lde-batz          #+#    #+#             */
/*   Updated: 2021/02/15 16:11:26 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void		handle_fat_64(t_otool *otool, void *ptr)
{
	uint32_t			i;
	uint32_t			nfat;
	struct fat_header	*header;
	struct fat_arch_64	*fat_arch;

	header = (struct fat_header *)ptr;
	nfat = header->nfat_arch;
	nfat = swap_uint32(nfat);
	fat_arch = ptr + sizeof(*header);
	i = -1;
	while (++i < nfat)
	{
		ft_otool(otool, ptr + swap_uint64(fat_arch[i].offset));
	}
}
