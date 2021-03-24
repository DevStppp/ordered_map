#define CATCH_CONFIG_RUNNER
#include "constructor_test.h"
#include "iterator_test.h"
#include "lookup_test.h"
#include "modifier_test.h"
#include "swap_test.h"
#include <catch.hpp>

int main(int argc, char* argv[])
{
    int result = Catch::Session().run(argc, argv);

    return result;
}
