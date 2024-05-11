#pragma once

#include <memory>
#include <iostream>

namespace TriHarder {

    //! @template UniquePtr
    //! @brief Template alias for std::unique_ptr.
    //!
    //! This template alias simplifies the usage of std::unique_ptr by providing a
    //! shorthand notation. std::unique_ptr is a smart pointer that owns and manages
    //! another object through a pointer and disposes of that object when the unique_ptr
    //! goes out of scope. Unlike std::shared_ptr, no two unique_ptr instances can
    //! manage the same object.
    //!
    //! @tparam T The type of the object managed by the pointer.
    template<typename T>
    using UniquePtr = std::unique_ptr<T>;

    //! @function createUniquePtr
    //! @brief Creates a UniquePtr<T> using the given constructor arguments.
    //!
    //! This template function simplifies the creation of a UniquePtr (std::unique_ptr)
    //! by utilizing std::make_unique. It forwards all provided arguments to the
    //! constructor of T, enabling efficient creation and initialization of a T
    //! object managed by a UniquePtr. This method is constexpr, meaning it can be
    //! evaluated at compile time if given constant expressions.
    //!
    //! @tparam T The type of the object to create and manage.
    //! @tparam Args Variadic template arguments corresponding to the constructor
    //!              parameters of the type T.
    //! @param args The arguments to forward to the constructor of T.
    //! @return A UniquePtr<T> that owns the newly created object.
    template<typename T, typename ... Args>
    constexpr UniquePtr<T> createUniquePtr(Args&& ... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    //! @template SharedPtr
    //! @brief Template alias for std::shared_ptr.
    //!
    //! This template alias offers a simplified notation for std::shared_ptr, which is
    //! a smart pointer that retains shared ownership of an object through a pointer.
    //! Multiple shared_ptr instances can own the same object, and the object is
    //! destroyed automatically once the last shared_ptr owning it is destroyed or
    //! reset. This smart pointer type is useful for managing objects in scenarios
    //! where multiple owners might be needed, preventing premature deletion.
    //!
    //! @tparam T The type of the object managed by the pointer.
    template<typename T>
    using SharedPtr = std::shared_ptr<T>;

    //! @function createSharedPtr
    //! @brief Creates a SharedPtr<T> using the given constructor arguments.
    //!
    //! This template function facilitates the creation of a SharedPtr (std::shared_ptr)
    //! using std::make_shared. It efficiently forwards all provided arguments to the
    //! constructor of T, allowing for the direct initialization of a T object managed
    //! by a SharedPtr. The use of std::make_shared ensures that the memory for the
    //! object and its control block is allocated in a single operation, enhancing
    //! performance and reducing memory overhead. This method is constexpr, enabling
    //! it to be evaluated at compile time if given constant expressions.
    //!
    //! @tparam T The type of the object to create and manage.
    //! @tparam Args Variadic template arguments corresponding to the constructor
    //!              parameters of the type T.
    //! @param args The arguments to forward to the constructor of T.
    //! @return A SharedPtr<T> that owns the newly created object.
    template<typename T, typename  ... Args>
    constexpr SharedPtr<T> createSharedPtr(Args&& ... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    //! @typedef String
    //! @brief Type alias for std::string.
    //!
    //! This type definition simplifies code readability and writing by using 'String'
    //! as an alias for std::string. std::string is a standard library type that
    //! provides support for managing sequences of characters in a dynamic array,
    //! facilitating string manipulation operations such as concatenation, comparison,
    //! and assignment. Using 'String' as an alias allows for more succinct and
    //! potentially more familiar terminology in codebases where simple type names are
    //! preferred.
    typedef std::string String;

}
