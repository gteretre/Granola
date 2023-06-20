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


		//---------------------------------------------------------------------------------------------
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

		static constexpr float Luminance(const glm::vec3 color)
		{
			return (0.2126f * color.x) + (0.7152f * color.y) + (0.0722f * color.z);
		}

		static constexpr float Contrast(const glm::vec3 color1, const glm::vec3 color2)
		{
			return (Luminance(color1) + 0.05f) / (Luminance(color2) + 0.05f);
		}

		static constexpr float Brightness(const glm::vec3 color)
		{
			return (Luminance(color) + 0.05f) / 0.05f;
		}

		static constexpr float Saturation(const glm::vec3 color)
		{
			const float max = std::max(color.x, std::max(color.y, color.z));
			const float min = std::min(color.x, std::min(color.y, color.z));
			return (max - min) / max;
		}

		static constexpr glm::vec3 Tint(const glm::vec3 color, const glm::vec3 tint)
		{
			return {color.x * tint.x, color.y * tint.y, color.z * tint.z};
		}

		static glm::vec3 Hue(glm::vec3 color);
		static glm::vec3 HueShift(glm::vec3 color, float angle);
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
		static constexpr glm::vec3 Pink = ColorUtilities::HEXtoFloats(0xFFC0CB);
		static constexpr glm::vec3 Violet = ColorUtilities::HEXtoFloats(0xEE82EE);
		static constexpr glm::vec3 Lime = ColorUtilities::HEXtoFloats(0x00FF00);

		static constexpr glm::vec3 Aqua = ColorUtilities::HEXtoFloats(0x00FFFF);
		static constexpr glm::vec3 Turquoise = ColorUtilities::HEXtoFloats(0x40E0D0);
		static constexpr glm::vec3 Indigo = ColorUtilities::HEXtoFloats(0x4B0082);
		static constexpr glm::vec3 Lavender = ColorUtilities::HEXtoFloats(0xE6E6FA);
		static constexpr glm::vec3 Beige = ColorUtilities::HEXtoFloats(0xF5F5DC);

		static constexpr glm::vec3 Gold = ColorUtilities::HEXtoFloats(0xFFD700);
		static constexpr glm::vec3 Azure = ColorUtilities::HEXtoFloats(0xF0FFFF);
		static constexpr glm::vec3 Mint = ColorUtilities::HEXtoFloats(0x3EB489);
		static constexpr glm::vec3 OliveGreen = ColorUtilities::HEXtoFloats(0x6B8E23);
		static constexpr glm::vec3 Peach = ColorUtilities::HEXtoFloats(0xFFDAB9);

		static constexpr glm::vec3 Salmon = ColorUtilities::HEXtoFloats(0xFA8072);
		static constexpr glm::vec3 Tan = ColorUtilities::HEXtoFloats(0xD2B48C);
	};
}
