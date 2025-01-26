/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:23:12 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/01/24 15:34:49 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define MAX_ITER 120
# define WIDTH 800
# define HEIGHT 800
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define ESCAPE_KEY 65307
# define ESPACE_KEY 32
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "minilibx-linux/mlx.h"

typedef struct s_cmplx
{
	double	re;
	double	ig;
}	t_cplx;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_dagoat
{
	void	*mlx;
	void	*win;
	double	shiftx;
	double	shifty;
	double	zoom;
	t_data	image;
	t_cplx	i;
	int		data_color;
}	t_dagoat;

int			mandelbrot(t_cplx cst);

int			color_map(int iter, int i);

double		scale(double new_max, double new_min, double num, double old_max);

void		my_mlx_pixel_put(t_data *img, int x, int y, int color);

int			julia_set(t_cplx i, t_cplx cst);

int			draw_julia(t_dagoat *data);

double		scale(double new_max, double new_min, double num, double old_max);

void		my_mlx_pixel_put(t_data *img, int x, int y, int color);

int			draw_mandelbrot(t_dagoat *data);

int			key_hook(int keycode, t_dagoat *data);

int			mouse_hook(int keycode, int x, int y, t_dagoat *data);

int			ft_isvalide(char *str);

int			mlc_cldes(t_dagoat *data);

double		ft_atodd(char *str);

void		put_tricorn(t_dagoat *data);

int			draw_tricorn(t_dagoat *data);

int			tricorn_set(t_cplx i);

void		show_error(void);

#endif