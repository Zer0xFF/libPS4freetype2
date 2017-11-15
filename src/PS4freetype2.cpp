#include "PS4freetype2.hpp"

PS4freetype2::PS4freetype2(int h, int w, DrawCallback drawText)
{
	init(h,w, drawText);
}

PS4freetype2::PS4freetype2(int h, int w)
{
	init(h,w,
		[&](int x, int y, int color){ drawText(x,y,color);}
	);
}

PS4freetype2::~PS4freetype2()
{
	finish();
}

void PS4freetype2::DrawText(int x, int y, const char *text, int size, int color, int font_index)
{
	FT_GlyphSlot  slot;
	
	int num_chars = strlen(text);
	
	int pen_x = x;
	int pen_y = y;

	/* use {size}pt at 30dpi */
	FT_Set_Char_Size(face.at(font_index), size * 64, 0, 30, 0);

	slot = face.at(font_index)->glyph;

	for (int n = 0; n < num_chars; n++)
	{
		/* load glyph image into the slot (erase previous one) */
		if (FT_Load_Char(face.at(font_index), text[n], FT_LOAD_RENDER))
			continue;

		/* now, draw to our target surface (convert position) */
		draw_bitmap(&slot->bitmap,
			pen_x + slot->bitmap_left,
			pen_y - slot->bitmap_top + 10,
			size, color);

		/* increment pen position */
		pen_x += slot->advance.x >> 6;
		pen_y += slot->advance.y >> 6;
	}
	return;
}

int PS4freetype2::addFont(char* filename)
{
	FT_Face l_face;
	if(FT_New_Face(library, filename, 0, &l_face) == 0)
	{
		face.push_back(l_face);
		return ++count;
	}
	return -1;
}

int PS4freetype2::init(int height, int width, DrawCallback drawText)
{
	_height = height;
	_width = width;
	_drawText = drawText;

	if(FT_Init_FreeType(&library) == 0)
	{
		return addFont("/preinst/common/font/SST-Light.otf");
	}
	return -1;
}

void PS4freetype2::finish()
{
	for(int i = 0; i < count + 1; i++)
	{
		FT_Done_Face(face.at(i));
	}
	//free is currently causing segfault
	face.clear();
	FT_Done_FreeType(library);
}

void PS4freetype2::draw_bitmap(FT_Bitmap* bitmap, FT_Int x, FT_Int y, int size, int color)
{
	FT_Int x_max = x + bitmap->width;
	FT_Int y_max = y + bitmap->rows;


	for(int i = x; i < x_max; i++)
	{
		for(int j = y; j < y_max; j++)
		{
			if(i < 0 || j < 0 || i >= _width || j >= _height)
				continue;

			unsigned char bitmask = bitmap->buffer[(j - y) * bitmap->width + i - x];
			if(bitmask != 0)
			{
				_drawText(i, j, color);
			}
		}
	}
}
