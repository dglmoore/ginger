#include <ginger/vector.h>
#include <stdio.h>
#include <string.h>

void print_vector(int const *xs)
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

int main()
{
    int *xs = gvector_alloc(10, 5, sizeof(int));
    if (!xs)
    {
        perror("allocation failed");
        return 1;
    }
    memset(xs, 0, gvector_len(xs) * gvector_size(xs));
    print_vector(xs);
    printf("\n");

    xs = gvector_shrink(xs);
    print_vector(xs);

    gvector_free(xs);
}
