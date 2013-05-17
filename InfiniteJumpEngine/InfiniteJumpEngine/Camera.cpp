
#include "Camera.h"

// Constructors/Destructors
//  
Camera::Camera ( ) {
	initAttributes();
}

Camera::~Camera ( ) { 

}

//  
// Methods
//  
void Camera::update (glm::vec3 pos, glm::vec3 dir){
	glm::vec3 camPos = glm::normalize(dir) + glm::vec3( 0, 1, 0 );
	glm::vec3 scaleDir = glm::normalize( dir ) * 0.25f;
	switch( cameraProfile ) {
		case 0: //third person
			cam = glm::lookAt( glm::vec3( pos.x - scaleDir.x, 
				pos.y - scaleDir.y + 0.1f,
				pos.z - scaleDir.z ),
				pos, glm::vec3( 0, 1, 0 ) );
			break;
		case 1: //first person
			cam = glm::lookAt( glm::vec3( pos.x, 
				pos.y+0.05,
				pos.z ),
				glm::vec3( pos.x+dir.x, 
				pos.y+dir.y+0.01,
				pos.z+dir.z ), glm::vec3( 0, 1, 0 ) );
			break;
		case 2: //top down
			cam = glm::lookAt( glm::vec3( pos.x, 
				pos.y+6.0f,
				pos.z ),
				pos, glm::vec3( 0, 0, -1 ) );
			break;
		default:
			break;
		}
}

void Camera::switchProfile( int profile ) {
	cameraProfile = profile;
}

// Accessor methods
//  


// Other methods
//  

void Camera::initAttributes ( ) {

}
