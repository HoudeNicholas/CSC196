#pragma once
#include <cmath>
#include <iostream>

namespace nc {

	struct Vector2 {
		float x, y;

		float& operator [] (size_t index) { return (&x)[index]; }

		const float& operator [] (size_t index) const { return (&x)[index]; }

		Vector2() : x{ 0 }, y{ 0 } {}
		Vector2(float x, float y) : x{ x }, y{ y } {}
		Vector2(int x, int y) : x{ static_cast<float>(x) }, y{ static_cast<float>(y) } {}

		void set(float x, float y) { this->x = x; this->y = y; }

		Vector2 operator + (const Vector2& v) const { return Vector2{x + v.x, y + v.y}; }
		Vector2 operator - (const Vector2& v) const { return Vector2{x - v.x, y - v.y}; }
		Vector2 operator * (const Vector2& v) const { return Vector2{x * v.x, y * v.y}; }
		Vector2 operator / (const Vector2& v) const { return Vector2{x - v.x, y / v.y}; }

		Vector2 operator + (float s) const { return Vector2{x + s, y + s}; }
		Vector2 operator - (float s) const { return Vector2{x - s, y - s}; }
		Vector2 operator * (float s) const { return Vector2{x * s, y * s}; }
		Vector2 operator / (float s) const { return Vector2{x / s, y / s}; }

		Vector2 operator += (const Vector2& v) { return Vector2{ x += v.x, y += v.y }; }
		Vector2 operator -= (const Vector2& v) { return Vector2{ x -= v.x, y -= v.y }; }
		Vector2 operator *= (const Vector2& v) { return Vector2{ x *= v.x, y *= v.y }; }
		Vector2 operator /= (const Vector2& v) { return Vector2{ x -= v.x, y /= v.y }; }

		Vector2 operator += (float s) { return Vector2{ x += s, y += s }; }
		Vector2 operator -= (float s) { return Vector2{ x -= s, y -= s }; }
		Vector2 operator *= (float s) { return Vector2{ x *= s, y *= s }; }
		Vector2 operator /= (float s) { return Vector2{ x /= s, y /= s }; }

		friend std::istream& operator >> (std::istream& stream, Vector2& v);

		inline float length() const {
			return std::sqrt((x * x) + (y * y));
		}

		inline static float distance(const Vector2& v1, const Vector2& v2) {
			Vector2 v = v1 - v2;
			return v.length();

		}

		inline Vector2 normalized() const {
			Vector2 n = (length() == 0.0f) ? Vector2{ 0.0f, 0.0f } : *this / length();

			return n;
		}

		inline void normalize() {
			if (length() == 0.0f) {
				*this = Vector2{ 0.0f, 0.0f };
			} else {
				*this /= length();
			}

		}

		inline static Vector2 rotate(const Vector2& v, float radians) {
			float x = v.x * std::cos(radians) - v.y * std::sin(radians);
			float y = v.x * std::sin(radians) + v.y * std::cos(radians);
			
			return Vector2{ x, y };
		}

		static const Vector2 left;
		static const Vector2 right;
		static const Vector2 up;
		static const Vector2 down;
		static const Vector2 forward;

	};

}