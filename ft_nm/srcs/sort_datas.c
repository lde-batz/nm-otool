/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_datas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 13:44:35 by lde-batz          #+#    #+#             */
/*   Updated: 2021/02/15 15:52:20 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	sort_datas_alp(int nsyms, t_data_tab *data_tab, uint8_t rvrs)
{
	int			i;
	int			j;
	int			cmp;
	t_data_tab	swap;

	i = -1;
	while (++i < nsyms - 1)
	{
		j = -1;
		while (++j < nsyms - (i + 1))
		{
			cmp = ft_strcmp(data_tab[j].symname, data_tab[j + 1].symname);
			if ((cmp > 0 && rvrs != 1) || (cmp < 0 && rvrs == 1))
			{
				swap = data_tab[j];
				data_tab[j] = data_tab[j + 1];
				data_tab[j + 1] = swap;
			}
		}
	}
}

void	sort_datas_num(int nsyms, t_data_tab *data_tab, uint8_t rvrs)
{
	int				i;
	int				j;
	long long int	cmp;
	t_data_tab		swap;

	i = -1;
	while (++i < nsyms - 1)
	{
		j = -1;
		while (++j < nsyms - (i + 1))
		{
			cmp = data_tab[j].value - data_tab[j + 1].value;
			cmp = (cmp == 0 && rvrs != 1 && data_tab[j].type != 'U') ? 1 : cmp;
			cmp = (cmp == 0 && rvrs == 1 && data_tab[j + 1].type != 'U')
																	? -1 : cmp;
			if ((cmp > 0 && rvrs != 1) || (cmp < 0 && rvrs == 1))
			{
				swap = data_tab[j];
				data_tab[j] = data_tab[j + 1];
				data_tab[j + 1] = swap;
			}
		}
	}
}

void	sort_datas(t_nm *nm, uint32_t nsyms, t_data_tab *data_tab)
{
	if (!nm->opt.p)
	{
		if (nm->opt.n != 1)
		{
			sort_datas_num(nsyms, data_tab, nm->opt.r);
			sort_datas_alp(nsyms, data_tab, nm->opt.r);
		}
		else
		{
			sort_datas_alp(nsyms, data_tab, nm->opt.r);
			sort_datas_num(nsyms, data_tab, nm->opt.r);
		}
	}
}
