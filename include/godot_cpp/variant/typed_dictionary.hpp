/**************************************************************************/
/*  typed_dictionary.hpp                                                  */
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

#ifndef GODOT_TYPED_DICTIONARY_HPP
#define GODOT_TYPED_DICTIONARY_HPP

#include <godot_cpp/core/type_info.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/variant.hpp>

namespace godot {

template <typename K, typename V>
class TypedDictionary : public Dictionary {
public:
	_FORCE_INLINE_ void operator=(const Dictionary &p_dictionary) {
		ERR_FAIL_COND_MSG(!is_same_typed(p_dictionary), "Cannot assign a dictionary with a different element type.");
		Dictionary::operator=(p_dictionary);
	}
	_FORCE_INLINE_ TypedDictionary(const Variant &p_variant) :
			TypedDictionary(Dictionary(p_variant)) {
	}
	_FORCE_INLINE_ TypedDictionary(const Dictionary &p_dictionary) {
		set_typed(Variant::OBJECT, K::get_class_static(), Variant(), Variant::OBJECT, V::get_class_static(), Variant());
		if (is_same_typed(p_dictionary)) {
			Dictionary::operator=(p_dictionary);
		} else {
			assign(p_dictionary);
		}
	}
	_FORCE_INLINE_ TypedDictionary() {
		set_typed(Variant::OBJECT, K::get_class_static(), Variant(), Variant::OBJECT, V::get_class_static(), Variant());
	}
};

//specialization for the rest of variant types

#define MAKE_TYPED_DICTIONARY_WITH_OBJECT(m_type, m_variant_type)                                                          \
	template <typename T>                                                                                                  \
	class TypedDictionary<T, m_type> : public Dictionary {                                                                 \
	public:                                                                                                                \
		_FORCE_INLINE_ void operator=(const Dictionary &p_dictionary) {                                                    \
			ERR_FAIL_COND_MSG(!is_same_typed(p_dictionary), "Cannot assign an dictionary with a different element type."); \
			Dictionary::operator=(p_dictionary);                                                                           \
		}                                                                                                                  \
		_FORCE_INLINE_ TypedDictionary(const Variant &p_variant) :                                                         \
				TypedDictionary(Dictionary(p_variant)) {                                                                   \
		}                                                                                                                  \
		_FORCE_INLINE_ TypedDictionary(const Dictionary &p_dictionary) {                                                   \
			set_typed(Variant::OBJECT, T::get_class_static(), Variant(), m_variant_type, StringName(), Variant());         \
			if (is_same_typed(p_dictionary)) {                                                                             \
				Dictionary::operator=(p_dictionary);                                                                       \
			} else {                                                                                                       \
				assign(p_dictionary);                                                                                      \
			}                                                                                                              \
		}                                                                                                                  \
		_FORCE_INLINE_ TypedDictionary() {                                                                                 \
			set_typed(Variant::OBJECT, T::get_class_static(), Variant(), m_variant_type, StringName(), Variant());         \
		}                                                                                                                  \
	};                                                                                                                     \
	template <typename T>                                                                                                  \
	class TypedDictionary<m_type, T> : public Dictionary {                                                                 \
	public:                                                                                                                \
		_FORCE_INLINE_ void operator=(const Dictionary &p_dictionary) {                                                    \
			ERR_FAIL_COND_MSG(!is_same_typed(p_dictionary), "Cannot assign an dictionary with a different element type."); \
			Dictionary::operator=(p_dictionary);                                                                           \
		}                                                                                                                  \
		_FORCE_INLINE_ TypedDictionary(const Variant &p_variant) :                                                         \
				TypedDictionary(Dictionary(p_variant)) {                                                                   \
		}                                                                                                                  \
		_FORCE_INLINE_ TypedDictionary(const Dictionary &p_dictionary) {                                                   \
			set_typed(m_variant_type, StringName(), Variant(), Variant::OBJECT, T::get_class_static(), Variant());         \
			if (is_same_typed(p_dictionary)) {                                                                             \
				Dictionary::operator=(p_dictionary);                                                                       \
			} else {                                                                                                       \
				assign(p_dictionary);                                                                                      \
			}                                                                                                              \
		}                                                                                                                  \
		_FORCE_INLINE_ TypedDictionary() {                                                                                 \
			set_typed(m_variant_type, StringName(), Variant(), Variant::OBJECT, T::get_class_static(), Variant());         \
		}                                                                                                                  \
	};

#define MAKE_TYPED_DICTIONARY_EXPANDED(m_type_key, m_variant_type_key, m_type_value, m_variant_type_value)                 \
	template <>                                                                                                            \
	class TypedDictionary<m_type_key, m_type_value> : public Dictionary {                                                  \
	public:                                                                                                                \
		_FORCE_INLINE_ void operator=(const Dictionary &p_dictionary) {                                                    \
			ERR_FAIL_COND_MSG(!is_same_typed(p_dictionary), "Cannot assign an dictionary with a different element type."); \
			Dictionary::operator=(p_dictionary);                                                                           \
		}                                                                                                                  \
		_FORCE_INLINE_ TypedDictionary(const Variant &p_variant) :                                                         \
				TypedDictionary(Dictionary(p_variant)) {                                                                   \
		}                                                                                                                  \
		_FORCE_INLINE_ TypedDictionary(const Dictionary &p_dictionary) {                                                   \
			set_typed(m_variant_type_key, StringName(), Variant(), m_variant_type_value, StringName(), Variant());         \
			if (is_same_typed(p_dictionary)) {                                                                             \
				Dictionary::operator=(p_dictionary);                                                                       \
			} else {                                                                                                       \
				assign(p_dictionary);                                                                                      \
			}                                                                                                              \
		}                                                                                                                  \
		_FORCE_INLINE_ TypedDictionary() {                                                                                 \
			set_typed(m_variant_type_key, StringName(), Variant(), m_variant_type_value, StringName(), Variant());         \
		}                                                                                                                  \
	};

#define MAKE_TYPED_DICTIONARY_NIL(m_type, m_variant_type)                                                     \
	MAKE_TYPED_DICTIONARY_WITH_OBJECT(m_type, m_variant_type)                                                 \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, bool, Variant::BOOL)                               \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, uint8_t, Variant::INT)                             \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, int8_t, Variant::INT)                              \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, uint16_t, Variant::INT)                            \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, int16_t, Variant::INT)                             \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, uint32_t, Variant::INT)                            \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, int32_t, Variant::INT)                             \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, uint64_t, Variant::INT)                            \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, int64_t, Variant::INT)                             \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, float, Variant::FLOAT)                             \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, double, Variant::FLOAT)                            \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, String, Variant::STRING)                           \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Vector2, Variant::VECTOR2)                         \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Vector2i, Variant::VECTOR2I)                       \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Rect2, Variant::RECT2)                             \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Rect2i, Variant::RECT2I)                           \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Vector3, Variant::VECTOR3)                         \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Vector3i, Variant::VECTOR3I)                       \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Transform2D, Variant::TRANSFORM2D)                 \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Transform2Di, Variant::TRANSFORM2DI)               \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Plane, Variant::PLANE)                             \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Quaternion, Variant::QUATERNION)                   \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, AABB, Variant::AABB)                               \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Basis, Variant::BASIS)                             \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Transform3D, Variant::TRANSFORM3D)                 \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Color, Variant::COLOR)                             \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, StringName, Variant::STRING_NAME)                  \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, NodePath, Variant::NODE_PATH)                      \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, RID, Variant::RID)                                 \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Callable, Variant::CALLABLE)                       \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Signal, Variant::SIGNAL)                           \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Dictionary, Variant::DICTIONARY)                   \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Array, Variant::ARRAY)                             \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, PackedByteArray, Variant::PACKED_BYTE_ARRAY)       \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, PackedInt32Array, Variant::PACKED_INT32_ARRAY)     \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, PackedInt64Array, Variant::PACKED_INT64_ARRAY)     \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, PackedFloat32Array, Variant::PACKED_FLOAT32_ARRAY) \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, PackedFloat64Array, Variant::PACKED_FLOAT64_ARRAY) \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, PackedStringArray, Variant::PACKED_STRING_ARRAY)   \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, PackedVector2Array, Variant::PACKED_VECTOR2_ARRAY) \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, PackedVector2iArray, Variant::PACKED_VECTOR2I_ARRAY) \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, PackedVector3Array, Variant::PACKED_VECTOR3_ARRAY) \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, PackedColorArray, Variant::PACKED_COLOR_ARRAY)     \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, PackedVector4Array, Variant::PACKED_VECTOR4_ARRAY) \
	/*MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, IPAddress, Variant::STRING)*/

