#include <ginger/vector.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

void print_vector(double const *xs)
{
    printf("Capacity:     %d\n", (int)gvector_cap(xs));
    printf("Length:       %d\n", (int)gvector_len(xs));
    printf("Element Size: %d\n", (int)gvector_size(xs));
    printf("[ ");
    for (size_t i = 0; i < gvector_len(xs); ++i)
    {
        printf("%.6lf ", xs[i]);
    }
    printf("]\n");
}

int main()
{
    double *xs = gvector_alloc(0, 0, sizeof(double));
    if (!xs)
    {
        perror("allocation failed");
        return 1;
    }
    print_vector(xs);
    printf("\n");

    gvector_push(xs, 0.5);
    gvector_push(xs, 2.3);
    print_vector(xs);
    printf("\n");
    
    gvector_push(xs, sqrt(5));
    gvector_push(xs, 25);
    gvector_push(xs, 'a');
    print_vector(xs);
    printf("\n");

    gvector_pop(xs);
    gvector_pop(xs);
    print_vector(xs);
    printf("\n");

    gvector_free(xs);
}
