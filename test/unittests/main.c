// Copyright 2016 Douglas Moore. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include <unit.h>

IMPORT_SUITE(Canary);
IMPORT_SUITE(Vector);

BEGIN_REGISTRATION
  REGISTER(Canary)
  REGISTER(Vector)
END_REGISTRATION

UNIT_MAIN();
