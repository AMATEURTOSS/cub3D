/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 22:33:46 by yochoi            #+#    #+#             */
/*   Updated: 2020/06/12 15:38:03 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parser_param(int argc, char **argv, t_cub3d *t)
{
	int		fd;
	char	*file_name;

	if (argc != 2 && argc != 3)
		exitprogram(ARGV_ERROR);
	file_name = ft_strjoin(argv[1], ".cub");
	t->map->map_name = ft_strdup(file_name);
	if ((fd = open(file_name, 0x00)) <= 0)
		exitprogram(ARGV_ERROR);
	if (argc == 3 && (ft_strncmp(argv[2], "--save", 6)))
		exitprogram(ARGV_ERROR);
	if (argc == 3)
		t->save = true;
	ft_strdel(&file_name);
	return (fd);
}

void	parser(int fd, t_cub3d *t)
{
	char *line;

	while (get_next_line(fd, &line))
	{
		if (!(ft_strncmp("NO", line, 2)) || !(ft_strncmp("SO", line, 2)) ||
			(!(ft_strncmp("WE", line, 2)) || !(ft_strncmp("EA", line, 2))) ||
			(!(ft_strncmp("S ", line, 2))))
			texture_name(t, line);
		else if (!(ft_strncmp("R", line, 1)))
			render_size(t, line);
		else if (!(ft_strncmp("F", line, 1)) || !(ft_strncmp("C", line, 1)))
			get_floor_celling(t, line);
		else if (ft_strlen(line))
			map_info(t, line);
		else
			ft_strdel(&line);
	}
	ft_strdel(&line);
	close(fd);
	if (!(t->item = (t_sp *)malloc(sizeof(t_sp) * t->map->item_count + 1)))
		exitprogram(MALLOC_ERROR);
}
