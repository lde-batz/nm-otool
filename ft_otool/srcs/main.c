/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 12:21:05 by lde-batz          #+#    #+#             */
/*   Updated: 2020/10/08 15:47:57 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	init_t_otool(t_otool *otool)
{
	ft_memset(otool, 0, sizeof(t_otool));
	otool->files = NULL;
}

int		main(int argc, char **argv)
{
	t_otool	otool;

	init_t_otool(&otool);
	parsing(&otool, argc, argv);
	loop_otool(&otool);
	return (EXIT_SUCCESS);
}
