/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 18:12:24 by yochoi            #+#    #+#             */
/*   Updated: 2020/06/10 16:10:35 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			start_dirset(t_cub3d *t)
{
	char c;

	c = t->map->start_dir;
	if (c == 'N')
	{
		t->rc->dirx = -1;
		t->rc->diry = 0;
		t->rc->planex = 0;
		t->rc->planey = 0.66;
	}
	else if (c == 'S')
	{
		t->rc->dirx = 1;
		t->rc->diry = 0;
		t->rc->planex = 0;
		t->rc->planey = -0.66;
	}
	else if (c == 'E')
	{
		t->rc->dirx = 0;
		t->rc->diry = 1;
		t->rc->planex = 0.66;
		t->rc->planey = 0;
	}
	else if (c == 'W')
	{
		t->rc->dirx = 0;
		t->rc->diry = -1;
		t->rc->planex = -0.66;
		t->rc->planey = 0;
	}
}

int			deal_key(int key, void *param)
{
	t_cub3d *t;

	t = (t_cub3d *)param;
	if (key == ESC)
		exitprogram(TERMINATE);
	t->keycode = key;
	move_pos_view(t);
	draw(t);
	return (0);
}

void		init_dir(t_cub3d *t)
{
	char c;

	c = t->map->start_dir;
	t->rc->posx = t->map->playerx;
	t->rc->posy = t->map->playery;
	start_dirset(t);
	t->rc->time = 0;
	t->rc->oldtime = 0;
	t->rc->rotspeed = 0.1;
	t->rc->movespeed = 0.1;
}

void		init(t_cub3d *t)
{
	t->no->img = mlx_xpm_file_to_image(t->mlx, t->no->file, &t->no->width, \
					&t->no->height);
	t->so->img = mlx_xpm_file_to_image(t->mlx, t->so->file, &t->so->width, \
					&t->so->height);
	t->we->img = mlx_xpm_file_to_image(t->mlx, t->we->file, &t->we->width, \
					&t->we->height);
	t->ea->img = mlx_xpm_file_to_image(t->mlx, t->ea->file, &t->ea->width, \
					&t->ea->height);
	t->sp->img = mlx_xpm_file_to_image(t->mlx, t->sp->file, &t->sp->width, \
					&t->sp->height);
	init_dir(t);
}

void		render(t_cub3d *t)
{
	t->mlx = mlx_init();
	t->win = mlx_new_window(t->mlx, t->width, t->height, "yochoi");
	init(t);
	draw(t);
	mlx_hook(t->win, _KEY_PRESS, 0, deal_key, t);
	mlx_hook(t->win, _KEY_EXIT, 0, exitprogram, 0);
	mlx_loop(t->mlx);
}
