/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:20:32 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/02 18:29:50 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	if (c == 0)
		return ((char *)s + len);
	if (c != 0)
	{
		while (len--)
		{
			if (s[len] == (char)c)
				return ((char *)(s + len));
		}
		return (NULL);
	}
	return (NULL);
}
