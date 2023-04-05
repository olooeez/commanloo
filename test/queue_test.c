#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

Test(queue, init_queue) {
    queue_t *queue = init_queue();
    cr_assert_not_null(queue);
    cr_assert_null(queue->begin);
    cr_assert_null(queue->end);
    cr_assert_eq(queue->quantity, 0);

    end_queue(queue);
}

Test(queue, insert_and_consult_queue) {
    queue_t *queue = init_queue();
    execution_commands_t data = { 1, 2 };

    queue_err err = insert_queue(queue, data);
    cr_assert_eq(err, QUEUE_OK);
    cr_assert_eq(queue->quantity, 1);

    err = consult_queue(queue, &data);
    cr_assert_eq(err, QUEUE_OK);
    cr_assert_eq(data.index, 1);
    cr_assert_eq(data.times, 2);

    end_queue(queue);
}

Test(queue, remove_queue) {
    queue_t *queue = init_queue();
    execution_commands_t data1 = { 1, 2 };
    execution_commands_t data2 = { 3, 4 };

    queue_err err = insert_queue(queue, data1);
    cr_assert_eq(err, QUEUE_OK);
    cr_assert_eq(queue->quantity, 1);

    err = insert_queue(queue, data2);
    cr_assert_eq(err, QUEUE_OK);
    cr_assert_eq(queue->quantity, 2);

    err = remove_queue(queue);
    cr_assert_eq(err, QUEUE_OK);
    cr_assert_eq(queue->quantity, 1);

    execution_commands_t data;
    err = consult_queue(queue, &data);
    cr_assert_eq(err, QUEUE_OK);
    cr_assert_eq(data.index, 3);
    cr_assert_eq(data.times, 4);

    end_queue(queue);
}

Test(queue, is_queue_empty) {
    queue_t *queue = init_queue();
    execution_commands_t data = { 1, 2 };

    cr_assert(is_queue_empty(queue));

    insert_queue(queue, data);
    cr_assert_not(is_queue_empty(queue));

    remove_queue(queue);
    cr_assert(is_queue_empty(queue));

    end_queue(queue);
}
