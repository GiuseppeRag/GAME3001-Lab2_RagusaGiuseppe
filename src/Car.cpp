#include "Car.h"

Car::Car()
{
	TextureManager::Instance()->load("../Assets/textures/Car.png", "car");
	auto size = TextureManager::Instance()->getTextureSize("car");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setMaxSpeed(8.0f);
	setOrientation(glm::vec2(0.0f, -1.0f));
	setRotation(0.0f);
	setType(CAR);
}

Car::~Car()
= default;

void Car::draw()
{
	TextureManager::Instance()->draw("car", getTransform()->position.x, getTransform()->position.y, m_rotationAngle, 255, true);
	Util::DrawLine(getTransform()->position, getTransform()->position + m_orientation * 60.0f);
}

void Car::update()
{
	m_Move();
}

void Car::clean()
{
}

void Car::setDestination(const glm::vec2 destination)
{
	m_destination = destination;
}

void Car::setMaxSpeed(float speed) {
	m_maxSpeed = speed;
}

void Car::setOrientation(glm::vec2 orientation) {
	m_orientation = orientation;
}

void Car::setRotation(float rotation) {
	m_rotationAngle = rotation;
}

void Car::m_Move() {
	m_targetDirection = m_destination - getTransform()->position;
	m_targetDirection = Util::normalize(m_targetDirection);

	getRigidBody()->velocity = m_targetDirection * m_maxSpeed;
	getTransform()->position += getRigidBody()->velocity;
}