// Copyright 2016-2017 Douglas G. Moore. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#pragma once

#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct gvector_header
{
  size_t capacity;
  size_t size;
  size_t length;
};

typedef void* gvector;
typedef void const* gvector_const;

#define gvector_cap(v) ((struct gvector_header*)v)[-1].capacity
#define gvector_size(v) ((struct gvector_header*)v)[-1].size
#define gvector_len(v) ((struct gvector_header*)v)[-1].length
#define gvector_isempty(v) !(v && gvector_len(v))

gvector gvector_alloc(size_t capacity, size_t length, size_t size);
void gvector_free(gvector v);
gvector gvector_dup(gvector_const v);
size_t gvector_copy(gvector dst, gvector_const src);

gvector gvector_reserve(gvector v, size_t capacity);
gvector gvector_shrink(gvector v);

#define gvector_push(v, x) \
if (v && gvector_len(v) >= gvector_cap(v)) { \
  size_t cap = (v && gvector_cap(v)) ? 2*gvector_cap(v) : 1; \
  v = gvector_reserve(v, cap); \
} \
if (v) { v[gvector_len(v)++] = x; } else { raise(SIGSEGV); }

#define gvector_pop(v) if (v && gvector_len(v) > 0) { --gvector_len(v); }

#ifdef __cplusplus
}
#endif