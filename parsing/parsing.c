/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:39:23 by mmasstou          #+#    #+#             */
/*   Updated: 2022/08/02 20:20:07 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
//---------------------------------------------- function to get map size
int get_map_size(char *file)
{
	int index;
	int fd;
	char    *line;

	index = 0;
	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		exit (1);
	line = get_next_line(fd);
	if(line == NULL)
	{
		printf("Error\n");
		exit(1);
	}
	while (line)
	{
		index++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (index);
}
//------------------------------------------------------ function ti get all map 
char    **get_g_map(char *file, int *g_map_size)
{
	int     fd;
	char    **g_map;
	char    *line;
	int     index;

	(*g_map_size) = get_map_size(file);
	g_map = (char **)malloc(sizeof(char *) * (*g_map_size) + 1);
	if (!g_map)
		exit(1);
	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		exit (1);
	line = get_next_line(fd);
	index = 0;
	while (line)
	{
		g_map[index] = ft_strtrim(line, " \n"); // change ft_strdub with ft_strtrim
		free(line);
		line = get_next_line(fd);
		index++;
	}
	return (g_map[index] = NULL, g_map);
}
//---------------------------------------------------------- parsing 
void    parsing(char *argv[], t_data *data)
{
	char    **g_map;
	int     g_map_size;
	int     index;

	g_map = get_g_map(argv[1], &g_map_size);
	get_map_parameters(g_map, data);
	index = 0;
	while (g_map[index])
	{
		free(g_map[index]);
		index++;
	}
	free(g_map);
}
//--------------------------------------------------------------- get map parameters
void    get_map_parameters(char **map, t_data *data)
{
	int i;
	char **line;

	i = 0;
	line = NULL;
	while(map[i])
	{
		if(data->params == 6)
		{
			data->start_map = i + 1;
			break;
		}
		line = ft_split(map[i], ' ');
		if(array_size(line) != 2 && array_size(line) != 0)
		{
			printf("Error\n");
			exit(1);
		}
		get_line_parameters(line, data);
		free_array(line);
		i++;
	}
	// check file extentions and check they execist 
	check_files(data->no);
	check_files(data->so);
	check_files(data->we);
	check_files(data->ea);
}

//--------------------------------------------------- function to trait each line
void    get_line_parameters(char **line, t_data *data)
{
	if(line[0] && (ft_strncmp(line[0], "NO", 2) && ft_strncmp(line[0], "SO", 2) && ft_strncmp(line[0], "WE", 2) \
	&& ft_strncmp(line[0], "EA", 2) && ft_strncmp(line[0], "F", 1) \
	&& ft_strncmp(line[0], "C", 1)))
	{
		printf("Error\n");
		exit(1);
	}
	else if((line[0] && (!ft_strncmp(line[0], "NO", 2) || !ft_strncmp(line[0], "SO", 2) || !ft_strncmp(line[0], "WE", 2) \
	|| !ft_strncmp(line[0], "EA", 2) || !ft_strncmp(line[0], "F", 1) \
	|| !ft_strncmp(line[0], "C", 1)) && data->params != 6))
	{
		save_data(line, data);
		data->params++;
	}
}
//-------------------------------------------------------
void	save_data(char **line, t_data *data)
{
	save_no(line, data);
	save_so(line, data);
	save_we(line, data);
	save_ea(line, data);
	save_f(line, data);
	save_c(line, data);
}
//-----------------------------------------------------
void	save_no(char **line, t_data *data)
{
	if(!ft_strncmp(line[0], "NO", 2) && data->exit.no == 0)
	{
		data->no = ft_strdup(line[1]);
		data->exit.no++;
	}
	else if(!ft_strncmp(line[0], "NO", 2) && data->exit.no == 1)
	{
		printf("Error\n");
		exit(1);
	}
}
//-----------------------------------------------------
void	save_so(char **line, t_data *data)
{
	if(!ft_strncmp(line[0], "SO", 2) && data->exit.so == 0)
	{
		data->so = ft_strdup(line[1]);
		data->exit.so++;
	}
	else if(!ft_strncmp(line[0], "SO", 2) && data->exit.so == 1)
	{
		printf("Error\n");
		exit(1);
	}
}
//-----------------------------------------------------
void	save_we(char **line, t_data *data)
{
	if(!ft_strncmp(line[0], "WE", 2) && data->exit.we == 0)
	{
		data->we = ft_strdup(line[1]);
		data->exit.we++;
	}
	else if(!ft_strncmp(line[0], "WE", 2) && data->exit.we == 1)
	{
		printf("Error\n");
		exit(1);
	}
}
//-----------------------------------------------------
void	save_ea(char **line, t_data *data)
{
	if(!ft_strncmp(line[0], "EA", 2) && data->exit.ea == 0)
	{
		data->ea = ft_strdup(line[1]);
		data->exit.ea++;
	}
	else if(!ft_strncmp(line[0], "EA", 2) && data->exit.ea == 1)
	{
		printf("Error\n");
		exit(1);
	}
}
//----------------------------------------------
void	save_f(char **line, t_data *data)
{
	if(!ft_strncmp(line[0], "F", 1) && data->exit.f == 0)
	{
		save_color(line[0], line[1], data);
		data->exit.f++;
	}
	else if(!ft_strncmp(line[0], "F", 2) && data->exit.f == 1)
	{
		printf("Error\n");
		exit(1);
	}
}
//----------------------------------------------
void	save_c(char **line, t_data *data)
{
	if(!ft_strncmp(line[0], "C", 1) && data->exit.c == 0)
	{
		save_color(line[0], line[1], data);
		data->exit.c++;
	}
	else if(!ft_strncmp(line[0], "C", 2) && data->exit.c == 1)
	{
		printf("Error\n");
		exit(1);
	}
}
//------------------------------------------------------------------------
void	save_color(char *color, char *color_data, t_data *data)
{
	char **color_tab;

	color_tab = ft_split(color_data, ',');
	check_color_validity(color_tab);
	if(ft_strncmp(color, "C", 1) == 0)
	{
		data->c.r = ft_atoi(color_tab[0]);
		data->c.g = ft_atoi(color_tab[1]);
		data->c.b = ft_atoi(color_tab[2]);
	}
	else if (ft_strncmp(color, "F", 1) == 0)
	{
		data->f.r = ft_atoi(color_tab[0]);
		data->f.g = ft_atoi(color_tab[1]);
		data->f.b = ft_atoi(color_tab[2]);
	}
	free_array(color_tab);
}
//--------------------------------------------------
void	check_color_validity(char **color_tab)
{
	int r;
	int g;
	int b;

	if(color_tab[0] && color_tab[1] && color_tab[2])
	{
		r = ft_atoi(color_tab[0]);
		g = ft_atoi(color_tab[1]);
		b = ft_atoi(color_tab[2]);
	}
	check_color_digit(color_tab);
	if(array_size(color_tab) != 3 || r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
	{
		printf("Error\n");
		exit(1);
	}
}
//-------------------------------------------
void	check_color_digit(char **color_tab)
{
	int i;
	int j;

	i = 0;
	while(color_tab[i])
	{
		j = 0;
		while(color_tab[i][j])
		{
			if(ft_isdigit(color_tab[i][j]) == 0)
			{
				printf("Error\n");
				exit(1);
			}
			j++;	
		}
		i++;
	}
}
//--------------------------------------------
void	check_files(char *filename)
{
	int fd;
	
	char *extension;

	extension = ft_strrchr(filename, '.');		
	if(extension == NULL || ft_strncmp(extension, ".xpm", 4))
	{
		printf("Error\n");
		exit(1);
	}
	fd = open(filename, O_RDONLY);
	if(fd < 0)
	{
		printf("Error\n");
		exit(1);
	}
	close(fd);
}
