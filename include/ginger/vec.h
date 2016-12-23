// Copyright 2016 Douglas Moore. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#pragma once

#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

struct gvec_header
{
  size_t capacity;
  size_t size;
  size_t length;
};

typedef void* gvec_t;
typedef void const* gvec_const_t;

#define gvec_cap(v) ((struct gvec_header*)v)[-1].capacity
#define gvec_size(v) ((struct gvec_header*)v)[-1].size
#define gvec_len(v) ((struct gvec_header*)v)[-1].length
#define gvec_isempty(v) !(v && gvec_len(v))

gvec_t gvec_alloc(size_t capacity, size_t length, size_t size);
void gvec_free(gvec_t v);
gvec_t gvec_dup(gvec_const_t v);

gvec_t gvec_reserve(gvec_t v, size_t capacity);
gvec_t gvec_shrink(gvec_t v);

#define gvec_push(v, x) \
if (v && gvec_len(v) >= gvec_cap(v)) { \
  size_t cap = (v && gvec_cap(v)) ? 2*gvec_cap(v) : 1; \
  v = gvec_reserve(v, cap); \
} \
if (v) { v[gvec_len(v)++] = x; } else { raise(SIGSEGV); }

#define gvec_pop(v) if (v && gvec_len(v) > 0) { --gvec_len(v); }

#define gvec_print(fmt, v) do \
{ \
  for (size_t i = 0; i < gvec_len(v); ++i) printf(fmt, v[i]); \
} while(0);
