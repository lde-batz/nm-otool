/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 12:52:54 by lde-batz          #+#    #+#             */
/*   Updated: 2021/02/15 16:15:37 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	print_data(t_otool *otool)
{
	if (otool->type.type == TYPE_ARCHIVE)
		if (!otool->type.first)
			ft_printf("Archive : %s\n", otool->files->file);
	ft_putstr(otool->files->file);
	if (otool->type.type == TYPE_ARCHIVE)
		ft_printf("(%s)", otool->type.str_data);
	else if (otool->type.type == TYPE_FAT)
	{
		if (otool->type.is_ppc == 1)
			ft_printf(" (architecture ppc%s)", (otool->len > 8) ? "64" : "");
		else if (otool->type.is_ppc == 2)
			ft_printf(" (architecture %s)",
										(otool->len > 8) ? "x86_64" : "i386");
	}
	ft_putstr(":\nContents of (__TEXT,__text) section\n");
	otool->type.first = 1;
}

void	putocthex(uint8_t n, char *base)
{
	if (n >= 16)
	{
		putocthex(n / 16, base);
		putocthex(n % 16, base);
	}
	else
		ft_putchar(base[n]);
}

void	print_output_norm(t_otool *otool, uint64_t i)
{
	if (i != 0)
		write(1, "\n", 1);
	else
	{
		ft_putstr_fd(otool->files->file, 2);
		ft_putstr_fd(": is a malformed object\n", 2);
	}
}

void	print_output(t_otool *otool, void *ptr, uint64_t size, uint64_t addr)
{
	uint64_t	i;

	i = -1;
	if (ptr + otool->ptr_size < ptr + size)
		return ;
	print_data(otool);
	while (++i < size)
	{
		if (i % 16 == 0)
			ft_printf("%*0lx\t", otool->len, addr + i);
		if (*(uint8_t *)ptr < 16)
			ft_putchar('0');
		putocthex(*(uint8_t *)ptr, "0123456789abcdef");
		if (otool->ppc && i % 4 == 3)
			ft_putchar(' ');
		if (!otool->ppc)
			ft_putchar(' ');
		if (i % 16 == 15 && i + 1 < size)
			write(1, "\n", 1);
		ptr = (void *)ptr + sizeof(uint8_t);
	}
	print_output_norm(otool, i);
}
