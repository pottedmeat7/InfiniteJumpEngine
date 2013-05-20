
#ifndef CAMERA_H
#define CAMERA_H

#include "glIncludes.h"

class Camera
{
public:
	
    Camera ( );
	
    virtual ~Camera ( );

	glm::mat4 cam, proj;
	glm::vec3 lightPos;
	void update(glm::vec3, glm::vec3);
	void switchProfile( int profile );
protected:

private:
	int cameraProfile;
    void initAttributes ( ) ;
	
	glm::vec3 camEye;
	glm::vec3 camLookAt;
	glm::vec3 camUp;
};

#endif CAMERA_H
