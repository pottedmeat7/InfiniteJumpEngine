#include "TileSet.h"
#include "Camera.h"


TileSet::TileSet(void)
{
}


TileSet::~TileSet(void)
{
}

void TileSet::update(float dT){
	for (tileIter t = tiles.begin(); t != tiles.end(); t++){
		(*t)->update(dT);
	}
}

void TileSet::draw( Camera * camera ){
	for (tileIter t = tiles.begin(); t != tiles.end(); t++){
		(*t)->draw(camera);
	}
}