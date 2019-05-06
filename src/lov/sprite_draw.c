#include "doom.h"

Uint32            calc_gradient(Uint32 color1, Uint32 color2, double stage)
{
        Uint32             color;
        Uint32             r;
        Uint32             g;
        Uint32             b;

        r = (Uint32)((((color1 >> 16) & 0xFF) + ((color2 >> 16) & 0xFF)) * stage) << 16;
        g = (Uint32)((((color1 >> 8) & 0xFF) + ((color2 >> 8) & 0xFF)) * stage) << 8;
        b = (Uint32)((color1 & 0xFF) + (color2 & 0xFF)) * stage;
        color = r | g | b;
        return (color);
}

void  swap(double *a, double *b)
{
  double  *tmp;

  *tmp = *a;
  *a = *b;
  *b = *tmp;
}

//sort algorithm
void combSort(int* order, double* dist, int amount)
{
  int i;
  int j;
  double tmp;
  int gap = amount;
  int swapped = 0;
  while (gap > 1 || swapped)
  {
    //shrink factor 1.3
    gap = (gap * 10) / 13;
    if (gap == 9 || gap == 10) gap = 11;
    if (gap < 1) gap = 1;
    swapped = 0;

    i = -1;
    while (++i < amount - gap)
    {
      j = i + gap;
      if (dist[i] < dist[j])
      {

        tmp = dist[i];
        dist[i] = dist[j];
        dist[j] = tmp;
        tmp = order[i];
        order[i] = order[j];
        order[j] = tmp;
        //swap(&dist[i], &dist[j]);
        //swap((double *)&order[i], (double *)&order[j]);
        swapped = 1;
      }
    }
  }
}

void              sprite_flat_draw(t_raycasting *rc, double **z_buffer, SDL_Surface *texture_sprite, Uint32 **canvas)
{
  int stripe;
  Uint32 color;
  int y;
  int d;
  
  stripe = rc->draw_start_x - 1;
  while (++stripe < rc->draw_end_x)
  {
    rc->tex_x = (int)((stripe - (-rc->sprite_width / 2 + rc->sprite_screen_x)) * texture_sprite->w / rc->sprite_width);
    //the conditions in the if are:
    //1) it's in front of camera plane so you don't see things behind you
    //2) it's on the screen (left)
    //3) it's on the screen (right)
    //4) ZBuffer, with perpendicular distance
    if (rc->transform.y > 0 && stripe > 0 && stripe < WIN_W && rc->transform.y < (*z_buffer)[stripe])
    {
      y = rc->draw_start_y - 1;
      while (++y < rc->draw_end_y) //for every pixel of the current stripe
      {
        d = ((y - rc->v_move_screen) - (WIN_H * rc->p_z)) * 256 + rc->sprite_height * 128; //256 and 128 factors to avoid floats
        //d = (y - (WIN_H * rc->p_z)) * 256) + rc->lineHeight * 128; 
        rc->tex_y = ((d * texture_sprite->h) / rc->sprite_height) / 256; // this 64 whas HEIGHT the other WIDTH
        color = ((Uint32*)texture_sprite->pixels)[texture_sprite->w * rc->tex_y + rc->tex_x]; //get current color from the texture
        if((color & 0x00FFFFFF) != 0)
          (*canvas)[y * WIN_W + stripe] = color;//calc_gradient(0xFFFFFF - (*canvas)[y * WIN_W + stripe], color, 0.35);// + color / 2; //paint pixel if it isn't black, black is the invisible color

      }
    }
  }
}

void    sprite_wall_draw(t_raycasting *rc, double **z_buffer, Uint32 **canvas)
{
  int     d;
  Uint32  color;
  int     y;

  if (rc->perp_wall_dist > 0 && rc->perp_wall_dist < (*z_buffer)[rc->x])
  {
    y = rc->draw_start - 1;
    while (++y < rc->draw_end)
    {
      d = (y - (WIN_H * rc->p_z)) * 256 + rc->lineHeight * 128; //256 and 128 factors to avoid floats
      // TODO: avoid the division to speed this up
      rc->tex.y = ((d * rc->texture->h) / rc->lineHeight) / 256;
      rc->tex.y = rc->tex.y % rc->texture->h;
      color = ((Uint32 *)rc->texture->pixels)[rc->texture->w * rc->tex.y + rc->tex.x];
      //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
      if(rc->side == 1) color = (color >> 1) & 8355711;
      (*canvas)[y * WIN_W + rc->x] = color;//calc_gradient((*canvas)[y * WIN_W + rc->x], color + 0x000066, 0.5);
    }
  }
}