#define MAKE_TYPED_DICTIONARY(m_type, m_variant_type)                             \
	MAKE_TYPED_DICTIONARY_EXPANDED(m_type, m_variant_type, Variant, Variant::NIL) \
	MAKE_TYPED_DICTIONARY_NIL(m_type, m_variant_type)

MAKE_TYPED_DICTIONARY_NIL(Variant, Variant::NIL)
MAKE_TYPED_DICTIONARY(bool, Variant::BOOL)
MAKE_TYPED_DICTIONARY(uint8_t, Variant::INT)
MAKE_TYPED_DICTIONARY(int8_t, Variant::INT)
MAKE_TYPED_DICTIONARY(uint16_t, Variant::INT)
MAKE_TYPED_DICTIONARY(int16_t, Variant::INT)
MAKE_TYPED_DICTIONARY(uint32_t, Variant::INT)
MAKE_TYPED_DICTIONARY(int32_t, Variant::INT)
MAKE_TYPED_DICTIONARY(uint64_t, Variant::INT)
MAKE_TYPED_DICTIONARY(int64_t, Variant::INT)
MAKE_TYPED_DICTIONARY(float, Variant::FLOAT)
MAKE_TYPED_DICTIONARY(double, Variant::FLOAT)
MAKE_TYPED_DICTIONARY(String, Variant::STRING)
MAKE_TYPED_DICTIONARY(Vector2, Variant::VECTOR2)
MAKE_TYPED_DICTIONARY(Vector2i, Variant::VECTOR2I)
MAKE_TYPED_DICTIONARY(Rect2, Variant::RECT2)
MAKE_TYPED_DICTIONARY(Rect2i, Variant::RECT2I)
MAKE_TYPED_DICTIONARY(Vector3, Variant::VECTOR3)
MAKE_TYPED_DICTIONARY(Vector3i, Variant::VECTOR3I)
MAKE_TYPED_DICTIONARY(Transform2D, Variant::TRANSFORM2D)
MAKE_TYPED_DICTIONARY(Transform2Di, Variant::TRANSFORM2DI)
MAKE_TYPED_DICTIONARY(Plane, Variant::PLANE)
MAKE_TYPED_DICTIONARY(Quaternion, Variant::QUATERNION)
MAKE_TYPED_DICTIONARY(AABB, Variant::AABB)
MAKE_TYPED_DICTIONARY(Basis, Variant::BASIS)
MAKE_TYPED_DICTIONARY(Transform3D, Variant::TRANSFORM3D)
MAKE_TYPED_DICTIONARY(Color, Variant::COLOR)
MAKE_TYPED_DICTIONARY(StringName, Variant::STRING_NAME)
MAKE_TYPED_DICTIONARY(NodePath, Variant::NODE_PATH)
MAKE_TYPED_DICTIONARY(RID, Variant::RID)
MAKE_TYPED_DICTIONARY(Callable, Variant::CALLABLE)
MAKE_TYPED_DICTIONARY(Signal, Variant::SIGNAL)
MAKE_TYPED_DICTIONARY(Dictionary, Variant::DICTIONARY)
MAKE_TYPED_DICTIONARY(Array, Variant::ARRAY)
MAKE_TYPED_DICTIONARY(PackedByteArray, Variant::PACKED_BYTE_ARRAY)
MAKE_TYPED_DICTIONARY(PackedInt32Array, Variant::PACKED_INT32_ARRAY)
MAKE_TYPED_DICTIONARY(PackedInt64Array, Variant::PACKED_INT64_ARRAY)
MAKE_TYPED_DICTIONARY(PackedFloat32Array, Variant::PACKED_FLOAT32_ARRAY)
MAKE_TYPED_DICTIONARY(PackedFloat64Array, Variant::PACKED_FLOAT64_ARRAY)
MAKE_TYPED_DICTIONARY(PackedStringArray, Variant::PACKED_STRING_ARRAY)
MAKE_TYPED_DICTIONARY(PackedVector2Array, Variant::PACKED_VECTOR2_ARRAY)
MAKE_TYPED_DICTIONARY(PackedVector2iArray, Variant::PACKED_VECTOR2I_ARRAY)
MAKE_TYPED_DICTIONARY(PackedVector3Array, Variant::PACKED_VECTOR3_ARRAY)
MAKE_TYPED_DICTIONARY(PackedColorArray, Variant::PACKED_COLOR_ARRAY)
MAKE_TYPED_DICTIONARY(PackedVector4Array, Variant::PACKED_VECTOR4_ARRAY)
/*
MAKE_TYPED_DICTIONARY(IPAddress, Variant::STRING)
*/

