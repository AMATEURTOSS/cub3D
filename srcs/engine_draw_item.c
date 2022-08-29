/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_draw_item.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 14:33:27 by yochoi            #+#    #+#             */
/*   Updated: 2020/06/12 22:10:59 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_item(t_cub3d *t)
{
	int				i;
	int				j;
	t_sp			temp;
	t_sp			*it;

	it = t->item;
	i = -1;
	while (++i < t->map->item_count - 1)
	{
		j = -1;
		while (++j < t->map->item_count - 1 - i)
		{
			if (it[j].distance < it[j + 1].distance)
			{
				ft_memmove(&temp, &t->item[j], sizeof(t_sp));
				ft_memmove(&t->item[j], &t->item[j + 1], sizeof(t_sp));
				ft_memmove(&t->item[j + 1], &temp, sizeof(t_sp));
			}
		}
	}
}

void	get_distance_sort(t_cub3d *t)
{
	int				i;

	i = -1;
	while (++i < t->map->item_count)
	{
		t->item[i].distance = (t->rc->posx - t->item[i].x) *
			(t->rc->posx - t->item[i].x)
			+ ((t->rc->posy - t->item[i].y)
					* (t->rc->posy - t->item[i].y));
	}
	sort_item(t);
}

void	calculate_item(t_id *id, t_sp *it, t_cub3d *t)
{
	id->spritex = it->x - t->rc->posx;
	id->spritey = it->y - t->rc->posy;
	id->invdet = 1.0 / (t->rc->planex * t->rc->diry - t->rc->dirx * t->rc->planey);
	id->transformx = id->invdet * (t->rc->diry * id->spritex - t->rc->dirx
			* id->spritey);
	id->transformy = id->invdet * (-t->rc->planey * id->spritex + t->rc->planex
			* id->spritey);
	id->spritescreenx = (int)((t->width / 2) * (1 + id->transformx
				/ id->transformy));
	id->spriteheight = abs((int)((double)t->height / id->transformy));
	id->drawstarty = -id->spriteheight / 2 + t->height / 2;
	if (id->drawstarty < 0)
		id->drawstarty = 0;
	id->drawendy = id->spriteheight / 2 + t->height / 2;
	if (id->drawendy >= t->height)
		id->drawendy = t->height - 1;
	id->spritewidth = abs((int)(t->height / id->transformy));
	id->drawstartx = -id->spritewidth / 2 + id->spritescreenx;
	if (id->drawstartx < 0)
		id->drawstartx = 0;
	id->drawendx = id->spritewidth / 2 + id->spritescreenx;
	if (id->drawendx >= t->width)
		id->drawendx = t->width - 1;
}

void	draw_item2(t_id *id, t_cub3d *t)
{
	int				y;
	t_img			*item;

	item = t->sp;
	id->texx = (int)(256 * (id->stripe - (-id->spritewidth / 2 +
		id->spritescreenx)) * item->width / id->spritewidth) / 256;
	if (id->transformy > 0 && id->stripe > 0 && id->stripe < t->width
			&& id->transformy < t->rc->zbuffer[id->stripe])
	{
		y = id->drawstarty - 1;
		while (++y < id->drawendy)
		{
			id->d = y * 256 - t->height * 128 + id->spriteheight * 128;
			id->texy = ((id->d * item->height) / id->spriteheight) / 256;
			if ((item->data[item->height * id->texy + id->texx] &
						0xffffff) != 0)
				t->screen->data[y * t->width + id->stripe] =
					item->data[item->height * id->texy + id->texx];
		}
	}
}

void	draw_item(t_cub3d *t)
{
	int				i;
	t_id			id;
	t_sp			*it;

	get_distance_sort(t);
	it = t->item;
	i = -1;
	t->sp->data = (int *)mlx_get_data_addr(t->sp->img, &t->sp->bpp,
			&t->sp->size_line, &t->sp->endian);
	while (++i < t->map->item_count)
	{
		calculate_item(&id, &t->item[i], t);
		id.stripe = id.drawstartx - 1;
		while (++id.stripe < id.drawendx)
			draw_item2(&id, t);
	}
}
