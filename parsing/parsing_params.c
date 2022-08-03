/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 07:25:24 by abellakr          #+#    #+#             */
/*   Updated: 2022/08/03 07:26:04 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

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