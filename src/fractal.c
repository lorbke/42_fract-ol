/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:27:10 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/22 23:56:03 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	convert_x(int x, t_data *data)
{
	double	result;

	result = (double) x / data->width;
	result *= data->scale;
	result += -data->scale / 2;
	return (result);
}

double	convert_y(int y, t_data *data)
{
	double	result;

	result = (double) y / data->height;
	result *= -data->scale;
	result += data->scale / 2;
	return (result);
}

int	get_iter(int x, int y, t_data *data)
{
	int		iter;
	double	fx;
	double	fy;
	double	x2;
	double	y2;
	double	tx;
	double	ty;

	fx = convert_x(x, data) + data->xoffset;
	fy = convert_y(y, data) + data->yoffset;
	x2 = 0;
	y2 = 0;
	tx = 0;
	ty = 0;
	iter = 0;
	while (x2 + y2 <= 4 && iter < data->max_iter)
	{
		ty = 2 * tx * ty + fy;
		tx = x2 - y2 + fx;
		x2 = tx * tx; 
		y2 = ty * ty;
		iter++;
	}
	return (iter);
}

void	mandelbrot(t_data *data)
{
	int		x;
	int		y;

	x = 0;
	while (x < data->width)
	{
		y = 0;
		while (y < data->height)
		{
			mlx_put_pixel(data->img, x, y, convert_to_color
				(get_iter(x, y, data), data->max_iter, data->shift, data->palette));
			y++;
		}
		x++;
	}
}
