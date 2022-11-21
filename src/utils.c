/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:27:19 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/22 00:02:05 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// mouse hook
// 	track mouse position
// zoom hook
// 	convert mouse position
// 	zoom
// 	convert mouse position

// mandelbrot
// 	convert 

double	convert_x(int x, t_data *data)
{
	double	result;

	// calculates fraction x of total width and scales down to total width of 1
	result = (double) x / data->width;
	// scales up the fraction to the total width of 4 (mandelbrot scale)
	result *= data->scale;
	// offsets the fraction to the left because mandelbrot scale starts at -2, not 0
	// printf("%f\n\n\n", data->xoffset);
	// offset = data->xbef - data->xaft;
	// printf("offset: %f", offset);
	result += -data->scale / 2;
	return (result);
}

double	convert_y(int y, t_data *data)
{
	double	result;

	result = (double) y / data->height;
	result *= -data->scale;
	// offset = data->ybef - data->yaft;
	result += data->scale / 2;
	return (result);
}
