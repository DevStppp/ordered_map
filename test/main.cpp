#define CATCH_CONFIG_RUNNER
#include "constructor_test.h"
#include "iterator_test.h"
#include "lookup_test.h"
#include "modifier_test.h"
#include "multi_thread_test.h"
#include "swap_test.h"
#include <catch.hpp>

#ifdef TEST_FIFO_MAP
    #include "fifomap_multi_thread_test.h"
    #include "fifomap_swap_test.h"
#endif  //TEST_FIFO_MAP

int main(int argc, char* argv[])
{
    int result = Catch::Session().run(argc, argv);

    return result;
}
