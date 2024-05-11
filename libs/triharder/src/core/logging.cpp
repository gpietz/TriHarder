#include "logging.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace TriHarder {

    LogManager& LogManager::getInstance() {
        static LogManager instance;
        return instance;
    }

    SharedPtr<ILogger> LogManager::getLogger() {
        return getLogger("TriHarder");
    }

    SharedPtr<ILogger> LogManager::getLogger(const String& name,
                                             bool allowFile,
                                             bool allowNetwork) {
        auto it = m_loggers.find(name);
        if (it != m_loggers.end()) {
            return it->second;
        }

        // Create multi-sink logger for different destinations
        std::vector<spdlog::sink_ptr> sinks;
        if (m_defaultTargets & LogTargets::Console) {
            auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            consoleSink->set_level(SpdLogger::getLevel(m_defaultLevel));
            consoleSink->set_pattern(m_defaultPattern);
            sinks.push_back(consoleSink);
        }

        if (m_defaultTargets & LogTargets::File && allowFile) {
            namespace fs = std::filesystem;
            fs::path logPath = fs::path("logs") / (name + ".log");
            auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logPath.string(), false);
            file_sink->set_level(SpdLogger::getLevel(m_defaultLevel));
            file_sink->set_pattern(m_defaultPattern);
            sinks.push_back(file_sink);
        }

        auto logger = createSharedPtr<spdlog::logger>(name, begin(sinks), end(sinks));
        spdlog::register_logger(logger);

        auto spdLogger = createSharedPtr<SpdLogger>(name, logger);
        m_loggers[name] = spdLogger;
        return spdLogger;
    }

    bool LogManager::isDefaultTargetEnabled(uint8_t target) const {
        return m_defaultTargets & target;
    }

}
