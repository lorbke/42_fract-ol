/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:12:03 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/16 18:32:14 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "MLX42.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <memory.h>
# include <math.h>

// utils
double			convert_x(int x, int width);
double			convert_y(int y, int height);
unsigned int	convert_to_hexcode(
	unsigned char r, unsigned char g, unsigned char b, unsigned char a);

// fractal
unsigned int	convert_to_color(int n, int max);
int				get_iter(int x, int y, int width, int height, int max);
void			draw_mandelbrot(mlx_image_t *img, int width, int height);

// main
void			hook(void *param);

#endif
