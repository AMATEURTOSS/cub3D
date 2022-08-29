/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 01:58:23 by yochoi            #+#    #+#             */
/*   Updated: 2020/06/12 15:45:20 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"

# define MAX_WIDTH		1920
# define MAX_HEIGHT		1080
# define MIN_WIDTH		192
# define MIN_HEIGHT		108

# define _KEY_PRESS		2
# define _KEY_EXIT		17

# define UP				126
# define LEFT			123
# define RIGHT			124
# define DOWN			125
# define W				13
# define A				0
# define D				0
# define S				1
# define ESC			53

# define TERMINATE		0
# define ARGV_ERROR		1
# define MALLOC_ERROR	2
# define MAP_ERROR		3
# define TEXTURE_ERROR	4
# define SAVE_ERROR		5

# define EMPTY_SPACE	0
# define WALL			1
# define SPRITE			2
# define OUTSIDE		3

typedef struct		s_sp
{
	double			x;
	double			y;
	double			distance;
}					t_sp;

typedef struct		s_item_draw
{
	double			spritex;
	double			spritey;
	double			invdet;
	double			transformx;
	double			transformy;
	int				spritescreenx;
	int				spriteheight;
	int				drawstarty;
	int				drawendy;
	int				spritewidth;
	int				drawstartx;
	int				drawendx;
	int				texx;
	int				d;
	int				texy;
	int				stripe;
}					t_id;

typedef struct		s_img
{
	void			*img;
	char			*file;
	int				width;
	int				height;
	int				bpp;
	int				size_line;
	int				endian;
	int				*data;
}					t_img;

typedef struct		s_map
{
	char			*map_name;
	int				**map;
	int				map_max;
	int				mapheight;
	int				item_count;
	int				floor;
	int				ceiling;
	int				playerx;
	int				playery;
	char			start_dir;
}					t_map;

typedef struct		s_raycasting
{
	double			posx;
	double			posy;
	int				mapx;
	int				mapy;
	int				stepx;
	int				stepy;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	double			perpwalldist;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	double			time;
	double			oldtime;
	double			camerax;
	double			raydirx;
	double			raydiry;
	int				lineheight;
	int				drawstart;
	int				drawend;
	double			movespeed;
	double			rotspeed;
	bool			hit;
	bool			side;
	double			wallx;
	int				texx;
	int				texy;
	double			step;
	double			texpos;
	double			oldplanex;
	double			olddirx;
	double			*zbuffer;
}					t_rc;

typedef struct		s_cub3d
{
	int				keycode;
	int				x;
	void			*mlx;
	void			*win;
	int				width;
	int				height;
	bool			save;
	t_map			*map;
	t_rc			*rc;
	t_img			*screen;
	t_img			*no;
	t_img			*we;
	t_img			*ea;
	t_img			*so;
	t_img			*sp;
	t_sp			*item;
	t_sp			*sorted_item;
}					t_cub3d;

/*
** exit.c
*/

int					exitprogram(int num);
void				save_exit(t_cub3d *t, t_img *img);

/*
** parser.c
*/

int					parser_param(int argc, char **argv, t_cub3d *t);
void				parser(int fd, t_cub3d *t);

/*
** get_map.c
*/

void				get_map(t_cub3d *t);

/*
** get_info.c
*/

void				map_info(t_cub3d *t, char *line);
void				size_check(t_cub3d *t);
void				render_size(t_cub3d *t, char *line);
void				texture_name(t_cub3d *t, char *line);
void				get_floor_celling(t_cub3d *t, char *line);

/*
** is_valid.c
*/

void				is_valid(t_cub3d *t);

/*
** engine_render.c
*/

void				render(t_cub3d *t);

/*
** engine_draw.c
*/

void				draw(t_cub3d *t);

/*
** engine_pos_view.c
*/

void				move_pos_view(t_cub3d *t);

/*
** engine_draw_screen.c
*/

void				draw_screen(t_cub3d *t);

/*
** engine_draw_item.c
*/

void				draw_item(t_cub3d *t);
#endif
