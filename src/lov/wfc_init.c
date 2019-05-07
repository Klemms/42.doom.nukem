#include "doom.h"

void    wfc_rayhit(t_raycasting *rc, t_player *p, t_nmap *nmap)
{
  int hit;

  (void)p;
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
    if (nmap->map[rc->map.y][rc->map.x].collides && nmap->map[rc->map.y][rc->map.x].block_type != block_door && nmap->map[rc->map.y][rc->map.x].block_type != block_window)
      hit = 1;
  }
}

void    wfc_init(t_raycasting *rc, t_player *p)
{
  rc->p_z = p->pitch;
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

void    wfc_wall_init(t_raycasting *rc, t_player *p)
{
  if (rc->side == 0) // HERE
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

void    wfc_fc_init(t_raycasting *rc)
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