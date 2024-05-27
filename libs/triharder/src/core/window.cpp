#include "window.h"
#include "logging.h"
#include "sdl_context.h"
#include <glad/glad.h>

namespace TriHarder {
    UniquePtr<Window> Window::create(const WindowDescriptor &descriptor) {
        auto window = new Window();
        window->initialize(descriptor);
        return UniquePtr<Window>(window);
    }

    void Window::initialize(const TriHarder::WindowDescriptor &descriptor) {
        title_ = descriptor.Title;
        width_ = descriptor.Width;
        height_ = descriptor.Height;

        SdlContext::getInstance().initialize();

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        auto logger = LogManager::getInstance().getLogger();
        logger->info(std::format("Creating window with title: {}, width: {}, height: {}",
                                 title_, width_, height_));

        window_ = SDL_CreateWindow(title_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    (int)width_, (int)height_, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (!window_) {
            logger->error(std::format("Failed to create window: {}", SDL_GetError()));
            throw std::runtime_error("Failed to create window");
        }

        // Create OpenGL context
        gl_context_ = SDL_GL_CreateContext(window_);
        if (!gl_context_) {
            logger->error(std::format("Failed to create OpenGL context: {}", SDL_GetError()));
            throw std::runtime_error("Failed to create OpenGL context");
        }

        // Initialize GLAD
        if (!gladLoadGLLoader(GLADloadproc(SDL_GL_GetProcAddress))) {
            logger->error("Failed to initialize GLAD");
            throw std::runtime_error("Failed to initialize GLAD");
        }
    }

    Window::~Window() {
        SDL_GL_DeleteContext(gl_context_);
        SDL_DestroyWindow(window_);
    }

    void Window::SwapBuffers() const {
        SDL_GL_SwapWindow(window_);
    }
}
