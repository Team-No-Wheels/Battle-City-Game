#pragma once

namespace AnonymousEngine
{
	namespace Graphics
	{
		class Color
		{
		public:
			unsigned char r;
			unsigned char b;
			unsigned char g;

			Color() :
				r(255), g(255), b(255)
			{}

			Color(unsigned char pRed, unsigned char pGreen, unsigned char pBlue) : 
				r(pRed), g(pGreen), b(pBlue)
			{}
			
			static const Color WHITE;
			static const Color RED;
			static const Color BLUE;
			static const Color GREEN;
		};
	}
}