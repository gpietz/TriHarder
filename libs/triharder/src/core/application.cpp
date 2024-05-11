#include <glad/glad.h>
#include <SDL_events.h>
#include <chrono>
#include <thread>
#include "application.h"
#include "window.h"
#include "logging.h"

namespace TriHarder {

    bool isEscapePressed(const SDL_Event& event) {
        return event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE;
    }

    void Application::run() {
        window_ = Window::create();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        auto logger = LogManager::getInstance().getLogger();
        while (true){
            glClear(GL_COLOR_BUFFER_BIT);
            window_->SwapBuffers();
            SDL_Event event;
            if (SDL_PollEvent(&event) && event.type) {
                switch (event.type) {
                    case SDL_QUIT:
                        return;
                    case SDL_KEYDOWN:
                        if (isEscapePressed(event)) {
                            logger->info("Escape pressed - exiting...");
                            return;
                        }
                        break;
                    default:
                        break;
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}
