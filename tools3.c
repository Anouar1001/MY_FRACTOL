/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:32:39 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/01/22 16:27:27 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	scale(double new_max, double new_min, double num, double old_max)
{
	return (((new_max - new_min) * num / old_max) + new_min);
}

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	draw_mandelbrot(t_dagoat *data)
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
			iter = mandelbrot(o);
			color = color_map(iter, data->data_color);
			my_mlx_pixel_put(&data->image, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	return (0);
}

int	key_hook(int keycode, t_dagoat *data)
{
	if (keycode == ESCAPE_KEY)
	{
		mlc_cldes(data);
		exit(0);
	}
	if (keycode == LEFT_ARROW)
		data->shiftx -= 0.1 * data->zoom;
	if (keycode == RIGHT_ARROW)
		data->shiftx += 0.1 * data->zoom;
	if (keycode == UP_ARROW)
		data->shifty += 0.1 * data->zoom;
	if (keycode == DOWN_ARROW)
		data->shifty -= 0.1 * data->zoom;
	if (keycode == ESPACE_KEY)
		data->data_color += 12;
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_dagoat *data)
{
	double	mouse_re;
	double	mouse_im;

	mouse_re = (scale(2.0, -2.0, x, WIDTH) * data->zoom) + data->shiftx;
	mouse_im = (scale(-2.0, 2.0, y, HEIGHT) * data->zoom) + data->shifty;
	if (keycode == 5)
	{
		data->zoom *= 0.95;
		data->shiftx += (mouse_re - data->shiftx) * 0.05;
		data->shifty += (mouse_im - data->shifty) * 0.05;
	}
	else if (keycode == 4)
	{
		data->zoom *= 1.05;
		data->shiftx += (mouse_re - data->shiftx) * 0.05;
		data->shifty += (mouse_im - data->shifty) * 0.05;
	}
	return (1);
}
