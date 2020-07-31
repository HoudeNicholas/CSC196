#pragma once
#include "Math/Matrix33.h"
#include "Vector2.h"

namespace nc
{
	struct transform
	{
		Vector2 position;
		float scale;
		float angle;

		Matrix33 matrix;

		void update() {
			nc::Matrix33 mxScale;
			mxScale.scale(scale);

			nc::Matrix33 rotate;
			rotate.rotate(angle);

			nc::Matrix33 translate;
			translate.translate(position);

			matrix = mxScale * rotate * translate;
		}

		transform() : position{ 0, 0 }, scale{ 1 }, angle{ 0 } {}
		transform(const Vector2& position, float scale, float angle) { this->position = position; this->scale = scale; this->angle = angle; }
		transform(const Vector2& position) : position{ position }, scale{ 5 }, angle{ 0 } {}

		/*friend std::ifstream& operator >> (std::ifstream& stream, transform& transform) {
			
			stream >> transform.position;
			stream >> transform.scale;
			stream >> transform.angle;

			return stream;

		}*/
	};
}