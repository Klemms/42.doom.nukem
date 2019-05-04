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
  rc->p_z = p->pos.z;
  rc->camera_x = 2 * rc->x / (double)(WIN_W) - 1;
  rc->ray_dir.x = p->dir.x + p->plane.x * rc->camera_x;
  rc->ray_dir.y = p->dir.y + p->plane.y * rc->camera_x;
  rc->map.x = (int)(p->pos.x);
  rc->map.y = (int)(p->pos.y);
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

void    ray_hit(t_raycasting *rc, t_nmap *nmap)
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
    if (nmap->map[rc->map.y][rc->map.x].block_type != 0 && nmap->map[rc->map.y][rc->map.x].block_type != 3)
      hit = 1;
  }
}


// Épurer lov dans lov_cp, trouver comment gérer le choix des textures
// Probablement quelques variables a ajouter dans rc
// Bien vérifier que chacun s'y trouvant est utile
// Ajouter variable hauteur de tête / angle
// Fog sur la distance?

void    init_raycasting_draw_wall(t_raycasting *rc, t_player *p)
{
  if (rc->side == 0)
    rc->perp_wall_dist = (rc->map.x - p->pos.x + (1 - rc->step.x) / 2) / rc->ray_dir.x;
  else
    rc->perp_wall_dist = (rc->map.y - p->pos.y + (1 - rc->step.y) / 2) / rc->ray_dir.y;
  rc->lineHeight = (int)(WIN_H / rc->perp_wall_dist);
  rc->draw_start = -rc->lineHeight / 2 + WIN_H * rc->p_z;
  rc->draw_end = rc->lineHeight / 2 + WIN_H * rc->p_z;
  if(rc->draw_start < 0)
    rc->draw_start = 0;
  if(rc->draw_end >= WIN_H)
    rc->draw_end = WIN_H - 1;
  if (rc->draw_end < rc->draw_start)
  {
    rc->draw_start = 0;
    rc->draw_end = WIN_H - 1;
  }
  //int texNum = doom->map.m[rc->map.x][rc->map.y] - 1; //1 subtracted from it so that texture 0 can be used!
  if (rc->side == 0)
    rc->wall_x = p->pos.y + rc->perp_wall_dist * rc->ray_dir.y;
  else 
    rc->wall_x = p->pos.x + rc->perp_wall_dist * rc->ray_dir.x;
  rc->wall_x -= floor((rc->wall_x));
  rc->tex.x = (int)(rc->wall_x * (double)(rc->texture->w));
  rc->tex.x = rc->tex.x % rc->texture->w;
  if(rc->side == 0 && rc->ray_dir.x > 0)
    rc->tex.x = rc->texture->w - rc->tex.x - 1;
  if(rc->side == 1 && rc->ray_dir.y < 0)
    rc->tex.x = rc->texture->w - rc->tex.x - 1;
}

void    draw_wall(t_raycasting *rc, Uint32 **canvas)
{
  int     d;
  Uint32  color;
  int     y;

  y = rc->draw_start - 1;
  while (++y < rc->draw_end)
  {
    d = y * 256 - (WIN_H * rc->p_z * 256) + rc->lineHeight * 128; //256 and 128 factors to avoid floats
    // TODO: avoid the division to speed this up
    rc->tex.y = ((d * rc->texture->h) / rc->lineHeight) / 256;
    rc->tex.y = rc->tex.y % rc->texture->h;
    color = ((Uint32 *)rc->texture->pixels)[rc->texture->w * rc->tex.y + rc->tex.x];
    //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
    if(rc->side == 1) color = (color >> 1) & 8355711;
    (*canvas)[y * WIN_W + rc->x] = color;
  }
}

