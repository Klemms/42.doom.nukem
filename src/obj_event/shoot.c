#include "doom.h"
#include "../../libft/libft.h"
void			shoot(t_doom *doom, t_player *p)
{
    if (SDL_GetMouseState(NULL, NULL) == SDL_BUTTON_LMASK)
    {
        t_sprite *new;
        new = mmalloc(sizeof(t_sprite));
        new->pos.x = p->pos.x;
        new->pos.y = p->pos.y;
        new->vel.x = p->dir.x * 2;
        new->vel.y = p->dir.y * 2;
        new->type = rend_flat;
        doom->lsprite.numbSprites++;
        lstcontainer_add(doom->nmap->sprites, new);
    }
}
/*
int			is_right_clicking()
{
    if (SDL_GetMouseState(NULL, NULL) == SDL_BUTTON_RMASK)
        doom->settings.right_click = 1;
	return (SDL_GetMouseState(NULL, NULL) == SDL_BUTTON_RMASK);
}
*/
