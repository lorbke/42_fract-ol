/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:27:19 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/16 18:28:13 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	convert_x(int x, int width)
{
	double	result;
	
	// calculates fraction x of total width and scales down to total width of 1
	result = (double) x / width;
	// scales up the fraction to the total width of 4 (mandelbrot scale)
	result *= 4;
	// offsets the fraction to the left because mandelbrot scale starts at -2, not 0
	result += -2;
	
	return (result);
}

double	convert_y(int y, int height)
{
	double	result;

	result = (double) y / height;
	result *= -4;
	result += 2;
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
