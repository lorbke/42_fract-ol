/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:25:35 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/22 00:11:48 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// use linker command (more performance because smaller binary)
// switch put pixel function?

void	hook(void *param)
{
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
}

void	convert_mouse_bef(t_data *data)
{
	double	temp;
	int		x;
	int		y;

	mlx_get_mouse_pos(data->mlx, &x, &y);
	data->xbef = (float)x;
	data->ybef = (float)y;
	data->xbef = data->xbef / (double) data->width;
	data->xbef *= data->scale;
	data->xbef += -(data->scale / 2);
	data->ybef = data->ybef / (double) data->height;
	data->ybef *= -data->scale;
	data->ybef += data->scale / 2;
}

void	convert_mouse_aft(t_data *data)
{
	double	temp;
	int		x;
	int		y;

	mlx_get_mouse_pos(data->mlx, &x, &y);
	data->xaft = (float)x;
	data->yaft = (float)y;
	data->xaft = data->xaft / (double) data->width;
	data->xaft *= data->scale;
	data->xaft += -(data->scale / 2);
	data->yaft = data->yaft / (double) data->height;
	data->yaft *= -data->scale;
	data->yaft += data->scale / 2;
	// printf("%f\n", data->xaft);
	// printf("%f\n", data->yaft);
}

void	zoom_hook(double xdelta, double ydelta, void *param)
{
	t_data	*data;

	data = param;
	convert_mouse_bef(data);
	// printf("bef: %f\n", data->xbef);
	if (ydelta > 0)
		data->scale *= 0.9;
	else if (ydelta < 0)
		data->scale *= 1.1;
	convert_mouse_aft(data);
	data->xoffset += data->xbef - data->xaft;
	data->yoffset += data->ybef - data->yaft;
	printf("x offset: %f\n", data->xoffset);
	printf("y offset: %f\n", data->yoffset);
	data->fract->type(data);
}

// void	mouse_hook(double xpos, double ypos, void *param)
// {
// 	t_data	*data;

// 	data = param;
// 	data->xpos = xpos;
// 	data->ypos = ypos;
// 	// data->xpos = xpos / (double) data->width;
// 	// data->xpos *= data->scale;
// 	// data->xpos += -(data->scale / 2);
// 	// data->ypos = ypos / (double) data->height;
// 	// data->ypos *= -data->scale;
// 	// data->ypos += data->scale / 2;
// }

void	data_init(t_data *data)
{
	data->width = 500;
	data->height = 500;
	data->max_iter = 100;
	data->scale = 4;
	data->xoffset = 0;
	data->yoffset = 0;
	data->xbef = 0;
	data->ybef = 0;
	data->yaft = 0;
	data->yaft = 0;
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
	// mlx_cursor_hook(data.mlx, &mouse_hook, &data);

	// memset(back->pixels, 255, back->width * back->height * sizeof(int));
	mlx_image_to_window(data.mlx, data.img, 0,0);

	mlx_loop(data.mlx);

	mlx_terminate(data.mlx);
	return (0);
}