void    init_raycasting_draw_floor(t_raycasting *rc)
{
  //4 different wall directions possible
  if(rc->side == 0 && rc->ray_dir.x > 0)
  {
    rc->floor.x = rc->map.x;
    rc->floor.y = rc->map.y + rc->wall_x;
  }
  else if(rc->side == 0 && rc->ray_dir.x < 0)
  {
    rc->floor.x = rc->map.x + 1.0;
    rc->floor.y = rc->map.y + rc->wall_x;
  }
  else if(rc->side == 1 && rc->ray_dir.y > 0)
  {
    rc->floor.x = rc->map.x + rc->wall_x;
    rc->floor.y = rc->map.y;
  }
  else
  {
    rc->floor.x = rc->map.x + rc->wall_x;
    rc->floor.y = rc->map.y + 1.0;
  }
  if (rc->draw_end < 0)
    rc->draw_end = WIN_H; //becomes < 0 when the integer overflows
}

void    draw_floor(t_raycasting *rc, t_player *p, Uint32 **canvas)
{
  double weight;
  double currentFloorX;
  double currentFloorY;
  double distWall, distPlayer, currentDist;
  int   y;

  distWall = rc->perp_wall_dist;
  distPlayer = 0.0;
  y = rc->draw_end;
  while (++y < WIN_H)
  {
    currentDist = WIN_H / (2.0 * y - (WIN_H * rc->p_z * 2.0)); //you could make a small lookup table for this instead
    weight = (currentDist - distPlayer) / (distWall - distPlayer);
    currentFloorX = weight * rc->floor.x + (1.0 - weight) * p->pos.x;
    currentFloorY = weight * rc->floor.y + (1.0 - weight) * p->pos.y;
    rc->floor_tex.x = (int)(currentFloorX * rc->texture->w) % rc->texture->w;
    rc->floor_tex.y = (int)(currentFloorY * rc->texture->h) % rc->texture->h;
    // int checkerBoardPattern = ((int)(currentFloorX + currentFloorY)) % 2;
    // int floorTexture;
    // if(checkerBoardPattern == 0) floorTexture = 3;
    // else floorTexture = 4;
    (*canvas)[y * WIN_W + rc->x] = (((Uint32 *)rc->texture->pixels)[rc->texture->w * rc->floor_tex.y + rc->floor_tex.x] >> 1) & 8355711; //floor
  }
}

void    draw_ceiling(t_raycasting *rc, t_player *p, Uint32 **canvas)
{
  double weight;
  double currentFloorX;
  double currentFloorY;
  double distWall, distPlayer, currentDist;
  int   y;

  distWall = rc->perp_wall_dist;
  distPlayer = 0.0;
  y = 0;
  while (++y < rc->draw_start)
  {
    currentDist = WIN_H / ((WIN_H * rc->p_z * 2.0) - 2.0 * y); //you could make a small lookup table for this instead
    weight = (currentDist - distPlayer) / (distWall - distPlayer);
    currentFloorX = weight * rc->floor.x + (1.0 - weight) * p->pos.x;
    currentFloorY = weight * rc->floor.y + (1.0 - weight) * p->pos.y;
    rc->floor_tex.x = (int)(currentFloorX * rc->texture->w) % rc->texture->w;
    rc->floor_tex.y = (int)(currentFloorY * rc->texture->h) % rc->texture->h;
    // int checkerBoardPattern = ((int)(currentFloorX + currentFloorY)) % 2;
    // int floorTexture;
    // if(checkerBoardPattern == 0) floorTexture = 3;
    // else floorTexture = 4;
    (*canvas)[y * WIN_W + rc->x] = ((Uint32 *)rc->texture->pixels)[rc->texture->w * rc->floor_tex.y + rc->floor_tex.x]; //ceiling (symmetrical!)
  }
}

void    draw_screen(t_doom *doom)
{
  doom->raycasting.texture = get_surface(doom, 2);
  doom->raycasting.x = -1;
  while (++doom->raycasting.x < WIN_W)
  {
    init_raycasting(&doom->raycasting, &doom->you);
    ray_hit(&doom->raycasting, doom->nmap);

    init_raycasting_draw_wall(&doom->raycasting, &doom->you);
    draw_wall(&doom->raycasting, &doom->s_pixels);

    init_raycasting_draw_floor(&doom->raycasting);
    draw_floor(&doom->raycasting, &doom->you, &doom->s_pixels);
    draw_ceiling(&doom->raycasting, &doom->you, &doom->s_pixels);
  }
}