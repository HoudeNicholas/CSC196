#pragma once
#include <core.h>
#include <vector>
#include <list>
#include "Actor.h"
#include "Enemy.h"
#include "Player.h"

std::vector<nc::Vector2> points = { {0, -3}, {3 ,3}, {0, 1}, {-3, 3}, {0, -3} };
nc::Shape playerShip(points, nc::Color(0, 1, 0));
nc::transform playerTransform{ {400, 300}, 5, 0 };
nc::Player player{ playerTransform, playerShip };
nc::Actor* actor = &player;

nc::Shape enemyShip(points, nc::Color(1, 0, 0));
nc::transform enemyTrans{ {400, 600}, 2.5f, 0 };
nc::Enemy enemy{ enemyTrans, enemyShip, actor };
nc::Actor* enemyActor = &enemy;

namespace nc
{
	class Scene
	{
	public:
		void Startup() {}
		void Shutdown() {
			for (Actor* actor : m_actors) {
				delete(actor);
			}
			m_actors.clear();
		}

		void Update(float dt) {
			for (Actor* actor : m_actors) {
				actor->Update(dt);
			}
		}

		void Draw(Core::Graphics& graphics) {
			for (Actor* actor : m_actors) {
				actor->Draw(graphics);
			}
		}

		void AddActor(class Actor* actor) {
			m_actors.push_back(actor);
		}

		void RemoveActor(Actor* actor)
		{
			std::list<Actor*>::iterator iter = std::find(m_actors.begin(), m_actors.end(), actor);
			if (iter != m_actors.end())
			{
				delete* iter;
				m_actors.erase(iter);
			}
		}


		template <typename T>
		T* GetActor() {}


		template <typename T>
		std::vector<T*> GetActors() {}

	private:
		std::list<class Actor*> m_actors;
	};
}
