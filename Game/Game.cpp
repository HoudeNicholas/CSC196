// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include <iostream>
#include <string>
#include "Math/Transform.h"
#include "Graphics/Shape.h"

std::vector<nc::Vector2> points = { {0, -3}, {3 ,3}, {0, 1}, {-3, 3}, {0, -3} };
nc::Color color{0.2f, 0.4f, 0.75f};
const size_t numPoints = 40;
float speed = 300.0f;
float frametime;
float roundtime;
bool gameover = false;

DWORD prevTime;
DWORD deltaTime;

nc::Shape ship;

nc::transform transform{ {400, 300}, 5, 0 };

bool Update(float dt)
{
	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;

	bool quit = false;

	frametime = dt;
	roundtime += dt;

	if (roundtime >= 5) {
		gameover = true;
	}
	if (gameover) { dt = 0; }

	quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	//if (Core::Input::IsPressed('A')) {
	//	position = position + nc::Vector2::left * speed * dt;
	//}

	//if (Core::Input::IsPressed('D')) {
	//	position = position + nc::Vector2::right * speed * dt;
	//}

	nc::Vector2 force{ 0 ,0 };

	if (Core::Input::IsPressed('W')) {
		force = nc::Vector2::forward * speed * dt;
	}
	nc::Vector2 direction = force;
	direction = nc::Vector2::rotate(direction, transform.angle);
	transform.position = transform.position + direction;


	if (Core::Input::IsPressed('S')) {
		transform.position = transform.position + nc::Vector2::down * speed * dt;
	}

	if (Core::Input::IsPressed('A')) {
		transform.angle = transform.angle - dt * 5;
	}
	
	if (Core::Input::IsPressed('D')) {
		transform.angle = transform.angle + dt * 5;
	}

	int x;
	int y;

	Core::Input::GetMousePos(x, y);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(color);
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1 / frametime).c_str());
	if (gameover) { graphics.DrawString(400, 300, "GAME OVER"); }
	graphics.DrawString(10, 30, std::to_string(deltaTime / 1000.0f).c_str());

	std::vector<nc::Vector2> bowtiePoints = { {0, 0}, {5, -3}, {5, 3}, {-5, -3}, {-5, 3}, {0, 0} };
	nc::Vector2 middle = { 400, 300 };
	nc::Shape bowtie = { bowtiePoints, nc::Color(1, 1, 1)};

	//bowtie.Draw(graphics, middle, 5.0f, 0.0f);

	ship.Draw(graphics, middle, 5.0f, 0.0f);

	for (size_t i = 0; i < points.size() - 1; i++) {
		nc::Vector2 p1 = points[i];
		nc::Vector2 p2 = points[i + 1];

		p1 = p1 * transform.scale;
		p2 = p2 * transform.scale;

		p1 = nc::Vector2::rotate(p1, transform.angle);
		p2 = nc::Vector2::rotate(p2, transform.angle);

		p1 = p1 + transform.position;
		p2 = p2 + transform.position;

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

int main()
{
	ship.load("ship.txt");

	DWORD ticks = GetTickCount();
	std::cout << ticks / 1000 / 60 / 60 << std::endl;

	char name[] = "CSC196";
	Core::Init(name, 800, 600, 60);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
