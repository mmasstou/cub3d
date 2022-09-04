/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 19:40:37 by abellakr          #+#    #+#             */
/*   Updated: 2022/09/04 19:40:52 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//-------------------------------------------------
double	percent_function(double value, double max_value)
{
	double percent = 100 / (max_value / value);
	return(percent);
}
//----------------------------------------------
int shadowing_function(int color, double percent)
{
	int red;
	int green;
	int blue;

	red = color >> 16;
	red &= 255;
	green = color >> 8;
	green &= 255;
	blue = color >> 0;
	blue &= 255;
	red /= (100 + percent) / 100;
	green /= (100 + percent) / 100;
	blue /= (100 + percent) / 100;
	return(red << 16 | green << 8 | blue << 0);
}