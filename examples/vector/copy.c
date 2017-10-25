#include <ginger/vector.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char *xs = gvector_alloc(5, 5, sizeof(char));
    if (!xs)
    {
        perror("allocation failed");
        return 1;
    }
    memset(xs, 'a', gvector_len(xs) * gvector_size(xs));

    char *ys = gvector_alloc(3, 3, sizeof(char));
    if (!ys)
    {
        gvector_free(xs);
        perror("duplication failed");
        return 1;
    }

    int n = (int)gvector_copy(ys, xs);
    printf("Copied %d elements\n", n);

    printf("Capacity:     %d\n", (int)gvector_cap(ys));
    printf("Length:       %d\n", (int)gvector_len(ys));
    printf("Element Size: %d\n", (int)gvector_size(ys));
    printf("\"");
    for (size_t i = 0; i < 3; ++i)
    {
        printf("%c", ys[i]);
    }
    printf("\"\n");

    gvector_free(ys);
    gvector_free(xs);
}
