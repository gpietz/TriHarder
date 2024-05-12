#include <catch2/catch_test_macros.hpp>
#include "core/result.h"

using namespace TriHarder;

TEST_CASE("Result class functionality with int", "[Result]") {
    using ResultType = Result<int, std::string>;

    SECTION("Constructor with Ok value initializes correctly") {
        ResultType res = ResultType(42);
        REQUIRE(res.is_ok());
        REQUIRE(res.unwrap() == 42);
    }

    SECTION("Error factory creates correct Error result") {
        ResultType res = ResultType::error("Error message");
        REQUIRE_FALSE(res.is_ok());
        REQUIRE(res.unwrap_err() == "Error message");
    }

    SECTION("unwrap throws on Error result") {
        ResultType res = ResultType::error("Error");
        REQUIRE_THROWS_AS(res.unwrap(), std::runtime_error);
    }

    SECTION("unwrap_err throws on Ok result") {
        ResultType res = ResultType(42);
        REQUIRE_THROWS_AS(res.unwrap_err(), std::runtime_error);
    }

    SECTION("unwrap_or provides correct alternative on Error result") {
        ResultType res = ResultType::error("Error");
        REQUIRE(res.unwrap_or(100) == 100);
    }

    SECTION("unwrap_or_else provides function alternative on Error result") {
        ResultType res = ResultType::error("Error");
        auto alternative = []() { return 100; };
        REQUIRE(res.unwrap_or_else(alternative) == 100);
    }

    SECTION("unwrap_or_default returns default value on Error result") {
        ResultType res = ResultType::error("Error");
        REQUIRE(res.unwrap_or_default() == 0);
    }

    SECTION("operator bool returns true on Ok result and false on Error result") {
        ResultType okRes = ResultType(42);
        ResultType errorRes = ResultType::error("Error");
        REQUIRE(static_cast<bool>(okRes));
        REQUIRE_FALSE(static_cast<bool>(errorRes));
    }
}
