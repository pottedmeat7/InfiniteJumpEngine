#include "PositionComponent.h"


PositionComponent::PositionComponent(glm::vec3 n_pos, glm::vec3 n_rot, glm::vec3 n_sca)
{
	setPosition(n_pos);
	setRotation(n_rot);
	setScale(n_sca);
}


PositionComponent::~PositionComponent(void)
{
}

glm::mat4 PositionComponent::getTransform(){
	glm::mat4 t = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rX = glm::rotate( glm::mat4( ), rotation.x, glm::vec3( 1, 0, 0 ) );
	glm::mat4 rY = glm::rotate( glm::mat4( ), rotation.y, glm::vec3( 0, 1, 0 ) );
	glm::mat4 rZ = glm::rotate( glm::mat4( ), rotation.z, glm::vec3( 0, 0, 1 ) );
	glm::mat4 r = rX * rY * rZ;
	glm::mat4 s = glm::scale(glm::mat4(), scale);
	return t * r * s;
}

const PositionComponent PositionComponent::operator+(const PositionComponent &that){
	PositionComponent out;
	out.position = position + that.position;
	out.rotation = rotation + that.rotation;
	out.scale = scale + that.scale;
	return out;
}

const PositionComponent PositionComponent::operator*(const float scalar){
	PositionComponent out;
	out.position = position * scalar;
	out.rotation = rotation * scalar;
	out.scale = scale * scalar;
	return out;
}