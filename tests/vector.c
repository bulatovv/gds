#include "../greatest/greatest.h"

#define T int
#include "../gds/vector.h"


TEST at(void) {
    int data[] = {10, 20, 30};
    size_t size = sizeof(data) / sizeof(data[0]);

    int_vec vec;
    int_vec_init(&vec);

    for (int i = 0; i < size; i++) {
        int_vec_push_back(&vec, data[i]);
    }

    ASSERT_EQ(data[0], *int_vec_at(&vec, 0));
    ASSERT_EQ(data[1], *int_vec_at(&vec, 1));

    int_vec_free(&vec);
    PASS();
}

TEST front(void) {
    int data[] = {10, 20, 30};
    size_t size = sizeof(data) / sizeof(data[0]);

    int_vec vec;
    int_vec_init(&vec);

    for (int i = 0; i < size; i++) {
        int_vec_push_back(&vec, data[i]);
    }

    ASSERT_EQ(data[0], *int_vec_front(&vec));

    int_vec_free(&vec);
    PASS();
}


TEST back(void) {
    int data[] = {10, 20, 30};
    size_t size = sizeof(data) / sizeof(data[0]);

    int_vec vec;
    int_vec_init(&vec);

    for (int i = 0; i < size; i++) {
        int_vec_push_back(&vec, data[i]);
    }

    ASSERT_EQ(data[size - 1], *int_vec_back(&vec));

    int_vec_free(&vec);
    PASS();
}

TEST data(void) {
    int data[] = {10, 20, 30};
    size_t size = sizeof(data) / sizeof(data[0]);

    int_vec vec;
    int_vec_init(&vec);

    for (int i = 0; i < size; i++) {
        int_vec_push_back(&vec, data[i]);
    }

    ASSERT_MEM_EQ(data, int_vec_data(&vec), size * sizeof(int));

    int_vec_free(&vec);
    PASS();
}

TEST empty(void) {
    int_vec vec;
    int_vec_init(&vec);

    
    ASSERT(int_vec_empty(&vec));
    int_vec_push_back(&vec, 1);
    ASSERT_FALSE(int_vec_empty(&vec));

    int_vec_free(&vec);
    PASS();
}

TEST size(void) {
    int data[] = {10, 20, 30};
    size_t size = sizeof(data) / sizeof(data[0]);

    int_vec vec;
    int_vec_init(&vec);

    ASSERT_EQ(int_vec_size(&vec), 0);

    for (int i = 0; i < size; i++) {
        int_vec_push_back(&vec, data[i]);
    }

    ASSERT_EQ(int_vec_size(&vec), size);
    
    int_vec_free(&vec);
    PASS();
}

TEST capacity(void) {
    int data[] = {10, 20, 30};
    size_t size = sizeof(data) / sizeof(data[0]);

    int_vec vec;
    int_vec_init(&vec);

    ASSERT_GTE(int_vec_capacity(&vec), int_vec_size(&vec));

    for (int i = 0; i < size; i++) {
        int_vec_push_back(&vec, data[i]);
    }

    ASSERT_GTE(int_vec_capacity(&vec), int_vec_size(&vec));

    int_vec_free(&vec);
    PASS();
}

TEST reserve(void) {
    int_vec vec;
    int_vec_init(&vec);

    int_vec_reserve(&vec, 32);
    ASSERT_GTE(int_vec_capacity(&vec), 32);

    int_vec_push_back(&vec, 10);
    int_vec_push_back(&vec, 20);
    int_vec_push_back(&vec, 30);
    
    int_vec_reserve(&vec, 64);
    ASSERT_GTE(int_vec_capacity(&vec), 64);

    int_vec_free(&vec);
    PASS();
}

TEST shrink(void) {
    int data[] = {10, 20, 30, 40, 50, 60, 70, 80};
    size_t size = sizeof(data) / sizeof(data[0]);
    
    int_vec vec;
    int_vec_init(&vec);
    int_vec_shrink(&vec);

    ASSERT_EQ(int_vec_size(&vec), int_vec_capacity(&vec));

    for (int i = 0; i < size; i++) {
        int_vec_push_back(&vec, data[i]);
    }
    
    for (int i = 0; i < size / 2; i++) {
        int_vec_pop_back(&vec);
    }
    
    int_vec_shrink(&vec);
    ASSERT_EQ(int_vec_size(&vec), int_vec_capacity(&vec));

    int_vec_free(&vec);
    PASS();
}

TEST push_back(void) {
    int data[] = {10, 20, 30};
    size_t size = sizeof(data) / sizeof(data[0]);

    int_vec vec;
    int_vec_init(&vec);

    for (int i = 0; i < size; i++) {
        int_vec_push_back(&vec, data[i]);
    }
    
    ASSERT_EQ(int_vec_size(&vec), size);
    ASSERT_GTE(int_vec_capacity(&vec), int_vec_size(&vec));
    ASSERT_MEM_EQ(
        int_vec_data(&vec), data,
        size * sizeof(int)
    );
    
    int_vec_free(&vec);
    PASS();
}

