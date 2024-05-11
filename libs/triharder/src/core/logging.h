#include <unordered_map>
#include <filesystem>
#include <utility>
#include <format>
#include "../triharder.h"
#include "spdlog/spdlog.h"

namespace TriHarder {

    //! @enum LogLevel
    //! @brief Represents the severity levels of logging messages.
    //!
    //! This enum defines different levels of logging severity from least to most
    //! severe. It uses uint8_t as the underlying type for memory efficiency.
    //!
    //! @var LogLevel::Debug
    //! @brief The Debug level for detailed system information.
    //!
    //! @var LogLevel::Info
    //! @brief The Info level for general operational messages.
    //!
    //! @var LogLevel::Warn
    //! @brief The Warn level for potential issues or non-critical warnings.
    //!
    //! @var LogLevel::Error
    //! @brief The Error level for serious errors.
    enum LogLevel : uint8_t {
        Debug = 1, //!< Detailed debug information, typically for development.
        Info  = 2, //!< General operational messages - service status or configuration.
        Warn  = 3, //!< Warnings about issues that are not critical.
        Error = 4, //!< Errors that could lead to system malfunction.
    };

    //! @class ILogger
    //! @brief Interface for logging functionality across different log levels.
    //!
    //! Provides an abstract base for logging mechanisms, enabling messages to be
    //! logged at various levels such as debug, info, warn, and error. It also
    //! includes a method to get the name of the logger.
    class ILogger {
    public:
        //! Logs a debug message.
        //! @param message The message to log at debug level.
        virtual void debug(const String &message) const = 0;

        //! Logs an informational message.
        //! @param message The message to log at information level.
        virtual void info(const String &message) const = 0;

        //! Logs a warning message.
        //! @param message The message to warn about.
        virtual void warn(const String &message) const = 0;

        //! Logs an error message.
        //! @param message The error message to log.
        virtual void error(const String &message) const = 0;

        //! Retrieves the name of the logger.
        //! @return The name of the logger.
        //! @note This method is marked as [[nodiscard]] to encourage checking the
        //! return value.
        [[nodiscard]] virtual const String& getName() const = 0;
    };

    //! @class SpdLogger
    //! @brief A concrete logger class that implements the ILogger interface using spdlog.
    //!
    //! This class wraps the spdlog functionality into the ILogger interface, allowing
    //! for logging at various levels and retrieving the logger's name. It also includes
    //! a method to translate generic log levels to spdlog-specific log levels.
    class SpdLogger : public ILogger {
    public:
        //! Constructs a SpdLogger with a name and a spdlog logger instance.
        //! @param name The name of the logger.
        //! @param logger A shared pointer to an spdlog::logger instance.
        SpdLogger(String name, SharedPtr<spdlog::logger> logger)
            : m_name(std::move(name)), m_logger(std::move(logger)) {}

        //! Logs a debug message using spdlog's debug method.
        //! @param message The message to log at debug level.
        void debug(const String& message) const override {
            m_logger->debug(message);
        }

        //! Logs an information message using spdlog's info method.
        //! @param message The message to log at info level.
        void info(const String& message) const override {
            m_logger->info(message);
        }

        //! Logs a warning message using spdlog's warn method.
        //! @param message The message to warn about.
        void warn(const String& message) const override {
            m_logger->warn(message);
        }

        //! Logs an error message using spdlog's error method.
        //! @param message The error message to log.
        void error(const String& message) const override {
            m_logger->error(message);
        }

        //! Retrieves the name of the logger.
        //! @return The name of the logger.
        [[nodiscard]] const String& getName() const override {
            return m_name;
        }

        //! Converts a generic LogLevel to an spdlog-specific log level.
        //! @param level The LogLevel to convert.
        //! @return The corresponding spdlog::level::level_enum value.
        static spdlog::level::level_enum getLevel(LogLevel level) {
            switch (level) {
                case LogLevel::Debug:
                    return spdlog::level::debug;
                case LogLevel::Info:
                    return spdlog::level::info;
                case LogLevel::Warn:
                    return spdlog::level::warn;
                case LogLevel::Error:
                    return spdlog::level::err;
                default:
                    return spdlog::level::debug;
            }
        }

    private:
        String m_name; //!< The name of the logger.
        SharedPtr<spdlog::logger> m_logger; //!< The spdlog logger instance.
    };