#undef MAKE_TYPED_DICTIONARY
#undef MAKE_TYPED_DICTIONARY_NIL
#undef MAKE_TYPED_DICTIONARY_EXPANDED
#undef MAKE_TYPED_DICTIONARY_WITH_OBJECT

template <typename K, typename V>
struct PtrToArg<TypedDictionary<K, V>> {
	_FORCE_INLINE_ static TypedDictionary<K, V> convert(const void *p_ptr) {
		return TypedDictionary<K, V>(*reinterpret_cast<const Dictionary *>(p_ptr));
	}
	typedef Dictionary EncodeT;
	_FORCE_INLINE_ static void encode(TypedDictionary<K, V> p_val, void *p_ptr) {
		*(Dictionary *)p_ptr = p_val;
	}
};

template <typename K, typename V>
struct PtrToArg<const TypedDictionary<K, V> &> {
	typedef Dictionary EncodeT;
	_FORCE_INLINE_ static TypedDictionary<K, V>
	convert(const void *p_ptr) {
		return TypedDictionary<K, V>(*reinterpret_cast<const Dictionary *>(p_ptr));
	}
};

template <typename K, typename V>
struct GetTypeInfo<TypedDictionary<K, V>> {
	static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_DICTIONARY;
	static constexpr GDExtensionClassMethodArgumentMetadata METADATA = GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;
	static inline PropertyInfo get_class_info() {
		return PropertyInfo(Variant::Type::DICTIONARY, String(), PROPERTY_HINT_DICTIONARY_TYPE, vformat("%s;%s", K::get_class_static(), V::get_class_static()));
	}
};

