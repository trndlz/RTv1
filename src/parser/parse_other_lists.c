/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_other_lists.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/13 13:54:38 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char		*parse_eye(t_env *e, char *file)
{
	while (file && *file && file[1] != '-')
	{
		file = skip_whitespace(file);
		if (ft_strncmp("[position] ", file, 11) == 0)
			file = parse_vc(file, &(e->eye_lookfrom));
		else if (ft_strncmp("[rotation] ", file, 11) == 0)
			file = parse_vc(file, &(e->eye_rot));
		else
			break ;
	}
	return (file);
}

void		parallel_lights(t_obj *light)
{
	if (light->rot.x == 0 && light->rot.y == 0 && light->rot.z == 0)
		return ;
	else
		light->pos = vec_mult(light->rot, -1 * SUN_DISTANCE);
}

char		*parse_light(t_env *e, char *file)
{
	t_obj *light;

	if (!(light = default_light()))
	{
		ft_putstr_fd("Malloc <light> object failed !\n", 2);
		return (file);
	}
	while (file && *file && file[1] != '-')
	{
		file = skip_whitespace(file);
		if (ft_strncmp("[position] ", file, 11) == 0)
			file = parse_vc(file, &(light->pos));
		else if (ft_strncmp("[rotation] ", file, 11) == 0)
			file = parse_vc(file, &(light->rot));
		else if (ft_strncmp("[color] ", file, 8) == 0)
			file = parse_color(file, &(light->col));
		else
			break ;
	}
	parallel_lights(light);
	obj_add(&e->light_link, light);
	return (file);
}

char		*parse_cutter(t_obj *obj, char *file)
{
	t_obj *cutter;

	if (!(cutter = default_cutter(obj)))
	{
		ft_putstr_fd("Malloc <cutter> object failed !\n", 2);
		return (file);
	}
	while (file && *file && file[1] != '-')
	{
		file = skip_whitespace(file);
		if (ft_strncmp("(position) ", file, 11) == 0)
			file = parse_vc(file, &(cutter->pos));
		else if (ft_strncmp("(rotation) ", file, 11) == 0)
			file = parse_vc(file, &(cutter->rot));
		else if (ft_strncmp("(size) ", file, 7) == 0)
			file = parse_double(file, &(cutter->size));
		else
			break ;
	}
	obj->cut = cutter;
	return (file);
}

char		*parse_scene_disc(t_env *e, char *file)
{
	if (ft_strncmp("<scene>\n", file, 8) == 0)
		file = parse_scene(e, file + 8);
	return (file);
}
