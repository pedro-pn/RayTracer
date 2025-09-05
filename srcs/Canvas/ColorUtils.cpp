#include "ColorUtils.hpp"
#include <cmath>

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

double	ColorUtils::rgbToColor(int color) {
	return ((double) color / (double) COLORMAX);
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

Color	ColorUtils::black(void) {
	return (color(0, 0, 0));
}

Color	ColorUtils::white(void) {
	return (color(1, 1, 1));
}

Color	ColorUtils::pixelColorToColor(int colorPixel) {
	double	red = rgbToColor(_getRed(colorPixel));
	double	green = rgbToColor(_getGreen(colorPixel));
	double	blue = rgbToColor(_getBlue(colorPixel));
	return (color(red, green, blue));
}
