/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 12:21:05 by lde-batz          #+#    #+#             */
/*   Updated: 2021/01/15 14:48:53 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	init_t_nm(t_nm *nm)
{
	ft_bzero(nm, sizeof(t_nm));
	nm->files = NULL;
	nm->ptr_end = NULL;
}

int		main(int argc, char **argv)
{
	t_nm	nm;

	init_t_nm(&nm);
	parsing(&nm, argc, argv);
	loop_nm(&nm);
	return (EXIT_SUCCESS);
}
