#pragma once

#include <exception>
#include <string>
#include <core/result.h>

namespace TriHarder {
    //! @class SceneError
    //! @brief This class represents an error that occurs within a scene. It inherits from the standard exception
    //! class and provides a custom error message.
    class SceneError : public std::exception {
    public:
        //! @brief Constructs a SceneError object without any error message.
        SceneError() = default;

        //! @brief Constructs a SceneError object with the specified error message.
        //! @param[in] msg The error message to be associated with the SceneError object.
        SceneError(const std::string &msg) : m_msg(msg) {}

        //! @return A pointer to a null-terminated string containing the error message.
        const char *what() const noexcept override {
            return m_msg.empty() ? "Scene error occurred" : m_msg.c_str();
        }

    protected:
        //! @brief The error message associated with the SceneError object.
        std::string m_msg;
    };

    //! @class ResourceLoadError
    //! @brief This class represents an error that occurs when a resource fails to load. It inherits from the SceneError.
    class ResourceLoadError : public SceneError {
    public:
        //! @brief Constructs a SceneError object without any error message.
        ResourceLoadError() : SceneError("Resource loading failed") {}

        //! @brief Constructs a ResourceLoadError object with the specified error message.
        //! @param[in] msg The error message to be associated with the ResourceLoadError object.
        ResourceLoadError(const std::string &msg) : SceneError(msg) {}
    };

    //! @class InvalidStateTransition
    //! @brief This class represents an error that occurs when a state transition is invalid. It inherits from the SceneError.
    class InvalidStateTransition : public SceneError {
    public:
        //! @brief Constructs an InvalidStateTransition object without any error message.
        InvalidStateTransition() :SceneError("Invalid state transition") {}

        //! @brief Constructs an InvalidStateTransition object with the specified error message.
        InvalidStateTransition(const std::string &msg) : SceneError(msg) {}
    };

    //! @class VaoCreationError
    //! @brief This class represents an error that occurs when a VAO fails to be created. It inherits from the SceneError.
    class VaoCreationError : public SceneError {
    public:
        VaoCreationError(const std::string& error) :SceneError("Failed to activate scene due to VAO creation error: " + error) {}
    };

    class VertexLayoutError : public SceneError {
    public:
        VertexLayoutError() : SceneError("Failed to setup vertex layout") {}
    };

    class TextureLoadError : public SceneError {
    public:
        TextureLoadError(const std::string& name) : SceneError("Failed to load texture: " + name) {}
    };

    using SceneResult = Result<std::monostate, SceneError*>;
}
