#include "doom.h"

Uint32            calc_gradient(Uint32 color1, Uint32 color2, double stage)
{
    return (((Uint32)((((color1 >> 16) & 0xFF) + ((color2 >> 16) & 0xFF)) * stage) << 16)
    | ((Uint32)((((color1 >> 8) & 0xFF) + ((color2 >> 8) & 0xFF)) * stage) << 8)
    | ((Uint32)(((color1 & 0xFF) + (color2 & 0xFF)) * stage)));
}

void  swap(double *a, double *b)
{
  double  tmp;

  tmp = *a;
  *a = *b;
  *b = tmp;
}

void combSort(int* order, double* dist, int amount)
{
  int i;
  int j;
  double tmp;
  int gap = amount;
  int swapped = 0;
  while (gap > 1 || swapped)
  {
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
        swapped = 1;
      }
    }
  }
}