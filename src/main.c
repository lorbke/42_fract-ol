/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:25:35 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/16 16:25:14 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

// unsigned int	convert_to_color(int n, int max)
// {
// 	double	result;

// 	result = (double) max / n;
// 	result *= (double) 0xFFFFFF;
// 	result += 0xFF;
// 	// printf("%f\n", result);
// 	return (result);
// }

unsigned int	convert_to_color(int n, int max)
{
	int				i;
	unsigned int	palette[16];

	if (n < max && n > 0)
	{
		i = n % 16;
		palette[0] = convert_to_hexcode(66, 30, 15, 255);
		palette[1] = convert_to_hexcode(25, 7, 26, 255);
		palette[2] = convert_to_hexcode(9, 1, 47, 255);
		palette[3] = convert_to_hexcode(4, 4, 73, 255);
		palette[4] = convert_to_hexcode(0, 7, 100, 255);
		palette[5] = convert_to_hexcode(12, 44, 138, 255);
		palette[6] = convert_to_hexcode(24, 82, 177, 255);
		palette[7] = convert_to_hexcode(57, 125, 209, 255);
		palette[8] = convert_to_hexcode(134, 181, 229, 255);
		palette[9] = convert_to_hexcode(211, 236, 248, 255);
		palette[10] = convert_to_hexcode(241, 233, 191, 255);
		palette[11] = convert_to_hexcode(248, 201, 95, 255);
		palette[12] = convert_to_hexcode(255, 170, 0, 255);
		palette[13] = convert_to_hexcode(204, 128, 0, 255);
		palette[14] = convert_to_hexcode(153, 87, 0, 255);
		palette[15] = convert_to_hexcode(106, 52, 3, 255);
		return (palette[i]);
	}
	return (0xFF);
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
	return (iter);
}

void	draw_mandelbrot(mlx_image_t *img, int width, int height)
{
	int		x;
	int		y;

	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			mlx_put_pixel(img, x, y, convert_to_color
				(get_iter(x, y, width, height, 100), 100));
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

	draw_mandelbrot(back, width, height);
	// printf("%u\n", convert_to_hexcode(69, 202, 88, 255));

	mlx_loop(mlx);

	mlx_terminate(mlx);
	return (0);
}
