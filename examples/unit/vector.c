#include <ginger/vector.h>
#include <ginger/unit.h>

UNIT(VectorAlloc)
{
    int *xs = gvector_alloc(5, 3, sizeof(int));
    ASSERT_NOT_NULL(xs);
    ASSERT_EQUAL_U(5, gvector_cap(xs));
    ASSERT_EQUAL_U(3, gvector_len(xs));
    ASSERT_EQUAL_U(sizeof(int), gvector_size(xs));
    gvector_free(xs);
}

UNIT(VectorPush)
{
    int *xs = NULL;
    ASSERT_SIGNAL(SIGSEGV, gvector_push(xs, 5));
}

BEGIN_SUITE(VectorSuite)
    ADD_UNIT(VectorAlloc)
    ADD_UNIT(VectorPush)
END_SUITE
