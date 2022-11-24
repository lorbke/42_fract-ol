/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 23:58:13 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/24 00:36:40 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static float	get_convmouse_x(t_data *data)
{
	int		temp;
	int		temp2;
	float	x;

	mlx_get_mouse_pos(data->mlx, &temp, &temp2);
	x = (float)temp;
	x = x / (double) WIDTH;
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
	y = y / (double) WIDTH;
	y *= -data->scale;
	y += data->scale / 2;
	return (y);
}

static void	key_hook_two(t_data *data)
{
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
	key_hook_two(data);
}

void	zoom_hook(double xdelta, double ydelta, void *param)
{
	t_data	*data;
	float	x_bef;
	float	y_bef;

	xdelta = 0;
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
	xdelta++;
	data->xoffset += x_bef - get_convmouse_x(data);
	data->yoffset += y_bef - get_convmouse_y(data);
}
