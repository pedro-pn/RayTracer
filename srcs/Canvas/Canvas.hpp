#ifndef CANVAS_HPP
# define CANVAS_HPP

# include <iostream>
# include "algebra.h"

using namespace std;

# include "ColorUtils.hpp"

class Canvas {

	public:

		Canvas(int width, int height);
		Canvas(Canvas const &rhs);
		Canvas(Canvas &&rhs) noexcept;
		~Canvas();

		Canvas	&operator=(Canvas const &rhs);
		Canvas	&operator=(Canvas &&rhs) noexcept;

		int		getWidth(void) const;
		int		getHeight(void) const;

		int		getPixel(int width, int height) const;
		void	writePixel(int width, int height, Color color);

	private:

		int	*_image;
		int	_width;
		int	_height;
		int	_size;

};

#endif /* CANVAS_HPP */
