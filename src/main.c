/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:25:35 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/23 23:13:47 by lorbke           ###   ########.fr       */
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
	write(1, "\t- Mandelbrot\n", 15);
	write(1, "\t- Julia (real) (imaginary) | e.g. -0.744 -0.148\n", 50);
	write(1, "\t- Tricorn\n", 11);
	exit(EXIT_FAILURE);
}

static float	get_convmouse_x(t_data *data)
{
	int		temp;
	int		temp2;
	float	x;

	mlx_get_mouse_pos(data->mlx, &temp, &temp2);
	x = (float)temp;
	x = x / (double) data->width;
	x *= data->scale;
	x += -(data->scale / 2);
	return (x);
}

static float	get_convmouse_y(t_data *data)
{
	int		temp;
	int		temp2;
	float	y;

	mlx_get_mouse_pos(data->mlx, &temp2, &temp);
	y = (float)temp;
	y = y / (double) data->width;
	y *= -data->scale;
	y += data->scale / 2;
	return (y);
}

void	key_hook(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->xoffset += 0.1 * (data->scale / 4);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->xoffset -= 0.1 * (data->scale / 4);
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		data->yoffset += 0.1 * (data->scale / 4);
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		data->yoffset -= 0.1 * (data->scale / 4);
	if (mlx_is_key_down(data->mlx, MLX_KEY_1))
		data->palette = &wiki_palette;
	if (mlx_is_key_down(data->mlx, MLX_KEY_2))
		data->palette = &br_palette;
	if (mlx_is_key_down(data->mlx, MLX_KEY_3))
		data->palette = &psych_palette;
	if (mlx_is_key_down(data->mlx, MLX_KEY_MINUS))
		data->max_iter -= 10;
	if (mlx_is_key_down(data->mlx, MLX_KEY_EQUAL))
		data->max_iter += 10;
	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		data->cx = get_convmouse_x(data);
		data->cy = get_convmouse_y(data);
		data->shift += 5;
	}
	draw_fract(data);
}

void	zoom_hook(double xdelta, double ydelta, void *param)
{
	t_data	*data;
	float	x_bef;
	float	y_bef;

	data = param;
	x_bef = get_convmouse_x(data);
	y_bef = get_convmouse_y(data);
	if (ydelta > 0)
	{
		data->scale *= 0.9;
		data->shift += 5;
	}
	else if (ydelta < 0)
	{
		data->scale *= 1.1;
		data->shift -= 5;
	}
	data->xoffset += x_bef - get_convmouse_x(data);
	data->yoffset += y_bef - get_convmouse_y(data);
}

void	data_init(t_data *data)
{
	data->width = 1000;
	data->height = 1000;
	data->max_iter = 100;
	data->scale = 4;
	data->xoffset = 0;
	data->yoffset = 0;
	data->shift = 0;
	data->palette = &wiki_palette;
	data->mlx = mlx_init(data->width, data->height, "fract-ol", false);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
}

t_fract	*parse(int argc, char *argv[], t_data *data)
{
	data->fract = malloc(sizeof(t_fract));
	if (argc == 2 && ft_strlen(argv[1]) <= 10 && !ft_strncmp(argv[1], "Mandelbrot", 10))
		data->fract->type = &mandelbrot;
	else if (argc == 4 && ft_strlen(argv[1]) <= 5 && !ft_strncmp(argv[1], "Julia", 5))
	{
		data->fract->type = &julia;
		data->cx = ft_atof(argv[2]);
		data->cy = ft_atof(argv[3]);
	}
	else if (argc == 2 && ft_strlen(argv[1]) <= 7 && !ft_strncmp(argv[1], "Tricorn", 7))
		data->fract->type = &tricorn;
	else
		ps_print_error();
	return (data->fract);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 2)
		ps_print_error();
	data.fract = parse(argc, argv, &data);
	if (!data.fract)
		return (0);
	data_init(&data);
	mlx_loop_hook(data.mlx, &key_hook, &data);
	mlx_scroll_hook(data.mlx, &zoom_hook, &data);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
