#pragma once
#ifndef __CAR__
#define __CAR__
#include "DisplayObject.h"
#include "TextureManager.h"
#include "Util.h"

class Car final : public DisplayObject {
public:
	Car();
	~Car();
	void draw() override;
	void update() override;
	void clean() override;

	void setDestination(const glm::vec2 destination);
	void setMaxSpeed(float speed);
	glm::vec2 getOrientation();
	void setOrientation(glm::vec2 orientation);
	float getRotation();
	void setRotation(float rotation);
	float getTurnRate();
	void setTurnRate(float rate);
	float getAccelerationRate();
	void setAccelerationRate(float rate);
private:
	glm::vec2 m_destination;
	glm::vec2 m_targetDirection;
	glm::vec2 m_orientation;
	float m_rotationAngle;
	float m_maxSpeed;
	float m_turnRate;
	float m_accelRate;

	void m_Move();
};

#endif // defined __CAR__
