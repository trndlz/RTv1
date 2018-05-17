/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 14:51:34 by tmervin           #+#    #+#             */
/*   Updated: 2018/05/17 14:36:41 by tmervin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	car(double a)
{
	return (a * a);
}

void	rot_x(t_vc *vc, int t)
{
	double y;
	double z;

	y = vc->y;
	z = vc->z;
	vc->y = y * cos(t * M_PI / 180) - z * sin(t * M_PI / 180);
	vc->z = y * sin(t * M_PI / 180) + z * cos(t * M_PI / 180);
}

void	rot_y(t_vc *vc, int t)
{
	double x;
	double z;

	x = vc->x;
	z = vc->z;
	vc->x = x * cos(t * M_PI / 180) + z * sin(t * M_PI / 180);
	vc->z = -x * sin(t * M_PI / 180) + z * cos(t * M_PI / 180);
}

void	rot_z(t_vc *vc, int t)
{
	double x;
	double y;

	x = vc->x;
	y = vc->y;
	vc->x = x * cos(t * M_PI / 180) - y * sin(t * M_PI / 180);
	vc->y = x * sin(t * M_PI / 180) + y * cos(t * M_PI / 180);
}

void	rot_all_axis(t_vc *vc, t_obj *obj)
{
	rot_x(vc, obj->rot.x);
	rot_y(vc, obj->rot.y);
	rot_z(vc, obj->rot.z);
}
