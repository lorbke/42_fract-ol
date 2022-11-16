/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:25:35 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/16 18:28:04 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	hook(void *param)
{
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
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
