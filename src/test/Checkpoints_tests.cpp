//
// Unit tests for block-chain checkpoints
//
#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/test/unit_test.hpp>
#include <boost/foreach.hpp>

#include "../checkpoints.h"
#include "../util.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(Checkpoints_tests)

BOOST_AUTO_TEST_CASE(sanity)
{
    uint256 p405 = uint256("0x00000000010a5becc2de4e7af1f48209383924342ed7bbbc822a63df311dc72a");
    uint256 p800 = uint256("0x0000000000c2d5be6c8eebc3f395db1f934773db0a882fb629f6a43568c56714");
    BOOST_CHECK(Checkpoints::CheckBlock(405, p405));
    BOOST_CHECK(Checkpoints::CheckBlock(800, p800));

    
    // Wrong hashes at checkpoints should fail:
    BOOST_CHECK(!Checkpoints::CheckBlock(405, p800));
    BOOST_CHECK(!Checkpoints::CheckBlock(800, p405));

    // ... but any hash not at a checkpoint should succeed:
    BOOST_CHECK(Checkpoints::CheckBlock(405+1, p800));
    BOOST_CHECK(Checkpoints::CheckBlock(800+1, p405));

    BOOST_CHECK(Checkpoints::GetTotalBlocksEstimate() >= 0);
}    

BOOST_AUTO_TEST_SUITE_END()
