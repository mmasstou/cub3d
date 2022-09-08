/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _error.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 11:24:54 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/26 15:32:57 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	_error(char *msg)
{
	ft_putstr_fd("\033[0;31m", STDERR_FILENO);
	ft_putstr_fd("Error", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(" ❌", STDERR_FILENO);
	if (msg != NULL)
		ft_putstr_fd(msg, STDERR_FILENO);
	ft_putendl_fd("\033[0m", STDERR_FILENO);
	exit(1);
}
