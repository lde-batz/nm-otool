/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 14:01:30 by lde-batz          #+#    #+#             */
/*   Updated: 2021/01/09 16:00:38 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	ft_otool(t_otool *otool, void *ptr)
{
	unsigned int	magic_number;

	magic_number = *(unsigned int *)ptr;
	if (magic_number == AR_MAGIC || magic_number == AR_CIGAM)
	{
		otool->type.type = TYPE_ARCHIVE;
		handle_arch(otool, ptr);
	}
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
		handle_32(otool, ptr);
	else if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
		handle_64(otool, ptr);
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
	{
		otool->type.type = TYPE_FAT;
		handle_fat_32(otool, ptr);
	}
	else if (magic_number == FAT_MAGIC_64 || magic_number == FAT_CIGAM_64)
	{
		otool->type.type = TYPE_FAT;
		handle_fat_64(otool, ptr);
	}
	else
		ft_printf("%s: is not an object file\n", otool->files->file);
}

int		ft_open_otool(t_otool *otool, int fd)
{
	char		*ptr;
	struct stat	buf;

	if (fstat(fd, &buf) < 0)
		return (print_error("Error: fstat()", 0));
	if (S_ISDIR(buf.st_mode))
		return (print_error("Error: Is a directory", 0));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
																== MAP_FAILED)
		return (ft_printf("%s: is not an object file\n", otool->files->file));
	otool->ptr_size = buf.st_size;
	otool->ptr_end = (void *)(ptr) + buf.st_size;
	ft_otool(otool, ptr);
	if (munmap(ptr, buf.st_size) < 0)
		return (print_error("Error: munmap()", 0));
	return (0);
}

void	loop_otool(t_otool *otool)
{
	int			fd;
	t_lst_file	*free_file;

	while (otool->files)
	{
		ft_bzero(&otool->type, sizeof(t_type));
		if ((fd = open(otool->files->file, O_RDONLY)) < 0)
		{
			ft_putstr_fd(otool->files->file, 2);
			ft_putendl_fd(": No such file or directory.", 2);
		}
		else
			ft_open_otool(otool, fd);
		free_file = otool->files;
		otool->files = otool->files->next;
		free(free_file);
	}
}
