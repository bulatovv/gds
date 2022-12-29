#include "../greatest/greatest.h"

#define T int
#include "../gds/forward_list.h"

TEST front(void) {
    int_flist lst;
    int_flist_init(&lst);

    int_flist_push_front(&lst, 1);
    ASSERT_EQ(1, *int_flist_front(&lst));

    int_flist_push_front(&lst, 2);
    ASSERT_EQ(2, *int_flist_front(&lst));

    int_flist_free(&lst);
    PASS();
}

TEST empty(void) {
    int_flist lst;
    int_flist_init(&lst);

    ASSERT(int_flist_empty(&lst));

    int_flist_push_front(&lst, 1);
    ASSERT(!int_flist_empty(&lst));

    int_flist_free(&lst);
    PASS();
}

TEST clear(void) {
    int_flist lst;
    int_flist_init(&lst);
    
    int_flist_clear(&lst);
    ASSERT(int_flist_empty(&lst));

    int_flist_push_front(&lst, 1);
    int_flist_push_front(&lst, 2);
    ASSERT(!int_flist_empty(&lst));

    int_flist_clear(&lst);
    ASSERT(int_flist_empty(&lst));

    int_flist_free(&lst);
    PASS();
}

TEST push_front(void) {
    int data[] = {10, 20, 30};
    size_t size = sizeof(data) / sizeof(data[0]);

    int_flist lst;
    int_flist_init(&lst);

    for (int i = size; i >= 0; i--) {
        int_flist_push_front(&lst, data[i]);
    }

    int_flist_node *curr = lst.head;
    for (int i = 0; i < size; i++) {
        ASSERT_EQ(curr->data, data[i]);
        curr = curr->next;
    }

    int_flist_free(&lst);
    PASS();
}

size_t int_flist_size(int_flist *lst) {
    size_t size = 0;
    int_flist_node *curr = lst->head;
    while (curr != NULL) {
        size++;
        curr = curr->next;
    }
    return size;
}

TEST resize(void) {
    int_flist lst;
    int_flist_init(&lst);
    
    int_flist_resize(&lst, 0);
    ASSERT_EQ(0, int_flist_size(&lst));

    int_flist_resize(&lst, 10);
    ASSERT_EQ(10, int_flist_size(&lst));
    
    int_flist_resize(&lst, 10);
    ASSERT_EQ(10, int_flist_size(&lst));

    int_flist_resize(&lst, 5);
    ASSERT_EQ(5, int_flist_size(&lst));
    
    int_flist_resize(&lst, 6);
    ASSERT_EQ(6, int_flist_size(&lst));

    int_flist_resize(&lst, 0);
    ASSERT_EQ(0, int_flist_size(&lst));

    int_flist_free(&lst);
    PASS();
}

TEST pop_front(void) {
    int data[] = {10, 20, 30};
    size_t size = sizeof(data) / sizeof(data[0]);

    int_flist lst;
    int_flist_init(&lst);

    for (int i = size - 1; i >= 0; i--) { 
        int_flist_push_front(&lst, data[i]);
    }

    int_flist_pop_front(&lst);
    ASSERT_EQ(lst.head->data, data[1]);
    
    for (int i = 0; i < size - 1; i++) {
        int_flist_pop_front(&lst);
    }
    
    ASSERT_EQ_FMT(lst.head, NULL, "%p");
    
    int_flist_free(&lst);
    PASS();
}

SUITE(forward_list) {
    RUN_TEST(front);
    RUN_TEST(empty);
    RUN_TEST(clear);
    RUN_TEST(resize);
    RUN_TEST(push_front);
    RUN_TEST(pop_front);
}
