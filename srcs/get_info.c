/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 07:04:21 by yochoi            #+#    #+#             */
/*   Updated: 2020/06/10 16:40:38 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		map_info(t_cub3d *t, char *line)
{
	int			i;
	int			len;

	i = -1;
	len = ft_strlen(line);
	while (++i < len)
	{
		if (!ft_strchr(" 012NWES", line[i]))
			exitprogram(MAP_ERROR);
		if (line[i] == '2')
			t->map->item_count++;
	}
	if (t->map->map_max < len)
		t->map->map_max = len;
	t->map->mapheight += 1;
	free(line);
}

void		size_check(t_cub3d *t)
{
	if (t->width > MAX_WIDTH)
		t->width = MAX_WIDTH;
	else if (t->width < MIN_WIDTH)
		t->width = MIN_WIDTH;
	if (t->height > MAX_HEIGHT)
		t->height = MAX_HEIGHT;
	else if (t->height < MIN_HEIGHT)
		t->height = MIN_HEIGHT;
}

void		render_size(t_cub3d *t, char *line)
{
	char		**split;

	split = ft_split(line, ' ');
	if (ft_split_len(split) != 3)
		exitprogram(MAP_ERROR);
	t->width = ft_atoi(split[1]);
	t->height = ft_atoi(split[2]);
	size_check(t);
	ft_split_del(split);
	free(line);
}

void		texture_name(t_cub3d *t, char *line)
{
	int			fd;
	char		**split;

	split = ft_split(line, ' ');
	if (ft_split_len(split) != 2)
		exitprogram(MAP_ERROR);
	if (!(ft_strncmp(split[0], "NO", 2)))
		t->no->file = ft_strdup(split[1]);
	else if (!(ft_strncmp(split[0], "SO", 2)))
		t->so->file = ft_strdup(split[1]);
	else if (!(ft_strncmp(split[0], "WE", 2)))
		t->we->file = ft_strdup(split[1]);
	else if (!(ft_strncmp(split[0], "EA", 2)))
		t->ea->file = ft_strdup(split[1]);
	else if (!(ft_strncmp(split[0], "S", 1)))
		t->sp->file = ft_strdup(split[1]);
	if ((fd = open(split[1], 0)) < 0)
		exitprogram(TEXTURE_ERROR);
	ft_split_del(split);
	free(line);
}

void		get_floor_celling(t_cub3d *t, char *line)
{
	char		**split;
	char		**color;
	int			rgb;
	int			i;

	split = ft_split(line, ' ');
	color = ft_split(split[1], ',');
	if (ft_split_len(split) != 2 || ft_split_len(color) != 3)
		exitprogram(MAP_ERROR);
	i = -1;
	rgb = 0;
	while (color[++i])
	{
		rgb = rgb << 8;
		rgb += ft_atoi(color[i]);
	}
	if (!(ft_strncmp(split[0], "F", 1)))
		t->map->floor = rgb;
	else
		t->map->ceiling = rgb;
	ft_split_del(split);
	ft_split_del(color);
	free(line);
}