template <typename K, typename V>
struct GetTypeInfo<const TypedDictionary<K, V> &> {
	static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_DICTIONARY;
	static constexpr GDExtensionClassMethodArgumentMetadata METADATA = GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;
	static inline PropertyInfo get_class_info() {
		return PropertyInfo(Variant::Type::DICTIONARY, String(), PROPERTY_HINT_DICTIONARY_TYPE, vformat("%s;%s", K::get_class_static(), V::get_class_static()));
	}
};

#define MAKE_TYPED_DICTIONARY_INFO_WITH_OBJECT(m_type, m_variant_type)                                                                                                     \
	template <typename T>                                                                                                                                                  \
	struct GetTypeInfo<TypedDictionary<T, m_type>> {                                                                                                                       \
		static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_DICTIONARY;                                                                        \
		static constexpr GDExtensionClassMethodArgumentMetadata METADATA = GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;                                                      \
		static inline PropertyInfo get_class_info() {                                                                                                                      \
			return PropertyInfo(Variant::Type::DICTIONARY, String(), PROPERTY_HINT_DICTIONARY_TYPE,                                                                        \
					vformat("%s;%s", T::get_class_static(), m_variant_type == Variant::Type::NIL ? "Variant" : Variant::get_type_name(m_variant_type).utf8().get_data())); \
		}                                                                                                                                                                  \
	};                                                                                                                                                                     \
	template <typename T>                                                                                                                                                  \
	struct GetTypeInfo<const TypedDictionary<T, m_type> &> {                                                                                                               \
		static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_DICTIONARY;                                                                        \
		static constexpr GDExtensionClassMethodArgumentMetadata METADATA = GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;                                                      \
		static inline PropertyInfo get_class_info() {                                                                                                                      \
			return PropertyInfo(Variant::Type::DICTIONARY, String(), PROPERTY_HINT_DICTIONARY_TYPE,                                                                        \
					vformat("%s;%s", T::get_class_static(), m_variant_type == Variant::Type::NIL ? "Variant" : Variant::get_type_name(m_variant_type).utf8().get_data())); \
		}                                                                                                                                                                  \
	};                                                                                                                                                                     \
	template <typename T>                                                                                                                                                  \
	struct GetTypeInfo<TypedDictionary<m_type, T>> {                                                                                                                       \
		static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_DICTIONARY;                                                                        \
		static constexpr GDExtensionClassMethodArgumentMetadata METADATA = GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;                                                      \
		static inline PropertyInfo get_class_info() {                                                                                                                      \
			return PropertyInfo(Variant::Type::DICTIONARY, String(), PROPERTY_HINT_DICTIONARY_TYPE,                                                                        \
					vformat("%s;%s", m_variant_type == Variant::Type::NIL ? "Variant" : Variant::get_type_name(m_variant_type).utf8().get_data(), T::get_class_static())); \
		}                                                                                                                                                                  \
	};                                                                                                                                                                     \
	template <typename T>                                                                                                                                                  \
	struct GetTypeInfo<const TypedDictionary<m_type, T> &> {                                                                                                               \
		static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_DICTIONARY;                                                                        \
		static constexpr GDExtensionClassMethodArgumentMetadata METADATA = GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;                                                      \
		static inline PropertyInfo get_class_info() {                                                                                                                      \
			return PropertyInfo(Variant::Type::DICTIONARY, String(), PROPERTY_HINT_DICTIONARY_TYPE,                                                                        \
					vformat("%s;%s", m_variant_type == Variant::Type::NIL ? "Variant" : Variant::get_type_name(m_variant_type).utf8().get_data(), T::get_class_static())); \
		}                                                                                                                                                                  \
	};

