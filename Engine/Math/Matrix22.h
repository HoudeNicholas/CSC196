#pragma once
#include "Math/Vector2.h"


namespace nc
{
	struct Matrix22
	{
		float m[2][2]; //column, row

		// m[0][0] m[1][0]
		// m[0][1] m[1][1]

		Matrix22() = default;

		Matrix22(const Vector2& c1, const Vector2& c2) {
			m[0][0] = c1[0]; m[1][0] = c2[0];
			m[0][1] = c1[1]; m[1][1] = c2[1];

		}

		void scale(float s) {
			m[0][0] = s; m[1][0] = 0;
			m[0][1] = 0; m[1][1] = s;
		}

		void scale(float sx, float sy) {
			m[0][0] = sx; m[1][0] = 0;
			m[0][1] = 0; m[1][1] = sy;
		}

		void scale(const Vector2& s) {
			m[0][0] = s.x; m[1][0] = 0;
			m[0][1] = 0; m[1][1] = s.y;
		}

		void rotate(float angle) {
			m[0][0] = std::cos(angle); m[1][0] = std::sin(angle);
			m[0][1] = -std::sin(angle); m[1][1] = std::cos(angle);
		}

		void setIdentity() {
			m[0][0] = 1; m[1][0] = 0;
			m[0][1] = 0; m[1][1] = 1;
		}

		Matrix22 operator * (const Matrix22& mx) {
			Matrix22 result;
			result.m[0][0] = (m[0][0] * mx.m[0][0]) + (m[1][0] * mx.m[0][1]);
			result.m[1][0] = (m[0][0] * mx.m[1][0]) + (m[1][0] * mx.m[1][1]);
			result.m[0][1] = (m[0][1] * mx.m[0][0]) + (m[1][1] * mx.m[0][1]);
			result.m[1][1] = (m[0][1] * mx.m[1][0]) + (m[1][1] * mx.m[1][1]);

			return result;
		}

		Vector2 operator * (const Vector2& v) {
			Vector2 result;

			result.x = v.x * m[0][0] + v.y * m[0][1];
			result.y = v.x * m[1][0] + v.y * m[1][1];

			return result;
		}

		friend Vector2 operator * (const Vector2& v, const Matrix22& mx) {
			Vector2 result;

			result.x = v.x * mx.m[0][0] + v.y * mx.m[0][1];
			result.y = v.x * mx.m[1][0] + v.y * mx.m[1][1];

			return result;
		}

	};
}