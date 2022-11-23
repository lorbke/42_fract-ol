/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:27:10 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/24 00:15:27 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	convert_x(int x, t_data *data)
{
	double	result;

	result = (double) x / WIDTH;
	result *= data->scale;
	result += -data->scale / 2;
	return (result);
}

double	convert_y(int y, t_data *data)
{
	double	result;

	result = (double) y / HEIGHT;
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

	fx = convert_x(x, data) + data->xoffset;
	fy = convert_y(y, data) + data->yoffset;
	x2 = 0;
	y2 = 0;
	data->cx = 0;
	data->cy = 0;
	iter = 0;
	while (x2 + y2 <= 4 && iter < data->max_iter)
	{
		data->cy = 2 * data->cx * data->cy + fy;
		data->cx = x2 - y2 + fx;
		x2 = data->cx * data->cx;
		y2 = data->cy * data->cy;
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
	double	temp;

	zx = convert_x(x, data) + data->xoffset;
	zy = convert_y(y, data) + data->yoffset;
	data->cx = zx;
	data->cy = zy;
	iter = 0;
	while (zx * zx + zy * zy <= 4 && iter < data->max_iter)
	{
		temp = zx * zx - zy * zy + data->cx;
		zy = -2 * zx * zy + data->cy;
		zx = temp;
		iter++;
	}
	return (iter);
}
