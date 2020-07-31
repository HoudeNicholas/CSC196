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
#include "Graphics/Actor.h"
#include "Graphics/Player.h"
#include "Graphics/Enemy.h"
#include "Math/Matrix33.h"
#include "Graphics/Scene.h"

nc::Color color{0.2f, 0.4f, 0.75f};
const size_t numPoints = 40;
float speed = 300.0f;
float frametime;
float roundtime;
float scale = 5;
bool gameover = false;

float t = 1;

DWORD prevTime;
DWORD deltaTime;

nc::Shape ship;

nc::transform transform{ {400, 300}, 5, 0 };

std::vector<nc::Vector2> points2{ {1, 1}, {0, 4}, {-1, 1}, {-4, 0}, {-1, -1}, {0, -4}, {1, -1}, {4, 0}, {1, 1}, {-1, 1}, {-1, -1}, {1, -1}, {1, 1} };
nc::Shape thing{ points2, nc::Color(1, 0, 0) };
nc::transform thingTrans{ {400, 450}, 3, 0 };
nc::Enemy thingAct{ thingTrans, thing, actor };

std::vector<nc::Vector2> spikePoints{ {0, -6}, {3, 0}, {6, -6}, {9, 0}, {-9, 0}, {-6, -6}, {-3, 0}, {0, -6} };
nc::Shape spike{spikePoints, nc::Color(1, 0, 0)};
nc::transform spikeTrans{ {600, 150}, 5, 0 };
nc::Actor spikeAct{ spikeTrans, spike };

std::vector<nc::Vector2> barrelPoints{ {2, -3}, {2, 3}, {-2, 3}, {-2, -3}, {2, -3}, {2, -2}, {-2, 2}, {-2, -2}, {2, 2}, {-2, 2}, {-2, -2}, {2, -2} };
nc::Shape barrel{ barrelPoints, nc::Color(1, 0, 0) };
nc::transform barrelTrans{ {600, 450}, 5, 0 };
nc::Actor barrelAct{ barrelTrans, barrel };

nc::Scene scene;

float time;

bool Update(float dt)
{
	t = t + (dt * 0.1f);

	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;

	bool quit = false;

	thingAct.Update(dt);

	frametime = dt;
	roundtime += dt;
	time += dt;

	if (roundtime > 3.2f) {
		scene.AddActor(enemyActor);
		roundtime = 0;
	}
	//if (gameover) { dt = 0; }

	quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	//if (Core::Input::IsPressed('A')) {
	//	position = position + nc::Vector2::left * speed * dt;
	//}

	//if (Core::Input::IsPressed('D')) {
	//	position = position + nc::Vector2::right * speed * dt;
	//}

	nc::Vector2 force{ 0 ,0 };

	/*if (Core::Input::IsPressed('W')) {
		force = nc::Vector2::forward * speed * dt;
	}*/



	//nc::Vector2 direction = force;
	//direction = nc::Vector2::rotate(direction, transform.angle);
	//transform.position = transform.position + direction;
	//transform.position.x = nc::clamp(transform.position.x, 0, 800);
	//transform.position.y = nc::clamp(transform.position.y, 0, 600);

	/*if (Core::Input::IsPressed('S')) {
		transform.position = transform.position + nc::Vector2::down * speed * dt;
	}

	if (Core::Input::IsPressed('A')) {
		transform.angle = transform.angle - dt * nc::degToRad(360);
	}
	
	if (Core::Input::IsPressed('D')) {
		transform.angle = transform.angle + dt * nc::degToRad(360);
	}*/

	int x;
	int y;

	scene.Update(dt);

	Core::Input::GetMousePos(x, y);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	thingAct.Draw(graphics);
	graphics.SetColor(color);
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1 / frametime).c_str());
	if (gameover) { graphics.DrawString(400, 300, "GAME OVER"); }
	graphics.DrawString(10, 30, std::to_string(deltaTime).c_str());

	std::vector<nc::Vector2> bowtiePoints = { {0, 0}, {5, -3}, {5, 3}, {-5, -3}, {-5, 3}, {0, 0} };
	nc::Vector2 middle = { 400, 300 };
	nc::Shape bowtie = { bowtiePoints, nc::Color(1, 1, 1)};

	//bowtie.Draw(graphics, middle, 5.0f, 0.0f);

	/*ship.Draw(graphics, middle, 5.0f, 0.0f);*/

	//nc::Matrix33 mxScale;
	//mxScale.scale(scale);

	//float angle = 0;

	//nc::Matrix33 rotate;
	//rotate.rotate(angle);

	//nc::Matrix33 translate;
	//translate.translate(transform.position);

	//nc::Matrix33 mx = mxScale * rotate * translate;

	//for (size_t i = 0; i < points.size() - 1; i++) {
	//	nc::Vector2 p1 = points[i];
	//	nc::Vector2 p2 = points[i + 1];

	//	p1 = p1 * mx;
	//	p2 = p2 * mx;

	//	graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	//}
	scene.Draw(graphics);
}

int main()
{
	scene.AddActor(actor);
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
