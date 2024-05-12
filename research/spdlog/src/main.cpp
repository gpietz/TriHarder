#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

int main() {
    spdlog::info("Hello, spdlog!");
    spdlog::error("This is an testerror.");

    // Console logger
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::debug); // Minimum log-level
    console_sink->set_pattern("[multi_sink_example] [%^%L%$] %v");

    // FIle logger
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/multisink.txt",  true);
    file_sink->set_level(spdlog::level::trace);

    // Multi logger
    spdlog::logger logger("multi_sink", {console_sink, file_sink});
    logger.set_level(spdlog::level::trace);
    logger.warn("Warning");
    logger.error("Error");
    logger.info("Info");
    logger.debug("Debug");

    return 0;
}