#define MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type_key, m_variant_type_key, m_type_value, m_variant_type_value)                                           \
	template <>                                                                                                                                           \
	struct GetTypeInfo<TypedDictionary<m_type_key, m_type_value>> {                                                                                       \
		static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_DICTIONARY;                                                       \
		static constexpr GDExtensionClassMethodArgumentMetadata METADATA = GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;                                     \
		static inline PropertyInfo get_class_info() {                                                                                                     \
			return PropertyInfo(Variant::Type::DICTIONARY, String(), PROPERTY_HINT_DICTIONARY_TYPE,                                                       \
					vformat("%s;%s", m_variant_type_key == Variant::Type::NIL ? "Variant" : Variant::get_type_name(m_variant_type_key).utf8().get_data(), \
							m_variant_type_value == Variant::Type::NIL ? "Variant" : Variant::get_type_name(m_variant_type_value).utf8().get_data()));    \
		}                                                                                                                                                 \
	};                                                                                                                                                    \
	template <>                                                                                                                                           \
	struct GetTypeInfo<const TypedDictionary<m_type_key, m_type_value> &> {                                                                               \
		static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_DICTIONARY;                                                       \
		static constexpr GDExtensionClassMethodArgumentMetadata METADATA = GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;                                     \
		static inline PropertyInfo get_class_info() {                                                                                                     \
			return PropertyInfo(Variant::Type::DICTIONARY, String(), PROPERTY_HINT_DICTIONARY_TYPE,                                                       \
					vformat("%s;%s", m_variant_type_key == Variant::Type::NIL ? "Variant" : Variant::get_type_name(m_variant_type_key).utf8().get_data(), \
							m_variant_type_value == Variant::Type::NIL ? "Variant" : Variant::get_type_name(m_variant_type_value).utf8().get_data()));    \
		}                                                                                                                                                 \
	};

