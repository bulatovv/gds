#include "../greatest/greatest.h"


SUITE_EXTERN(vector);


GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();    
    
    RUN_SUITE(vector);
    
    GREATEST_MAIN_END(); 
}
