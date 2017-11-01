#pragma once

typedef void (*DrawText)(int x, int y, int color);

int initPS4FreeType(int height, int width, DrawText drawText);
void finishPS4FreeType();
void drawPS4FreeTypeText(int x, int y, const char *text, int size, int color);
void drawCustomFontPS4FreeTypeText(int x, int y, const char *text, int size, int color, int font_index);
int addFontPS4FreeType(char* filename);
