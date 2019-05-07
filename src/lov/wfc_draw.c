#include "doom.h"

void    wfc_wall_draw(t_raycasting *rc, Uint32 **canvas)
{
  int     d;
  Uint32  color;
  int     y;

  y = rc->draw_start - 1;
  while (++y < rc->draw_end)
  {
    d = ((int)(y - (WIN_H * rc->p_z)) << 8) + ((int)rc->lineHeight << 7); //256 and 128 factors to avoid floats
    // TODO: avoid the division to speed this up
    rc->tex.y = ((d * rc->texture->h) / rc->lineHeight) >> 8;
    rc->tex.y = rc->tex.y % rc->texture->h;
    color = ((Uint32 *)rc->texture->pixels)[rc->texture->w * rc->tex.y + rc->tex.x];
    //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
    if(rc->side == 1) color = (color >> 1) & 8355711;
    (*canvas)[y * WIN_W + rc->x] = color;
  }
}


void    wfc_floor_draw(t_raycasting *rc, t_player *p, Uint32 **canvas)
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
    currentDist = WIN_H / (2.0 * (y - (WIN_H * rc->p_z))); //you could make a small lookup table for this instead
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

void    wfc_ceiling_draw(t_raycasting *rc, t_player *p, Uint32 **canvas)
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
    currentDist = WIN_H / (((WIN_H * rc->p_z) - y) * 2.0); //you could make a small lookup table for this instead
    weight = (currentDist - distPlayer) / (distWall - distPlayer);
    currentFloorX = weight * rc->floor.x + (1.0 - weight) * p->pos.x;
    currentFloorY = weight * rc->floor.y + (1.0 - weight) * p->pos.y;
    rc->floor_tex.x = (int)(currentFloorX * rc->texture->w) % rc->texture->w;
    rc->floor_tex.y = (int)(currentFloorY * rc->texture->h) % rc->texture->h;
    (*canvas)[y * WIN_W + rc->x] = ((Uint32 *)rc->texture->pixels)[rc->texture->w * rc->floor_tex.y + rc->floor_tex.x]; //ceiling (symmetrical!)
  }
}

void  draw_wfc(t_doom *doom, double **z_buffer)
{
  wfc_init(&doom->raycasting, &doom->you);
  wfc_rayhit(&doom->raycasting, &doom->you, doom->nmap);
  if (side == 0)
  {
    if (doom->raycasting.step.x < 0)
      doom->raycasting.texture = get_surface(doom, doom->nmap.map[doom->raycasting.map.y][doom->raycasting.map.x].texture);
    else
      doom->raycasting.texture = get_surface(doom, doom->nmap.map[doom->raycasting.map.y][doom->raycasting.map.x].texture);
  }
  wfc_wall_init(&doom->raycasting, &doom->you);
  wfc_wall_draw(&doom->raycasting, &doom->s_pixels);

  (*z_buffer)[doom->raycasting.x] = doom->raycasting.perp_wall_dist;
  wfc_fc_init(&doom->raycasting);
  wfc_floor_draw(&doom->raycasting, &doom->you, &doom->s_pixels);
  wfc_ceiling_draw(&doom->raycasting, &doom->you, &doom->s_pixels);
}