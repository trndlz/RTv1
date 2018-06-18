/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:51:13 by tmervin           #+#    #+#             */
/*   Updated: 2018/06/18 18:45:21 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vc	create_ray(t_env *e)
{
	t_vc v;

	v.x = (double)(FOV);
	v.y = (double)(WINY / 2 - e->y);
	v.z = (double)(WINZ / 2 - e->z);
	v = rot_all_axis(v, e->eye_rot);
	return (v);
}

double	distance_to_inter(t_env *e, t_obj *obj_list, t_vc ray, t_vc p)
{
	if (obj_list->type == 1)
		return (inter_sph(e, obj_list, ray, p));
	else if (obj_list->type == 2)
		return (inter_cyl(e, obj_list, ray, p));
	else if (obj_list->type == 3)
		return (inter_cone(e, obj_list, ray, p));
	else if (obj_list->type == 4)
		return (inter_plane(ray, p));
	return (-1);
}

t_obj	*nearest_node(t_env *e)
{
	double	t;
	t_obj	*ret;
	t_obj	*olst;

	e->t = 999999999;
	ret = NULL;
	olst = e->obj_link;
	while (olst)
	{
		e->ray = create_ray(e);
		e->offset = vec_sub(e->eye_lookfrom, olst->pos);
		e->ray = rot_all_axis(e->ray, olst->rot);
		e->offset = rot_all_axis(e->offset, olst->rot);
		t = distance_to_inter(e, olst, e->ray, e->offset);
		if (t > 0.00001 && t < e->t)
		{
			e->t = t;
			ret = olst;
		}
		olst = olst->next;
	}
	return (ret);
}

void	compute_scene_vectors(t_env *e, t_obj *tmp)
{
	t_obj	*llst;
	int		color;
	int		nb_shadow;

	llst = e->light_link;
	color = multiply_color(tmp->col, 0.4);
	while (llst)
	{
		lighting_vectors(e, tmp, llst);
		e->v2 = vec_add(vec_mult(e->ray, e->t), e->eye_lookfrom);
		e->lm = vec_sub(llst->pos, e->v2);
		e->lm = rot_all_axis_inv(e->lm, tmp->rot);
		e->cost = vec_dot(e->n, e->lm);
		nb_shadow = shadows(e, tmp, e->obj_link, llst);
		if (nb_shadow > 0)
			draw_point(e, e->y, e->z,
				multiply_color(tmp->col, 0.85 * e->cost / nb_shadow));
		else
		{
			color = specular_diffuse(color, llst, e);
			draw_point(e, e->y, e->z, color);
		}
		llst = llst->next;
	}
}

void	*scene_plot(void *arg)
{
	t_obj	*tmp;
	t_env	*e;

	e = (t_env *)arg;
	e->z = (e->thread_int) * WINZ / TH_NB - 1;
	while (++(e->z) < ((e->thread_int + 1) * WINZ) / TH_NB)
	{
		e->y = -1;
		while (++(e->y) < WINY)
		{
			tmp = nearest_node(e);
			e->ray = create_ray(e);
			if (tmp)
				compute_scene_vectors(e, tmp);
		}
	}
	return (NULL);
}
