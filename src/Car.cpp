#include "Car.h"
#include "Game.h"

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
	setAccelerationRate(10.0f);
	setTurnRate(10.0f);
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

glm::vec2 Car::getOrientation()
{
	return m_orientation;
}

void Car::setOrientation(glm::vec2 orientation) {
	m_orientation = orientation;
}

float Car::getRotation()
{
	return m_rotationAngle;
}

void Car::setRotation(float rotation) {
	m_rotationAngle = rotation;
	auto angleRads = (rotation - 90.0f) * Util::Deg2Rad;

	auto x = cos(angleRads);
	auto y = sin(angleRads);

	setOrientation(glm::vec2(x, y));
}

float Car::getTurnRate()
{
	return m_turnRate;
}

void Car::setTurnRate(float rate)
{
	m_turnRate = rate;
}

float Car::getAccelerationRate()
{
	return m_accelRate;
}

void Car::setAccelerationRate(float rate)
{
	m_accelRate = rate;
}

void Car::m_Move() {
	auto deltaTime = TheGame::Instance()->getDeltaTime();

	m_targetDirection = m_destination - getTransform()->position;
	m_targetDirection = Util::normalize(m_targetDirection);

	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);

	if (target_rotation > 0)
	{
		setRotation(getRotation() + getTurnRate());
	}
	else if (target_rotation < 0)
	{
		setRotation(getRotation() - getTurnRate());
	}

	getRigidBody()->acceleration = getOrientation() * getAccelerationRate();
	getRigidBody()->velocity += getOrientation() * deltaTime + 0.5f * getRigidBody()->acceleration * deltaTime;
	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);
	getTransform()->position += getRigidBody()->velocity;
}