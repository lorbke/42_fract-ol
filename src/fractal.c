/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:27:10 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/23 17:59:09 by lorbke           ###   ########.fr       */
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

int	mandelbrot(int x, int y, t_data *data)
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

int	julia(int x, int y, t_data *data)
{
	int		iter;
	double	zx;
	double	zy;
	double	temp;

	zx = convert_x(x, data) + data->xoffset;
	zy = convert_y(y, data) + data->yoffset;
	iter = 0;
	while (zx * zx + zy * zy <= 4 && iter < data->max_iter)
	{
		temp = zx * zx - zy * zy;
		zy = 2 * zx * zy + data->cy;
		zx = temp + data->cx;
		iter++;
	}
	return (iter);
}

int	tricorn(int x, int y, t_data *data)
{
	int		iter;
	double	zx;
	double	zy;
	double	tx;
	double	ty;
	double	temp;

	zx = convert_x(x, data) + data->xoffset;
	zy = convert_y(y, data) + data->yoffset;
	tx = zx;
	ty = zy;
	iter = 0;
	while (zx * zx + zy * zy <= 4 && iter < data->max_iter)
	{
		temp = zx * zx - zy * zy + tx;
		zy = -2 * zx * zy + ty;
		zx = temp;
		iter++;
	}
	return (iter);
}

void	draw_fract(t_data *data)
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
				(data->fract->type(x, y, data),
					data->max_iter, data->shift, data->palette));
			y++;
		}
		x++;
	}
}
