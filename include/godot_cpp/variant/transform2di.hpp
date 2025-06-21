/**************************************************************************/
/*  transform2di.hpp                                                       */
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

#ifndef GODOT_TRANSFORM2DI_HPP
#define GODOT_TRANSFORM2DI_HPP

#include <godot_cpp/variant/packed_vector2i_array.hpp>
#include <godot_cpp/variant/rect2i.hpp>
#include <godot_cpp/variant/vector2i.hpp>

namespace godot {

class String;

struct [[nodiscard]] Transform2Di {
	// Warning #1: basis of Transform2D is stored differently from Basis. In terms of columns array, the basis matrix looks like "on paper":
	// M = (columns[0][0] columns[1][0])
	//     (columns[0][1] columns[1][1])
	// This is such that the columns, which can be interpreted as basis vectors of the coordinate system "painted" on the object, can be accessed as columns[i].
	// Note that this is the opposite of the indices in mathematical texts, meaning: $M_{12}$ in a math book corresponds to columns[1][0] here.
	// This requires additional care when working with explicit indices.
	// See https://en.wikipedia.org/wiki/Row-_and_column-major_order for further reading.

	// Warning #2: 2D be aware that unlike 3D code, 2D code uses a left-handed coordinate system: Y-axis points down,
	// and angle is measure from +X to +Y in a clockwise-fashion.

	Vector2i columns[3];

	_FORCE_INLINE_ int32_t tdotx(const Vector2i &v) const { return columns[0][0] * v.x + columns[1][0] * v.y; }
	_FORCE_INLINE_ int32_t tdoty(const Vector2i &v) const { return columns[0][1] * v.x + columns[1][1] * v.y; }

	const Vector2i &operator[](int p_idx) const { return columns[p_idx]; }
	Vector2i &operator[](int p_idx) { return columns[p_idx]; }

	void invert();
	Transform2Di inverse() const;

	void affine_invert();
	Transform2Di affine_inverse() const;

	void scale(const Size2i &p_scale);
	void scale_basis(const Size2i &p_scale);
	void translate_local(const int32_t p_tx, const int32_t p_ty);
	void translate_local(const Vector2i &p_translation);

	int32_t basis_determinant() const;

	Size2i get_scale() const;
	void set_scale(const Size2i &p_scale);

	_FORCE_INLINE_ const Vector2i &get_origin() const { return columns[2]; }
	_FORCE_INLINE_ void set_origin(const Vector2i &p_origin) { columns[2] = p_origin; }

	Transform2Di basis_scaled(const Size2i &p_scale) const;
	Transform2Di scaled(const Size2i &p_scale) const;
	Transform2Di scaled_local(const Size2i &p_scale) const;
	Transform2Di translated(const Vector2i &p_offset) const;
	Transform2Di translated_local(const Vector2i &p_offset) const;

	Transform2Di untranslated() const;

	void orthonormalize();
	Transform2Di orthonormalized() const;
	bool is_equal(const Transform2Di &p_transform) const;

	bool operator==(const Transform2Di &p_transform) const;
	bool operator!=(const Transform2Di &p_transform) const;

	void operator*=(const Transform2Di &p_transform);
	Transform2Di operator*(const Transform2Di &p_transform) const;
	void operator*=(const int32_t p_val);
	Transform2Di operator*(const int32_t p_val) const;

	Transform2Di interpolate_with(const Transform2Di &p_transform, const real_t p_c) const;

	_FORCE_INLINE_ Vector2i basis_xform(const Vector2i &p_vec) const;
	_FORCE_INLINE_ Vector2i basis_xform_inv(const Vector2i &p_vec) const;
	_FORCE_INLINE_ Vector2i xform(const Vector2i &p_vec) const;
	_FORCE_INLINE_ Vector2i xform_inv(const Vector2i &p_vec) const;
	_FORCE_INLINE_ Rect2i xform(const Rect2i &p_rect) const;
	_FORCE_INLINE_ Rect2i xform_inv(const Rect2i &p_rect) const;
	_FORCE_INLINE_ PackedVector2iArray xform(const PackedVector2iArray &p_array) const;
	_FORCE_INLINE_ PackedVector2iArray xform_inv(const PackedVector2iArray &p_array) const;

