/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:36:08 by lde-batz          #+#    #+#             */
/*   Updated: 2021/01/15 17:34:09 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	parse_section_32(t_nm *nm, struct load_command *lc)
{
	uint32_t				i;
	uint32_t				nsects;
	struct segment_command	*segm;
	struct section			*sect;

	segm = (struct segment_command *)lc;
	sect = (struct section *)((void *)segm + sizeof(*segm));
	nsects = swap_ppc32(segm->nsects, nm->ppc);
	if (nm->type.is_ppc != 1 && !(check_binary_seg32(nm, segm->nsects, sect)))
		return ;
	i = -1;
	while (++i < nsects)
	{
		if (!ft_strcmp((sect + i)->sectname, SECT_TEXT)
								&& !ft_strcmp((sect + i)->segname, SEG_TEXT))
			nm->section.text = nm->section.index + 1;
		else if (!ft_strcmp((sect + i)->sectname, SECT_DATA)
								&& !ft_strcmp((sect + i)->segname, SEG_DATA))
			nm->section.data = nm->section.index + 1;
		else if (!ft_strcmp((sect + i)->sectname, SECT_BSS)
								&& !ft_strcmp((sect + i)->segname, SEG_DATA))
			nm->section.bss = nm->section.index + 1;
		nm->section.index++;
	}
}

void	print_output_32(t_nm *nm, char *ptr, struct symtab_command *symtab_cmd)
{
	uint32_t		i;
	uint32_t		nsyms;
	char			*stringtab;
	struct nlist	*symtab;
	t_data_tab		*data_tab;

	stringtab = (void *)ptr + swap_ppc32(symtab_cmd->stroff, nm->ppc);
	symtab = (void *)ptr + swap_ppc32(symtab_cmd->symoff, nm->ppc);
	nsyms = swap_ppc32(symtab_cmd->nsyms, nm->ppc);
	if (!(data_tab = set_data_tab_32(nm, nsyms, symtab, stringtab)))
		return ;
	sort_datas(nm, nsyms, data_tab);
	i = -1;
	while (++i < nsyms)
		if ((nm->opt.g != 1 || ft_isupper(data_tab[i].type))
				&& (nm->opt.u != 1 || data_tab[i].type == 'U'))
			print_line(nm, &data_tab[i], 8);
	free(data_tab);
}

void	handle_32(t_nm *nm, void *ptr)
{
	int						i;
	int						ncmds;
	struct mach_header		*header;
	struct load_command		*lc;

	ft_bzero(&nm->section, sizeof(t_section));
	header = (struct mach_header *)ptr;
	nm->ppc = (swap_uint32(header->cputype) == CPU_TYPE_POWERPC);
	ncmds = swap_ppc32(header->ncmds, nm->ppc);
	lc = ptr + sizeof(*header);
	if (nm->type.is_ppc != 1 && !(check_binary_cmd(nm, ncmds, lc)))
		return ;
	nm->type.first = 0;
	i = 0;
	while (++i < ncmds)
	{
		if (swap_ppc32(lc->cmd, nm->ppc) == LC_SEGMENT)
			parse_section_32(nm, lc);
		if (swap_ppc32(lc->cmd, nm->ppc) == LC_SYMTAB)
		{
			print_output_32(nm, ptr, (struct symtab_command *)lc);
			break ;
		}
		lc = (void *)lc + swap_ppc32(lc->cmdsize, nm->ppc);
	}
}
