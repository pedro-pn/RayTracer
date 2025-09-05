#pragma once

#include <UnitTest++/UnitTest++.h>
#include "TestUtils.hpp"
#include "Canvas.hpp"
#include <fstream>

#define PPMFILE "P3\n5 3\n255\n255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n\
0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n"

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

	TEST(SAVING_PPM_TEST) {
		Canvas c(5, 3);

		Color	c1 = color(1.5, 0, 0);
		Color	c2 = color(0, 0.5, 0);
		Color	c3 = color(-0.5, 0, 1);

		c.writePixel(0, 0, c1);
		c.writePixel(2, 1, c2);
		c.writePixel(4, 2, c3);

		c.saveToPPM("teste.ppm");
		fstream	file;

		file.open("teste.ppm");
		stringstream	buffer;
		string			line;
		while (getline(file, line)){
			buffer << line << "\n";
		}
		CHECK(buffer.str() == PPMFILE);
	}
}
