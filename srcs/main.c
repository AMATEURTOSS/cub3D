/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 23:13:47 by yochoi            #+#    #+#             */
/*   Updated: 2020/06/12 15:43:49 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	malloc_tex(t_cub3d *t)
{
	t_img *no;
	t_img *so;
	t_img *ea;
	t_img *we;
	t_img *sp;

	no = (t_img *)malloc(sizeof(t_img));
	so = (t_img *)malloc(sizeof(t_img));
	ea = (t_img *)malloc(sizeof(t_img));
	we = (t_img *)malloc(sizeof(t_img));
	sp = (t_img *)malloc(sizeof(t_img));
	ft_bzero(no, sizeof(t_img));
	ft_bzero(so, sizeof(t_img));
	ft_bzero(we, sizeof(t_img));
	ft_bzero(ea, sizeof(t_img));
	ft_bzero(sp, sizeof(t_img));
	t->no = no;
	t->so = so;
	t->ea = ea;
	t->we = we;
	t->sp = sp;
}

t_cub3d	*init_t(void)
{
	t_cub3d	*t;
	t_rc	*rc;
	t_map	*map;
	t_img	*screen;

	if (!(t = (t_cub3d *)malloc(sizeof(t_cub3d))))
		exitprogram(MALLOC_ERROR);
	if (!(map = (t_map *)malloc(sizeof(t_map))))
		exitprogram(MALLOC_ERROR);
	if (!(rc = (t_rc *)malloc(sizeof(t_rc))))
		exitprogram(MALLOC_ERROR);
	if (!(screen = (t_img *)malloc(sizeof(t_img))))
		exitprogram(MALLOC_ERROR);
	ft_bzero(t, sizeof(t_cub3d));
	ft_bzero(map, sizeof(t_map));
	ft_bzero(rc, sizeof(t_rc));
	ft_bzero(screen, sizeof(t_img));
	t->map = map;
	t->rc = rc;
	t->screen = screen;
	malloc_tex(t);
	return (t);
}

int		main(int argc, char **argv)
{
	t_cub3d *t;

	t = init_t();
	parser(parser_param(argc, argv, t), t);
	get_map(t);
	is_valid(t);
	render(t);
	return (0);
}
