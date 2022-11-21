/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:27:10 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/22 00:06:00 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

int	get_iter(int x, int y, t_data *data)
{
	int		iter;
	double	fx;
	double	fy;
	double	tx;
	double	ty;
	double	temp;

	fx = convert_x(x, data) + data->xoffset;
	fy = convert_y(y, data) + data->yoffset;
	tx = 0;
	ty = 0;
	iter = 0;
	while (tx * tx + ty * ty <= 4 && iter < data->max_iter)
	{
		temp = tx * tx - ty * ty + fx;
		ty = 2 * tx * ty + fy;
		tx = temp; 
		iter++;
	}
	return (iter);
}

// // BUG: Linux may experience a red hue instead due to endiannes
// void mlx_draw_pixel(uint8_t* pixel, uint32_t color)
// {
// 	*(pixel++) = (uint8_t)(color >> 24);
// 	*(pixel++) = (uint8_t)(color >> 16);
// 	*(pixel++) = (uint8_t)(color >> 8);
// 	*(pixel++) = (uint8_t)(color & 0xFF);
// }

//= Public =//

// void ft_mlx_put_pixel (mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
// {
// 	// MLX_NONNULL(image);
// 	// MLX_ASSERT(x < image->width, "Pixel is out of bounds");
// 	// MLX_ASSERT(y < image->height, "Pixel is out of bounds");

// 	uint32_t* pixelstart = (uint32_t *)(&image->pixels[(y * image->width + x) * 4]);
// 	*pixelstart = color;
// 	// mlx/_draw_pixel(pixelstart, color);
// }

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
				(get_iter(x, y, data), data->max_iter));
			y++;
		}
		x++;
	}
}