void    sprite_door_draw(t_raycasting *rc, double **z_buffer, Uint32 **canvas)
{
  int     d;
  Uint32  color;
  int     y;

  if (rc->perp_wall_dist > 0 && rc->perp_wall_dist < (*z_buffer)[rc->x])
  {
    y = rc->draw_start - 1;
    while (++y < rc->draw_end)
    {
      d = (y - (WIN_H * rc->p_z)) * 256 + rc->lineHeight * 128; //256 and 128 factors to avoid floats
      // TODO: avoid the division to speed this up
      rc->tex.y = ((d * rc->texture->h) / rc->lineHeight) / 256;
      rc->tex.y = rc->tex.y % rc->texture->h;
      color = ((Uint32 *)rc->texture->pixels)[rc->texture->w * rc->tex.y + rc->tex.x];
      //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
      if(rc->side == 1) color = (color >> 1) & 8355711;
      (*canvas)[y * WIN_W + rc->x] = color;//calc_gradient((*canvas)[y * WIN_W + rc->x], color + 0x000066, 0.5);
    }
  }
}

int    sprite_rayhit(t_raycasting *rc, t_player *p, t_nmap *nmap, int block_type)
{
  int hit;
  hit = 0;
  rc->dist_hit = 0;
  while (hit == 0 && rc->dist_hit < 40)
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

    if (nmap->map[rc->map.y][rc->map.x].collides)
    {
      if (nmap->map[rc->map.y][rc->map.x].block_type == block_type)
        return (1);
      else
        return (0);
    }
  }
  return (0);
}

void    draw_sprites(t_doom *doom, t_raycasting *rc, t_player *p, double **z_buffer, Uint32 **canvas)
{
  //SPRITE CASTING
  
  //t_list_thin_blocks  thin_blocks;
  //t_thin_block *b;

  int numSprites_wall = 10;
  int spriteOrder_wall[10];
  double spriteDistance_wall[10];
  t_vec sprite_wall[10] = { { 4, 4, 1 }, { 4, 6, 0 } };

  int numSprites = 2;
  int spriteOrder[2];
  double spriteDistance[2];
  t_vec   sprite_flat[2] = { { 4.5, 3.5, 1 }, { 2.5, 2.5, 0 } };

  int i;
  SDL_Surface *texture_sprite;

  i = -1;
  while (++i < numSprites)
  {
    spriteOrder[i] = i;
    spriteDistance[i] = ((p->pos.x - sprite_flat[i].x) * (p->pos.x - sprite_flat[i].x) + (p->pos.y - sprite_flat[i].y) * (p->pos.y - sprite_flat[i].y)); //sqrt not taken, unneeded
  }

  i = -1;
  while (++i < numSprites_wall)
  {
    spriteOrder_wall[i] = i;
    spriteDistance_wall[i] = ((p->pos.x - sprite_wall[i].x) * (p->pos.x - sprite_wall[i].x) + (p->pos.y - sprite_wall[i].y) * (p->pos.y - sprite_wall[i].y)); //sqrt not taken, unneeded
  }
  combSort(spriteOrder, spriteDistance, numSprites);
  combSort(spriteOrder_wall, spriteDistance_wall, numSprites_wall);
  i = -1;

  int end = -1;
  int start = 0;
  rc->texture = get_surface(doom, 2);
  while (++i < numSprites_wall)
  {
    //if (sprite[numSprites].cast == wall_like)
    // {
    rc->x = end;
    while (++rc->x < WIN_W)
    {
      wfc_init(rc, p);
      if (sprite_rayhit(&doom->raycasting, &doom->you, doom->nmap, block_small_wall))
      {
        wfc_init(rc, p);
        while (sprite_rayhit(&doom->raycasting, &doom->you, doom->nmap) && rc->x < WIN_W)
        {
          wfc_wall_init(rc, p);//, sprite_wall, spriteOrder, i);
          sprite_wall_draw(rc, z_buffer, canvas);
          rc->x++;
          wfc_init(rc, p);
          end = rc->x - 1;
        }
        break ;
      }
    }
    // }
  }
  i = -1;
  while (++i < numSprites)
  {
    //else if (sprite[numSprites].cast == flat)
    //{
    texture_sprite = get_surface(doom, sprite_flat[spriteOrder[i]].z);
    sprite_flat_init(rc, p, i, texture_sprite, sprite_flat, spriteOrder);
    sprite_flat_draw(rc, z_buffer, texture_sprite, canvas);
    //}
  }
}