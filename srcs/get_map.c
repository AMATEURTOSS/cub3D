/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 07:09:33 by yochoi            #+#    #+#             */
/*   Updated: 2020/06/12 14:25:13 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_check(t_cub3d *t, int x, int y, char dir)
{
	t->map->map[x][y] = 0;
	t->map->playerx = x;
	t->map->playery = y;
	t->map->start_dir = dir;
}

void	item_location(t_cub3d *t, int x, int y, int *count)
{
	t->item[*count].x = x;
	t->item[*count].y = y;
	t->map->map[x][y] = SPRITE;
	*count += 1;
}

void	map_copy(t_cub3d *t, char *line, int x)
{
	int y;
	int len;
	int item_num;

	y = -1;
	len = ft_strlen(line);
	item_num = 0;
	if (!(t->map->map[x] = (int *)malloc(sizeof(int) * (t->map->map_max))))
		exitprogram(MALLOC_ERROR);
	while (++y < t->map->map_max)
	{
		if (y < len)
		{
			if (line[y] == '1' || line[y] == '0')
				t->map->map[x][y] = (line[y] == '0') ? EMPTY_SPACE : WALL;
			else if (line[y] == ' ')
				t->map->map[x][y] = OUTSIDE;
			else if (line[y] == 'N' || line[y] == 'W'
			|| line[y] == 'S' || line[y] == 'E')
				player_check(t, x, y, line[y]);
			else if (line[y] == '2')
				item_location(t, x, y, &item_num);
		}
		else
			t->map->map[x][y] = OUTSIDE;
	}
}

void	get_map(t_cub3d *t)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open(t->map->map_name, 0);
	ft_strdel(&t->map->map_name);
	t->map->map = (int **)malloc(sizeof(int *) * (t->map->mapheight));
	while (get_next_line(fd, &line))
	{
		if (!(ft_strncmp("R", line, 1)) || !(ft_strncmp("NO", line, 2))
		|| !(ft_strncmp("SO", line, 2)) || !(ft_strncmp("WE", line, 2))
		|| !(ft_strncmp("EA", line, 2)) || !(ft_strncmp("", line, 1)))
			ft_strdel(&line);
		else if (!(ft_strncmp("S", line, 1))
		|| !(ft_strncmp("F", line, 1)) || !(ft_strncmp("C", line, 1)))
			ft_strdel(&line);
		else
		{
			map_copy(t, line, i++);
			ft_strdel(&line);
		}
	}
	map_copy(t, line, i);
	ft_strdel(&line);
}
