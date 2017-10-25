#include <ginger/vector.h>
#include <stdio.h>

int main()
{
    int *xs = gvector_alloc(5, 3, sizeof(int));
    if (!xs)
    {
        perror("allocation failed");
        return 1;
    }

    int *ys = gvector_dup(xs);
    if (!ys)
    {
        gvector_free(xs);
        perror("duplication failed");
        return 1;
    }

    printf("Capacity:     %d\n", (int)gvector_cap(ys));
    printf("Length:       %d\n", (int)gvector_len(ys));
    printf("Element Size: %d\n", (int)gvector_size(ys));
    printf("[ ");
    for (size_t i = 0; i < gvector_len(ys); ++i)
    {
        printf("%d ", ys[i]);
    }
    printf("]\n");

    gvector_free(ys);
    gvector_free(xs);
}
