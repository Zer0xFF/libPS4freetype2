# libPS4freetype2

libPS4freetype2 is a C & C++ wrapper around standard upstream freetype2

you might be asking, why not use PS4 builtin library?
well, (1) there are few reasons, i dont actually have a hackable PS4 Console, (2) that would require some Reverse Engineering and (3) I've been working on getting CMake setup for PS4 projects and wanted to test it on non-PS4 cmake make projects and it worked a treat in this very case (more about CMake later).

### How-To CMake ###
 - to use this library, just add it as subdirectory in cmake `add_subdirectory`
 - link your app with library `PS4freetype2` will automatically include headers directory
 - include one of the following headers C `PS4freetype2.h` or C++: `PS4freetype2.hpp` in your project
 - build your cmake project or this project with `-DCMAKE_TOOLCHAIN_FILE=$PS4SDK/cmake/PS4.toolchain.cmake` argument to set the correct build flags for PS4

### Methods Documantation ###
- C Methods
  - int initPS4FreeType(int height, int width, DrawText drawText);
  - void finishPS4FreeType();
  - void drawPS4FreeTypeText(int x, int y, const char *text, int size, int color);
  - int addFontPS4FreeType(char* filename);
  - void drawCustomFontPS4FreeTypeText(int x, int y, const char *text, int size, int color, int index);
- C++ Methods
  - PS4freetype2(int height, int width, DrawText); Constructor
  -	void drawText(int x, int y, const char *text, int size, int color);
  - void drawCustomFontText(int x, int y, const char *text, int size, int color, int font_index);
  - int addFont(char* filename);

### How-To Methods ###
- **if you're using C**
    - `initPS4FreeType(int height, int width, DrawText drawText)` should be called 1st, height/width is the screen height/width, while DrawText is a pointer to the draw method provided by your app that takes 3 parameters int x, int y, int color e.g `orbis2dWritePixelColor()`
        - this is how this would look like `initPS4FreeType(720, 1280, &orbis2dWritePixelColor);`
    - `drawPS4FreeTypeText(int x, int y, const char *text, int size, int color)` is self explanatory, x/y are screen positions, size is point per 30 ppi, color is in the format your draw method takes
        - `color` is expected in RGB format `0x80000000|R<<16|G<<8|B`
    - `addFontPS4FreeType(char* filename)` takes path location to `otf` or `ttf` font, on success return value `font_index` > 0, on fail returns -1
    - `drawCustomFontPS4FreeTypeText(int x, int y, const char *text, int size, int color, int font_index)` works the same as `drawPS4FreeTypeText()` except the method requires `font_index` which is provided by `addFontPS4FreeType()`
- **if you're using C++**
    - methods work exactly the same, as they're merely wrappers for convenience
    - `PS4freetype2(int height, int width, DrawText drawText)` the constructor takes place instead of `initPS4FreeType()`
    - there is no equivalent to `finishPS4FreeType()`, as it will be called automatically on deconstructor
    - since C++ methods can be overloaded `drawCustomFontText()` will be removed in-favour of an overloaded `drawText()` method

### Note ###
 - The font will look a bit fuzzy, that's most likely because we dont currently have a way to print pixels with alpha support, as such that channel is completely ignored
 - once we find a different way, I'm likely to update the DrawText method to pass on the Alpha value
 
### Bugs ###
 - currently the the free'ing method in `finishPS4FreeType()` crashes on `free(face)`, so it's been commented out, not sure if there is something wrong, or a misunderstanding on my part
 - the C++ wrapper has not been tested, but it's assumed to work, since it's a mere wrapper
 
 ### Credit ###
- Thanks to [@ZeraTron](https://github.com/ZeraTron) & [@Fx0day](https://github.com/fx0day) for testing for me (as I dont have a hackable PS4)
