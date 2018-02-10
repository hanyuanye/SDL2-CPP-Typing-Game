#ifndef VEC2D_H
#define VEC2D_H

#pragma once
#include <vector>

class Vec2d
{
private:
	double x;
	double y;

public:
	Vec2d();
	Vec2d(double _x, double _y);
	Vec2d(const Vec2d& v);

	Vec2d operator=(const Vec2d&);
	Vec2d operator+(const Vec2d&) const;
	Vec2d operator+=(const Vec2d&);
	Vec2d operator-(const Vec2d&) const;
	Vec2d operator-=(const Vec2d&);
	Vec2d scalarMultiple(const double &_scalar) const;

	double dotProduct(const Vec2d&) const;
	double crossProduct(const Vec2d&) const;

	double get_x() const;
	double get_y() const;

	void set_x(const double &_x);
	void set_y(const double &_y);
	void set_vector(const double  &_x, const double  &_y);


};

#endif