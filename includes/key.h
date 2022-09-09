/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasstou <mmasstou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:35:08 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/30 18:35:09 by mmasstou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H
# define KEY_H

# define AROW_LEFT 123
# define AROW_RIGHT 124 
# define AROW_UP 126 
# define AROW_DOWN 125
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2 
// mask
# define KeyPressMask 1L<<0
# define KeyReleaseMask 1L<<1
// events
# define KeyPress 02
# define KeyRelease 03

#endif