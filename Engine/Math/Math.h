#pragma once

namespace nc {

	const float pi = 3.1415f;
	const float twoPi = pi * 2;
	const float halfPi = pi / 2;

	inline float radToDeg(float radians) { return radians * (180 / pi); }

	inline float degToRad(float degrees) { return degrees * (pi / 180); }

	inline float clamp(float v, float min, float max) {
		if (v < min) {
			v = min;
		}
		else if (v > max) {
			v = max;
		}
		return v;
	}

	template <typename T>
	inline T lerp(T a, T b, float t) {
		t = clamp(t, 0, 1);
		return (a + ((b - a) * t));

	}

}


