/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 16:22:45 by lde-batz          #+#    #+#             */
/*   Updated: 2021/01/15 17:07:59 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/stab.h>
# include <mach-o/fat.h>
# include <ar.h>

# define AR_MAGIC 0x72613c21
# define AR_CIGAM 0x213c6172

# define TYPE_NOT 0x0
# define TYPE_ARCHIVE 0x1
# define TYPE_FAT 0x2
# define TYPE_FAT_64 0x4

# define SYMNAME_SIZE 512

typedef struct	s_opt_nm
{
	uint8_t	g;
	uint8_t	n;
	uint8_t	o;
	uint8_t	p;
	uint8_t	r;
	uint8_t	u;
}				t_opt_nm;

typedef struct	s_lst_file
{
	char				*file;
	struct s_lst_file	*next;
}				t_lst_file;

typedef struct	s_section
{
	uint32_t	index;
	uint32_t	text;
	uint32_t	data;
	uint32_t	bss;
}				t_section;

typedef struct	s_data_tab
{
	uint64_t	value;
	char		type;
	char		symname[SYMNAME_SIZE];
}				t_data_tab;

typedef struct	s_type
{
	char		type;
	char		is_ppc;
	char		first;
	uint32_t	i;
	char		*str_data;
}				t_type;

typedef struct	s_nm
{
	t_lst_file	*files;
	int			lst_file_len;
	char		ppc;
	t_opt_nm	opt;
	t_section	section;
	void		*ptr_end;
	t_type		type;
}				t_nm;

void			parsing(t_nm *nm, int argc, char **argv);

void			loop_nm(t_nm *nm);
void			ft_nm(t_nm *nm, char *ptr);

void			handle_32(t_nm *nm, void *ptr);
void			handle_64(t_nm *nm, void *ptr);
void			handle_arch(t_nm *nm, void *ptr);
void			handle_fat_32(t_nm *nm, void *ptr);
void			handle_fat_64(t_nm *nm, void *ptr);

t_data_tab		*set_data_tab_64(t_nm *nm, int nsyms, struct nlist_64 *symtab,
															char *stringtab);
t_data_tab		*set_data_tab_32(t_nm *nm, int nsyms, struct nlist *symtab,
															char *stringtab);

void			sort_datas(t_nm *nm, uint32_t nsyms, t_data_tab *data_tab);

void			print_data(t_nm *nm);
void			print_line(t_nm *nm, t_data_tab *data_tab, uint8_t len);

int				print_error(const char *error, int ret);
void			print_help(t_nm *nm);

char			check_binary_memory(t_nm *nm, void *ptr);
char			check_binary_cmd(t_nm *nm, size_t ncmds,
													struct load_command *lc);
char			check_binary_seg32(t_nm *nm, size_t nsects,
													struct section *sect);
char			check_binary_seg64(t_nm *nm, size_t nsects,
													struct section_64 *sect);

char			cpu_type(uint32_t type);
uint32_t		swap_uint32(uint32_t n);
uint32_t		swap_ppc32(uint32_t n, char ppc);
uint64_t		swap_uint64(uint64_t n);
uint64_t		swap_ppc64(uint64_t n, char ppc);

#endif
