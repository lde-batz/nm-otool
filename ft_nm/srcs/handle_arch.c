/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:21:59 by lde-batz          #+#    #+#             */
/*   Updated: 2021/01/15 17:08:31 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	handle_arch(t_nm *nm, void *ptr)
{
	int				len;
	struct ar_hdr	*hdr;

	ptr += SARMAG;
	hdr = (struct ar_hdr *)ptr;
	ptr += sizeof(struct ar_hdr) + ft_atoi(hdr->ar_size);
	while (ptr)
	{
		hdr = (struct ar_hdr *)ptr;
		if (ft_atoi(hdr->ar_size) <= 0)
			return ;
		nm->type.str_data = ptr + sizeof(struct ar_hdr);
		len = ft_strlen(nm->type.str_data);
		while (!nm->type.str_data[len++])
			;
		ft_nm(nm, ptr + (sizeof(struct ar_hdr) + len - 1));
		ptr += sizeof(struct ar_hdr) + ft_atoi(hdr->ar_size);
	}
}
