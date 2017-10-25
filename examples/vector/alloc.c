#include <ginger/vector.h>
#include <stdio.h>

int main()
{
    int *xs = gvector_alloc(5, 3, sizeof(int));
    if (xs)
    {
        printf("Capacity:     %d\n", (int)gvector_cap(xs));
        printf("Length:       %d\n", (int)gvector_len(xs));
        printf("Element Size: %d\n", (int)gvector_size(xs));
        printf("[ ");
        for (size_t i = 0; i < gvector_len(xs); ++i)
        {
            printf("%d ", xs[i]);
        }
        printf("]\n");
    }
    gvector_free(xs);
}
