/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_draw_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 21:08:42 by yochoi            #+#    #+#             */
/*   Updated: 2020/06/10 16:06:26 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			before_verline(t_cub3d *t, t_img *text)
{
	if (t->rc->side == 0)
		t->rc->wallx = t->rc->posy + t->rc->perpwalldist * t->rc->raydiry;
	else
		t->rc->wallx = t->rc->posx + t->rc->perpwalldist * t->rc->raydirx;
	t->rc->wallx -= floor(t->rc->wallx);
	t->rc->texx = (int)(t->rc->wallx * (double)text->width);
	if (t->rc->side == 0 && t->rc->raydirx > 0)
		t->rc->texx = text->width - t->rc->texx - 1;
	if (t->rc->side == 1 && t->rc->raydiry < 0)
		t->rc->texx = text->width - t->rc->texx - 1;
	t->rc->step = 1.0 * text->height / t->rc->lineheight;
	t->rc->texpos = (t->rc->drawstart - (double)t->height / 2
			+ t->rc->lineheight / 2) * t->rc->step;
}

void			verline(t_cub3d *t, int *data, t_img *text)
{
	int			bottom;
	int			color;

	before_verline(t, text);
	bottom = -1;
	while (++bottom <= t->height)
	{
		if (bottom < t->rc->drawstart)
			data[bottom * t->width + t->x] = t->map->ceiling;
		else if (bottom < t->rc->drawend)
		{
			t->rc->texy = (int)t->rc->texpos;
			t->rc->texpos += t->rc->step;
			color = text->data[text->width * t->rc->texy + t->rc->texx];
			data[bottom * t->width + t->x] = color;
		}
		else
			data[bottom * t->width + t->x] = t->map->floor;
	}
}

void			draw_screen(t_cub3d *t)
{
	t_img		*text;

	if (t->rc->side == 1)
	{
		if ((t->rc->raydirx <= 0 && t->rc->raydiry <= 0) ||
				(t->rc->raydirx >= 0 && t->rc->raydiry <= 0))
			text = t->ea;
		else
			text = t->we;
	}
	else
	{
		if ((t->rc->raydirx <= 0 && t->rc->raydiry <= 0) ||
				(t->rc->raydirx <= 0 && t->rc->raydiry >= 0))
			text = t->so;
		else
			text = t->no;
	}
	text->data = (int *)mlx_get_data_addr(text->img, &text->bpp,
			&text->size_line, &text->endian);
	verline(t, t->screen->data, text);
}
