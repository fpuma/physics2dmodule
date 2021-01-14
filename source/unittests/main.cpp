#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "worldtest.h"
#include "frametest.h"

int main( int argc, char* argv[] )
{
    ::testing::InitGoogleTest( &argc, argv );
    ::RUN_ALL_TESTS();
    return 0;
}
