/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 12:31:48 by yochoi            #+#    #+#             */
/*   Updated: 2020/06/12 15:29:54 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void		check_north_wall(t_cub3d *t)
{
	int i;
	int tmp;

	i = -1;
	while (++i < t->map->map_max)
	{
		tmp = 0;
		if (t->map->map[0][i] == WALL)
			continue ;
		else if (t->map->map[0][i] == OUTSIDE)
		{
			while (t->map->map[0 + tmp][i] == OUTSIDE)
				tmp++;
			if (t->map->map[0 + tmp][i] == WALL)
				continue ;
			else
				exitprogram(MAP_ERROR);
		}
		else
			exitprogram(MAP_ERROR);
	}
}

void		check_south_wall(t_cub3d *t)
{
	int i;
	int tmp;

	i = -1;
	while (++i < t->map->map_max - 1)
	{
		tmp = 0;
		if (t->map->map[t->map->mapheight][i] == WALL)
			continue ;
		else if (t->map->map[t->map->mapheight][i] == OUTSIDE)
		{
			while (t->map->map[t->map->mapheight - tmp][i] == OUTSIDE)
				tmp++;
			if (t->map->map[t->map->mapheight - tmp][i] == WALL)
				continue ;
			else
				exitprogram(MAP_ERROR);
		}
		else
			exitprogram(MAP_ERROR);
	}
}

void		check_west_wall(t_cub3d *t)
{
	int i;
	int tmp;

	i = -1;
	while (++i < t->map->mapheight)
	{
		tmp = 0;
		if (t->map->map[i][0] == WALL)
			continue ;
		else if (t->map->map[i][0] == OUTSIDE)
		{
			while (t->map->map[i][0 + tmp] == OUTSIDE)
				tmp++;
			if (t->map->map[i][0 + tmp] == WALL)
				continue ;
			else
				exitprogram(MAP_ERROR);
		}
		else
			exitprogram(MAP_ERROR);
	}
}

void		check_east_wall(t_cub3d *t)
{
	int i;
	int tmp;

	i = -1;
	while (++i < t->map->mapheight)
	{
		tmp = 0;
		if (t->map->map[i][t->map->map_max - 1] == WALL)
			continue ;
		else if (t->map->map[i][t->map->map_max - 1] == OUTSIDE)
		{
			while (t->map->map[i][t->map->map_max - tmp - 1] == OUTSIDE)
				tmp++;
			if (t->map->map[i][t->map->map_max - tmp - 1] == WALL)
				continue ;
			else
				exitprogram(MAP_ERROR);
		}
		else
			exitprogram(MAP_ERROR);
	}
}

void		is_valid(t_cub3d *t)
{
	check_east_wall(t);
	check_west_wall(t);
	check_north_wall(t);
	check_south_wall(t);
}
