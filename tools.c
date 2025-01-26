/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:59:42 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/01/24 14:20:58 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	color_map(int iter, int i)
{
	int	r;
	int	g;
	int	b;

	if (iter == MAX_ITER)
		return (0x00000000);
	r = (iter * (3 + i));
	g = (iter * (5 + i));
	b = (iter * (11 + i));
	return ((r << 16) | (g << 8) | b);
}

int	mandelbrot(t_cplx cst)
{
	t_cplx	i;
	double	tmp;
	int		j;

	j = 0;
	i.re = 0.0;
	i.ig = 0.0;
	while (i.re * i.re + i.ig * i.ig < 4.0 && j < MAX_ITER)
	{
		tmp = i.re * i.re - i.ig * i.ig + cst.re;
		i.ig = 2 * i.ig * i.re + cst.ig;
		i.re = tmp;
		j++;
	}
	return (j);
}

int	julia_set(t_cplx i, t_cplx cst)
{
	double	tmp;
	int		j;

	j = 0;
	while ((i.re * i.re + i.ig * i.ig) < 4.0 && j < MAX_ITER)
	{
		tmp = i.re * i.re - i.ig * i.ig + cst.re;
		i.ig = 2 * i.ig * i.re + cst.ig;
		i.re = tmp;
		j++;
	}
	return (j);
}

int	draw_julia(t_dagoat *data)
{
	t_cplx	o;
	int		x;
	int		y;
	int		iter;
	int		color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			o.re = (scale(2.0, -2.0, x, WIDTH) * data->zoom) + data->shiftx;
			o.ig = (scale(-2.0, 2.0, y, HEIGHT) * data->zoom) + data->shifty;
			iter = julia_set(o, data->i);
			color = color_map(iter, data->data_color);
			my_mlx_pixel_put(&data->image, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	return (0);
}

int	mlc_cldes(t_dagoat *data)
{
	mlx_destroy_image(data->mlx, data->image.img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}
