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
	};
}
