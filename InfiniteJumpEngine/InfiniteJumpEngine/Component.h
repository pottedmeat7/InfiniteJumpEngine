#ifndef COMPONENT_H
#define COMPONENT_H
#include "IJMessage.h"
#include "luaIncludes.h"
#include "Drawable.h"
#include <vector>

using namespace std;
class Component: public Drawable
{
public:
	Component(){
		parent = NULL;
	}
	virtual Component * getParent(){return parent;};
	virtual void setParent(Component * p){parent = p;};
	virtual glm::mat4 transform(void){
		return transform(glm::mat4());
	}
	virtual glm::mat4 transform(glm::mat4 in){
		if (parent)
			return parent->transform(in);
		return in;
	}
	virtual glm::vec3 getPickId( ) {
		return pickId;
	}

	virtual void sendMessage(Component* that, Component* other, char *s, glm::vec4 v = glm::vec4(0,0,0,0)){
		IJMessage *m =  new IJMessage(this, that, other, s, v);
		sendMessage(m, that);
		delete m; m = NULL;
	}

	virtual void sendMessage( IJMessage *m, Component* that){
		if (that){
			that->receiveMessage(m);
		} else {
			cout << "Message fell out of parent chain:" << m->content << " " << m->vecContent.x << " " << m->vecContent.y << " " << m->vecContent.z << endl;
		}
	}

	virtual void receiveMessage( IJMessage *m ){
		sendMessage(m, parent);
	}

	virtual char* getType(){
		return "Component";
	}

protected:
	Component *parent;
	glm::vec3 pickId;
	lua_State* lua;
};

typedef std::vector<Component*> componentVector;
typedef componentVector::iterator componentIter;

#endif COMPONENT_H