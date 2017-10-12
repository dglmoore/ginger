// Copyright 2016-2017 Douglas G. Moore. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include <ginger/unit.h>
#include <ginger/vector.h>

UNIT(AllocateZeroSize)
{
  ASSERT_NULL(gvector_alloc(0, 0, 0));
  ASSERT_NULL(gvector_alloc(5, 0, 0));
  ASSERT_NULL(gvector_alloc(0, 5, 0));
  ASSERT_NULL(gvector_alloc(5, 5, 0));
}

UNIT(AllocateZero)
{
  int *v = gvector_alloc(0, 0, sizeof(int));
  ASSERT_NOT_NULL(v);
  ASSERT_EQUAL(0, gvector_cap(v));
  ASSERT_EQUAL(sizeof(int), gvector_size(v));
  ASSERT_EQUAL(0, gvector_len(v));
  gvector_free(v);
}

UNIT(AllocateOne)
{
  int *v = gvector_alloc(1, 0, sizeof(int));
  ASSERT_NOT_NULL(v);
  ASSERT_EQUAL(1, gvector_cap(v));
  ASSERT_EQUAL(sizeof(int), gvector_size(v));
  ASSERT_EQUAL(0, gvector_len(v));
  gvector_free(v);

  v = gvector_alloc(1, 1, sizeof(int));
  ASSERT_NOT_NULL(v);
  ASSERT_EQUAL(1, gvector_cap(v));
  ASSERT_EQUAL(sizeof(int), gvector_size(v));
  ASSERT_EQUAL(1, gvector_len(v));
  gvector_free(v);

  v = gvector_alloc(1, 2, sizeof(int));
  ASSERT_NOT_NULL(v);
  ASSERT_EQUAL(1, gvector_cap(v));
  ASSERT_EQUAL(sizeof(int), gvector_size(v));
  ASSERT_EQUAL(1, gvector_len(v));
  gvector_free(v);
}

UNIT(Duplicate)
{
  int q[5] = {2,3,4,5,6};
  int *v = gvector_alloc(5, 5, sizeof(int));
  ASSERT_NOT_NULL(v);
  memcpy(v, q, 5*sizeof(int));
  for (size_t i = 0; i < 5; ++i) ASSERT_EQUAL(i+2, v[i]);

  int *w = gvector_dup(v);
  ASSERT_NOT_NULL(w);
  ASSERT_EQUAL(5, gvector_cap(w));
  ASSERT_EQUAL(sizeof(int), gvector_size(w));
  ASSERT_EQUAL(5, gvector_len(w));
  for (size_t i = 0; i < 5; ++i) ASSERT_EQUAL(i+2, w[i]);

  gvector_free(w);
  gvector_free(v);
}

UNIT(CopyNull)
{
  int *v = NULL, *w = NULL;
  ASSERT_EQUAL(0, gvector_copy(w, v));

  v = gvector_alloc(5, 2, sizeof(int));
  ASSERT_NOT_NULL(v);
  ASSERT_EQUAL(0, gvector_copy(w, v));
  ASSERT_EQUAL(0, gvector_copy(v, w));
  gvector_free(v);
}

UNIT(CopySameSize)
{
  int *v = gvector_alloc(5, 5, sizeof(int));
  ASSERT_NOT_NULL(v);
  for (size_t i = 0; i < 5; ++i) v[i] = i;
  int *w = gvector_alloc(3, 3, sizeof(int));
  ASSERT_NOT_NULL(w);

  ASSERT_EQUAL(3, gvector_copy(w, v));
  for (size_t i = 0; i < 3; ++i) ASSERT_EQUAL(i, w[i]);

  for (size_t i = 0; i < 3; ++i) w[i] = i * i;
  ASSERT_EQUAL(3, gvector_copy(v, w));
  for (size_t i = 0; i < 3; ++i) ASSERT_EQUAL(i*i, v[i]);

  gvector_free(w);
  gvector_free(v);
}

UNIT(CopyDiffSize)
{
  int *v = gvector_alloc(5, 5, sizeof(int));
  ASSERT_NOT_NULL(v);
  char *w = gvector_alloc(10, 10, sizeof(char));
  ASSERT_NOT_NULL(w);

  ASSERT_EQUAL(0, gvector_copy(w,v));

  gvector_free(w);
  gvector_free(v);
}

UNIT(ReserveGrow)
{
  size_t const N = 2;

  int *v = gvector_alloc(N, N, sizeof(int));
  for (size_t i = 0; i < N; ++i) v[i] = (int)i;
  ASSERT_NOT_NULL(v);

  int *w = gvector_reserve(v, 3*N);
  ASSERT_NOT_NULL(w);
  ASSERT_EQUAL(6, gvector_cap(w));
  ASSERT_EQUAL(sizeof(int), gvector_size(w));
  ASSERT_EQUAL(N, gvector_len(w));
  for (size_t i = 0; i < N; ++i) ASSERT_EQUAL(i, w[i]);

  gvector_free(w);
}

