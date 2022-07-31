#include "libft.h"

char	*ft_strstr(char *str, char *to_find)
{
	char	*sav_str;
	char	*sav_to_find;

	if (!(*to_find))
		return (str);
	while (*str)
	{
		sav_str = str;
		sav_to_find = to_find;
		while (*str++ == *to_find++)
		{
			if (*to_find == '\0')
				return (sav_str);
		}
		str = sav_str++;
		to_find = sav_to_find;
	}
	return (NULL);
}