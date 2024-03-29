#include "glIncludes.h"
#include "Game.h"

int main(int argc, char** argv){
	glutInit(&argc, argv);

	setupGLUT();

	setupInterface( );

	glewInit();

	glutMainLoop();

	Game::clear();

	return 0;
}

//reshape function for GLUT
void reshape(int w, int h) {
	Game::game()->reshape(w,h);
}

//display function for GLUT
void display() {
	Game::game()->display();
}

//idle function for GLUT
void idle() {
	Game::game()->idle();
}

//captures keyborad input for GLUT
void keyboard(unsigned char key, int x, int y) {
	Game::game()->keyboard(key,x,y);
}

//do some GLUT initialization
void setupGLUT() {
	Game::game()->setupGLUT();

	glutReshapeFunc(reshape);

	glutDisplayFunc(display);

	glutKeyboardFunc(keyboard);

	glutIdleFunc(idle);
}

void setupInterface( ) {
	Game::game()->setupInterface();
}