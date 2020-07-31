#pragma once
#include "Actor.h"

namespace nc
{
	class Player : public Actor
	{

		public:
			Player() { this->speed = 0; this->rotationRate = 0; }
			Player(const transform& transform, const Shape& shape) { this->m_transform = transform; this->m_shape = shape; this->speed = 300.0f; }
			virtual ~Player() {}

			virtual bool Load(const std::string& filename) override {
				return false;
			}
			virtual void Update(float dt) override {
				nc::Vector2 force{ 0 ,0 };

				if (Core::Input::IsPressed('W')) {force = nc::Vector2::forward * speed * dt;}

				velocity = force;

				if (Core::Input::IsPressed('A')) { m_transform.angle = m_transform.angle - dt * nc::degToRad(360); }
				if (Core::Input::IsPressed('D')) { m_transform.angle = m_transform.angle + dt * nc::degToRad(360); }
				 
				velocity = nc::Vector2::rotate(velocity, m_transform.angle);
				m_transform.position = m_transform.position + velocity;
				m_transform.position.x = nc::clamp(m_transform.position.x, 0, 800);
				m_transform.position.y = nc::clamp(m_transform.position.y, 0, 600);

				m_transform.update();
				
			}

			virtual void Draw(Core::Graphics& graphics) {

				this->m_shape.Draw(graphics, this->m_transform);

			}

		protected:
			float speed = 0;
			float rotationRate = 0;
			Vector2 velocity;

	};
}