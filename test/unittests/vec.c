// Copyright 2016 Douglas Moore. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include <ginger/vec.h>
#include <unit.h>

UNIT(AllocateZeroSize)
{
  ASSERT_NULL(gvec_alloc(0, 0, 0));
  ASSERT_NULL(gvec_alloc(5, 0, 0));
  ASSERT_NULL(gvec_alloc(0, 5, 0));
  ASSERT_NULL(gvec_alloc(5, 5, 0));
}

UNIT(AllocateZero)
{
  int *v = gvec_alloc(0, 0, sizeof(int));
  ASSERT_NOT_NULL(v);
  ASSERT_EQUAL(0, gvec_cap(v));
  ASSERT_EQUAL(sizeof(int), gvec_size(v));
  ASSERT_EQUAL(0, gvec_len(v));
  gvec_free(v);
}

UNIT(AllocateOne)
{
  int *v = gvec_alloc(1, 0, sizeof(int));
  ASSERT_NOT_NULL(v);
  ASSERT_EQUAL(1, gvec_cap(v));
  ASSERT_EQUAL(sizeof(int), gvec_size(v));
  ASSERT_EQUAL(0, gvec_len(v));
  gvec_free(v);

  v = gvec_alloc(1, 1, sizeof(int));
  ASSERT_NOT_NULL(v);
  ASSERT_EQUAL(1, gvec_cap(v));
  ASSERT_EQUAL(sizeof(int), gvec_size(v));
  ASSERT_EQUAL(1, gvec_len(v));

  v = gvec_alloc(1, 2, sizeof(int));
  ASSERT_NOT_NULL(v);
  ASSERT_EQUAL(1, gvec_cap(v));
  ASSERT_EQUAL(sizeof(int), gvec_size(v));
  ASSERT_EQUAL(1, gvec_len(v));
}

UNIT(ReserveGrow)
{
  size_t const N = 2;

  int *v = gvec_alloc(N, N, sizeof(int));
  for (size_t i = 0; i < N; ++i) v[i] = (int)i;
  ASSERT_NOT_NULL(v);

  int *w = gvec_reserve(v, 3*N);
  ASSERT_NOT_NULL(w);
  ASSERT_EQUAL(6, gvec_cap(w));
  ASSERT_EQUAL(sizeof(int), gvec_size(w));
  ASSERT_EQUAL(N, gvec_len(w));
  for (size_t i = 0; i < N; ++i) ASSERT_EQUAL(i, w[i]);

  gvec_free(w);
}

UNIT(ReserveShrink)
{
  size_t const N = 2;
  int *v = gvec_alloc(3*N, 3*N, sizeof(int));
  for (size_t i = 0; i < 3*N; ++i) v[i] = (int)i;
  ASSERT_NOT_NULL(v);

  int *w = gvec_reserve(v, N);
  ASSERT_NOT_NULL(w);
  ASSERT_EQUAL(N, gvec_cap(w));
  ASSERT_EQUAL(sizeof(int), gvec_size(w));
  ASSERT_EQUAL(N, gvec_len(w));
  for (size_t i = 0; i < N; ++i) ASSERT_EQUAL(i, w[i]);

  gvec_free(w);
}

UNIT(ReserveZero)
{
  size_t const N = 2;
  int *v = gvec_alloc(3*N, 3*N, sizeof(int));
  for (size_t i = 0; i < 3*N; ++i) v[i] = (int)i;
  ASSERT_NOT_NULL(v);

  int *w = gvec_reserve(v, 0);
  ASSERT_NOT_NULL(w);
  ASSERT_EQUAL(0, gvec_cap(w));
  ASSERT_EQUAL(sizeof(int), gvec_size(w));
  ASSERT_EQUAL(0, gvec_len(w));

  gvec_free(w);
}

UNIT(ReserveNULL)
{
  ASSERT_NULL(gvec_reserve(NULL, 5));
}

UNIT(PushSuccess)
{
  int *v = gvec_alloc(3, 0, sizeof(int));
  ASSERT_NOT_NULL(v);
  gvec_push(v,1);
  gvec_push(v,2);
  gvec_push(v,3);
  ASSERT_EQUAL(3, gvec_cap(v));
  ASSERT_EQUAL(3, gvec_len(v));
  for (size_t i = 0; i < 3; ++i) ASSERT_EQUAL(i+1, v[i]);
  gvec_push(v,4);
  ASSERT_EQUAL(6, gvec_cap(v));
  ASSERT_EQUAL(4, gvec_len(v));
  for (size_t i = 0; i < 4; ++i) ASSERT_EQUAL(i+1, v[i]);
  gvec_free(v);
}

UNIT(PushFailure)
{
  int *v = NULL;
  ASSERT_SIGNAL(SIGSEGV, gvec_push(v, 0));
}

UNIT(Pop)
{
  int *v = gvec_alloc(3, 3, sizeof(int));
  ASSERT_NOT_NULL(v);

  gvec_pop(v);
  ASSERT_EQUAL(3, gvec_cap(v));
  ASSERT_EQUAL(2, gvec_len(v));

  gvec_pop(v);
  ASSERT_EQUAL(3, gvec_cap(v));
  ASSERT_EQUAL(1, gvec_len(v));

  gvec_pop(v);
  ASSERT_EQUAL(3, gvec_cap(v));
  ASSERT_EQUAL(0, gvec_len(v));

  gvec_pop(v);
  ASSERT_EQUAL(3, gvec_cap(v));
  ASSERT_EQUAL(0, gvec_len(v));

  gvec_free(v);
}

UNIT(IsEmpty)
{
  ASSERT_TRUE(gvec_isempty(NULL));

  int *v = NULL;
  ASSERT_TRUE(gvec_isempty(v));

  v = gvec_alloc(3, 0, sizeof(int));
  ASSERT_TRUE(gvec_isempty(v));

  gvec_push(v, 1);
  ASSERT_FALSE(gvec_isempty(v));

  gvec_free(v);
}

UNIT(Shrink)
{
  int *v = gvec_alloc(5, 2, sizeof(int));
  ASSERT_NOT_NULL(v);
  ASSERT_EQUAL(5, gvec_cap(v));
  ASSERT_EQUAL(sizeof(int), gvec_size(v));
  ASSERT_EQUAL(2, gvec_len(v));

  int *w = gvec_shrink(v);
  ASSERT_NOT_NULL(w);
  ASSERT_EQUAL(2, gvec_cap(w));
  ASSERT_EQUAL(sizeof(int), gvec_size(w));
  ASSERT_EQUAL(2, gvec_len(w));

  gvec_len(w) = 0;
  ASSERT_NOT_NULL(w);
  ASSERT_EQUAL(2, gvec_cap(w));
  ASSERT_EQUAL(sizeof(int), gvec_size(w));
  ASSERT_EQUAL(0, gvec_len(w));

  v = gvec_shrink(w);
  ASSERT_NOT_NULL(v);
  ASSERT_EQUAL(0, gvec_cap(v));
  ASSERT_EQUAL(sizeof(int), gvec_size(v));
  ASSERT_EQUAL(0, gvec_len(v));

  gvec_free(v);
}

BEGIN_SUITE(Vector)
  ADD_UNIT(AllocateZeroSize)
  ADD_UNIT(AllocateZero)
  ADD_UNIT(AllocateOne)
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
