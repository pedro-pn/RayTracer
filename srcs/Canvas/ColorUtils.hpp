#ifndef COLORUTILS_HPP
# define COLORUTILS_HPP

# include "algebra.h"

# define COLORMAX 255
# define COLORMIN 0

class ColorUtils {

	public:

		~ColorUtils();

		static int	makeColor(Color tcolor);

		static int	_getRed(int color);
		static int	_getGreen(int color);
		static int	_getBlue(int color);
		static int	_ColorToRgb(double color);

	private:

		ColorUtils();
};

#endif /* COLORUTILS_HPP */
