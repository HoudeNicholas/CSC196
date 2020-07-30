#pragma once
#include <Windows.h>
#include <iostream>
#include <string>

namespace nc 
{
	struct Color 
	{
		float r, g, b;

		Color() : r{ 0 }, g{ 0 }, b{ 0 } {};
		Color(float r, float g, float b) : r{ r }, g{ g }, b{ b } {};

		inline COLORREF pack888() const {
			BYTE _r = static_cast<BYTE>(r * 255);
			BYTE _g = static_cast<BYTE>(g * 255);
			BYTE _b = static_cast<BYTE>(b * 255);

			return (_r) | (_g << 8) | (_b << 16);
		}

		operator COLORREF() const {
			return pack888();
		}

		Color operator + (const Color& c) const { return Color{ r + c.r, g + c.g, b + c.b }; }
		Color operator - (const Color& c) const { return Color{ r - c.r, g - c.g, b - c.b }; }
		Color operator * (const Color& c) const { return Color{ r * c.r, g * c.g, b * c.b }; }
		Color operator / (const Color& c) const { return Color{ r / c.r, g / c.g, b / c.b }; }

		Color operator + (float s) const { return Color{ r + s, g + s, b + s }; }
		Color operator - (float s) const { return Color{ r - s, g - s, b - s }; }
		Color operator * (float s) const { return Color{ r * s, g * s, b * s }; }
		Color operator / (float s) const { return Color{ r / s, g / s, b / s }; }

		Color operator -= (const Color& c) { return Color{ r -= c.r, g -= c.g, b -= c.b }; }
		Color operator += (const Color& c) { return Color{ r += c.r, g += c.g, b += c.b }; }
		Color operator *= (const Color& c) { return Color{ r *= c.r, g *= c.g, b *= c.b }; }
		Color operator /= (const Color& c) { return Color{ r /= c.r, g /= c.g, b /= c.b }; }

		Color operator += (float s) { return Color{ r += s, g += s, b += s }; }
		Color operator -= (float s) { return Color{ r -= s, g -= s, b -= s }; }
		Color operator *= (float s) { return Color{ r *= s, g *= s, b *= s }; }
		Color operator /= (float s) { return Color{ r /= s, g /= s, b /= s }; }

		friend std::istream& operator >> (std::istream& stream, Color& c)
		{
			std::string line;
			std::getline(stream, line);

			if (line.find("{") != std::string::npos)
			{
				std::string cr = line.substr(line.find("{") + 1, line.find(",") - line.find("{"));
				c.r = std::stof(cr);

				line = line.substr(line.find(",") + 1, line.find("}") - line.find(","));

				std::string cg = line.substr(0, line.find(","));
				c.g = std::stof(cg);

				std::string cb = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);
				c.b = std::stof(cb);

				
			}
			return stream;
		}

	};
}