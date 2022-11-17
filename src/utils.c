/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:27:19 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/17 01:24:38 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	convert_x(int x, t_data *data)
{
	double	result;
	
	// calculates fraction x of total width and scales down to total width of 1
	result = (double) x / data->width;
	// scales up the fraction to the total width of 4 (mandelbrot scale)
	result *= data->scale;
	// offsets the fraction to the left because mandelbrot scale starts at -2, not 0
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

unsigned int	convert_to_hexcode(
	unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	unsigned int	rgba;

	rgba = r;
	rgba = (rgba << 8) + g;
	rgba = (rgba << 8) + b;
	rgba = (rgba << 8) + a;
	return (rgba);
}
