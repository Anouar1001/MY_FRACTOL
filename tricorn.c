/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:42:23 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/01/24 14:29:54 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	tricorn_set(t_cplx i)
{
	t_cplx	z;
	double	tmp;
	int		j;

	j = 0;
	z.ig = 0.0;
	z.re = 0.0;
	while (z.ig * z.ig + z.re * z.re < 4.0 && j < MAX_ITER)
	{
		tmp = z.re * z.re - z.ig * z.ig + i.re;
		z.ig = -2 * z.re * z.ig + i.ig;
		z.re = tmp;
		j++;
	}
	return (j);
}

int	draw_tricorn(t_dagoat *data)
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
			iter = tricorn_set(o);
			color = color_map(iter, data->data_color);
			my_mlx_pixel_put(&data->image, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	return (0);
}

void	put_tricorn(t_dagoat *data)
{
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "TRICORN SET");
	data->image.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->image.img == NULL)
	{
		perror("Error creating image");
		exit(1);
	}
	data->image.addr = mlx_get_data_addr(data->image.img,
			&data->image.bits_per_pixel,
			&data->image.line_length, &data->image.endian);
	draw_tricorn(data);
	mlx_mouse_hook(data->win, mouse_hook, data);
	mlx_loop_hook(data->mlx, draw_tricorn, data);
}

void	show_error(void)
{
	write(1, "INVALID INPUT\n", 14);
	write(1, "valide parameters :\n", 22);
	write(1, "-mandelbrot\n-julia\n-tricorn\n", 29);
	exit(0);
}
