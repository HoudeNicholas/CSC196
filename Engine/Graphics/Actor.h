#pragma once
#include "Math/Transform.h"
#include "Math/Vector2.h"
#include "Graphics/Shape.h"
#include "Math/Math.h"

namespace nc
{
	class Actor
	{
	public:
		Actor() {}
		Actor(const transform& transform, const Shape& shape) : m_transform { transform }, m_shape{ shape } {} // make sure to initialize m_transform and m_shape
		

		virtual bool Load(const std::string& filename) {
			bool success = false;
			return success;
		}

		virtual void Update(float dt) {}
		virtual void Draw(Core::Graphics& graphics) {

			this->m_shape.Draw(graphics, this->m_transform);

		}

		transform& GetTransform() { return m_transform; } // return the transform
		Shape& GetShape() { return m_shape; } // return the shape

	protected:
		transform m_transform;
		Shape m_shape;
	};
}
