/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:36:08 by lde-batz          #+#    #+#             */
/*   Updated: 2021/02/15 16:12:55 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	output_section(t_otool *otool, void *ptr, struct load_command *lc)
{
	uint32_t				i;
	uint32_t				nsects;
	struct segment_command	*segm;
	struct section			*sect;

	otool->len = 8;
	segm = (struct segment_command *)lc;
	sect = (struct section *)((void *)segm + sizeof(*segm));
	nsects = swap_ppc32(segm->nsects, otool->ppc);
	if (otool->type.is_ppc != 1
						&& !(check_binary_seg32(otool, segm->nsects, sect)))
		return ;
	i = -1;
	while (++i < nsects)
	{
		if (!ft_strcmp((sect + i)->sectname, SECT_TEXT)
								&& !ft_strcmp((sect + i)->segname, SEG_TEXT))
		{
			print_output(otool,
						ptr + swap_ppc32((sect + i)->offset, otool->ppc),
						swap_ppc32((sect + i)->size, otool->ppc),
						swap_ppc32((sect + i)->addr, otool->ppc));
		}
	}
}

void	handle_32(t_otool *otool, void *ptr)
{
	int						i;
	int						ncmds;
	struct mach_header		*header;
	struct load_command		*lc;

	header = (struct mach_header *)ptr;
	otool->ppc = (swap_uint32(header->cputype) == CPU_TYPE_POWERPC);
	ncmds = swap_ppc32(header->ncmds, otool->ppc);
	lc = ptr + sizeof(*header);
	if (otool->type.is_ppc != 1 && !(check_binary_cmd(otool, ncmds, lc)))
		return ;
	i = 0;
	while (++i < ncmds)
	{
		if (swap_ppc32(lc->cmd, otool->ppc) == LC_SEGMENT)
			output_section(otool, ptr, lc);
		lc = (void *)lc + swap_ppc32(lc->cmdsize, otool->ppc);
	}
}
