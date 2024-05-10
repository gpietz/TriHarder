# TriHarder Coding Guidelines
<hr>

### 1. Use Lowercase Letters 

Using lowercase for filenames can help avoid issues with case sensitivity on different operating systems. 
This is particularly important if you're working in a team or distributing your code across platforms like Windows, 
Linux, and macOS.

### 2. Use Underscores to Separate Words

Some developers prefer using underscores to separate words in filenames. This approach is particularly common in 
C++ projects and helps improve readability:

* `render_engine.cpp`
* `game_controller.cpp`

### 3. Match Filenames to Class Names

If a file contains a single class or a closely related set of classes, name the file after the primary class. 
This makes it easier to find the relevant file when looking for specific class implementations:

* For a class named `GameController`, the file name should be `game_controller.cpp` and `game_controller.h`.

### 4. Header and Source Files

Keep the naming consistent between header and source files to make it easy to associate related files:

* `game_controller.h` for headers
* `game_controller.cpp`for source files

### 5. Group Related Files in Directories

Organize related files within the same directory. Use directory names to indicate what types of files are inside, 
and structure your directories in a way that reflects the components or modules of your project:

* `/graphics` for rendering related files.
* `/network` for networking related files.

### 6. Use Specific Suffixes for Special Types

For specific types of files, like templates or inline implementations, consider using additional suffixes:

* `myclass_impl.h` for template implementations if they are not in the .cpp file.
* `myclass.inl` for inline function definitions that included in the headers.

### 7. Avoid Using Spaces

paces in filenames can cause issues with build scripts and command-line operations. Always use underscores or 
camelCase instead of spaces.

### 8. Keep It Short and Descriptive

Filenames should be both concise and descriptive enough to reflect their contents without being overly verbose. 
This balance helps in maintaining an easily navigable codebase.

### 9. Consistency

Perhaps the most important rule is to be consistent. Whatever naming convention you choose, apply it consistently 
throughout the project. Consistency helps in reducing the learning curve for new developers and in maintaining
the project.

### 10. Documentation

Document your naming conventions in your project's README or developer guidelines. This helps new contributors 
follow the established patterns.

By following these practices, you can ensure that your C++ project remains organized and that your files are easy 
to navigate and understand.
