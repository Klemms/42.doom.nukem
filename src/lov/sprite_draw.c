#include "doom.h"

void              sprite_flat_draw(t_raycasting *rc, double **z_buffer, Uint32 **canvas)
{
  int stripe;
  Uint32 color;
  int y;
  int d;
  
  stripe = rc->draw_start_x - 1;
  while (++stripe < rc->draw_end_x)
  {
    rc->tex_x = (int)((stripe - (-((int)rc->sprite_width >> 1) + rc->sprite_screen_x)) * rc->texture->w / rc->sprite_width);
    //the conditions in the if are:
    //1) it's in front of camera plane so you don't see things behind you
    //2) it's on the screen (left)
    //3) it's on the screen (right)
    //4) ZBuffer, with perpendicular distance
    if (rc->transform.y > 0 && stripe > 0 && stripe < WIN_W && rc->transform.y < (*z_buffer)[stripe])
    {
      //(*z_buffer)[stripe] = rc->transform.y;
      y = rc->draw_start_y - 1;
      while (++y < rc->draw_end_y) //for every pixel of the current stripe
      {
        d = ((int)((y - rc->v_move_screen) - (WIN_H * rc->p_z)) << 8) + ((int)rc->sprite_height << 7); //256 and 128 factors to avoid floats
        //d = (y - (WIN_H * rc->p_z)) * 256) + rc->lineHeight * 128; 
        rc->tex_y = ((d * rc->texture->h) / rc->sprite_height) >> 8; // this 64 whas HEIGHT the other WIDTH
        color = ((Uint32*)rc->texture->pixels)[rc->texture->w * rc->tex_y + rc->tex_x]; //get current color from the texture
        if((color & 0x00FFFFFF) != 0)
          (*canvas)[y * WIN_W + stripe] = color;//calc_gradient(0xFFFFFF - (*canvas)[y * WIN_W + stripe], color, 0.35);// + color / 2; //paint pixel if it isn't black, black is the invisible color

      }
    }
  }
}

int    sprite_rayhit(t_raycasting *rc, t_player *p, t_nmap *nmap)
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
      if (nmap->map[rc->map.y][rc->map.x].block_type == block_window || nmap->map[rc->map.y][rc->map.x].block_type == block_door)
        return (1);
      else
        return (0);
    }
  }
  return (0);
}

void    sprite_door_draw(t_raycasting *rc, double **z_buffer, Uint32 **canvas, t_nmap *nmap, double stage)
{
  int     d;
  Uint32  color;
  int     y;

  if (rc->perp_wall_dist > 0 && rc->perp_wall_dist < (*z_buffer)[rc->x])
  {
    y = rc->draw_start - 1 + rc->lineHeight * stage;
    while (++y < rc->draw_end)
    {
      d = ((int)((y - rc->lineHeight * stage) - (WIN_H * rc->p_z)) << 8) + ((int)rc->lineHeight << 7); //256 and 128 factors to avoid floats
      // TODO: avoid the division to speed this up
      rc->tex.y = ((d * rc->texture->h) / rc->lineHeight) >> 8;
      rc->tex.y = rc->tex.y % rc->texture->h;
      color = ((Uint32 *)rc->texture->pixels)[rc->texture->w * rc->tex.y + rc->tex.x];
      //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
      if(rc->side == 1) color = (color >> 1) & 8355711;
      if (rc->cur_sprite.render_mode == rend_window)
        color = calc_gradient((*canvas)[y * WIN_W + rc->x], color + 0x222266, 0.5);
      (*canvas)[y * WIN_W + rc->x] = color;
    }
  }
}

void sprite_cast_wall(t_raycasting *rc, t_player *p, t_nmap *nmap, double **z_buffer, Uint32 **canvas)
{
  rc->x = -1;
  while (++rc->x < WIN_W)
  {
    wfc_init(rc, p);
    if (sprite_rayhit(rc, p, nmap))// && rc->perp_wall_dist < (*z_buffer)[rc->x])
    {
      if (rc->cur_sprite.pos.x != rc->map.x || rc->cur_sprite.pos.y != rc->map.y)
        continue ;
      sprite_door_init(rc, p);//, sprite_wall, spritesOrder, i);
      sprite_door_draw(rc, z_buffer, canvas, nmap, rc->cur_sprite.stage);
      wfc_init(rc, p);
    }
  }
}

void    draw_sprites(t_doom *doom, t_raycasting *rc, t_player *p, double **z_buffer, Uint32 **canvas, t_l_sprite *lsprite)
{
  //SPRITE CASTING
  lsprite->numbSprites = 4;

  int i;
  
  i = -1; 
  while (++i < lsprite->numbSprites)
  {
    lsprite->spritesOrder[i] = i;
    lsprite->spritesDist[i] = ((p->pos.x - lsprite->sprites[i].pos.x) * (p->pos.x - lsprite->sprites[i].pos.x) + (p->pos.y - lsprite->sprites[i].pos.y) * (p->pos.y - lsprite->sprites[i].pos.y)); //sqrt not taken, unneeded
  }

  combSort(lsprite->spritesOrder, lsprite->spritesDist, lsprite->numbSprites);
  i = -1;
  while (++i < lsprite->numbSprites)
  {
    rc->cur_sprite = lsprite->sprites[lsprite->spritesOrder[i]];
    if (rc->cur_sprite.animated == 1)
    {
      if (rc->cur_sprite.stage < 1) lsprite->sprites[lsprite->spritesOrder[i]].stage += 0.01;
      else lsprite->sprites[lsprite->spritesOrder[i]].animated = 2;
    }
    else if (rc->cur_sprite.animated == 2)
    {
      if (rc->cur_sprite.stage > 0) lsprite->sprites[lsprite->spritesOrder[i]].stage -= 0.01;
      else lsprite->sprites[lsprite->spritesOrder[i]].animated = 1;
    }
    rc->texture = get_surface(doom, rc->cur_sprite.texture);
    if (rc->cur_sprite.render_mode == rend_door || rc->cur_sprite.render_mode == rend_window)
    {
      sprite_cast_wall(rc, p, doom->nmap, z_buffer, canvas);
    }
    else if (rc->cur_sprite.render_mode == rend_flat)
    {
      sprite_flat_init(rc, p, i, lsprite->sprites, lsprite->spritesOrder);
      sprite_flat_draw(rc, z_buffer, canvas);
    }
  }
}