	operator String() const;

	Transform2Di(const int32_t xx, const int32_t xy, const int32_t yx, const int32_t yy, const int32_t ox, const int32_t oy) {
		columns[0][0] = xx;
		columns[0][1] = xy;
		columns[1][0] = yx;
		columns[1][1] = yy;
		columns[2][0] = ox;
		columns[2][1] = oy;
	}

	Transform2Di(const Vector2i &p_x, const Vector2i &p_y, const Vector2i &p_origin) {
		columns[0] = p_x;
		columns[1] = p_y;
		columns[2] = p_origin;
	}

	Transform2Di(const Vector2i &p_pos);

	Transform2Di(const Size2i &p_scale, const Vector2i &p_pos);

	Transform2Di() {
		columns[0][0] = 1;
		columns[1][1] = 1;
	}
};

Vector2i Transform2Di::basis_xform(const Vector2i &p_vec) const {
	return Vector2i(
			tdotx(p_vec),
			tdoty(p_vec));
}

Vector2i Transform2Di::basis_xform_inv(const Vector2i &p_vec) const {
	return Vector2i(
			columns[0].dot(p_vec),
			columns[1].dot(p_vec));
}

Vector2i Transform2Di::xform(const Vector2i &p_vec) const {
	return Vector2i(
				   tdotx(p_vec),
				   tdoty(p_vec)) +
			columns[2];
}

Vector2i Transform2Di::xform_inv(const Vector2i &p_vec) const {
	Vector2i v = p_vec - columns[2];

	return Vector2i(
			columns[0].dot(v),
			columns[1].dot(v));
}

Rect2i Transform2Di::xform(const Rect2i &p_rect) const {
	Vector2i x = columns[0] * p_rect.size.x;
	Vector2i y = columns[1] * p_rect.size.y;
	Vector2i pos = xform(p_rect.position);

	Rect2i new_rect;
	new_rect.position = pos;
	new_rect.expand_to(pos + x);
	new_rect.expand_to(pos + y);
	new_rect.expand_to(pos + x + y);
	return new_rect;
}

Rect2i Transform2Di::xform_inv(const Rect2i &p_rect) const {
	Vector2i ends[4] = {
		xform_inv(p_rect.position),
		xform_inv(Vector2i(p_rect.position.x, p_rect.position.y + p_rect.size.y)),
		xform_inv(Vector2i(p_rect.position.x + p_rect.size.x, p_rect.position.y + p_rect.size.y)),
		xform_inv(Vector2i(p_rect.position.x + p_rect.size.x, p_rect.position.y))
	};

	Rect2i new_rect;
	new_rect.position = ends[0];
	new_rect.expand_to(ends[1]);
	new_rect.expand_to(ends[2]);
	new_rect.expand_to(ends[3]);

	return new_rect;
}

PackedVector2iArray Transform2Di::xform(const PackedVector2iArray &p_array) const {
	PackedVector2iArray array;
	array.resize(p_array.size());

	const Vector2i *r = p_array.ptr();
	Vector2i *w = array.ptrw();

	for (int i = 0; i < p_array.size(); ++i) {
		w[i] = xform(r[i]);
	}
	return array;
}

PackedVector2iArray Transform2Di::xform_inv(const PackedVector2iArray &p_array) const {
	PackedVector2iArray array;
	array.resize(p_array.size());

	const Vector2i *r = p_array.ptr();
	Vector2i *w = array.ptrw();

	for (int i = 0; i < p_array.size(); ++i) {
		w[i] = xform_inv(r[i]);
	}
	return array;
}

} // namespace godot

#endif // GODOT_TRANSFORM2DI_HPP
