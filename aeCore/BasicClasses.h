#pragma once
#include "PlatformDefinitions.h"
#include "dll_definition.h"

namespace aeCore
{
	/**********************************************************************************************//**
	 * @struct	aePoint
	 *
	 * @brief	It's a 2 elements structure, it has an union between integer values x and w, and also
	 * 			y and h; it's for easy access.
	 **************************************************************************************************/

	struct LIBRARY_EXPORT aePoint
	{
		union
		{
			struct 
			{
				int x, y;
			};
			struct
			{
				int w, h;
			};
		};

		aePoint() : x(0), y(0) {};
		~aePoint() {};

		aePoint(const aePoint& Other)
		{
			*this = Other;
		}
		aePoint(int X, int Y) : x(X), y(Y)
		{
		}
	};


	/**********************************************************************************************//**
	 * @struct	aeRect
	 *
	 * @brief	A rectangle.
	 **************************************************************************************************/

	struct LIBRARY_EXPORT aeRect
	{
		int x, y, w, h;

		aeRect() : x(0), y(0), w(0), h(0) {};
		~aeRect() {};

		aeRect(const aeRect& Other)
		{
			*this = Other;
		}
		aeRect(int X, int Y, int W, int H) : x(X), y(Y), w(W), h(H)
		{
		}

		inline bool HitTest(int X, int Y)
		{
			return X >= x && X < x + w && Y >= y && Y < y + h ? true : false;
		}
	};

	/**********************************************************************************************//**
	 * @struct	aeRGB
	 *
	 * @brief	Is a color structure with RGB capacity.
	 **************************************************************************************************/

	struct LIBRARY_EXPORT aeRGB
	{
		union
		{
			struct
			{
				unsigned __int8 r, g, b;
			};
			unsigned __int32 Color;
		};

		aeRGB() : r(0), g(0), b(0)
		{
		}
		~aeRGB() {}

		aeRGB(const aeRGB& Other)
		{
			*this = Other;
		}
		aeRGB(uint8 R, uint8 G, uint8 B) : r(R), g(G), b(B)
		{
		}
		aeRGB(unsigned __int32 COLOR) : Color(COLOR)
		{
		}
	};

	/**********************************************************************************************//**
	 * @struct	aeRGBQuad
	 *
	 * @brief	Is a color structure with RGBA capacity.
	 **************************************************************************************************/

	struct LIBRARY_EXPORT aeRGBQuad
	{
		union
		{
			struct
			{
				unsigned __int8 r, g, b, a;
			};
			unsigned __int32 Color;
		};

		aeRGBQuad() : r(0), g(0), b(0), a(0)
		{
		}
		~aeRGBQuad() 
		{
		}

		aeRGBQuad(const aeRGBQuad& Other)
		{
			*this = Other;
		}
		aeRGBQuad(unsigned char R, unsigned char G, unsigned char B, unsigned char A) : r(R), g(G), b(B), a(A)
		{
		}
		aeRGBQuad(unsigned __int32 COLOR) : Color(COLOR)
		{
		}
	};

	
}