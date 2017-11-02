
extern "C"
{	
	#include "PS4freetype2.h"
}
#include "PS4freetype2.hpp"

PS4freetype2::PS4freetype2(int h, int w, DrawText drawText)
{
	initPS4FreeType(h,w, drawText);
}

PS4freetype2::~PS4freetype2()
{
	finishPS4FreeType();
}

void PS4freetype2::drawText(int x, int y, const char *text, int size, int color, int font_index)
{
	drawCustomFontPS4FreeTypeText(x, y, text, size, color, font_index);
}

int PS4freetype2::addFont(char* filename)
{
	return addFontPS4FreeType(filename);
}
