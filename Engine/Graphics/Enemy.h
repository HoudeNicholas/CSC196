#pragma once
#include "Actor.h"

namespace nc
{
	class Enemy : public Actor
	{
	public:
		Enemy() { this->speed = 0; }
		Enemy(const transform& transform, const Shape& shape, Actor* target) { this->m_transform = transform; this->m_shape = shape; this->m_target = target; this->speed = 150.0f; }
		virtual ~Enemy() {}

		void Update(float dt) {
			nc::Vector2 direction = m_target->GetTransform().position - m_transform.position;
			direction.normalize();

			this->m_transform.position = this->m_transform.position + direction * speed * dt;

			m_transform.update();

		}

		void setTarget(Actor* target) {
			this->m_target = target;
		}

	protected:
		float speed{ 0.0f };
		Actor* m_target{ nullptr };

	};
}