#pragma once

#include <iostream>

namespace TriHarder {

    enum class ResultType {
        Ok,
        Error
    };

    template<typename T, typename E = std::string>
    class Result {
    public:

        [[nodiscard]] static Result<T, E> ok(T value) {
            auto result = Result<T, E>(value);
            result.type_ = ResultType::Ok;
            return result;
        }

        [[nodiscard]] static Result<T, E> error(E errorValue) {
            auto result = Result<T, E>();
            result.value_error_ = errorValue;
            result.type_ = ResultType::Error;
            return result;
        }

        [[nodiscard]] constexpr bool is_ok() const {
            return type_ == ResultType::Ok;
        }

        [[nodiscard]] constexpr bool is_error() const {
            return type_ == ResultType::Error;
        }

        [[nodiscard]] T unwrap() const {
            if (is_ok()) {
                return value_ok_;
            }
            throw std::runtime_error("Attended to unwrap an error result");
        }

        [[nodiscard]] E unwrap_err() const {
            if (!is_ok()) {
                return value_error_;
            }
            throw std::runtime_error("Attended to unwrap a success result");
        }

        [[nodiscard]] T unwrap_or(const T& alternative) const {
            return is_ok() ? unwrap() : alternative;
        }

        template<typename F>
        [[nodiscard]] T unwrap_or_else(F&& alternative) const {
            return is_ok() ? unwrap() : alternative();
        }

        [[nodiscard]] T unwrap_or_default() const {
            if (is_ok()) {
                return value_ok_;
            }
            return T();
        }

        [[nodiscard]] explicit operator bool() const {
            return is_ok();
        }

    private:
        T value_ok_;
        E value_error_;
        ResultType type_;

        explicit Result() : type_(ResultType::Error) {};
        explicit Result(T value) : value_ok_(std::move(value)), type_(ResultType::Ok) {};
    };
}
