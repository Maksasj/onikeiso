#include <stdlib.h>

#include "unity.h"
#include "onikeiso.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void queue_create_test(void) {
    Queue queue;

    create_queue(&queue, 1024);

    TEST_ASSERT_EQUAL(queue_size(&queue), 0);
    TEST_ASSERT_EQUAL(queue_capacity(&queue), 1024);

    free_queue(&queue);
}

void queue_push_test(void) {
    Queue queue;

    create_queue(&queue, 1024);

    for(int i = 0; i < 100; ++i) {
        int* item = (int*) malloc(sizeof(int));
        *item = i;
        queue_push(&queue, item);
    }

    unsigned int size = queue_size(&queue);

    TEST_ASSERT_EQUAL(100, size);

    free_queue(&queue);
}

void queue_pop_test(void) {
    Queue queue;

    create_queue(&queue, 1024);

    for(int i = 0; i < 100; ++i) {
        int* item = (int*) malloc(sizeof(int));
        *item = i;
        queue_push(&queue, item);
    }

    TEST_ASSERT_EQUAL(100, queue_size(&queue));

    for(int i = 0; i < 20; ++i) {
        void* item = queue_pop(&queue);

        free(item);
    }

    TEST_ASSERT_EQUAL(80, queue_size(&queue));
    TEST_ASSERT_EQUAL(0, queue_empty(&queue));

    for(int i = 0; i < 20; ++i) {
        void* item = queue_pop(&queue);

        free(item);
    }

    TEST_ASSERT_EQUAL(60, queue_size(&queue));
    TEST_ASSERT_EQUAL(0, queue_empty(&queue));

    for(int i = 0; i < 60; ++i) {
        queue_pop(&queue);
    }

    TEST_ASSERT_EQUAL(0, queue_size(&queue));
    TEST_ASSERT_EQUAL(1, queue_empty(&queue));

    free_queue_content(&queue);
    free_queue(&queue);
}

void queue_store_test(void) {
    Queue queue;

    create_queue(&queue, 1024);

    for(int i = 0; i < 100; ++i) {
        int* item = (int*) malloc(sizeof(int));
        *item = i;
        queue_push(&queue, item);
    }

    TEST_ASSERT_EQUAL(queue_capacity(&queue), 1024);

    for(int i = 99; i >= 0; --i) {
        int* item = (int*) queue_pop(&queue);

        TEST_ASSERT_EQUAL(*item, i);
    }

    TEST_ASSERT_EQUAL(queue_capacity(&queue), 16);

    free_queue_content(&queue);
    free_queue(&queue);
}

void queue_huge_store_test(void) {
    Queue queue;

    create_queue(&queue, 100);

    for(int i = 0; i < 1000; ++i) {
        int* item = (int*) malloc(sizeof(int));
        *item = i;
        queue_push(&queue, item);
    }

    TEST_ASSERT_EQUAL(queue_capacity(&queue), 1600);

    for(int i = 999; i >= 0; --i) {
        int* item = (int*) queue_pop(&queue);

        TEST_ASSERT_EQUAL(*item, i);

    }

    TEST_ASSERT_EQUAL(queue_capacity(&queue), 12);

    free_queue_content(&queue);
    free_queue(&queue);
}

void queue_colossal_store_test(void) {
    Queue queue;

    create_queue(&queue, 10);

    for(int i = 0; i < 1000000; ++i) {
        int* item = (int*) malloc(sizeof(int));
        *item = i;
        queue_push(&queue, item);
    }

    TEST_ASSERT_EQUAL(queue_capacity(&queue), 1310720);

    for(int i = 999999; i >= 0; --i) {
        int* item = (int*) queue_pop(&queue);

        TEST_ASSERT_EQUAL(*item, i);
    }

    TEST_ASSERT_EQUAL(queue_capacity(&queue), 20);

    free_queue_content(&queue);
    free_queue(&queue);
}

void queue_little_store_test(void) {
    Queue queue;

    create_queue(&queue, 1);

    for(int i = 0; i < 2; ++i) {
        int* item = (int*) malloc(sizeof(int));
        *item = i;
        queue_push(&queue, item);
    }

    TEST_ASSERT_EQUAL(queue_capacity(&queue), 2);

    for(int i = 1; i >= 0; --i) {
        int* item = (int*) queue_pop(&queue);

        TEST_ASSERT_EQUAL(*item, i);
    }

    TEST_ASSERT_EQUAL(queue_capacity(&queue), 2);

    free_queue_content(&queue);
    free_queue(&queue);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(queue_create_test);
    RUN_TEST(queue_push_test);
    RUN_TEST(queue_pop_test);
    RUN_TEST(queue_store_test);

    RUN_TEST(queue_little_store_test);

    RUN_TEST(queue_huge_store_test);
    RUN_TEST(queue_colossal_store_test);

    return UNITY_END();
}
