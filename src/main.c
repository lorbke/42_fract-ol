/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:25:35 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/24 00:12:15 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// use linker command (more performance because smaller binary)
// check opengl path in makefile

void	ps_print_error(void)
{
	write(2, "Input error!\n\n", 14);
	write(1, "You have to specify what fractal you want to display.\n", 54);
	write(1, "Fractals you can render are:\n", 30);
	write(1, "\t-Mandelbrot\n", 14);
	write(1, "\t-Julia (real) (imaginary) | e.g. -0.744 -0.148\n", 49);
	write(1, "\t-Tricorn\n", 10);
	exit(EXIT_FAILURE);
}

int	data_init(t_data *data)
{
	data->max_iter = 100;
	data->scale = 4;
	data->xoffset = 0;
	data->yoffset = 0;
	data->shift = 0;
	data->palette = &wiki_palette;
	data->mlx = mlx_init(WIDTH, HEIGHT, "fract-ol", false);
	if (!data->mlx)
		return (0);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->mlx)
		return (0);
	return (1);
}

void	parse(int argc, char *argv[], t_data *data)
{
	if (argc == 2 && ft_strlen(argv[1]) <= 10
		&& !ft_strncmp(argv[1], "Mandelbrot", 10))
		data->fract = &mandelbrot;
	else if (argc == 4 && ft_isnum(argv[2]) && ft_isnum(argv[3])
		&& ft_strlen(argv[1]) <= 5 && !ft_strncmp(argv[1], "Julia", 5))
	{
		data->fract = &julia;
		data->cx = ft_atof(argv[2]);
		data->cy = ft_atof(argv[3]);
	}
	else if (argc == 2 && ft_strlen(argv[1]) <= 7
		&& !ft_strncmp(argv[1], "Tricorn", 7))
		data->fract = &tricorn;
	else
		ps_print_error();
}

void	draw_fract(t_data *data)
{
	int		x;
	int		y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			mlx_put_pixel(data->img, x, y, convert_to_color
				(data->fract(x, y, data),
					data->max_iter, data->shift, data->palette));
			y++;
		}
		x++;
	}
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 2)
		ps_print_error();
	parse(argc, argv, &data);
	if (!data_init(&data))
	{
		write(1, "mlx error\n", 10);
		return (0);
	}
	mlx_loop_hook(data.mlx, &key_hook, &data);
	mlx_scroll_hook(data.mlx, &zoom_hook, &data);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
