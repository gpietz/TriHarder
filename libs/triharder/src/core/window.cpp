#include "window.h"
#include "logging.h"
#include "sdl_context.h"

namespace TriHarder {
    UniquePtr<Window> Window::create(const WindowDescriptor &descriptor) {
        auto window = new Window();
        window->initialize(descriptor);
        return UniquePtr<Window>(window);
    }

    void Window::initialize(const TriHarder::WindowDescriptor &descriptor) {
        m_title = descriptor.Title;
        m_width = descriptor.Width;
        m_height = descriptor.Height;

        SdlContext::getInstance().initialize();

        auto logger = LogManager::getInstance().getLogger();
        logger->info(std::format("Creating window with title: {}, width: {}, height: {}",
                                 m_title, m_width, m_height));

        m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    (int)m_width, (int)m_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (!m_window) {
            logger->error(std::format("Failed to create window: {}", SDL_GetError()));
            throw std::runtime_error("Failed to create window");
        }

        // Create OpenGL context
        m_glContext = SDL_GL_CreateContext(m_window);
        if (!m_glContext) {
            logger->error(std::format("Failed to create OpenGL context: {}", SDL_GetError()));
            throw std::runtime_error("Failed to create OpenGL context");
        }
    }

    Window::~Window() {
        SDL_GL_DeleteContext(m_glContext);
        SDL_DestroyWindow(m_window);
    }
}
