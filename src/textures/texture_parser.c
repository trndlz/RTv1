/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 18:25:04 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/20 15:56:42 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		*get_wh(char *str, int *wh)
{
	char **split;

	replace_char(str);
	if (!(split = ft_strsplit(str, ' ')))
		return (NULL);
	wh[0] = ft_atoi(split[0]);
	wh[1] = ft_atoi(split[1]);
	free_split(split);
	free(str);
	return (wh);
}

int		*get_xpm_size(char *file)
{
	int		fd;
	int		line;
	int		*wh;
	char	*str;

	line = 0;
	fd = open(file, O_RDONLY);
	if (!(wh = (int *)malloc(sizeof(int) * 2)) || fd < 0)
		return (NULL);
	while (get_next_line(fd, &str) == 1 && line <= 4)
	{
		line++;
		if (line == 4)
		{
			if (!(wh = get_wh(str, wh)))
				return (NULL);
			return (wh);
		}
		free(str);
	}
	free(str);
	return (NULL);
}

int		**create_color_tab(int *imgstr, int *size)
{
	int		**color_tab;
	int		x;
	int		y;
	int		i;

	y = 0;
	i = 0;
	if (!(color_tab = (int **)malloc(sizeof(int*) * size[1] * 2)))
		return (NULL);
	while (y < size[1])
	{
		if (!(color_tab[y] = (int *)malloc(sizeof(int) * size[0] * 2)))
			return (NULL);
		x = 0;
		while (x < size[0])
		{
			color_tab[y][x] = imgstr[i];
			x++;
			i++;
		}
		y++;
	}
	return (color_tab);
}

int		load_texture_to_obj(t_env *e, t_obj *obj)
{
	void	*image;
	int		*imgstr;
	int		*size;
	int		a[3];

	if (!(size = get_xpm_size("xpm/earth.xpm")))
		return (0);
	obj->file_txt.size = size;
	image = mlx_xpm_file_to_image(e->mlx.mlx, "xpm/earth.xpm",
			&size[0], &size[1]);
	imgstr = (int *)mlx_get_data_addr(image, &a[0], &a[1], &a[2]);
	if (!(obj->file_txt.tab = create_color_tab(imgstr, obj->file_txt.size)))
		return (0);
	return (1);
}

int		load_tex_height_to_obj(t_env *e, t_obj *obj)
{
	void	*image;
	int		*imgstr;
	int		*size;
	int		a[3];

	if (!(size = get_xpm_size("xpm/earth_height.xpm")))
		return (0);
	obj->file_height.size = size;
	image = mlx_xpm_file_to_image(e->mlx.mlx,
			"xpm/earth_height.xpm", &size[0], &size[1]);
	imgstr = (int *)mlx_get_data_addr(image, &a[0], &a[1], &a[2]);
	if (!(obj->file_height.tab = create_color_tab(imgstr,
				obj->file_height.size)))
		return (0);
	return (1);
}
