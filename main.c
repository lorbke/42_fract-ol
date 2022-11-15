/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:25:35 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/15 23:16:05 by lorbke           ###   ########.fr       */
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

// void	draw_mandelbrot(mlx_image_t *img, int width, int height, int color)
// {
// 	int	xO;
// 	int	yO;
// 	double x;
// 	double y;
// 	int	iter;
// 	int	max;

// 	max = 1000;
// 	x = 0;
// 	while (x < width)
// 	{
// 		y = 0;
// 		while (y < height)
// 		{
// 			x0 = 
// 			iter = 0;
// 			while (x * 2 + y * 2 <= 2 * 2 && iter < max)
// 			{
				
// 			}
// 			mlx_put_pixel(img, x, y, color);
// 			y++;
// 		}
// 		x++;
// 	}
// }

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
	
	// calculates fraction x of total width and scales down to total width of 1
	result = (double) y / height;
	// scales up the fraction to the total width of 4 (mandelbrot scale)
	result *= -4;
	// offsets the fraction to the left because mandelbrot scale starts at -2, not 0
	result += 2;
	
	return (result);
}

int	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*back;
	int			width;
	int			height;

	width = 300;
	height = 300;

	printf("%f\n", convert_x(0, width));
	printf("%f\n", convert_y(0, height));
	// mlx = mlx_init(width, height, "fract-ol", true);
	// if (!mlx)
	// 	exit(EXIT_FAILURE);

	// mlx_loop_hook(mlx, &hook, mlx);

	// back = mlx_new_image(mlx, width / 2, height / 2);
	// if (!back)
	// {
	// 	write(1, "1", 1);
	// 	exit(EXIT_FAILURE);
	// }
	// // memset(back->pixels, 255, back->width * back->height * sizeof(int));
	// if (mlx_image_to_window(mlx, back, 0,0) < 0)
	// {
	// 	write(1, "2", 1);
	// 	exit(EXIT_FAILURE);
	// }
	// put_color(back, width / 2, height / 2, 0xFA8072);
	// mlx_loop(mlx);

	// mlx_terminate(mlx);
	return (0);
}
