#include "pch.h"
#include "Shape.h"
#include <iostream>
#include <fstream>

void nc::Shape::Draw(Core::Graphics& graphics, const nc::transform& transform)
{
	Draw(graphics, transform.position, transform.scale, transform.angle);
}

bool nc::Shape::load(const std::string& filename)
{
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open()) {
		success = true;
		//read color
		stream >> m_color;

		//get # of points
		size_t size;
		std::string line;
		std::getline(stream, line);
		size = stoi(line);

		//read points
		for (size_t i = 0; i < size; i++) {
			Vector2 v;
			stream >> v;
			v.y *= -1;
			m_points.push_back(v);
		}

		stream.close();
	}

	return success;
}

void nc::Shape::Draw(Core::Graphics& graphics, nc::Vector2 position, float scale, float angle)
{
	graphics.SetColor(this->getColor());

	for (size_t i = 0; i < this->m_points.size() - 1; i++) {
		nc::Vector2 p1 = m_points[i];
		nc::Vector2 p2 = m_points[i + 1];

		p1 *= scale;
		p2 *= scale;

		p1 = nc::Vector2::rotate(p1, angle);
		p2 = nc::Vector2::rotate(p2, angle);

		p1 += position;
		p2 += position;

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}

}

void nc::Shape::setColor(Color color)
{
	this->m_color = color;
}

const nc::Color& nc::Shape::getColor()
{
	return this->m_color;
}
