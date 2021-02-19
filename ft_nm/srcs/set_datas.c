/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_datas.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 15:44:14 by lde-batz          #+#    #+#             */
/*   Updated: 2021/02/15 15:57:35 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char		find_type_sect(t_nm *nm, uint8_t type, uint8_t sect)
{
	if (sect == nm->section.bss)
		return ((type & N_EXT) ? 'B' : 'b');
	else if (sect == nm->section.data)
		return ((type & N_EXT) ? 'D' : 'd');
	else if (sect == nm->section.text)
		return ((type & N_EXT) ? 'T' : 't');
	else
		return ((type & N_EXT) ? 'S' : 's');
}

char		find_type(t_nm *nm, uint8_t type, uint8_t sect, uint64_t value)
{
	if (type & N_STAB)
		return (' ');
	else
	{
		if ((type & N_TYPE) == N_UNDF)
		{
			if (value != 0)
				return ('C');
			return ((type & N_EXT) ? 'U' : '?');
		}
		else if ((type & N_TYPE) == N_ABS)
			return ((type & N_EXT) ? 'A' : 'a');
		else if ((type & N_TYPE) == N_SECT)
			return (find_type_sect(nm, type, sect));
		else if ((type & N_TYPE) == N_PBUD)
			return ('P');
		else if ((type & N_TYPE) == N_INDR)
			return ((type & N_EXT) ? 'I' : 'i');
		return ('?');
	}
}

t_data_tab	*set_data_tab_32(t_nm *nm, int nsyms, struct nlist *symtab,
															char *stringtab)
{
	int			i;
	t_data_tab	*data_tab;

	if (!(data_tab = (t_data_tab *)malloc(sizeof(t_data_tab) * nsyms)))
	{
		ft_putendl_fd("Error malloc()", 2);
		return (NULL);
	}
	i = -1;
	while (++i < nsyms)
	{
		data_tab[i].value = symtab[i].n_value;
		data_tab[i].type = find_type(nm, symtab[i].n_type, symtab[i].n_sect,
															symtab[i].n_value);
		if (data_tab[i].type == 'U')
			data_tab[i].value = 0;
		else
			data_tab[i].value = swap_ppc32(symtab[i].n_value, nm->ppc);
		ft_strncpy(data_tab[i].symname, &stringtab
				[swap_ppc32(symtab[i].n_un.n_strx, nm->ppc)], SYMNAME_SIZE);
	}
	return (data_tab);
}

t_data_tab	*set_data_tab_64(t_nm *nm, int nsyms,
									struct nlist_64 *symtab, char *stringtab)
{
	int			i;
	t_data_tab	*data_tab;

	if (!(data_tab = (t_data_tab *)malloc(sizeof(t_data_tab) * nsyms)))
	{
		ft_putendl_fd("Error malloc()", 2);
		return (NULL);
	}
	i = -1;
	while (++i < nsyms)
	{
		data_tab[i].value = symtab[i].n_value;
		data_tab[i].type = find_type(nm, symtab[i].n_type, symtab[i].n_sect,
															symtab[i].n_value);
		if (data_tab[i].type == 'U' || data_tab[i].type == 'I')
			data_tab[i].value = 0;
		else
			data_tab[i].value = swap_ppc64(symtab[i].n_value, nm->ppc);
		ft_strncpy(data_tab[i].symname, &stringtab
				[swap_ppc64(symtab[i].n_un.n_strx, nm->ppc)], SYMNAME_SIZE);
	}
	return (data_tab);
}
