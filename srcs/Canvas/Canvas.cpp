#include "Canvas.hpp"
#include <cstring>
#include <fstream>
#include <sstream>

Canvas::Canvas(int width, int height) : _width(width), _height(height), _size(width * height) {
	this->_image = new int[height * width];
	bzero(this->_image, _size * sizeof(int));
}

Canvas::~Canvas() {
	delete [] this->_image;
	this->_image = nullptr;
}

Canvas::Canvas(Canvas const &rhs) : _width(rhs._width), _height(rhs._height), _size(rhs._size) {
	this->_image = new int[_size * sizeof(int)];
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
	this->_image = new int[_size * sizeof(int)];
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

void	Canvas::saveToPPM(string const &fileName) {
	fstream		file;
	std::string	fileContent;

	file.open(fileName, ios::out);
	if (file.fail())
		throw runtime_error("Cannot create file '" + fileName + "'");
	fileContent = _makePPMBuffer();
	file.write(fileContent.c_str(), fileContent.size());
	file.close();
}

string	Canvas::_makePPMBuffer(void) {
	stringstream	buffer;
	int				red, green, blue;

	_makePPMHeader(buffer);
	for (int y = 0; y < _height; y++) {
		for(int x = 0; x < _width; x++) {
			red = ColorUtils::_getRed(getPixel(x, y));
			green = ColorUtils::_getGreen(getPixel(x, y));
			blue = ColorUtils::_getBlue(getPixel(x, y));
			buffer << red << " " << green << " " << blue;
			if (x != _width - 1)
				buffer << " ";
		}
		buffer << "\n";
	}
	return (move(buffer.str()));
}

void	Canvas::_makePPMHeader(stringstream &buffer) {
	buffer << "P3\n" << _width << " " << _height << "\n" << 255 << "\n";
}
