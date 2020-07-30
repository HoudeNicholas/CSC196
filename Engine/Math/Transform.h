#pragma once
#include "Vector2.h"

namespace nc
{
	struct transform
	{
		Vector2 position;
		float scale;
		float angle;

		transform() : position{ 0, 0 }, scale{ 1 }, angle{ 0 } {}
		transform(const Vector2& position, float scale, float angle) { this->position = position; this->scale = scale; this->angle = angle; }

		friend std::ifstream& operator >> (std::ifstream& stream, transform& transform) {
			
			stream >> transform.position;
			stream >> transform.scale;
			stream >> transform.angle;

			return stream;

		}
	};
}