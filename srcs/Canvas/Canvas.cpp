#include "Canvas.hpp"
#include <cstring>

Canvas::Canvas(int width, int height) : _width(width), _height(height), _size(width * height) {
	this->_image = new int[height * width];
	bzero(this->_image, _size);
}

Canvas::~Canvas() {
	delete [] this->_image;
	this->_image = nullptr;
}

Canvas::Canvas(Canvas const &rhs) : _width(rhs._width), _height(rhs._height), _size(rhs._size) {
	this->_image = new int[_size];
	for (int i = 0; i < _size; i++)
		this->_image[i] = rhs._image[i];
}

Canvas	&Canvas::operator=(Canvas const &rhs) {
	if (this == &rhs)
		return (*this);
	if (_image)
		delete [] _image;
	this->_size = rhs._size;
	this->_width = rhs._width;
	this->_height = rhs._height;
	this->_image = new int[_size];
	for (int i = 0; i < _size; i++)
		this->_image[i] = rhs._image[i];
	return (*this);
}

Canvas::Canvas(Canvas &&rhs) noexcept{
	_size = rhs._size;
	_width = rhs._width;
	_height = rhs._height;
	_image = rhs._image;
	rhs._image = nullptr;
}

Canvas	&Canvas::operator=(Canvas &&rhs) noexcept {
	_size = rhs._size;
	_width = rhs._width;
	_height = rhs._height;
	_image = rhs._image;
	rhs._image = nullptr;
	return (*this);
}

int	Canvas::getHeight(void) const {
	return (this->_height);
}

int	Canvas::getWidth(void) const {
	return (this->_width);
}

int		Canvas::getPixel(int width, int height) const {
	return (_image[(height * _height) + width]);
}

void	Canvas::writePixel(int width, int height, Color color) {
	this->_image[(height * _height) + width] = ColorUtils::makeColor(color);
}
