/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 15:34:20 by lde-batz          #+#    #+#             */
/*   Updated: 2020/10/13 16:07:26 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char		cpu_type(uint32_t type)
{
	if (type == CPU_TYPE_X86_64 && sizeof(void *) == 8)
		return (1);
	if (type == CPU_TYPE_I386 && sizeof(void *) == 4)
		return (1);
	return (0);
}

uint32_t	swap_uint32(uint32_t n)
{
	n = ((n << 8) & 0xFF00FF00) | ((n >> 8) & 0xFF00FF);
	return ((n << 16) | (n >> 16));
}

uint32_t	swap_ppc32(uint32_t n, char ppc)
{
	if (ppc)
		return (swap_uint32(n));
	return (n);
}

uint64_t	swap_uint64(uint64_t n)
{
	n = ((n << 8) & 0xFF00FF00FF00FF00)
										| ((n >> 8) & 0x00FF00FF00FF00FF);
	n = ((n << 16) & 0xFFFF0000FFFF0000)
										| ((n >> 16) & 0x0000FFFF0000FFFF);
	return ((n << 32) | (n >> 32));
}

uint64_t	swap_ppc64(uint64_t n, char ppc)
{
	if (ppc)
		return (swap_uint64(n));
	return (n);
}
