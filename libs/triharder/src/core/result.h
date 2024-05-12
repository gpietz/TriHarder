#pragma once

#include <iostream>
#include <variant>
#include <string>
#include <functional>

namespace TriHarder {

    enum class ResultType {
        Ok,
        Error
    };

    template<typename T>
    class Result {
    public:
        Result(T value) : value_(value), type_(ResultType::Ok) {}

        [[nodiscard]] static Result<T> error(T errorValue) {
            auto result = Result<T>(errorValue);
            result.type_ = ResultType::Error;
            return result;
        }

        [[nodiscard]] bool is_ok() const {
            return type_ == ResultType::Ok;
        }

        [[nodiscard]] T unwrap() const {
            if (is_ok()) {
                return std::get<0>(value_);
            }
            throw std::runtime_error("Attended to unwrap an error result");
        }

        [[nodiscard]] T unwrap_err() const {
            if (!is_ok()) {
                return std::get<1>(value_);
            }
            throw std::runtime_error("Attended to unwrap a success result");
        }

        [[nodiscard]] T unwrap_or(const T& alternative) const {
            return is_ok() ? unwrap() : alternative;
        }

        [[nodiscard]] T unwrap_or_else(std::function<T> alternative) const {
            return is_ok() ? unwrap() : alternative();
        }

        [[nodiscard]] T unwrap_or_default() const {
            return is_ok() ? unwrap() : T();
        }

        [[nodiscard]] explicit operator bool() const {
            return is_ok();
        }

    private:
        std::variant<T, std::string> value_;
        ResultType type_;
    };
}
