/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 00:06:44 by yochoi            #+#    #+#             */
/*   Updated: 2020/06/09 19:25:23 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		exitprogram(int num)
{
	if (num == TERMINATE)
	{
		ft_printf("cub3d: Terminated normally\n");
		exit(0);
	}
	if (num == ARGV_ERROR)
	{
		ft_printf("cub3d: ARGV_ERROR\nexample:\n");
		ft_printf("        %s\n", "./cub3d map0");
		ft_printf("        %s\n", "./cub3d map0 --save");
	}
	if (num == MALLOC_ERROR)
		ft_printf("cub3d: MALLOC_ERROR\n");
	if (num == MAP_ERROR)
		ft_printf("cub3d: MAP_ERROR\n");
	if (num == TEXTURE_ERROR)
		ft_printf("cub3d: TEXTURE_ERROR\n");
	if (num == SAVE_ERROR)
		ft_printf("cub3d: SAVE_ERROR\n");
	exit(-1);
	return (0);
}

void			bmp_header(int fd, t_cub3d *t, int file_size)
{
	char		header[54];
	int			height;

	ft_bzero(header, 54);
	ft_memcpy(header, "BM", 2);
	ft_memcpy(header + 2, &file_size, 4);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	ft_memcpy(header + 18, &t->width, 4);
	ft_memcpy(header + 22, &t->height, 4);
	height = -t->height;
	header[22] = (unsigned char)(height);
	header[23] = (unsigned char)(height >> 8);
	header[25] = (unsigned char)(height >> 16);
	header[24] = (unsigned char)(height >> 24);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(32);
	write(fd, header, 54);
}

void			save_exit(t_cub3d *t, t_img *img)
{
	int			fd;
	int			file_size;

	if ((fd = open("saved", O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		exitprogram(SAVE_ERROR);
	file_size = 14 + 40 + t->width * t->height * 4;
	bmp_header(fd, t, file_size);
	write(fd, img->data, (t->width * t->height * 4));
	close(fd);
	exit(0);
}
