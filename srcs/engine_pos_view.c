/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_pos_view.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 23:07:28 by yochoi            #+#    #+#             */
/*   Updated: 2020/06/10 16:23:22 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int					newpos(t_cub3d *t)
{
	if (t->keycode == W)
	{
		t->rc->posx = t->rc->posx +
			t->rc->dirx * t->rc->movespeed;
		t->rc->posy = t->rc->posy +
			t->rc->diry * t->rc->movespeed;
	}
	else
	{
		t->rc->posx = t->rc->posx -
			t->rc->dirx * t->rc->movespeed;
		t->rc->posy = t->rc->posy -
			t->rc->diry * t->rc->movespeed;
	}
	return (1);
}

int					is_wall(t_cub3d *t)
{
	int				newx;
	int				newy;

	if (t->keycode == W)
	{
		newx = (int)(t->rc->posx +
				t->rc->dirx * t->rc->movespeed);
		newy = (int)(t->rc->posy +
				t->rc->diry * t->rc->movespeed);
	}
	else
	{
		newx = (int)(t->rc->posx -
				t->rc->dirx * t->rc->movespeed);
		newy = (int)(t->rc->posy -
				t->rc->dirx * t->rc->movespeed);
	}
	if (t->map->map[newx][newy] != 0)
		return (0);
	newpos(t);
	return (1);
}

int					change_view_right(t_cub3d *t)
{
	t->rc->olddirx = t->rc->dirx;
	t->rc->dirx = t->rc->dirx * cos(-t->rc->rotspeed)
					- t->rc->diry * sin(-t->rc->rotspeed);
	t->rc->diry = t->rc->olddirx * sin(-t->rc->rotspeed)
					+ t->rc->diry * cos(-t->rc->rotspeed);
	t->rc->oldplanex = t->rc->planex;
	t->rc->planex = t->rc->planex * cos(-t->rc->rotspeed)
					- t->rc->planey * sin(-t->rc->rotspeed);
	t->rc->planey = t->rc->oldplanex * sin(-t->rc->rotspeed)
					+ t->rc->planey * cos(-t->rc->rotspeed);
	return (0);
}

int					change_view_left(t_cub3d *t)
{
	t->rc->olddirx = t->rc->dirx;
	t->rc->dirx = t->rc->dirx * cos(t->rc->rotspeed)
					- t->rc->diry * sin(t->rc->rotspeed);
	t->rc->diry = t->rc->olddirx * sin(t->rc->rotspeed)
					+ t->rc->diry * cos(t->rc->rotspeed);
	t->rc->oldplanex = t->rc->planex;
	t->rc->planex = t->rc->planex * cos(t->rc->rotspeed)
					- t->rc->planey * sin(t->rc->rotspeed);
	t->rc->planey = t->rc->oldplanex * sin(t->rc->rotspeed)
					+ t->rc->planey * cos(t->rc->rotspeed);
	return (0);
}

void				move_pos_view(t_cub3d *t)
{
	if (t->keycode == W || t->keycode == S)
		is_wall(t);
	else if (t->keycode == RIGHT)
		change_view_right(t);
	else if (t->keycode == LEFT)
		change_view_left(t);
}
