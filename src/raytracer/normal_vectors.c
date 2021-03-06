/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_vectors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:42:39 by tmervin           #+#    #+#             */
/*   Updated: 2018/08/13 13:54:41 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vc	normal_cylinder(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	double	m;
	t_vc	n;
	t_vc	x;

	x = vec_sub(ray.origin, obj->pos);
	m = vec_x(ray.direction, obj->rot) * hit->t + vec_x(x, obj->rot);
	n = vec_add(vec_mult(ray.direction, hit->t), x);
	n = vec_sub(n, vec_mult(obj->rot, m));
	return (vec_norm(n));
}

t_vc	normal_paraboloid(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	double	k;
	double	m;
	t_vc	n;
	t_vc	x;

	k = obj->size;
	x = vec_sub(ray.origin, obj->pos);
	m = vec_x(ray.direction, obj->rot) * hit->t + vec_x(x, obj->rot);
	n = vec_add(vec_mult(ray.direction, hit->t), x);
	n = vec_sub(n, vec_mult(obj->rot, (m + k)));
	return (vec_norm(n));
}

t_vc	normal_cone(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	double	m;
	t_vc	n;
	t_vc	x;

	x = vec_sub(ray.origin, obj->pos);
	m = vec_x(ray.direction, obj->rot) * hit->t + vec_x(x, obj->rot);
	m *= 1 + car(tan(M_PI * obj->size / 180));
	n = vec_add(vec_mult(ray.direction, hit->t), x);
	n = vec_sub(n, vec_mult(obj->rot, m));
	return (vec_norm(n));
}

t_vc	normal_vectors(t_hit_rec *hit, t_obj *obj, t_ray ray)
{
	if (obj->o_type == CYLINDER)
		return (normal_cylinder(hit, obj, ray));
	else if (obj->o_type == CONE)
		return (normal_cone(hit, obj, ray));
	else if (obj->o_type == PLANE || obj->o_type == DISC)
		return (vec_norm(obj->rot));
	else if (obj->o_type == PARABOLOID)
		return (normal_paraboloid(hit, obj, ray));
	else
		return (vec_norm(vec_sub(inter_position(ray, hit->t), obj->pos)));
}
