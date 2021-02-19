/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:34:33 by lde-batz          #+#    #+#             */
/*   Updated: 2021/02/15 16:14:01 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	output_section_64(t_otool *otool, void *ptr, struct load_command *lc)
{
	uint32_t					i;
	uint32_t					nsects;
	struct segment_command_64	*segm;
	struct section_64			*sect;

	otool->len = 16;
	segm = (struct segment_command_64 *)lc;
	sect = (struct section_64 *)((void *)segm + sizeof(*segm));
	nsects = swap_ppc64(segm->nsects, otool->ppc);
	if (!(check_binary_seg64(otool, segm->nsects, sect)))
		return ;
	i = -1;
	while (++i < segm->nsects)
	{
		if (!ft_strcmp((sect + i)->sectname, SECT_TEXT)
								&& !ft_strcmp((sect + i)->segname, SEG_TEXT))
		{
			print_output(otool,
						ptr + swap_ppc64((sect + i)->offset, otool->ppc),
						swap_ppc64((sect + i)->size, otool->ppc),
						swap_ppc64((sect + i)->addr, otool->ppc));
		}
	}
}

void	handle_64(t_otool *otool, void *ptr)
{
	size_t					i;
	size_t					ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;

	header = (struct mach_header_64 *)ptr;
	otool->ppc = (swap_uint64(header->cputype) == CPU_TYPE_POWERPC);
	ncmds = swap_ppc64(header->ncmds, otool->ppc);
	lc = ptr + sizeof(*header);
	if (!(check_binary_cmd(otool, ncmds, lc)))
		return ;
	i = 0;
	while (++i < ncmds)
	{
		if (swap_ppc64(lc->cmd, otool->ppc) == LC_SEGMENT_64)
			output_section_64(otool, ptr, lc);
		lc = (void *)lc + swap_ppc64(lc->cmdsize, otool->ppc);
	}
}
