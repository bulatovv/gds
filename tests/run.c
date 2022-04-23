#include "../greatest/greatest.h"


SUITE_EXTERN(vector);
SUITE_EXTERN(forward_list);


GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();    
    
    RUN_SUITE(vector);
    RUN_SUITE(forward_list);
    
    GREATEST_MAIN_END(); 
}
