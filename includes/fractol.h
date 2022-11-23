/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:12:03 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/23 17:55:52 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "MLX42.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <memory.h>
# include <math.h>

typedef struct s_fract
{
	int		(*type)();
}	t_fract;

typedef struct s_data
{
	int				width;
	int				height;
	int				max_iter;
	double			scale;
	unsigned char	shift;
	unsigned int	(*palette)();
	double			xoffset;
	double			yoffset;
	double			cx;
	double			cy;
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_fract			*fract;
}	t_data;

// utils
void			convert_mouse(t_data *data);
double			convert_x(int x, t_data *data);
double			convert_y(int x, t_data *data);

// colors
unsigned int	fortytwo_palette(int n);
unsigned int	br_palette(int n);
unsigned int	psych_palette(int n);
unsigned int	wiki_palette(int n);
unsigned int	convert_to_color(int n, int max, unsigned char shift, unsigned int (*palette)(int));

// fractal
int				mandelbrot(int x, int y, t_data *data);
int				julia(int x, int y, t_data *data);
int				tricorn(int x, int y, t_data *data);
void			draw_fract(t_data *data);

// main
void			hook(void *param);

#endif
