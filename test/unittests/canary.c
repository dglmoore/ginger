// Copyright 2016-2017 Douglas G. Moore. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include <ginger/unit.h>

UNIT(OnePlusTwo)
{
  ASSERT_EQUAL(3, 1+2);
}

BEGIN_SUITE(Canary)
  ADD_UNIT(OnePlusTwo)
END_SUITE