#define MAKE_TYPED_DICTIONARY_INFO_NIL(m_type, m_variant_type)                                                     \
	MAKE_TYPED_DICTIONARY_INFO_WITH_OBJECT(m_type, m_variant_type)                                                 \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, bool, Variant::BOOL)                               \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, uint8_t, Variant::INT)                             \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, int8_t, Variant::INT)                              \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, uint16_t, Variant::INT)                            \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, int16_t, Variant::INT)                             \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, uint32_t, Variant::INT)                            \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, int32_t, Variant::INT)                             \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, uint64_t, Variant::INT)                            \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, int64_t, Variant::INT)                             \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, float, Variant::FLOAT)                             \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, double, Variant::FLOAT)                            \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, String, Variant::STRING)                           \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, Vector2, Variant::VECTOR2)                         \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, Vector2i, Variant::VECTOR2I)                       \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, Rect2, Variant::RECT2)                             \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, Rect2i, Variant::RECT2I)                           \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, Vector3, Variant::VECTOR3)                         \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, Vector3i, Variant::VECTOR3I)                       \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, Transform2D, Variant::TRANSFORM2D)                 \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, Transform2Di, Variant::TRANSFORM2DI)               \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, Plane, Variant::PLANE)                             \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, Quaternion, Variant::QUATERNION)                   \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, AABB, Variant::AABB)                               \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, Basis, Variant::BASIS)                             \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, Transform3D, Variant::TRANSFORM3D)                 \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, Color, Variant::COLOR)                             \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, StringName, Variant::STRING_NAME)                  \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, NodePath, Variant::NODE_PATH)                      \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, RID, Variant::RID)                                 \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, Callable, Variant::CALLABLE)                       \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, Signal, Variant::SIGNAL)                           \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, Dictionary, Variant::DICTIONARY)                   \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, Array, Variant::ARRAY)                             \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, PackedByteArray, Variant::PACKED_BYTE_ARRAY)       \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, PackedInt32Array, Variant::PACKED_INT32_ARRAY)     \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, PackedInt64Array, Variant::PACKED_INT64_ARRAY)     \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, PackedFloat32Array, Variant::PACKED_FLOAT32_ARRAY) \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, PackedFloat64Array, Variant::PACKED_FLOAT64_ARRAY) \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, PackedStringArray, Variant::PACKED_STRING_ARRAY)   \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, PackedVector2Array, Variant::PACKED_VECTOR2_ARRAY) \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, PackedVector2iArray, Variant::PACKED_VECTOR2I_ARRAY) \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, PackedVector3Array, Variant::PACKED_VECTOR3_ARRAY) \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, PackedVector4Array, Variant::PACKED_VECTOR4_ARRAY) \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, PackedColorArray, Variant::PACKED_COLOR_ARRAY)     \
	/* MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, IPAddress, Variant::STRING) */

#define MAKE_TYPED_DICTIONARY_INFO(m_type, m_variant_type)                             \
	MAKE_TYPED_DICTIONARY_INFO_EXPANDED(m_type, m_variant_type, Variant, Variant::NIL) \
	MAKE_TYPED_DICTIONARY_INFO_NIL(m_type, m_variant_type)

