// Copyright 2016 Douglas Moore. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#pragma once

#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

struct gvector_header
{
  size_t capacity;
  size_t size;
  size_t length;
};

typedef void* gvector_t;
typedef void const* gvector_const_t;

#define gvector_cap(v) ((struct gvector_header*)v)[-1].capacity
#define gvector_size(v) ((struct gvector_header*)v)[-1].size
#define gvector_len(v) ((struct gvector_header*)v)[-1].length
#define gvector_isempty(v) !(v && gvector_len(v))

gvector_t gvector_alloc(size_t capacity, size_t length, size_t size);
void gvector_free(gvector_t v);
gvector_t gvector_dup(gvector_const_t v);
size_t gvector_copy(gvector_t dst, gvector_const_t src);

gvector_t gvector_reserve(gvector_t v, size_t capacity);
gvector_t gvector_shrink(gvector_t v);

#define gvector_push(v, x) \
if (v && gvector_len(v) >= gvector_cap(v)) { \
  size_t cap = (v && gvector_cap(v)) ? 2*gvector_cap(v) : 1; \
  v = gvector_reserve(v, cap); \
} \
if (v) { v[gvector_len(v)++] = x; } else { raise(SIGSEGV); }

#define gvector_pop(v) if (v && gvector_len(v) > 0) { --gvector_len(v); }

#define gvector_print(fmt, v) do \
{ \
  for (size_t i = 0; i < gvector_len(v); ++i) printf(fmt, v[i]); \
} while(0);
