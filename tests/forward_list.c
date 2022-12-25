#include "../greatest/greatest.h"

#define T int
#include "../gds/forward_list.h"

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
    RUN_TEST(push_front);
    RUN_TEST(pop_front);
}
