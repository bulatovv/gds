#include "../greatest/greatest.h"

#define T int
#include "../vector.h"


TEST at(void) {
    int data[] = {10, 20, 30};
    size_t size = sizeof(data) / sizeof(data[0]);

    int_vector vec;
    int_vector_init(&vec);

    for (int i = 0; i < size; i++) {
        int_vector_push_back(&vec, data[i]);
    }

    ASSERT_EQ(data[0], *int_vector_at(&vec, 0));
    ASSERT_EQ(data[1], *int_vector_at(&vec, 1));

    int_vector_free(&vec);
    PASS();
}

TEST front(void) {
    int data[] = {10, 20, 30};
    size_t size = sizeof(data) / sizeof(data[0]);

    int_vector vec;
    int_vector_init(&vec);

    for (int i = 0; i < size; i++) {
        int_vector_push_back(&vec, data[i]);
    }

    ASSERT_EQ(data[0], *int_vector_front(&vec));

    int_vector_free(&vec);
    PASS();
}


TEST back(void) {
    int data[] = {10, 20, 30};
    size_t size = sizeof(data) / sizeof(data[0]);

    int_vector vec;
    int_vector_init(&vec);

    for (int i = 0; i < size; i++) {
        int_vector_push_back(&vec, data[i]);
    }

    ASSERT_EQ(data[size - 1], *int_vector_back(&vec));

    int_vector_free(&vec);
    PASS();
}

TEST data(void) {
    int data[] = {10, 20, 30};
    size_t size = sizeof(data) / sizeof(data[0]);

    int_vector vec;
    int_vector_init(&vec);

    for (int i = 0; i < size; i++) {
        int_vector_push_back(&vec, data[i]);
    }

    ASSERT_MEM_EQ(data, int_vector_data(&vec), size * sizeof(int));

    int_vector_free(&vec);
    PASS();
}

TEST empty(void) {
    int_vector vec;
    int_vector_init(&vec);

    
    ASSERT(int_vector_empty(&vec));
    int_vector_push_back(&vec, 1);
    ASSERT_FALSE(int_vector_empty(&vec));

    int_vector_free(&vec);
    PASS();
}

TEST size(void) {
    int data[] = {10, 20, 30};
    size_t size = sizeof(data) / sizeof(data[0]);

    int_vector vec;
    int_vector_init(&vec);

    ASSERT_EQ(int_vector_size(&vec), 0);

    for (int i = 0; i < size; i++) {
        int_vector_push_back(&vec, data[i]);
    }

    ASSERT_EQ(int_vector_size(&vec), size);
    
    int_vector_free(&vec);
    PASS();
}

TEST capacity(void) {
    int data[] = {10, 20, 30};
    size_t size = sizeof(data) / sizeof(data[0]);

    int_vector vec;
    int_vector_init(&vec);

    ASSERT_GTE(int_vector_capacity(&vec), int_vector_size(&vec));

    for (int i = 0; i < size; i++) {
        int_vector_push_back(&vec, data[i]);
    }

    ASSERT_GTE(int_vector_capacity(&vec), int_vector_size(&vec));

    int_vector_free(&vec);
    PASS();
}

TEST reserve(void) {
    int_vector vec;
    int_vector_init(&vec);

    int_vector_reserve(&vec, 32);
    ASSERT_GTE(int_vector_capacity(&vec), 32);

    int_vector_push_back(&vec, 10);
    int_vector_push_back(&vec, 20);
    int_vector_push_back(&vec, 30);
    
    int_vector_reserve(&vec, 64);
    ASSERT_GTE(int_vector_capacity(&vec), 64);

    int_vector_free(&vec);
    PASS();
}

TEST shrink(void) {
    int data[] = {10, 20, 30, 40, 50, 60, 70, 80};
    size_t size = sizeof(data) / sizeof(data[0]);
    
    int_vector vec;
    int_vector_init(&vec);
    int_vector_shrink(&vec);

    ASSERT_EQ(int_vector_size(&vec), int_vector_capacity(&vec));

    for (int i = 0; i < size; i++) {
        int_vector_push_back(&vec, data[i]);
    }
    
    for (int i = 0; i < size / 2; i++) {
        int_vector_pop_back(&vec);
    }
    
    int_vector_shrink(&vec);
    ASSERT_EQ(int_vector_size(&vec), int_vector_capacity(&vec));

    int_vector_free(&vec);
    PASS();
}

TEST push_back(void) {
    int data[] = {10, 20, 30};
    size_t size = sizeof(data) / sizeof(data[0]);

    int_vector vec;
    int_vector_init(&vec);

    for (int i = 0; i < size; i++) {
        int_vector_push_back(&vec, data[i]);
    }
    
    ASSERT_EQ(int_vector_size(&vec), size);
    ASSERT_MEM_EQ(
        int_vector_data(&vec), data,
        size * sizeof(int)
    );
    
    int_vector_free(&vec);
    PASS();
}

