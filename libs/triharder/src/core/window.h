#pragma once
#include <utility>
#include <SDL_video.h>

#include "../triharder.h"

namespace TriHarder {

    /**
     * @struct WindowDescriptor
     * @brief Defines the properties of a window to be created.
     *
     * This structure is used to specify the characteristics of a window, including its title,
     * width, and height. It serves as a parameter for window creation functions, allowing
     * for the customization of window properties before creation.
     *
     * @param Title The title of the window. Default is "TriHarder Library".
     * @param Width The width of the window in pixels. Default is 1600.
     * @param Height The height of the window in pixels. Default is 900.
     */
    struct WindowDescriptor {
        String Title; ///< The title of the window.
        uint32_t Width; ///< The width of the window in pixels.
        uint32_t Height; ///< The height of the window in pixels.

        /**
         * @brief Constructs a WindowDescriptor with specified properties.
         *
         * This constructor initializes a WindowDescriptor object with the given title, width,
         * and height. If no arguments are provided, it defaults to a predefined set of values.
         *
         * @param title The title of the window. Defaults to "TriHarder Library".
         * @param width The width of the window in pixels. Defaults to 1600.
         * @param height The height of the window in pixels. Defaults to 900.
         */
        explicit WindowDescriptor(String title = "TriHarder Library", uint32_t width = 1600, uint32_t height = 900)
            : Title(std::move(title)), Width(width), Height(height)
        {
        }
    };

    class Window {
    public:
        static UniquePtr<Window> create(const WindowDescriptor &descriptor = WindowDescriptor());
        ~Window();

        void SwapBuffers() const;

    private:
        String title_;
        uint32_t width_ = 0;
        uint32_t height_ = 0;
        SDL_Window *window_ = nullptr;
        SDL_GLContext gl_context_ = nullptr;

        void initialize(const WindowDescriptor &descriptor);
    };
}
