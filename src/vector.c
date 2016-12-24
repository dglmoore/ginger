// Copyright 2016 Douglas Moore. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include <ginger/vector.h>
#include <math.h>
#include <string.h>

#define min(x,y) (x < y) ? x : y;

gvec_t gvec_alloc(size_t capacity, size_t length, size_t size)
{
  if (size)
  {
    length = (length > capacity) ? capacity : length;
    struct gvec_header *v = malloc(sizeof(struct gvec_header) + capacity * size);
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

void gvec_free(gvec_t v)
{
  if (v)
  {
    struct gvec_header *w = v;
    --w;
    free(w);
  }
}

gvec_t gvec_dup(gvec_const_t v)
{
  if (v)
  {
    gvec_t *w = gvec_alloc(gvec_cap(v), gvec_len(v), gvec_size(v));
    if (w)
    {
      memcpy(w, v, gvec_len(v) * gvec_size(v));
    }
    return w;
  }
  return NULL;
}

size_t gvec_copy(gvec_t dst, gvec_const_t src)
{
  if (dst && src)
  {
    if (gvec_size(dst) == gvec_size(src))
    {
      size_t len = min(gvec_len(dst), gvec_len(src));
      memcpy(dst, src, len * gvec_size(src));
      return len;
    }
  }
  return 0;
}

gvec_t gvec_reserve(gvec_t v, size_t capacity)
{
  if (v)
  {
    struct gvec_header *w = ((struct gvec_header*)v) - 1;
    struct gvec_header *u = realloc(w, sizeof(struct gvec_header) + capacity * w->size);
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

gvec_t gvec_shrink(gvec_t v)
{
  if (v)
  {
    return gvec_reserve(v, gvec_len(v));
  }
  return NULL;
}
