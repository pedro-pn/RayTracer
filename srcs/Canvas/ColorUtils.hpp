#ifndef COLORUTILS_HPP
# define COLORUTILS_HPP

# include "Algebra.hpp"

# define COLORMAX 255
# define COLORMIN 0

namespace ColorUtils {

	int		makeColor(Color tcolor);
	
	int		_getRed(int color);
	int		_getGreen(int color);
	int		_getBlue(int color);
	int		_ColorToRgb(double color);
	double	rgbToColor(int color);
	Color	black(void);
	Color	white(void);	
	Color	pixelColorToColor(int color);
}

#endif /* COLORUTILS_HPP */
