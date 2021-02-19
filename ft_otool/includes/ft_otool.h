/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 16:22:45 by lde-batz          #+#    #+#             */
/*   Updated: 2021/02/15 16:10:48 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <ar.h>

# define AR_MAGIC 0x72613c21
# define AR_CIGAM 0x213c6172

# define TYPE_NOT 0x0
# define TYPE_FAT 0x1
# define TYPE_ARCHIVE 0x2

typedef struct	s_lst_file
{
	char				*file;
	struct s_lst_file	*next;
}				t_lst_file;

typedef struct	s_type
{
	char		type;
	char		is_ppc;
	char		first;
	uint32_t	i;
	char		*str_data;
}				t_type;

typedef struct	s_otool
{
	t_lst_file	*files;
	off_t		ptr_size;
	void		*ptr_end;
	char		ppc;
	int			len;
	char		err;
	t_type		type;
}				t_otool;

void			parsing(t_otool *otool, int argc, char **argv);

void			loop_otool(t_otool *otool);
void			ft_otool(t_otool *otool, void *ptr);

void			handle_32(t_otool *otool, void *ptr);
void			handle_64(t_otool *otool, void *ptr);
void			handle_arch(t_otool *otool, void *ptr);
void			handle_fat_32(t_otool *otool, void *ptr);
void			handle_fat_64(t_otool *otool, void *ptr);

void			print_output(t_otool *otool, void *ptr, uint64_t size,
																uint64_t addr);

int				print_error(const char *error, int ret);

char			check_binary_memory(t_otool *otool, void *ptr);
char			check_binary_cmd(t_otool *otool, size_t ncmds,
													struct load_command *lc);
char			check_binary_seg32(t_otool *otool, size_t nsects,
													struct section *sect);
char			check_binary_seg64(t_otool *otool, size_t nsects,
													struct section_64 *sect);

char			cpu_type(uint32_t type);
uint32_t		swap_uint32(uint32_t n);
uint32_t		swap_ppc32(uint32_t n, char ppc);
uint64_t		swap_uint64(uint64_t n);
uint64_t		swap_ppc64(uint64_t n, char ppc);

#endif
