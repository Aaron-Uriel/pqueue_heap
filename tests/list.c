#include <dstructs.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>

int32_t
main(void)
{
    struct linked_list *lltest = linked_list_new();
    double dtest[5] = {1, 2, 99, 0.99, 3.141592};

    for (size_t i = 0; i < 5; i += 1) {
        linked_list_add_last(lltest, &dtest[i]);    
    }
    for (size_t i = 0; i < 5; i += 1) {
        printf("%g ", *(double *)linked_list_get(lltest, i));
    }
    printf("\n");
    assert(linked_list_pop_last(lltest) == &dtest[4]);
    assert(linked_list_pop_first(lltest) == &dtest[0]);
    assert(linked_list_get(lltest, UINT64_MAX) == NULL);
    assert(linked_list_get(lltest, 0) == &dtest[1]);
    assert(linked_list_get(lltest, 2) == &dtest[3]);
    return 0;
}
