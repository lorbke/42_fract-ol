/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:10:44 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/23 17:51:31 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static unsigned int	convert_to_hexcode(
	unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	unsigned int	rgba;

	rgba = r;
	rgba = (rgba << 8) + g;
	rgba = (rgba << 8) + b;
	rgba = (rgba << 8) + a;
	return (rgba);
}

unsigned int	wiki_palette(int n)
{
	int				i;
	unsigned int	palette[16];
	unsigned char	a;

	a = (unsigned char)255;
	i = n % 16;
	palette[0] = convert_to_hexcode(66, 30, 15, a);
	palette[1] = convert_to_hexcode(25, 7, 26, a);
	palette[2] = convert_to_hexcode(9, 1, 47, a);
	palette[3] = convert_to_hexcode(4, 4, 73, a);
	palette[4] = convert_to_hexcode(0, 7, 100, a);
	palette[5] = convert_to_hexcode(12, 44, 138, a);
	palette[6] = convert_to_hexcode(24, 82, 177, a);
	palette[7] = convert_to_hexcode(57, 125, 209, a);
	palette[8] = convert_to_hexcode(134, 181, 229, a);
	palette[9] = convert_to_hexcode(211, 236, 248, a);
	palette[10] = convert_to_hexcode(241, 233, 191, a);
	palette[11] = convert_to_hexcode(248, 201, 95, a);
	palette[12] = convert_to_hexcode(255, 170, 0, a);
	palette[13] = convert_to_hexcode(204, 128, 0, a);
	palette[14] = convert_to_hexcode(153, 87, 0, a);
	palette[15] = convert_to_hexcode(106, 52, 3, a);
	return (palette[i]);
}

unsigned int	br_palette(int n)
{
	int				i;
	unsigned int	palette[10];
	unsigned char	a;

	a = (unsigned char)255;
	i = n % 10;
	palette[0] = convert_to_hexcode(3, 50, 112, a);
	palette[1] = convert_to_hexcode(19, 104, 170, a);
	palette[2] = convert_to_hexcode(64, 145, 201, a);
	palette[3] = convert_to_hexcode(157, 206, 226, a);
	palette[4] = convert_to_hexcode(254, 223, 212, a);
	palette[5] = convert_to_hexcode(242, 148, 121, a);
	palette[6] = convert_to_hexcode(242, 106, 79, a);
	palette[7] = convert_to_hexcode(239, 60, 45, a);
	palette[8] = convert_to_hexcode(203, 27, 22, a);
	palette[9] = convert_to_hexcode(101, 1, 12, a);
	return (palette[i]);
}

unsigned int	psych_palette(int n)
{
	int				i;
	unsigned int	palette[8];
	unsigned char	a;

	a = (unsigned char)255;
	i = n % 8;
	palette[0] = convert_to_hexcode(0, 0, 0, a);
	palette[1] = convert_to_hexcode(255, 0, 255, a);
	palette[2] = convert_to_hexcode(0, 0, 255, a);
	palette[3] = convert_to_hexcode(0, 255, 255, a);
	palette[4] = convert_to_hexcode(0, 187, 0, a);
	palette[5] = convert_to_hexcode(255, 255, 0, a);
	palette[6] = convert_to_hexcode(255, 128, 0, a);
	palette[7] = convert_to_hexcode(255, 0, 0, a);
	return (palette[i]);
}

unsigned int	convert_to_color(
	int n, int max, unsigned char shift, unsigned int (*palette)(int))
{
	if (n < max && n > 0)
	{
		n += (shift / 8);
		return (palette(n));
	}
	return (0xFF);
}
