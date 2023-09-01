#ifndef COLORUTILS_HPP
# define COLORUTILS_HPP

# include "algebra.h"

# define COLORMAX 255
# define COLORMIN 0

class ColorUtils {

	public:

		~ColorUtils();

		static int	makeColor(Color tcolor);

	private:

		ColorUtils();

		static int	_getRed(int color);
		static int	_getGreen(int color);
		static int	_getBlue(int color);
		static int	_ColorToRgb(int color);
};

#endif /* COLORUTILS_HPP */
