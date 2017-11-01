#pragma once

class PS4freetype2
{
public:
	typedef void (*DrawText)(int x, int y, int color);
	
	PS4freetype2(int, int, DrawText);
	~PS4freetype2();
	void drawText(int x, int y, const char *text, int size, int color);
	void drawCustomFontText(int x, int y, const char *text, int size, int color, int font_index);
	int addFont(char* filename);
};
