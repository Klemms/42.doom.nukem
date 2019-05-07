#include "doom.h"

void              sprite_flat_draw(t_raycasting *rc, double **z_buffer, SDL_Surface *texture_sprite, Uint32 **canvas)
{
  int stripe;
  Uint32 color;
  int y;
  int d;
  
  stripe = rc->draw_start_x - 1;
  while (++stripe < rc->draw_end_x)
  {
    rc->tex_x = (int)((stripe - (-rc->sprite_width / 2 + rc->sprite_screen_x)) * rc->texture.w / rc->sprite_width);
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
        d = ((y - rc->v_move_screen) - (WIN_H * rc->p_z)) * 256 + rc->sprite_height * 128; //256 and 128 factors to avoid floats
        //d = (y - (WIN_H * rc->p_z)) * 256) + rc->lineHeight * 128; 
        rc->tex_y = ((d * rc->texture.h) / rc->sprite_height) / 256; // this 64 whas HEIGHT the other WIDTH
        color = ((Uint32*)rc->texture.pixels)[rc->texture.w * rc->tex_y + rc->tex_x]; //get current color from the texture
        if((color & 0x00FFFFFF) != 0)
          (*canvas)[y * WIN_W + stripe] = color;//calc_gradient(0xFFFFFF - (*canvas)[y * WIN_W + stripe], color, 0.35);// + color / 2; //paint pixel if it isn't black, black is the invisible color

      }
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

void    sprite_door_draw(t_raycasting *rc, double **z_buffer, Uint32 **canvas, t_nmap *nmap)
{
  int     d;
  Uint32  color;
  int     y;

  if (rc->perp_wall_dist > 0 && rc->perp_wall_dist < (*z_buffer)[rc->x])
  {
    //if (nmap->map[rc->map.y][rc->map.x].block_type == block_small_wall)
    //  (*z_buffer)[rc->x] = rc->perp_wall_dist;
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
      (*canvas)[y * WIN_W + rc->x] = color;//calc_gradient((*canvas)[y * WIN_W + rc->x], color + 0x222266, 0.5);
    }
  }
}


void sprite_cast_wall(t_raycasting *rc, t_player *p, t_nmap nmap, double **z_buffer, Uint32 **canvas);
{
  while (++rc->x < WIN_W)
  {
    wfc_init(rc, p);
    if (sprite_rayhit(rc, p, nmap, block_small_wall))// && rc->perp_wall_dist < (*z_buffer)[rc->x])
    {
      if (cur_sprite->pos.x != rc->map.x || cur_sprite->pos.y != rc->map.y)
        continue ;
      sprite_door_init(rc, p);//, sprite_wall, spriteOrder, i);
      sprite_door_draw(rc, z_buffer, canvas, nmap);
      wfc_init(rc, p);
    }
  }
}

void    draw_sprites(t_doom *doom, t_raycasting *rc, t_player *p, double **z_buffer, Uint32 **canvas)
{
  //SPRITE CASTING
  int       numbSprites = 4;
//  int       spritesOrder[4];
//  int       spritesDist[4];
  t_sprite  sprites[] = { { { 3,3 }, 0, 0 }, { { 4.3, 5.5 }, 1, 1 }, { { 6, 6 }, 0, 1 }, { { 9.4, 7 }, 2, 1 } };
  int i;

  t_l_sprite  lsprite;
// HERE
  // INIT t_l_sprite == lsprite->sprites = sprites[0];
  i = -1;
  while (++i < numbSprites)
  {
    spritesOrder[i] = i;
    spritesDistance[i] = ((p->pos.x - sprites[i].pos.x) * (p->pos.x - sprites[i].pos.x) + (p->pos.y - sprites[i].pos.y) * (p->pos.y - sprites[i].pos.y)); //sqrt not taken, unneeded
  }

  combSort(spritesOrder, spritesDistance, numbSprites);
  i = -1;
  t_sprite *cur_sprite;
  while (++i < numbSprites)
  {
    rc->cur_sprite = sprites[spritesOrder[i]];
    rc->texture = get_surface(doom, cur_sprite->texture_id);
    if (cur_sprite->render_mode == door || cur_sprite->render_mode == window)
    {
      sprite_cast_wall(rc, p, doom->nmap, z_buffer, canvas);

    }
    else if (cur_sprite->render_mode == door)
    {
      sprite_flat_init(rc, p, i, sprite_flat, spriteOrder);
      sprite_flat_draw(rc, z_buffer, canvas);
    }
  }
}

        /*
        wfc_init(rc, p);
        if (sprite_rayhit(&doom->raycasting, &doom->you, doom->nmap, block_small_wall))
        {
          wfc_init(rc, p);
          while (sprite_rayhit(&doom->raycasting, &doom->you, doom->nmap, block_small_wall) && rc->x < WIN_W)
          {
            wfc_wall_init(rc, p);//, sprite_wall, spriteOrder, i);
            sprite_wall_draw(rc, z_buffer, canvas);
            rc->x++;
            wfc_init(rc, p);
            end = rc->x - 1;
          }
          break ;
        }*/