#pragma once
#include <functional>
#include <vector>
extern "C"
{
	#include <ft2build.h>
	#include FT_FREETYPE_H
}

#define PS4FREETYPE2_HPP

class PS4freetype2
{
private:
	int					_width = 1280;
	int					_height = 720;

	FT_Library			library;
	std::vector<FT_Face>	face;
	int					count = -1;

	typedef std::function<void(int x, int y, int color)> DrawCallback;
	DrawCallback			_drawText;

	int					init(int height, int width, DrawCallback drawText);
	void				finish();
	void				draw_bitmap(FT_Bitmap* bitmap, FT_Int x, FT_Int y, int size, int color);
	virtual void		drawText(int, int, int) = 0;

public:
	PS4freetype2(int, int, DrawCallback);
	PS4freetype2(int, int);
	~PS4freetype2();
	void DrawText(int x, int y, const char *text, int size, int color, int font_index = 0);
	int addFont(char* filename);
};
