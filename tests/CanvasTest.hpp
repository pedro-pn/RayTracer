#ifndef CANVASTEST_HPP
# define CANVASTEST_HPP

# include <UnitTest++/UnitTest++.h>
# include "TestUtils.hpp"
# include "Canvas.hpp"

SUITE(CANVAS) {

	TEST(CREATING_CAVAS) {
		Canvas	c(10, 20);

		CHECK_EQUAL(10, c.getWidth());
		CHECK_EQUAL(20, c.getHeight());
	}

	TEST(WRITING_PIXEL_TEST) {
		Canvas	c(10, 20);

		Color	red = color(1, 0, 0);
		Color	green = color(0, 1, 0);
		Color	blue = color(0, 0, 1);

		c.writePixel(2, 3, red);
		c.writePixel(4, 5, green);
		c.writePixel(1, 9, blue);

		CHECK_EQUAL(255 << 16, c.getPixel(2, 3));
		CHECK_EQUAL(255 << 8, c.getPixel(4, 5));
		CHECK_EQUAL(255, c.getPixel(1, 9));
	}
}

#endif /* CANVASTEST_HPP */
