// Granola - Granola - ColorUtilities.h
// Created: 2023.06.15-3:58 PM
// Modified: 2023.06.15-3:58 PM
// 
// Copyright Michael Kowalski 2023

#pragma once

namespace Granola
{
	class ColorUtilities
	{
	public:
		static constexpr glm::vec3 RGBtoFloats(const int r, const int g, const int b)
		{
			return {static_cast<float>(r) / 255.0f, static_cast<float>(g) / 255.0f, static_cast<float>(b) / 255.0f};
		}

		static constexpr glm::vec3 HEXtoFloats(const long hex)
		{
			return RGBtoFloats((hex >> 16) & 0xFF, (hex >> 8) & 0xFF, hex & 0xFF);
		}

		static constexpr glm::vec3 FloatstoRGB(const float r, const float g, const float b)
		{
			return {static_cast<int>(r * 255.0f), static_cast<int>(g * 255.0f), static_cast<int>(b * 255.0f)};
		}

		static constexpr glm::vec3 Darken(const glm::vec3 color, const float factor = 0.1f)
		{
			return {color.x * factor, color.y * factor, color.z * factor};
		}

		static constexpr glm::vec3 Lighten(const glm::vec3 color, const float factor = 0.1f)
		{
			return {
				color.x + (1.0f - color.x) * factor, color.y + (1.0f - color.y) * factor,
				color.z + (1.0f - color.z) * factor
			};
		}

		static constexpr glm::vec3 Invert(const glm::vec3 color)
		{
			return {1.0f - color.x, 1.0f - color.y, 1.0f - color.z};
		}

		static constexpr glm::vec3 Blend(const glm::vec3 color1, const glm::vec3 color2, const float factor = 0.5f)
		{
			return {
				color1.x * factor + color2.x * (1.0f - factor), color1.y * factor + color2.y * (1.0f - factor),
				color1.z * factor + color2.z * (1.0f - factor)
			};
		}
	};

	struct RGBColorPallete
	{
		// Base Colors
		static constexpr glm::vec3 Black = ColorUtilities::HEXtoFloats(0x000000);
		static constexpr glm::vec3 White = ColorUtilities::HEXtoFloats(0xFFFFFF);
		static constexpr glm::vec3 Red = ColorUtilities::HEXtoFloats(0xFF0000);
		static constexpr glm::vec3 Green = ColorUtilities::HEXtoFloats(0x00FF00);
		static constexpr glm::vec3 Blue = ColorUtilities::HEXtoFloats(0x0000FF);
		static constexpr glm::vec3 Yellow = ColorUtilities::HEXtoFloats(0xFFFF00);
		static constexpr glm::vec3 Cyan = ColorUtilities::HEXtoFloats(0x00FFFF);
		static constexpr glm::vec3 Magenta = ColorUtilities::HEXtoFloats(0xFF00FF);
		static constexpr glm::vec3 Silver = ColorUtilities::HEXtoFloats(0xC0C0C0);
		static constexpr glm::vec3 Gray = ColorUtilities::HEXtoFloats(0x808080);
		static constexpr glm::vec3 Maroon = ColorUtilities::HEXtoFloats(0x800000);
		static constexpr glm::vec3 Olive = ColorUtilities::HEXtoFloats(0x808000);
		static constexpr glm::vec3 Purple = ColorUtilities::HEXtoFloats(0x800080);
		static constexpr glm::vec3 Teal = ColorUtilities::HEXtoFloats(0x008080);
		static constexpr glm::vec3 Navy = ColorUtilities::HEXtoFloats(0x000080);
		static constexpr glm::vec3 Orange = ColorUtilities::HEXtoFloats(0xFFA500);
		static constexpr glm::vec3 Brown = ColorUtilities::HEXtoFloats(0xA52A2A);

		// Light Colors
		static constexpr glm::vec3 LightBlack = ColorUtilities::Lighten(Black);
		static constexpr glm::vec3 LightWhite = ColorUtilities::Lighten(White);
		static constexpr glm::vec3 LightRed = ColorUtilities::Lighten(Red);
		static constexpr glm::vec3 LightGreen = ColorUtilities::Lighten(Green);
		static constexpr glm::vec3 LightBlue = ColorUtilities::Lighten(Blue);
		static constexpr glm::vec3 LightYellow = ColorUtilities::Lighten(Yellow);
		static constexpr glm::vec3 LightCyan = ColorUtilities::Lighten(Cyan);
		static constexpr glm::vec3 LightMagenta = ColorUtilities::Lighten(Magenta);
		static constexpr glm::vec3 LightSilver = ColorUtilities::Lighten(Silver);
		static constexpr glm::vec3 LightGray = ColorUtilities::Lighten(Gray);
		static constexpr glm::vec3 LightMaroon = ColorUtilities::Lighten(Maroon);
		static constexpr glm::vec3 LightOlive = ColorUtilities::Lighten(Olive);
		static constexpr glm::vec3 LightPurple = ColorUtilities::Lighten(Purple);
		static constexpr glm::vec3 LightTeal = ColorUtilities::Lighten(Teal);
		static constexpr glm::vec3 LightNavy = ColorUtilities::Lighten(Navy);
		static constexpr glm::vec3 LightOrange = ColorUtilities::Lighten(Orange);
		static constexpr glm::vec3 LightBrown = ColorUtilities::Lighten(Brown);

		// Dark Colors
		static constexpr glm::vec3 DarkBlack = ColorUtilities::Darken(Black);
		static constexpr glm::vec3 DarkWhite = ColorUtilities::Darken(White);
		static constexpr glm::vec3 DarkRed = ColorUtilities::Darken(Red);
		static constexpr glm::vec3 DarkGreen = ColorUtilities::Darken(Green);
		static constexpr glm::vec3 DarkBlue = ColorUtilities::Darken(Blue);
		static constexpr glm::vec3 DarkYellow = ColorUtilities::Darken(Yellow);
		static constexpr glm::vec3 DarkCyan = ColorUtilities::Darken(Cyan);
		static constexpr glm::vec3 DarkMagenta = ColorUtilities::Darken(Magenta);
		static constexpr glm::vec3 DarkSilver = ColorUtilities::Darken(Silver);
		static constexpr glm::vec3 DarkGray = ColorUtilities::Darken(Gray);
		static constexpr glm::vec3 DarkMaroon = ColorUtilities::Darken(Maroon);
		static constexpr glm::vec3 DarkOlive = ColorUtilities::Darken(Olive);
		static constexpr glm::vec3 DarkPurple = ColorUtilities::Darken(Purple);
		static constexpr glm::vec3 DarkTeal = ColorUtilities::Darken(Teal);
		static constexpr glm::vec3 DarkNavy = ColorUtilities::Darken(Navy);
		static constexpr glm::vec3 DarkOrange = ColorUtilities::Darken(Orange);
		static constexpr glm::vec3 DarkBrown = ColorUtilities::Darken(Brown);
	};
}