TEST pop_back(void) {
    int data[] = {10, 20, 30};
    size_t size = sizeof(data) / sizeof(data[0]);

    int_vec vec;
    int_vec_init(&vec);

    for (int i = 0; i < size; i++) {
        int_vec_push_back(&vec, data[i]);
    }

    int_vec_pop_back(&vec);

    ASSERT_EQ(int_vec_size(&vec), size - 1);
    ASSERT_GTE(int_vec_capacity(&vec), int_vec_size(&vec));
    ASSERT_EQ(
        *int_vec_back(&vec),
        data[size - 2]
    );
    
    int_vec_free(&vec);
    PASS();
}

TEST insert(void) {
    int_vec vec;
    int_vec_init(&vec);

    int_vec_insert(&vec, 0, 3);
    int_vec_insert(&vec, 0, 1);
    int_vec_insert(&vec, 1, 2);
    int_vec_insert(&vec, 3, 4);

    int data[] = {1, 2, 3, 4};
    
    ASSERT_EQ(int_vec_size(&vec), 4);
    ASSERT_GTE(int_vec_capacity(&vec), int_vec_size(&vec));
    ASSERT_MEM_EQ(
        int_vec_data(&vec), data,
        4 * sizeof(int)
    );
    
    int_vec_free(&vec);
    PASS();
}

TEST erase(void) {
    int_vec vec;
    int_vec_init(&vec);

    int_vec_insert(&vec, 0, 5);
    int_vec_insert(&vec, 0, 4);
    int_vec_insert(&vec, 0, 3);
    int_vec_insert(&vec, 0, 2);
    int_vec_insert(&vec, 0, 1);

    int_vec_erase(&vec, 0);
    int_vec_erase(&vec, 3);
    int_vec_erase(&vec, 1);

    int data[] = {2, 4};

    ASSERT_EQ(int_vec_size(&vec), 2);
    ASSERT_GTE(int_vec_capacity(&vec), int_vec_size(&vec));
    ASSERT_MEM_EQ(
        int_vec_data(&vec), data,
        2 * sizeof(int)
    );

    int_vec_free(&vec);
    PASS();
}


TEST clear(void) {
    int_vec vec;
    int_vec_init(&vec);

    int_vec_insert(&vec, 0, 5);
    int_vec_insert(&vec, 0, 4);
    int_vec_insert(&vec, 0, 3);
    int_vec_insert(&vec, 0, 2);
    int_vec_insert(&vec, 0, 1);

    int_vec_clear(&vec);
    ASSERT_EQ(int_vec_size(&vec), 0);
    ASSERT_GTE(int_vec_capacity(&vec), int_vec_size(&vec));

    int_vec_free(&vec);
    PASS();
}

TEST resize(void) {
    int_vec vec;
    int_vec_init(&vec);

    int_vec_resize(&vec, 5);
    ASSERT_EQ(int_vec_size(&vec), 5);
    ASSERT_GTE(int_vec_capacity(&vec), int_vec_size(&vec));


    int_vec_resize(&vec, 10);
    ASSERT_EQ(int_vec_size(&vec), 10);
    ASSERT_GTE(int_vec_capacity(&vec), int_vec_size(&vec));

    int_vec_resize(&vec, 3);
    ASSERT_EQ(int_vec_size(&vec), 3);
    ASSERT_GTE(int_vec_capacity(&vec), int_vec_size(&vec));

    int_vec_resize(&vec, 0);
    ASSERT_EQ(int_vec_size(&vec), 0);
    ASSERT_GTE(int_vec_capacity(&vec), int_vec_size(&vec));

    int_vec_free(&vec);
    PASS();
}

TEST swap(void) {
    int_vec vec1;
    int_vec_init(&vec1);

    int_vec vec2;
    int_vec_init(&vec2);

    int data1[] = {10, 20, 30, 40, 50, 60, 70, 80};
    int data2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < sizeof(data1) / sizeof(data1[0]); i++) {
        int_vec_push_back(&vec1, data1[i]);
    }

    for (int i = 0; i < sizeof(data2) / sizeof(data2[0]); i++) {
        int_vec_push_back(&vec2, data2[i]);
    }

    int_vec_swap(&vec1, &vec2);

    ASSERT_EQ(int_vec_size(&vec1), sizeof(data2) / sizeof(data2[0]));
    ASSERT_GTE(int_vec_capacity(&vec1), int_vec_size(&vec1));
    ASSERT_MEM_EQ(
        int_vec_data(&vec1), data2,
        sizeof(data2)
    );

    ASSERT_EQ(int_vec_size(&vec2), sizeof(data1) / sizeof(data1[0]));
    ASSERT_GTE(int_vec_capacity(&vec2), int_vec_size(&vec2));
    ASSERT_MEM_EQ(
        int_vec_data(&vec2), data1,
        sizeof(data1)
    );

    int_vec_free(&vec1);
    int_vec_free(&vec2);
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
