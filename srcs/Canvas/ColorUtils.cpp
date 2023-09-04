#include "ColorUtils.hpp"
#include <cmath>

ColorUtils::ColorUtils() {
}

ColorUtils::~ColorUtils() {
}

int	ColorUtils::makeColor(Color color) {
	int red;
	int	green;
	int blue;

	red = _ColorToRgb(color.x);
	green = _ColorToRgb(color.y);
	blue = _ColorToRgb(color.z);
	return (red << 16 | green << 8 | blue);
}

int	ColorUtils::_ColorToRgb(double color) {
	if (color < 0)
		return (COLORMIN);
	else if (color > 1)
		return (COLORMAX);
	return (ceil(color * COLORMAX));
}

int	ColorUtils::_getRed(int color) {
	return ((color >> 16) & 0xFF);
}

int	ColorUtils::_getGreen(int color) {
	return ((color >> 8) & 0xFF);
}

int	ColorUtils::_getBlue(int color) {
	return (color & 0xFF);
}
