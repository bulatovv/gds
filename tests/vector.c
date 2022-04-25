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

TEST push_back(void) {
    int data[] = {10, 20, 30};
    size_t size = sizeof(data) / sizeof(data[0]);

    int_vector vec;
    int_vector_init(&vec);

    for (int i = 0; i < size; i++) {
        int_vector_push_back(&vec, data[i]);
    }

    ASSERT_EQ(vec.top, size);
    ASSERT_MEM_EQ(vec.data, data, size * sizeof(int));
    
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

    ASSERT_EQ(vec.top, size - 1);
    ASSERT_EQ(
        vec.data[vec.top - 1],
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
    

    ASSERT_MEM_EQ(vec.data, data, 4 * sizeof(int));
    
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
    ASSERT_MEM_EQ(vec.data, data, 2 * sizeof(int));

    int_vector_free(&vec);

    PASS();
}


SUITE(vector) {
    RUN_TEST(at);
    RUN_TEST(front);
    RUN_TEST(back);
    RUN_TEST(data);
    RUN_TEST(push_back);
    RUN_TEST(pop_back);
    RUN_TEST(insert);
    RUN_TEST(erase);
}
