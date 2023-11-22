/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reassign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 12:01:28 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/30 18:35:25 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	*ft_reassign(void *oldptr, void *newptr)
{
	free(oldptr);
	return (newptr);
}
