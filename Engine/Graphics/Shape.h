#pragma once
#include "core.h"
#include <vector>
#include "../Math/Vector2.h"
#include "../Math/Color.h"
#include <string>
#include "Math/Transform.h"

namespace nc
{
	class Shape
	{
	public:
		Shape() {};
		Shape(std::vector<Vector2> points, Color color) {
			this->m_points = points;
			this->m_color = color;
		}

		void Draw(Core::Graphics& graphics, const nc::transform& transform);

		bool load(const std::string& filename);

		void Draw(Core::Graphics& graphics, nc::Vector2 position, float scale, float angle);

		void setColor(Color color);

		const Color& getColor();

	private:
		std::vector<Vector2> m_points;
		Color m_color;
	};
}