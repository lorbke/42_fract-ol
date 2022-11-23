/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:12:03 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/24 00:12:24 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "MLX42.h"
# include <stdlib.h>
# include <unistd.h>
# define WIDTH 500
# define HEIGHT 500

typedef struct s_data
{
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
	int				(*fract)();
}	t_data;

// colors
unsigned int	fortytwo_palette(int n);
unsigned int	br_palette(int n);
unsigned int	psych_palette(int n);
unsigned int	wiki_palette(int n);
unsigned int	convert_to_color(int n, int max, unsigned char shift,
					unsigned int (*palette)(int));

// fractal
int				mandelbrot(int x, int y, t_data *data);
int				julia(int x, int y, t_data *data);
int				tricorn(int x, int y, t_data *data);

// hooks
void			key_hook(void *param);
void			zoom_hook(double xdelta, double ydelta, void *param);

// main
void			draw_fract(t_data *data);

#endif