TEST pop_back(void) {
    int data[] = {10, 20, 30};
    size_t size = sizeof(data) / sizeof(data[0]);

    int_vector vec;
    int_vector_init(&vec);

    for (int i = 0; i < size; i++) {
        int_vector_push_back(&vec, data[i]);
    }

    int_vector_pop_back(&vec);

    ASSERT_EQ(int_vector_size(&vec), size - 1);
    ASSERT_EQ(
        *int_vector_back(&vec),
        data[size - 2]
    );
    
    int_vector_free(&vec);
    PASS();
}

TEST insert(void) {
    int_vector vec;
    int_vector_init(&vec);

    int_vector_insert(&vec, 0, 3);
    int_vector_insert(&vec, 0, 1);
    int_vector_insert(&vec, 1, 2);
    int_vector_insert(&vec, 3, 4);

    int data[] = {1, 2, 3, 4};
    

    ASSERT_MEM_EQ(
        int_vector_data(&vec), data,
        4 * sizeof(int)
    );
    
    int_vector_free(&vec);
    PASS();
}

TEST erase(void) {
    int_vector vec;
    int_vector_init(&vec);

    int_vector_insert(&vec, 0, 5);
    int_vector_insert(&vec, 0, 4);
    int_vector_insert(&vec, 0, 3);
    int_vector_insert(&vec, 0, 2);
    int_vector_insert(&vec, 0, 1);

    int_vector_erase(&vec, 0);
    int_vector_erase(&vec, 3);
    int_vector_erase(&vec, 1);

    int data[] = {2, 4}; 
    ASSERT_MEM_EQ(
        int_vector_data(&vec), data,
        2 * sizeof(int)
    );

    int_vector_free(&vec);
    PASS();
}


TEST clear(void) {
    int_vector vec;
    int_vector_init(&vec);

    int_vector_insert(&vec, 0, 5);
    int_vector_insert(&vec, 0, 4);
    int_vector_insert(&vec, 0, 3);
    int_vector_insert(&vec, 0, 2);
    int_vector_insert(&vec, 0, 1);

    int_vector_clear(&vec);
    ASSERT_EQ(int_vector_size(&vec), 0);

    int_vector_free(&vec);
    PASS();
}

TEST resize(void) {
    int_vector vec;
    int_vector_init(&vec);

    int_vector_resize(&vec, 5);
    ASSERT_EQ(int_vector_size(&vec), 5);
    ASSERT_GTE(int_vector_capacity(&vec), int_vector_size(&vec));


    int_vector_resize(&vec, 10);
    ASSERT_EQ(int_vector_size(&vec), 10);
    ASSERT_GTE(int_vector_capacity(&vec), int_vector_size(&vec));

    int_vector_resize(&vec, 3);
    ASSERT_EQ(int_vector_size(&vec), 3);
    ASSERT_GTE(int_vector_capacity(&vec), int_vector_size(&vec));

    int_vector_resize(&vec, 0);
    ASSERT_EQ(int_vector_size(&vec), 0);
    ASSERT_GTE(int_vector_capacity(&vec), int_vector_size(&vec));

    int_vector_free(&vec);
    PASS();
}

TEST swap(void) {
    int_vector vec1;
    int_vector_init(&vec1);

    int_vector vec2;
    int_vector_init(&vec2);

    int data1[] = {10, 20, 30, 40, 50, 60, 70, 80};
    int data2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < sizeof(data1) / sizeof(data1[0]); i++) {
        int_vector_push_back(&vec1, data1[i]);
    }

    for (int i = 0; i < sizeof(data2) / sizeof(data2[0]); i++) {
        int_vector_push_back(&vec2, data2[i]);
    }

    int_vector_swap(&vec1, &vec2);

    ASSERT_MEM_EQ(
        int_vector_data(&vec1), data2,
        sizeof(data2)
    );

    ASSERT_MEM_EQ(
        int_vector_data(&vec2), data1,
        sizeof(data1)
    );

    int_vector_free(&vec1);
    int_vector_free(&vec2);
    PASS();
}


SUITE(vector) {
    RUN_TEST(at);
    RUN_TEST(front);
    RUN_TEST(back);
    RUN_TEST(data);
    RUN_TEST(empty);
    RUN_TEST(size);
    RUN_TEST(capacity);
    RUN_TEST(reserve);
    RUN_TEST(push_back);
    RUN_TEST(pop_back);
    RUN_TEST(insert);
    RUN_TEST(erase);
    RUN_TEST(clear);
    RUN_TEST(resize);
    RUN_TEST(swap);
}
