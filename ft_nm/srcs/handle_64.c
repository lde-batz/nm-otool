/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:34:33 by lde-batz          #+#    #+#             */
/*   Updated: 2021/02/15 16:09:52 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	parse_section_64(t_nm *nm, struct load_command *lc)
{
	uint32_t					i;
	struct segment_command_64	*segm;
	struct section_64			*sect;

	segm = (struct segment_command_64 *)lc;
	sect = (struct section_64 *)((void *)segm + sizeof(*segm));
	if (nm->type.is_ppc != 1 && !(check_binary_seg64(nm, segm->nsects, sect)))
		return ;
	i = -1;
	while (++i < segm->nsects)
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

void	print_output_64(t_nm *nm, char *ptr,
											struct symtab_command *symtab_cmd)
{
	uint32_t		i;
	uint32_t		nsyms;
	char			*stringtab;
	struct nlist_64	*symtab;
	t_data_tab		*data_tab;

	stringtab = (void *)ptr + swap_ppc64(symtab_cmd->stroff, nm->ppc);
	symtab = (void *)ptr + swap_ppc64(symtab_cmd->symoff, nm->ppc);
	nsyms = swap_ppc64(symtab_cmd->nsyms, nm->ppc);
	if (!(data_tab = set_data_tab_64(nm, nsyms, symtab, stringtab)))
		return ;
	sort_datas(nm, nsyms, data_tab);
	i = -1;
	while (++i < nsyms)
		if ((nm->opt.g != 1 || ft_isupper(data_tab[i].type))
				&& (nm->opt.u != 1 || data_tab[i].type == 'U'))
			print_line(nm, &data_tab[i], 16);
	free(data_tab);
}

void	handle_64_norm(t_nm *nm, void *ptr, struct load_command *lc)
{
	if (nm->opt.o != 1)
		print_data(nm);
	print_output_64(nm, ptr, (struct symtab_command *)lc);
}

void	handle_64(t_nm *nm, void *ptr)
{
	int						i;
	int						ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;

	ft_bzero(&nm->section, sizeof(t_section));
	header = (struct mach_header_64 *)ptr;
	nm->ppc = (swap_uint64(header->cputype) == CPU_TYPE_POWERPC);
	ncmds = swap_ppc64(header->ncmds, nm->ppc);
	lc = ptr + sizeof(*header);
	if (nm->type.is_ppc != 1 && !(check_binary_cmd(nm, ncmds, lc)))
		return ;
	nm->type.first = 0;
	i = 0;
	while (++i < ncmds)
	{
		if (swap_ppc64(lc->cmd, nm->ppc) == LC_SEGMENT_64)
			parse_section_64(nm, lc);
		if (swap_ppc64(lc->cmd, nm->ppc) == LC_SYMTAB)
		{
			handle_64_norm(nm, ptr, lc);
			break ;
		}
		lc = (void *)lc + swap_ppc64(lc->cmdsize, nm->ppc);
	}
}
