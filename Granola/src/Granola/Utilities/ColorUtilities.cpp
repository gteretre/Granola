#include "grlpch.h"
#include "ColorUtilities.h"

namespace Granola
{
	glm::vec3 ColorUtilities::Hue(const glm::vec3 color)
	{
		const float max = std::max(color.x, std::max(color.y, color.z));
		const float min = std::min(color.x, std::min(color.y, color.z));
		const float delta = max - min;

		/*
		 * looks weird because of safe float comparison
		 * if delta is 0, then the color is grey
		 */

		if (std::fabs(delta) < std::numeric_limits<float>::epsilon())
			return {0.0f, 0.0f, max};
		if (std::fabs(max - color.x) < std::numeric_limits<float>::epsilon())
			return {60.0f * (fmodf(((color.y - color.z) / delta), 6.0f)), delta / max, max};
		if (std::fabs(max - color.y) < std::numeric_limits<float>::epsilon())
			return {60.0f * (((color.z - color.x) / delta) + 2.0f), delta / max, max};
		if (std::fabs(max - color.z) < std::numeric_limits<float>::epsilon())
			return {60.0f * (((color.x - color.y) / delta) + 4.0f), delta / max, max};

		return {0.0f, 0.0f, 0.0f};
	}

	glm::vec3 ColorUtilities::HueShift(glm::vec3 color, const float angle)
	{
		const float hue = Hue(color).x;
		const float hueShift = fmodf(hue + angle, 360.0f);
		const float saturation = Hue(color).y;
		const float value = Hue(color).z;

		const float chroma = saturation * value;
		const float huePrime = fmodf(hueShift / 60.0f, 6.0f);
		const float x = chroma * (1.0f - std::fabs(fmodf(huePrime, 2.0f) - 1.0f));
		const float m = value - chroma;

		if (huePrime >= 0.0f && huePrime < 1.0f)
			color = {chroma, x, 0.0f};
		else if (huePrime >= 1.0f && huePrime < 2.0f)
			color = {x, chroma, 0.0f};
		else if (huePrime >= 2.0f && huePrime < 3.0f)
			color = {0.0f, chroma, x};
		else if (huePrime >= 3.0f && huePrime < 4.0f)
			color = {0.0f, x, chroma};
		else if (huePrime >= 4.0f && huePrime < 5.0f)
			color = {x, 0.0f, chroma};
		else if (huePrime >= 5.0f && huePrime < 6.0f)
			color = {chroma, 0.0f, x};
		else
			color = {0.0f, 0.0f, 0.0f};

		return {color.x + m, color.y + m, color.z + m};
	}
}