    //! @enum LogTargets
    //! @brief Defines targets for log output.
    //!
    //! This enum is used to specify different logging targets by setting various
    //! bit flags. Each flag corresponds to a different output destination for
    //! logging operations.
    //!
    //! @var LogTargets::Console
    //! @brief Logs messages to the console.
    //! Corresponds to the least significant bit.
    //!
    //! @var LogTargets::File
    //! @brief Logs messages to a file.
    //! Set by shifting a 1 to the left by 1 position.
    //!
    //! @var LogTargets::Network
    //! @brief Logs messages over a network.
    //! Set by shifting a 1 to the left by 2 positions.
    enum LogTargets : int {
        Console = 1 << 0, //!< Target log output to the console.
        File    = 1 << 1, //!< Target log output to a file.
        Network = 1 << 2  //!< Target log output to a network location. (reserved)
    };

    //! @function operator|
    //! @brief Combines two LogTargets values using bitwise OR.
    //!
    //! This operator allows combining different logging targets into a single
    //! LogTargets value, enabling logging to multiple destinations simultaneously.
    //! The function uses the underlying integer type of the enum for the operation,
    //! ensuring proper type safety and bitwise operations.
    //!
    //! @param lhs Left-hand side LogTargets value.
    //! @param rhs Right-hand side LogTargets value.
    //! @return A LogTargets value representing the combination of lhs and rhs.
    inline LogTargets operator|(LogTargets lhs, LogTargets rhs) {
        return static_cast<LogTargets>(
            static_cast<std::underlying_type<LogTargets>::type>(lhs) |
            static_cast<std::underlying_type<LogTargets>::type>(rhs)
        );
    }

    //! @function operator&
    //! @brief Combines two LogTargets values using bitwise AND.
    //!
    //! This operator is used to intersect different logging targets. It enables
    //! checking if specific log targets are common between two LogTargets values.
    //! The operation is performed safely by casting to the underlying integer type
    //! of the enum before performing the bitwise AND, then casting the result back
    //! to LogTargets type.
    //!
    //! @param lhs Left-hand side LogTargets value.
    //! @param rhs Right-hand side LogTargets value.
    //! @return A LogTargets value representing the common elements between lhs and rhs.
    inline LogTargets operator&(LogTargets lhs, LogTargets rhs) {
        return static_cast<LogTargets>(
            static_cast<std::underlying_type<LogTargets>::type>(lhs) &
            static_cast<std::underlying_type<LogTargets>::type>(rhs)
        );
    }

    //! @function operator^
    //! @brief Combines two LogTargets values using bitwise XOR.
    //!
    //! This operator is used to toggle logging targets between two LogTargets values.
    //! It provides a way to enable or disable specific log targets based on their
    //! current states. The bitwise XOR operation is conducted by casting the enum
    //! values to their underlying type, performing the XOR, and then casting back
    //! to the LogTargets type for type safety and clarity.
    //!
    //! @param lhs Left-hand side LogTargets value.
    //! @param rhs Right-hand side LogTargets value.
    //! @return A LogTargets value that toggles the bits different between lhs and rhs.
    inline LogTargets operator^(LogTargets lhs, LogTargets rhs) {
        return static_cast<LogTargets>(
            static_cast<std::underlying_type<LogTargets>::type>(lhs) ^
            static_cast<std::underlying_type<LogTargets>::type>(rhs)
        );
    }

    inline LogTargets operator~(LogTargets rhs) {
        return static_cast<LogTargets>(
            ~static_cast<std::underlying_type<LogTargets>::type>(rhs)
        );
    }

    inline LogTargets& operator|=(LogTargets& lhs, LogTargets rhs) {
        lhs = lhs | rhs;
        return lhs;
    }

    inline LogTargets& operator&=(LogTargets& lhs, LogTargets rhs) {
        lhs = lhs & rhs;
        return lhs;
    }

    inline LogTargets& operator^=(LogTargets& lhs, LogTargets rhs) {
        lhs = lhs ^ rhs;
        return lhs;
    }

    class LogManager {
    public:
        static LogManager& getInstance();

        SharedPtr<ILogger> getLogger();
        SharedPtr<ILogger> getLogger(const String& name, bool allowFile = true, bool allowNetwork = true);

        [[nodiscard]] bool isDefaultTargetEnabled(uint8_t target) const;

    private:
        std::unordered_map<String, SharedPtr<ILogger>> m_loggers;
        LogTargets m_defaultTargets = LogTargets::Console | LogTargets::File;
        LogLevel m_defaultLevel = LogLevel::Debug;
        String m_defaultPattern = "[%Y-%m-%d %H:%M:%S] [%^%l%$] %v";
    };
}
