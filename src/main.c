/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:25:35 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/17 01:19:24 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	hook(void *param)
{
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
}

void	zoom_hook(double xdelta, double ydelta, void *param)
{
	t_data	*data;

	data = param;
	if (ydelta > 0)
	{
		data->scale -= 0.1;
		data->fract->type(data);
	}
	else if (ydelta < 0)
	{
		data->scale += 0.1;
		data->fract->type(data);
	}
}

void	mouse_hook(double xpos, double ypos, void *param)
{
	t_data	*data;

	data = param;
	data->xoffset = xpos;
	// data->xoffset = xpos / (double) data->width;
	// data->xoffset *= data->scale;
	// data->xoffset += -(data->scale / 2);
	// data->yoffset = ypos / (double) data->height;
	// data->yoffset *= -data->scale;
	// data->yoffset += data->scale / 2;
}

void	data_init(t_data *data)
{
	data->width = 1000;
	data->height = 1000;
	data->max_iter = 30;
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
	t_data data;

	if (argc < 2)
		return (0);
	data.fract = parse(argv, data.fract);
	if (!data.fract)
		return (0);
	data_init(&data);

	mlx_loop_hook(data.mlx, &hook, data.mlx);
	mlx_loop_hook(data.mlx, &hook, data.mlx);
	mlx_scroll_hook(data.mlx, &zoom_hook, &data);
	mlx_cursor_hook(data.mlx, &mouse_hook, &data);

	// memset(back->pixels, 255, back->width * back->height * sizeof(int));
	mlx_image_to_window(data.mlx, data.img, 0,0);

	mlx_loop(data.mlx);

	mlx_terminate(data.mlx);
	return (0);
}
