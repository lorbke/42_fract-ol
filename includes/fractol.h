/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:12:03 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/22 16:10:23 by lorbke           ###   ########.fr       */
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
	int		c;
	void	(*type)();
}	t_fract;

typedef struct s_data
{
	int			width;
	int			height;
	int			max_iter;
	double		scale;
	double		xoffset;
	double		yoffset;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_fract		*fract;
}	t_data;

// utils
void			convert_mouse(t_data *data);
double			convert_x(int x, t_data *data);
double			convert_y(int x, t_data *data);
unsigned int	convert_to_hexcode(
					unsigned char r, unsigned char g,
					unsigned char b, unsigned char a);

// fractal
unsigned int	convert_to_color(int n, int max);
int				get_iter(int x, int y, t_data *data);
void			mandelbrot(t_data *data);

// main
void			hook(void *param);

#endif
