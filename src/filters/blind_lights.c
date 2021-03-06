/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blind_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 10:54:34 by jostraye          #+#    #+#             */
/*   Updated: 2018/08/13 13:54:23 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	nearest_light(t_env *e, t_ray ray, t_hit_rec *hit)
{
	t_obj	*olst;
	char	hit_anything;

	hit_anything = 0;
	hit->hit_obj = NULL;
	hit->t = INFINITY;
	hit->t1 = -1;
	hit->t2 = -1;
	olst = e->light_link;
	while (olst)
	{
		if (olst->cut)
		{
			if (hit_not_cut(hit, olst, ray))
				hit_anything = 1;
		}
		olst = olst->next;
	}
	return (hit_anything);
}

void	blinding_lights(t_env *e)
{
	int			i;
	t_hit_rec	hit_rec;
	t_hit_rec	hit_light;
	t_ray		ray;

	e->z = 500;
	e->y = 500;
	e->nr = 1;
	e->nt = 2;
	ray = create_ray(e->y, e->z, e->eye_rot, e->eye_lookfrom);
	nearest_node(e, ray, &hit_rec);
	nearest_light(e, ray, &hit_light);
	i = -1;
	if (nearest_light(e, ray, &hit_light))
		if (hit_light.t < hit_rec.t)
			while (++i < WINY * WINZ)
				e->imgstr[i] = mix_colors(0xFFFFFF, e->imgstr[i], 0.7);
}
