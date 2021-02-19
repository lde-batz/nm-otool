/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:21:59 by lde-batz          #+#    #+#             */
/*   Updated: 2021/02/15 16:11:35 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	handle_arch(t_otool *otool, void *ptr)
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
		otool->type.str_data = ptr + sizeof(struct ar_hdr);
		len = ft_strlen(otool->type.str_data);
		while (!otool->type.str_data[len++])
			;
		ft_otool(otool, ptr + (sizeof(struct ar_hdr) + len - 1));
		ptr += sizeof(struct ar_hdr) + ft_atoi(hdr->ar_size);
	}
}
