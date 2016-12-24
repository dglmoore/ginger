// Copyright 2016 Douglas Moore. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include <ginger/vector.h>
#include <math.h>
#include <string.h>

#define min(x,y) (x < y) ? x : y;

gvector_t gvector_alloc(size_t capacity, size_t length, size_t size)
{
  if (size)
  {
    length = (length > capacity) ? capacity : length;
    struct gvector_header *v = malloc(sizeof(struct gvector_header) + capacity * size);
    if (v)
    {
      v->capacity = capacity; 
      v->size = size;
      v->length = length;
      ++v;
    }
    return v;
  }
  return NULL;
}

void gvector_free(gvector_t v)
{
  if (v)
  {
    struct gvector_header *w = v;
    --w;
    free(w);
  }
}

gvector_t gvector_dup(gvector_const_t v)
{
  if (v)
  {
    gvector_t *w = gvector_alloc(gvector_cap(v), gvector_len(v), gvector_size(v));
    if (w)
    {
      memcpy(w, v, gvector_len(v) * gvector_size(v));
    }
    return w;
  }
  return NULL;
}

size_t gvector_copy(gvector_t dst, gvector_const_t src)
{
  if (dst && src)
  {
    if (gvector_size(dst) == gvector_size(src))
    {
      size_t len = min(gvector_len(dst), gvector_len(src));
      memcpy(dst, src, len * gvector_size(src));
      return len;
    }
  }
  return 0;
}

gvector_t gvector_reserve(gvector_t v, size_t capacity)
{
  if (v)
  {
    struct gvector_header *w = ((struct gvector_header*)v) - 1;
    struct gvector_header *u = realloc(w, sizeof(struct gvector_header) + capacity * w->size);
    if (u)
    {
      u->capacity = capacity;
      if (u->length > u->capacity)
      {
        u->length = u->capacity;
      }
      ++u;
    }
    return u;
  }
  return NULL;
}

gvector_t gvector_shrink(gvector_t v)
{
  if (v)
  {
    return gvector_reserve(v, gvector_len(v));
  }
  return NULL;
}
