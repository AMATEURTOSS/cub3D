/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 15:24:52 by yochoi            #+#    #+#             */
/*   Updated: 2020/06/12 22:10:43 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			set_deltadist(t_cub3d *t)
{
	if (t->rc->raydiry == 0)
		t->rc->deltadistx = 0;
	else
	{
		if (t->rc->raydirx == 0)
			t->rc->deltadistx = 1;
		else
			t->rc->deltadistx = fabs(1 / t->rc->raydirx);
	}
	if (t->rc->raydirx == 0)
		t->rc->deltadisty = 0;
	else
	{
		if (t->rc->raydiry == 0)
			t->rc->deltadisty = 1;
		else
			t->rc->deltadisty = fabs(1 / t->rc->raydiry);
	}
}

void			draw_3(t_cub3d *t)
{
	if (t->rc->side == 0)
		t->rc->perpwalldist = (t->rc->mapx - t->rc->posx +
				(1 - t->rc->stepx) / 2) / t->rc->raydirx;
	else if (t->rc->side == 1)
		t->rc->perpwalldist = (t->rc->mapy - t->rc->posy +
				(1 - t->rc->stepy) / 2) / t->rc->raydiry;
	t->rc->zbuffer[t->x] = t->rc->perpwalldist;
	t->rc->lineheight = (int)(t->height / t->rc->perpwalldist);
	t->rc->drawstart = -t->rc->lineheight / 2 + t->height / 2;
	if (t->rc->drawstart < 0)
		t->rc->drawstart = 0;
	t->rc->drawend = t->rc->lineheight / 2 + t->height / 2;
	if (t->rc->drawend >= t->height)
		t->rc->drawend = t->height - 1;
}

int				draw_2(t_cub3d *t)
{
	while (t->rc->hit == 0)
	{
		if (t->rc->sidedistx < t->rc->sidedisty)
		{
			t->rc->sidedistx += t->rc->deltadistx;
			t->rc->mapx += t->rc->stepx;
			t->rc->side = 0;
		}
		else
		{
			t->rc->sidedisty += t->rc->deltadisty;
			t->rc->mapy += t->rc->stepy;
			t->rc->side = 1;
		}
		if (t->map->map[t->rc->mapx][t->rc->mapy] == 1)
			t->rc->hit = 1;
	}
	return (1);
}

void			draw_1(t_cub3d *t)
{
	t->rc->camerax = 2 * t->x / (double)t->width - 1;
	t->rc->raydirx = t->rc->dirx + t->rc->planex * t->rc->camerax;
	t->rc->raydiry = t->rc->diry + t->rc->planey * t->rc->camerax;
	t->rc->mapx = (int)(t->rc->posx);
	t->rc->mapy = (int)(t->rc->posy);
	set_deltadist(t);
	t->rc->hit = 0;
	if (t->rc->raydirx < 0 && (t->rc->stepx = -1))
		t->rc->sidedistx = (t->rc->posx - t->rc->mapx) * t->rc->deltadistx;
	else if (t->rc->raydirx >= 0 && (t->rc->stepx = 1))
		t->rc->sidedistx = (t->rc->mapx + 1.0 - t->rc->posx) *
			t->rc->deltadistx;
	if (t->rc->raydiry < 0 && (t->rc->stepy = -1))
		t->rc->sidedisty = (t->rc->posy - t->rc->mapy) * t->rc->deltadisty;
	else if (t->rc->raydiry >= 0 && (t->rc->stepy = 1))
		t->rc->sidedisty = (t->rc->mapy + 1.0 - t->rc->posy) *
			t->rc->deltadisty;
}

void			draw(t_cub3d *t)
{
	t->x = -1;
	t->screen->img = mlx_new_image(t->mlx, t->width, t->height);
	t->screen->data = (int *)mlx_get_data_addr(t->screen->img,
			&t->screen->bpp, &t->screen->size_line, &t->screen->endian);
	if (!(t->rc->zbuffer = (double *)malloc(sizeof(double) * t->width)))
		exitprogram(MALLOC_ERROR);
	while (++t->x < t->width)
	{
		draw_1(t);
		draw_2(t);
		draw_3(t);
		draw_screen(t);
	}
	draw_item(t);
	if (t->save == true)
		save_exit(t, t->screen);
	mlx_put_image_to_window(t->mlx, t->win, t->screen->img, 0, 0);
	mlx_destroy_image(t->mlx, t->screen->img);
	free(t->rc->zbuffer);
}
