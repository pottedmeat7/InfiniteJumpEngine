#pragma once
#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H
#include "glIncludes.h"
#include "TransformComponent.h"

class PositionComponent :
	public TransformComponent
{
public:
	PositionComponent(glm::vec3 n_pos = glm::vec3(0.0f,0.0f,0.0f), 
					  glm::vec4 n_rot = glm::vec4(0.0f,0.0f,0.0f,0.0f), 
					  glm::vec3 n_sca = glm::vec3(1.0f,1.0f,1.0f));
	~PositionComponent(void);
	//Translation
	glm::vec3 getPosition();
	void setPosition(glm::vec3 v){setPosition(v.x,v.y,v.z);};
	void setPosition(float x, float y, float z){
		setPosX(x);
		setPosY(y);
		setPosZ(z);
	}
	inline void setPosX(float v){position.x = v;}; 
	inline void setPosY(float v){position.y = v;};
	inline void setPosZ(float v){position.z = v;}; 
	
	//Rotation
	glm::vec4 getRotation();
	void setRotation(glm::vec4 v){setRotation(v.x,v.y,v.z,v.w);};
	void setRotation(float x, float y, float z, float w){
		setRotX(x);
		setRotY(y);
		setRotZ(z);
		setRotW(w);
	}
	inline void setRotX(float v){rotation.x = v;}; 
	inline void setRotY(float v){rotation.y = v;};
	inline void setRotZ(float v){rotation.z = v;}; 
	inline void setRotW(float v){rotation.w = v;}; 

	//Scale
	glm::vec3 getScale();
	void setScale(glm::vec3 v){setScale(v.x,v.y,v.z);};
	void setScale(float x, float y, float z){
		setScaX(x);
		setScaY(y);
		setScaZ(z);
	}
	inline void setScaX(float v){scale.x = v;}; 
	inline void setScaY(float v){scale.y = v;};
	inline void setScaZ(float v){scale.z = v;}; 

	//Combine transformations
	glm::mat4 getTransform();

	//Message handling
	void receiveMessage( IJMessage *m);

	//Operator Overloading
	const PositionComponent operator+(const PositionComponent&);
	const PositionComponent operator*(const float);
protected:
	glm::vec3 position;
	glm::vec4 rotation;
	glm::vec3 scale;
};

#endif POSITION_COMPONENT_H