UNIT(ReserveShrink)
{
  size_t const N = 2;
  int *v = gvector_alloc(3*N, 3*N, sizeof(int));
  for (size_t i = 0; i < 3*N; ++i) v[i] = (int)i;
  ASSERT_NOT_NULL(v);

  int *w = gvector_reserve(v, N);
  ASSERT_NOT_NULL(w);
  ASSERT_EQUAL(N, gvector_cap(w));
  ASSERT_EQUAL(sizeof(int), gvector_size(w));
  ASSERT_EQUAL(N, gvector_len(w));
  for (size_t i = 0; i < N; ++i) ASSERT_EQUAL(i, w[i]);

  gvector_free(w);
}

UNIT(ReserveZero)
{
  size_t const N = 2;
  int *v = gvector_alloc(3*N, 3*N, sizeof(int));
  for (size_t i = 0; i < 3*N; ++i) v[i] = (int)i;
  ASSERT_NOT_NULL(v);

  int *w = gvector_reserve(v, 0);
  ASSERT_NOT_NULL(w);
  ASSERT_EQUAL(0, gvector_cap(w));
  ASSERT_EQUAL(sizeof(int), gvector_size(w));
  ASSERT_EQUAL(0, gvector_len(w));

  gvector_free(w);
}

UNIT(ReserveNULL)
{
  ASSERT_NULL(gvector_reserve(NULL, 5));
}

UNIT(PushSuccess)
{
  int *v = gvector_alloc(3, 0, sizeof(int));
  ASSERT_NOT_NULL(v);
  gvector_push(v,1);
  gvector_push(v,2);
  gvector_push(v,3);
  ASSERT_EQUAL(3, gvector_cap(v));
  ASSERT_EQUAL(3, gvector_len(v));
  for (size_t i = 0; i < 3; ++i) ASSERT_EQUAL(i+1, v[i]);
  gvector_push(v,4);
  ASSERT_EQUAL(6, gvector_cap(v));
  ASSERT_EQUAL(4, gvector_len(v));
  for (size_t i = 0; i < 4; ++i) ASSERT_EQUAL(i+1, v[i]);
  gvector_free(v);
}

UNIT(PushFailure)
{
  int *v = NULL;
  ASSERT_SIGNAL(SIGSEGV, gvector_push(v, 0));
}

UNIT(Pop)
{
  int *v = gvector_alloc(3, 3, sizeof(int));
  ASSERT_NOT_NULL(v);

  gvector_pop(v);
  ASSERT_EQUAL(3, gvector_cap(v));
  ASSERT_EQUAL(2, gvector_len(v));

  gvector_pop(v);
  ASSERT_EQUAL(3, gvector_cap(v));
  ASSERT_EQUAL(1, gvector_len(v));

  gvector_pop(v);
  ASSERT_EQUAL(3, gvector_cap(v));
  ASSERT_EQUAL(0, gvector_len(v));

  gvector_pop(v);
  ASSERT_EQUAL(3, gvector_cap(v));
  ASSERT_EQUAL(0, gvector_len(v));

  gvector_free(v);
}

UNIT(IsEmpty)
{
  ASSERT_TRUE(gvector_isempty(NULL));

  int *v = NULL;
  ASSERT_TRUE(gvector_isempty(v));

  v = gvector_alloc(3, 0, sizeof(int));
  ASSERT_TRUE(gvector_isempty(v));

  gvector_push(v, 1);
  ASSERT_FALSE(gvector_isempty(v));

  gvector_free(v);
}

UNIT(Shrink)
{
  int *v = gvector_alloc(5, 2, sizeof(int));
  ASSERT_NOT_NULL(v);
  ASSERT_EQUAL(5, gvector_cap(v));
  ASSERT_EQUAL(sizeof(int), gvector_size(v));
  ASSERT_EQUAL(2, gvector_len(v));

  int *w = gvector_shrink(v);
  ASSERT_NOT_NULL(w);
  ASSERT_EQUAL(2, gvector_cap(w));
  ASSERT_EQUAL(sizeof(int), gvector_size(w));
  ASSERT_EQUAL(2, gvector_len(w));

  gvector_len(w) = 0;
  ASSERT_NOT_NULL(w);
  ASSERT_EQUAL(2, gvector_cap(w));
  ASSERT_EQUAL(sizeof(int), gvector_size(w));
  ASSERT_EQUAL(0, gvector_len(w));

  v = gvector_shrink(w);
  ASSERT_NOT_NULL(v);
  ASSERT_EQUAL(0, gvector_cap(v));
  ASSERT_EQUAL(sizeof(int), gvector_size(v));
  ASSERT_EQUAL(0, gvector_len(v));

  gvector_free(v);
}

BEGIN_SUITE(Vector)
  ADD_UNIT(AllocateZeroSize)
  ADD_UNIT(AllocateZero)
  ADD_UNIT(AllocateOne)
  ADD_UNIT(Duplicate)
  ADD_UNIT(CopyNull)
  ADD_UNIT(CopySameSize)
  ADD_UNIT(CopyDiffSize)
  ADD_UNIT(ReserveGrow)
  ADD_UNIT(ReserveShrink)
  ADD_UNIT(ReserveZero)
  ADD_UNIT(ReserveNULL)
  ADD_UNIT(PushSuccess)
  ADD_UNIT(PushFailure)
  ADD_UNIT(Pop)
  ADD_UNIT(IsEmpty)
  ADD_UNIT(Shrink)
END_SUITE
