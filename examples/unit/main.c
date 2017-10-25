#include <ginger/unit.h>

UNIT(CanaryTest)
{
    ASSERT_EQUAL(5, 1 + 2); // Should fail
}

BEGIN_SUITE(CanarySuite)
    ADD_UNIT(CanaryTest)
END_SUITE

IMPORT_SUITE(VectorSuite);

BEGIN_REGISTRATION
    REGISTER(CanarySuite)
    REGISTER(VectorSuite)
END_REGISTRATION

UNIT_MAIN()
