#include <catch2/catch_test_macros.hpp>
#include "core/result.h"

using namespace TriHarder;

TEST_CASE("Result:Constructor and OK status", "[Result]") {
    Result<int> result(42);

    SECTION("is_ok returns true fpr ok results") {
        REQUIRE(result.is_ok());
    }

    SECTION("unwrap returns the correct value") {
        REQUIRE(result.unwrap() == 42);
    }
}
