#include "../greatest/greatest.h"

#define T int
#include "../forward_list.h"

TEST push_front(void) {
    int data[] = {10, 20, 30};
    size_t size = sizeof(data) / sizeof(data[0]);

    int_fwd_list lst;
    int_fwd_list_init(&lst);

    for (int i = size; i >= 0; i--) {
        int_fwd_list_push_front(&lst, data[i]);
    }

    int_fwd_list_node *curr = lst.head;
    for (int i = 0; i < size; i++) {
        ASSERT_EQ(curr->data, data[i]);
        curr = curr->next;
    }

    int_fwd_list_free(&lst);
    PASS();
}

TEST pop_front(void) {
    int data[] = {10, 20, 30};
    size_t size = sizeof(data) / sizeof(data[0]);

    int_fwd_list lst;
    int_fwd_list_init(&lst);

    for (int i = size - 1; i >= 0; i--) { 
        int_fwd_list_push_front(&lst, data[i]);
    }

    int_fwd_list_pop_front(&lst);
    ASSERT_EQ(lst.head->data, data[1]);
    
    for (int i = 0; i < size - 1; i++) {
        int_fwd_list_pop_front(&lst);
    }
    
    ASSERT_EQ_FMT(lst.head, NULL, "%p");
    
    int_fwd_list_free(&lst);
    PASS();
}

SUITE(forward_list) {
    RUN_TEST(push_front);
    RUN_TEST(pop_front);
}
