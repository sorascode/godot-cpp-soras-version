/**************************************************************************/
/*  vector2i.cpp                                                          */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include <godot_cpp/variant/vector2i.hpp>

#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/vector2.hpp>

namespace godot {

real_t Vector2i::angle() const {
	return Math::atan2(y, x);
}

real_t Vector2i::angle_to_point(const Vector2i &p_vector2) const {
	return (p_vector2 - *this).angle();
}

int32_t Vector2i::dot(const Vector2i &p_other) const {
	return x * p_other.x + y * p_other.y;
}

int32_t Vector2i::cross(const Vector2i &p_other) const {
	return x * p_other.y - y * p_other.x;
}

bool Vector2i::is_equal(const Vector2i &p_v) const {
	return x == p_v.x && y == p_v.y;
}

bool Vector2i::is_zero() const {
	return x == 0 && y == 0;
}

void Vector2i::normalize() {
	int32_t l = x * x + y * y;
	if (l != 0) {
		l = Math::sqrt(l);
		x /= l;
		y /= l;
	}
}

Vector2i Vector2i::normalized() const {
	Vector2i v = *this;
	v.normalize();
	return v;
}


Vector2i Vector2i::snapped(const Vector2i &p_step) const {
	return Vector2i(
			Math::snapped(x, p_step.x),
			Math::snapped(y, p_step.y));
}

Vector2i Vector2i::snappedi(int32_t p_step) const {
	return Vector2i(
			Math::snapped(x, p_step),
			Math::snapped(y, p_step));
}

Vector2i Vector2i::clamp(const Vector2i &p_min, const Vector2i &p_max) const {
	return Vector2i(
			CLAMP(x, p_min.x, p_max.x),
			CLAMP(y, p_min.y, p_max.y));
}

Vector2i Vector2i::clampi(int32_t p_min, int32_t p_max) const {
	return Vector2i(
			CLAMP(x, p_min, p_max),
			CLAMP(y, p_min, p_max));
}

int64_t Vector2i::length_squared() const {
	return x * (int64_t)x + y * (int64_t)y;
}

double Vector2i::length() const {
	return Math::sqrt((double)length_squared());
}

int64_t Vector2i::distance_squared_to(const Vector2i &p_to) const {
	return (p_to - *this).length_squared();
}

double Vector2i::distance_to(const Vector2i &p_to) const {
	return (p_to - *this).length();
}

Vector2i Vector2i::operator+(const Vector2i &p_v) const {
	return Vector2i(x + p_v.x, y + p_v.y);
}

void Vector2i::operator+=(const Vector2i &p_v) {
	x += p_v.x;
	y += p_v.y;
}

Vector2i Vector2i::operator-(const Vector2i &p_v) const {
	return Vector2i(x - p_v.x, y - p_v.y);
}

void Vector2i::operator-=(const Vector2i &p_v) {
	x -= p_v.x;
	y -= p_v.y;
}

Vector2i Vector2i::operator*(const Vector2i &p_v1) const {
	return Vector2i(x * p_v1.x, y * p_v1.y);
}

Vector2i Vector2i::operator*(const int32_t &rvalue) const {
	return Vector2i(x * rvalue, y * rvalue);
}

void Vector2i::operator*=(const int32_t &rvalue) {
	x *= rvalue;
	y *= rvalue;
}

Vector2i Vector2i::operator/(const Vector2i &p_v1) const {
	return Vector2i(x / p_v1.x, y / p_v1.y);
}

Vector2i Vector2i::operator/(const int32_t &rvalue) const {
	return Vector2i(x / rvalue, y / rvalue);
}

void Vector2i::operator/=(const int32_t &rvalue) {
	x /= rvalue;
	y /= rvalue;
}

Vector2i Vector2i::operator%(const Vector2i &p_v1) const {
	return Vector2i(x % p_v1.x, y % p_v1.y);
}

Vector2i Vector2i::operator%(const int32_t &rvalue) const {
	return Vector2i(x % rvalue, y % rvalue);
}

void Vector2i::operator%=(const int32_t &rvalue) {
	x %= rvalue;
	y %= rvalue;
}

Vector2i Vector2i::operator-() const {
	return Vector2i(-x, -y);
}

bool Vector2i::operator==(const Vector2i &p_vec2) const {
	return x == p_vec2.x && y == p_vec2.y;
}

bool Vector2i::operator!=(const Vector2i &p_vec2) const {
	return x != p_vec2.x || y != p_vec2.y;
}

Vector2i::operator String() const {
	return "(" + itos(x) + ", " + itos(y) + ")";
}

Vector2i::operator Vector2() const {
	return Vector2((int32_t)x, (int32_t)y);
}

} // namespace godot
