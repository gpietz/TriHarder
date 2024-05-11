#include "sdl_context.h"
#include "logging.h"
#include <SDL2/SDL.h>

namespace TriHarder {

    SdlContext &SdlContext::getInstance() {
        static SdlContext instance;
        return instance;
    }

    bool SdlContext::initialize() {
        auto logger = LogManager::getInstance().getLogger();
        if (initialized_)
        {
            logger->warn("The SDL context has already been initialized. Attempting to initialize it again may lead to unexpected behavior.");
            return false;
        }

        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            logger->error(std::format("Failed to initialize SDL: {}", SDL_GetError()));
            throw std::runtime_error(std::format("Failed to initialize SDL: {}", SDL_GetError()));
            return false;
        }

        logger->info("SDL initialized");
        initialized_ = true;
        return true;
    }

    bool SdlContext::isInitialized() const {
        return initialized_;
    }

    void SdlContext::destroy() {
        if (!initialized_) {
            auto logger = LogManager::getInstance().getLogger();
            logger->warn("The SDL context has already been destroyed. Attempting to destroy it again may lead to unexpected behavior.");
            return;
        }

        SDL_Quit();
        initialized_ = false;
    }
}
