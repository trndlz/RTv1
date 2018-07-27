/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:37:19 by tmervin           #+#    #+#             */
/*   Updated: 2018/07/25 16:06:41 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj		*default_sphere(void)
{
	t_obj *sphere;

	if (!(sphere = malloc(sizeof(t_obj))))
		return (NULL);
	sphere->o_type = SPHERE;
	sphere->pos = (t_vc){0, 0, 0};
	sphere->rot = (t_vc){0, 0, 0};
	sphere->size = 100;
	sphere->col = ft_htoi("0xFF5733");
	sphere->texture = NONE;
	sphere->descartes = (t_vc){0, 0, 1.0};
	sphere->coef = (t_vc){0.5, 0.5, 0.2};
	sphere->cut = NULL;
	return (sphere);
}

t_obj		*default_cone(void)
{
	t_obj *cone;

	if (!(cone = malloc(sizeof(t_obj))))
		return (NULL);
	cone->o_type = CONE;
	cone->pos = (t_vc){0, 0, 0};
	cone->rot = (t_vc){0, 0, 1};
	cone->size = 15;
	cone->col = ft_htoi("0xFFC300");
	cone->texture = NONE;
	cone->descartes = (t_vc){0, 0, 1.0};
	cone->coef = (t_vc){0.5, 0.5, 0.2};
	cone->cut = NULL;
	return (cone);
}

t_obj		*default_cylinder(void)
{
	t_obj *cylinder;

	if (!(cylinder = malloc(sizeof(t_obj))))
		return (NULL);
	cylinder->o_type = CYLINDER;
	cylinder->pos = (t_vc){0, 0, 0};
	cylinder->rot = (t_vc){0, 0, 1};
	cylinder->size = 150;
	cylinder->col = ft_htoi("0x900C3F");
	cylinder->texture = NONE;
	cylinder->descartes = (t_vc){0, 0, 1.0};
	cylinder->coef = (t_vc){0.5, 0.5, 0.2};
	cylinder->cut = NULL;
	return (cylinder);
}

t_obj		*default_plane(void)
{
	t_obj *plane;

	if (!(plane = malloc(sizeof(t_obj))))
		return (NULL);
	plane->o_type = PLANE;
	plane->pos = (t_vc){10000, 0, 0};
	plane->rot = (t_vc){-1, 0, 0};
	plane->col = ft_htoi("0xDAF7A6");
	plane->texture = NONE;
	plane->descartes = (t_vc){0, 0, 1.0};
	plane->coef = (t_vc){0.5, 0.5, 0.2};
	plane->cut = NULL;
	return (plane);
}

t_obj		*default_cutter(void)
{
	t_obj *cut;

	if (!(cut = malloc(sizeof(t_obj))))
		return (NULL);
	cut->o_type = PLANE;
	cut->pos = (t_vc){0, 0, 0};
	cut->rot = (t_vc){0, 0, 1};
	cut->col = ft_htoi("0xFF5733");
	cut->texture = NONE;
	cut->descartes = (t_vc){0, 0, 1.0};
	cut->coef = (t_vc){0.5, 0.5, 0.2};
	cut->cut = NULL;
	return (cut);
}