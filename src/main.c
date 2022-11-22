/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:25:35 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/22 16:13:15 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// use linker command (more performance because smaller binary)
// switch put pixel function?

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
	data->fract->type(data);
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

void	zoom_hook(double xdelta, double ydelta, void *param)
{
	t_data	*data;
	float	x_bef;
	float	y_bef;

	data = param;
	x_bef = get_convmouse_x(data);
	y_bef = get_convmouse_y(data);
	if (ydelta > 0)
		data->scale *= 0.9;
	else if (ydelta < 0)
		data->scale *= 1.1;
	data->xoffset += x_bef - get_convmouse_x(data);
	data->yoffset += y_bef - get_convmouse_y(data);
}

void	data_init(t_data *data)
{
	data->width = 500;
	data->height = 500;
	data->max_iter = 100;
	data->scale = 4;
	data->xoffset = 0;
	data->yoffset = 0;
	data->mlx = mlx_init(data->width, data->height, "fract-ol", false);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
}

t_fract	*parse(char *argv[], t_fract *fract)
{
	fract = malloc(sizeof(t_fract));
	if (ft_strlen(argv[1]) > 10)
		return (NULL);
	if (!ft_strncmp(argv[1], "Mandelbrot", 10))
		fract->type = &mandelbrot;
	else
		return (NULL);
	fract->c = 0;
	return (fract);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 2)
		return (0);
	data.fract = parse(argv, data.fract);
	if (!data.fract)
		return (0);
	data_init(&data);
	mlx_loop_hook(data.mlx, &key_hook, &data);
	mlx_scroll_hook(data.mlx, &zoom_hook, &data);
	mlx_image_to_window(data.mlx, data.img, 0,0);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
