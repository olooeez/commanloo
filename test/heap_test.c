#include <criterion/criterion.h>

#include "heap.h"

Test(heap, init_heap) {
    heap_t *heap = init_heap();
    cr_assert_not_null(heap);
    cr_assert_null(heap->begin);
    cr_assert_null(heap->end);
    cr_assert_eq(heap->quantity, 0);

    end_heap(heap);
}

Test(heap, insert_heap) {
    heap_t *heap = init_heap();
    execution_commands_t data = { 1, 2 };

    heap_err err = insert_heap(heap, data);
    cr_assert_eq(err, HEAP_OK);
    cr_assert_not_null(heap->begin);
    cr_assert_null(heap->end);
    cr_assert_eq(heap->begin->data.index, 1);
    cr_assert_eq(heap->begin->data.times, 2);    
    cr_assert_eq(heap->quantity, 1);

    end_heap(heap);
}

Test(heap, consult_heap_empty) {
    heap_t *heap = init_heap();
    execution_commands_t data;

    heap_err err = consult_heap(heap, &data);
    cr_assert_eq(err, HEAP_EMPTY);

    end_heap(heap);
}

Test(heap, consult_heap) {
    heap_t *heap = init_heap();
    execution_commands_t data = { 1, 2 };

    insert_heap(heap, data);

    heap_err err = consult_heap(heap, &data);
    cr_assert_eq(err, HEAP_OK);
    cr_assert_eq(data.index, 1);
    cr_assert_eq(data.times, 2);

    end_heap(heap);
}

Test(heap, remove_heap_empty) {
    heap_t *heap = init_heap();

    heap_err err = remove_heap(heap);
    cr_assert_eq(err, HEAP_EMPTY);

    end_heap(heap);
}

Test(heap, remove_heap) {
    heap_t *heap = init_heap();
    execution_commands_t data = { 1, 2 };

    insert_heap(heap, data);

    heap_err err = remove_heap(heap);
    cr_assert_eq(err, HEAP_OK);
    cr_assert_null(heap->begin);
    cr_assert_null(heap->end);
    cr_assert_eq(heap->quantity, 0);

    end_heap(heap);
}

Test(heap, is_heap_empty_true) {
    heap_t *heap = init_heap();

    bool result = is_heap_empty(heap);
    cr_assert_eq(result, true);

    end_heap(heap);
}

Test(heap, is_heap_empty_false) {
    heap_t *heap = init_heap();
    execution_commands_t data = { 1, 2 };

    insert_heap(heap, data);

    bool result = is_heap_empty(heap);
    cr_assert_eq(result, false);

    end_heap(heap);
}
