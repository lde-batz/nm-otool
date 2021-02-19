/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 14:01:30 by lde-batz          #+#    #+#             */
/*   Updated: 2021/02/15 15:51:34 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	ft_nm(t_nm *nm, char *ptr)
{
	unsigned int	magic_number;

	magic_number = *(unsigned int *)ptr;
	if (magic_number == AR_MAGIC || magic_number == AR_CIGAM)
	{
		nm->type.type = TYPE_ARCHIVE;
		handle_arch(nm, ptr);
	}
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
		handle_32(nm, ptr);
	else if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
		handle_64(nm, ptr);
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
	{
		nm->type.type = TYPE_FAT;
		handle_fat_32(nm, ptr);
	}
	else if (magic_number == FAT_MAGIC_64 || magic_number == FAT_CIGAM_64)
	{
		nm->type.type = TYPE_FAT_64;
		handle_fat_64(nm, ptr);
	}
}

int		ft_open_nm(t_nm *nm, int fd)
{
	char		*ptr;
	struct stat	buf;

	if (fstat(fd, &buf) < 0)
		return (print_error("Error: fstat()", 0));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
																== MAP_FAILED)
		return (print_error("Error: mmap()", 0));
	nm->ptr_end = (void *)(ptr) + buf.st_size;
	ft_nm(nm, ptr);
	if (munmap(ptr, buf.st_size) < 0)
		return (print_error("Error: munmap()", 0));
	return (1);
}

void	loop_nm(t_nm *nm)
{
	int			fd;
	t_lst_file	*free_file;

	while (nm->files)
	{
		ft_bzero(&nm->section, sizeof(nm->section));
		ft_bzero(&nm->type, sizeof(t_type));
		if ((fd = open(nm->files->file, O_RDONLY)) < 0)
		{
			ft_putstr_fd(nm->files->file, 2);
			ft_putendl_fd(": No such file or directory.", 2);
		}
		else
			ft_open_nm(nm, fd);
		free_file = nm->files;
		nm->files = nm->files->next;
		free(free_file);
	}
}
