/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:40:51 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/01/26 13:30:09 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	is_valid_args(int ac, char **v)
{
	if (ac < 2 || ac > 4)
		return (0);
	if (ft_strcmp(v[1], "mandelbrot") != 0 && ft_strcmp(v[1], "julia") != 0
		&& ft_strcmp(v[1], "tricorn") != 0)
		return (0);
	if (ft_strcmp (v[1], "julia") == 0 && ac != 4)
		return (0);
	if ((ft_strcmp(v[1], "mandelbrot") == 0
			|| ft_strcmp(v[1], "tricorn") == 0) && ac != 2)
		return (0);
	return (1);
}

void	put_mandelbrot(t_dagoat *data)
{
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Mandelbrot Set");
	data->image.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->image.img == NULL)
	{
		perror("Error creating image");
		exit(1);
	}
	data->image.addr = mlx_get_data_addr(data->image.img,
			&data->image.bits_per_pixel,
			&data->image.line_length, &data->image.endian);
	draw_mandelbrot(data);
	mlx_mouse_hook(data->win, mouse_hook, data);
	mlx_loop_hook(data->mlx, draw_mandelbrot, data);
}

void	put_julia(t_dagoat *data, char *s1, char *s2)
{
	data->i.re = ft_atodd(s1);
	data->i.ig = ft_atodd(s2);
	if ((data->i.re > INT_MAX || data->i.re < INT_MIN)
		&& (data->i.ig > INT_MAX || data->i.ig < INT_MIN))
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		write(2, "error", 6);
		exit(0);
	}
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Julia Set");
	data->image.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->image.img == NULL)
	{
		perror("Error creating image");
		exit(1);
	}
	data->image.addr = mlx_get_data_addr(data->image.img,
			&data->image.bits_per_pixel,
			&data->image.line_length, &data->image.endian);
	mlx_loop_hook(data->mlx, draw_julia, data);
	mlx_mouse_hook(data->win, mouse_hook, data);
}

int	main(int ac, char **argv)
{
	t_dagoat	data;

	if (!is_valid_args(ac, argv) || (ft_strcmp("julia", argv[1]) == 0
			&& (ft_isvalide(argv[2]) == 0 || ft_isvalide(argv[3]) == 0)))
		show_error();
	if (ft_strcmp(argv[1], "julia") == 1)
	{
		ft_atodd(argv[2]);
		ft_atodd(argv[3]);
	}
	data.mlx = mlx_init();
	data.zoom = 1;
	data.shiftx = 0.0;
	data.shifty = 0.0;
	data.data_color = 0;
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
		put_mandelbrot(&data);
	else if (ft_strcmp(argv[1], "julia") == 0)
		put_julia(&data, argv[2], argv[3]);
	else
		put_tricorn(&data);
	mlx_hook(data.win, 17, 0, mlc_cldes, &data);
	mlx_mouse_hook(data.win, mouse_hook, &data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_loop(data.mlx);
}
