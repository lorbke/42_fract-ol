/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:27:19 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/22 14:54:13 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// converts 
double	convert_x(int x, t_data *data)
{
	double	result;

	result = (double) x / data->width;
	result *= data->scale;
	result += -data->scale / 2;
	return (result);
}

double	convert_y(int y, t_data *data)
{
	double	result;

	result = (double) y / data->height;
	result *= -data->scale;
	result += data->scale / 2;
	return (result);
}
