/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 11:20:18 by hdussert          #+#    #+#             */
/*   Updated: 2019/05/01 21:26:18 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void    init_raycasting(t_raycasting *rc, t_player *p)
{
  rc->ray_dir.x = p->dir.x + p->plane.x * rc->camera_x;
  rc->ray_dir.y = p->dir.y + p->plane.y * rc->camera_x;
  rc->delta_dist.x = fabs(1 / rc->ray_dir.x);//length of ray from one x or y-rc->side to next x or y-rc->side
  rc->delta_dist.y = fabs(1 / rc->ray_dir.y);
  if (rc->ray_dir.x < 0) //calculate step and initial sideDist
  {
    rc->step.x = -1;
    rc->side_dist.x = (p->pos.x - rc->map.x) * rc->delta_dist.x;
  }
  else
  {
    rc->step.x = 1;
    rc->side_dist.x = (rc->map.x + 1.0 - p->pos.x) * rc->delta_dist.x;
  }
  if (rc->ray_dir.y < 0)
  {
    rc->step.y = -1;
    rc->side_dist.y = (p->pos.y - rc->map.y) * rc->delta_dist.y;
  }
  else
  {
    rc->step.y = 1;
    rc->side_dist.y = (rc->map.y + 1.0 - p->pos.y) * rc->delta_dist.y;
  }
}

void    ray_hit(t_raycasting *rc, t_map map)
{
  int hit;
  hit = 0;
  rc->dist_hit = 0;
  while (hit == 0)
  {
    if (rc->side_dist.x < rc->side_dist.y)
    {
      rc->side_dist.x += rc->delta_dist.x;
      rc->map.x += rc->step.x;
      rc->side = 0;
    }
    else
    {
      rc->side_dist.y += rc->delta_dist.y;
      rc->map.y += rc->step.y;
      rc->side = 1;
    }
    rc->dist_hit++;
    if (map.m[rc->map.y][rc->map.x] != '.')
      hit = 1;
  }
}


// Épurer lov dans lov_cp, trouver comment gérer le choix des textures
// Probablement quelques variables a ajouter dans rc
// Bien vérifier que chacun s'y trouvant est utile
// Ajouter variable hauteur de tête / angle
// Fog sur la distance?

void    draw_wall(t_doom *doom, t_raycasting *rc)
{
  rc->lineHeight = (int)(doom->h / rc->perp_wall_dist);
  rc->draw_start = -rc->lineHeight / 2 + doom->h / 2;
  rc->draw_end = rc->lineHeight / 2 + doom->h / 2;
  
  if(rc->draw_start < 0)
    rc->draw_start = 0;
  if(rc->draw_end >= doom->h)
    rc->draw_end = doom->h - 1;
  if (rc->draw_end < rc->draw_start)
  {
    rc->draw_start = 0;
    rc->draw_end = doom->h - 1;
  }
  //int texNum = doom->map.m[rc->map.x][rc->map.y] - 1; //1 subtracted from it so that texture 0 can be used!
  if (rc->side == 0) rc->wall_x = doom->you.pos.y + rc->perp_wall_dist * rc->ray_dir.y;
  else rc->wall_x = doom->you.pos.x + rc->perp_wall_dist * rc->ray_dir.x;
  rc->wall_x -= floor((rc->wall_x));

  int texX = (int)(rc->wall_x * (double)(texture->w));
  if(rc->side == 0 && rc->ray_dir.x > 0)
    texX = texture->w - texX - 1;
  if(rc->side == 1 && rc->ray_dir.y < 0)
    texX = texture->w - texX - 1;
  int y = rc->draw_start - 1;
  while (++y < rc->draw_end)
  {
    int d = y * 256 - doom->h * 128 + rc->lineHeight * 128; //256 and 128 factors to avoid floats
    // TODO: avoid the division to speed this up
    int texY = ((d * texture->h) / rc->lineHeight) / 256;
    Uint32 color = ((Uint32 *)texture->pixels)[texture->w * texY + texX];
    //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
    if(rc->side == 1) color = (color >> 1) & 8355711;
    doom->s_pixels[y * doom->w + x] = color;
  }
}

void    draw_screen(t_doom *doom)
{
  int   x;
  x = -1;
  while (++x < doom->w)
  {
    rc->camera_x = 2 * x / (double)(doom->w) - 1;
    init_raycasting(&doom->raycasting, &doom->player);
    ray_hit(&doom->rc, doom->map);
    if (doom->rc.side == 0)
      doom->rc.perp_wall_dist = (doom->rc.map.x - doom->you.pos.x + (1 - doom->rc.step.x) / 2) / doom->rc.ray_dir.x;
    else
      doom->rc.perp_wall_dist = (doom->rc.map.y - doom->you.pos.y + (1 - doom->rc.step.y) / 2) / doom->rc.ray_dir.y;

  }
}