MAKE_TYPED_DICTIONARY_INFO_NIL(Variant, Variant::NIL)
MAKE_TYPED_DICTIONARY_INFO(bool, Variant::BOOL)
MAKE_TYPED_DICTIONARY_INFO(uint8_t, Variant::INT)
MAKE_TYPED_DICTIONARY_INFO(int8_t, Variant::INT)
MAKE_TYPED_DICTIONARY_INFO(uint16_t, Variant::INT)
MAKE_TYPED_DICTIONARY_INFO(int16_t, Variant::INT)
MAKE_TYPED_DICTIONARY_INFO(uint32_t, Variant::INT)
MAKE_TYPED_DICTIONARY_INFO(int32_t, Variant::INT)
MAKE_TYPED_DICTIONARY_INFO(uint64_t, Variant::INT)
MAKE_TYPED_DICTIONARY_INFO(int64_t, Variant::INT)
MAKE_TYPED_DICTIONARY_INFO(float, Variant::FLOAT)
MAKE_TYPED_DICTIONARY_INFO(double, Variant::FLOAT)
MAKE_TYPED_DICTIONARY_INFO(String, Variant::STRING)
MAKE_TYPED_DICTIONARY_INFO(Vector2, Variant::VECTOR2)
MAKE_TYPED_DICTIONARY_INFO(Vector2i, Variant::VECTOR2I)
MAKE_TYPED_DICTIONARY_INFO(Rect2, Variant::RECT2)
MAKE_TYPED_DICTIONARY_INFO(Rect2i, Variant::RECT2I)
MAKE_TYPED_DICTIONARY_INFO(Vector3, Variant::VECTOR3)
MAKE_TYPED_DICTIONARY_INFO(Vector3i, Variant::VECTOR3I)
MAKE_TYPED_DICTIONARY_INFO(Transform2D, Variant::TRANSFORM2D)
MAKE_TYPED_DICTIONARY_INFO(Transform2Di, Variant::TRANSFORM2DI)
MAKE_TYPED_DICTIONARY_INFO(Plane, Variant::PLANE)
MAKE_TYPED_DICTIONARY_INFO(Quaternion, Variant::QUATERNION)
MAKE_TYPED_DICTIONARY_INFO(AABB, Variant::AABB)
MAKE_TYPED_DICTIONARY_INFO(Basis, Variant::BASIS)
MAKE_TYPED_DICTIONARY_INFO(Transform3D, Variant::TRANSFORM3D)
MAKE_TYPED_DICTIONARY_INFO(Color, Variant::COLOR)
MAKE_TYPED_DICTIONARY_INFO(StringName, Variant::STRING_NAME)
MAKE_TYPED_DICTIONARY_INFO(NodePath, Variant::NODE_PATH)
MAKE_TYPED_DICTIONARY_INFO(RID, Variant::RID)
MAKE_TYPED_DICTIONARY_INFO(Callable, Variant::CALLABLE)
MAKE_TYPED_DICTIONARY_INFO(Signal, Variant::SIGNAL)
MAKE_TYPED_DICTIONARY_INFO(Dictionary, Variant::DICTIONARY)
MAKE_TYPED_DICTIONARY_INFO(Array, Variant::ARRAY)
MAKE_TYPED_DICTIONARY_INFO(PackedByteArray, Variant::PACKED_BYTE_ARRAY)
MAKE_TYPED_DICTIONARY_INFO(PackedInt32Array, Variant::PACKED_INT32_ARRAY)
MAKE_TYPED_DICTIONARY_INFO(PackedInt64Array, Variant::PACKED_INT64_ARRAY)
MAKE_TYPED_DICTIONARY_INFO(PackedFloat32Array, Variant::PACKED_FLOAT32_ARRAY)
MAKE_TYPED_DICTIONARY_INFO(PackedFloat64Array, Variant::PACKED_FLOAT64_ARRAY)
MAKE_TYPED_DICTIONARY_INFO(PackedStringArray, Variant::PACKED_STRING_ARRAY)
MAKE_TYPED_DICTIONARY_INFO(PackedVector2Array, Variant::PACKED_VECTOR2_ARRAY)
MAKE_TYPED_DICTIONARY_INFO(PackedVector2iArray, Variant::PACKED_VECTOR2I_ARRAY)
MAKE_TYPED_DICTIONARY_INFO(PackedVector3Array, Variant::PACKED_VECTOR3_ARRAY)
MAKE_TYPED_DICTIONARY_INFO(PackedVector4Array, Variant::PACKED_VECTOR4_ARRAY)
MAKE_TYPED_DICTIONARY_INFO(PackedColorArray, Variant::PACKED_COLOR_ARRAY)
/*
MAKE_TYPED_DICTIONARY_INFO(IPAddress, Variant::STRING)
*/

#undef MAKE_TYPED_DICTIONARY_INFO
#undef MAKE_TYPED_DICTIONARY_INFO_NIL
#undef MAKE_TYPED_DICTIONARY_INFO_EXPANDED
#undef MAKE_TYPED_DICTIONARY_INFO_WITH_OBJECT

} // namespace godot

#endif // GODOT_TYPED_DICTIONARY_HPP
