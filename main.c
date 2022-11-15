/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:25:35 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/16 00:07:10 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
// #include <math.h>

void	hook(void *param)
{
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
}

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

int	get_iter(int x, int y, int width, int height, int max)
{
	int		iter;
	double	fx;
	double	fy;
	double	tx;
	double	ty;
	double	temp;

	fx = convert_x(x, width);
	fy = convert_x(y, height);
	tx = 0;
	ty = 0;
	iter = 0;
	while (tx * tx + ty * ty <= 4 && iter < max)
	{
		temp = tx * tx - ty * ty + fx;
		ty = 2 * tx * ty + fy;
		tx = temp;
		iter++;
	}
	if (iter < 100)
		return (0xFFFFFFFF);
	return (0xFF);
}

void	draw_mandelbrot(mlx_image_t *img, int width, int height, int color)
{
	int		x;
	int		y;

	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			mlx_put_pixel(img, x, y, get_iter(x, y, width, height, 1000));
			y++;
		}
		x++;
	}
}

int	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*back;
	int			width;
	int			height;

	width = 1000;
	height = 1000;

	// printf("%f\n", convert_x(0, width));
	// printf("%f\n", convert_y(0, height));
	mlx = mlx_init(width, height, "fract-ol", true);
	if (!mlx)
		exit(EXIT_FAILURE);

	mlx_loop_hook(mlx, &hook, mlx);

	back = mlx_new_image(mlx, width, height);
	// memset(back->pixels, 255, back->width * back->height * sizeof(int));
	mlx_image_to_window(mlx, back, 0,0);

	draw_mandelbrot(back, width, height, 0);

	mlx_loop(mlx);

	mlx_terminate(mlx);
	return (0);
}
