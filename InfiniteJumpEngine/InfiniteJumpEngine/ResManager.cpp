
#include "ResManager.h"

ResManager::ResManager(void)
{
}


ResManager::~ResManager(void)
{
}

Level* ResManager::getTriangleLevel(string filename, int holeID){
	Level* level = new Level();
	level->maxSubLevels = 0;
	Entity* terrain = new Entity();
	TileSet* tiles = new TileSet();
	terrain->addComponent(tiles);
	level->addEntity(terrain);
	Ball * ball;
	vector<PlaneCollider*> tileColliders;
	bool end_hole = false;
	bool begin_hole = false;
	bool course = false;
	int skip = 0;

	string line;
	ifstream input;
	input.open(filename.c_str( ));

	if ( input.fail( ) ) {
		cerr << "Unable to open level file " << filename << endl;
	} else {
		while( !end_hole ) {
			getline( input, line );
			if ( input.eof( ) ) {
				break;
			}
			istringstream iss(line);
			string type, id_str, num_str;
			iss >> type;
			if ( !type.compare( "tile" ) ) {
				if ( !course || begin_hole ) {
					int id;
					iss >> id_str;
					id = atoi(id_str.c_str( ));
					iss >> num_str;
					int numVerts = atoi(num_str.c_str( ));
					vector<glm::vec3> verts;
					glm::vec3 vertex;
					string str_x, str_y, str_z;
					for( int v = 0; v < numVerts; v++ ) { 
						iss >> str_x;
						iss >> str_y;
						iss >> str_z;
						vertex = glm::vec3( static_cast<float>(atof(str_x.c_str( ))), 
							static_cast<float>(atof(str_y.c_str( ))),
							static_cast<float>(atof(str_z.c_str( ))));
						verts.push_back(vertex);
					}
					vector<int> neighbors;
					string n_str;
					for ( int n = 0; n < numVerts; n++ ) {
						iss >> n_str;
						neighbors.push_back( atoi(n_str.c_str( )) );
					}
					tiles->addTile( id, new Tile( id, verts, neighbors, glm::vec3( 0.0f, 0.7f , 0.0f ) ) );
					//tiles->addTile( id, new Tile( id, verts, neighbors, glm::vec3( (float)id/17.f, (float)id/17.f, (float)id/17.f) ) );
					//tiles->addTile( id, new Tile( id, verts, neighbors, glm::vec3( 0.5, 0.5, 0.5 + id/34.f ) ) );
				}
			} else if ( !type.compare( "tee" ) ) {
				if ( !course || begin_hole ) {
					Entity * teeEntity = new Entity( );
					Mesh * tee = new Mesh( );
					string str_id;
					string str_x, str_y, str_z;
					iss >> str_id;
					int id = atoi(str_id.c_str( ));
					iss >> str_x;
					iss >> str_y;
					iss >> str_z;
					float x = static_cast<float>(atof( str_x.c_str( ) ));
					float y = static_cast<float>(atof( str_y.c_str( ) ));
					float z = static_cast<float>(atof( str_z.c_str( ) ));
					//tee mesh
					
					glm::vec3 vert0 = glm::vec3( x-0.05f, y+0.001f, z+0.05f );
					glm::vec3 vert1 = glm::vec3( x+0.05f, y+0.001f, z+0.05f );
					glm::vec3 vert2 = glm::vec3( x+0.05f, y+0.001f, z-0.05f );
					glm::vec3 vert3 = glm::vec3( x-0.05f, y+0.001f, z-0.05f );

					glm::vec3 tangent = vert1 - vert0;
					glm::vec3 bitangent = vert2 - vert0;
					glm::vec3 norm = glm::cross( tangent, bitangent );
					
					tee->addVert( vert0.x, vert0.y, vert0.z, norm.x, norm.y, norm.z, 1, 1, 1 );
					tee->addVert( vert1.x, vert1.y, vert1.z, norm.x, norm.y, norm.z, 1, 1, 1 );
					tee->addVert( vert2.x, vert2.y, vert2.z, norm.x, norm.y, norm.z, 1, 1, 1 );
					
					tee->addVert( vert0.x, vert0.y, vert0.z, norm.x, norm.y, norm.z, 1, 1, 1 );
					tee->addVert( vert2.x, vert2.y, vert2.z, norm.x, norm.y, norm.z, 1, 1, 1 );
					tee->addVert( vert3.x, vert3.y, vert3.z, norm.x, norm.y, norm.z, 1, 1, 1 );
					//tee->createYCube( 0.1f, 0.005f, vert0, vert1, color );

					teeEntity->addComponent( tee );
					level->addEntity( teeEntity );

					//build ball on tee
					Entity * ballEntity = new Entity();
					ball = new Ball( glm::vec3(x, y, z), glm::vec3( 1, 1, 1), tiles, id );
					ballEntity->addComponent( ball );
					level->addEntity( ballEntity );
					level->pickedMesh = ball->getMesh( );
					level->ball = ball;
				}
			} else if ( !type.compare( "cup" ) ) {
				if ( !course || begin_hole ) {
					Entity * cupEntity = new Entity( );
					Mesh * cup = new Mesh( );
					string str_id;
					string str_x, str_y, str_z;
					iss >> str_id;
					int i = atoi(str_id.c_str( ));
					iss >> str_x;
					iss >> str_y;
					iss >> str_z;
					float x = static_cast<float>(atof( str_x.c_str( ) ));
					float y = static_cast<float>(atof( str_y.c_str( ) ));
					float z = static_cast<float>(atof( str_z.c_str( ) ));
					//cup mesh
					glm::vec3 vert0 = glm::vec3( x-0.1f, y+0.001f, z+0.1f );
					glm::vec3 vert1 = glm::vec3( x+0.1f, y+0.001f, z+0.1f );
					glm::vec3 vert2 = glm::vec3( x+0.1f, y+0.001f, z-0.1f );
					glm::vec3 vert3 = glm::vec3( x-0.1f, y+0.001f, z-0.1f );

					glm::vec3 tangent = vert1 - vert0;
					glm::vec3 bitangent = vert2 - vert0;
					glm::vec3 norm = glm::cross( tangent, bitangent );

					cup->addVert( vert0.x, vert0.y, vert0.z, norm.x, norm.y, norm.z, 0, 0, 0 );
					cup->addVert( vert1.x, vert1.y, vert1.z, norm.x, norm.y, norm.z, 0, 0, 0 );
					cup->addVert( vert2.x, vert2.y, vert2.z, norm.x, norm.y, norm.z, 0, 0, 0 );

					cup->addVert( vert0.x, vert0.y, vert0.z, norm.x, norm.y, norm.z, 0, 0, 0 );
					cup->addVert( vert2.x, vert2.y, vert2.z, norm.x, norm.y, norm.z, 0, 0, 0 );
					cup->addVert( vert3.x, vert3.y, vert3.z, norm.x, norm.y, norm.z, 0, 0, 0 );	

					/*float edgeHeight = 0.2f;
					glm::vec3 vert1Y = vert1;
					glm::vec3 vert0Y = vert0;
					glm::vec3 vert2Y = vert2;
					glm::vec3 vert3Y = vert3;
					vert0Y.y += edgeHeight;
					vert1Y.y += edgeHeight;
					vert2Y.y += edgeHeight;
					vert3Y.y += edgeHeight;
					PlaneCollider * pCollide = new PlaneCollider ( vert0, vert1, vert1Y, vert0Y, false );
					pCollide->setParent( this );
					ball->getPhysics()->addCollider( pCollide );

					pCollide = new PlaneCollider ( vert1, vert2, vert2Y, vert1Y, false );
					pCollide->setParent( this );
					ball->getPhysics()->addCollider( pCollide );				

					pCollide = new PlaneCollider ( vert2, vert3, vert3Y, vert2Y, false );
					pCollide->setParent( this );
					ball->getPhysics()->addCollider( pCollide );

					pCollide = new PlaneCollider ( vert3, vert0, vert0Y, vert3Y, false );
					pCollide->setParent( this );
					ball->getPhysics()->addCollider( pCollide );
					//cup->createYCube( 0.3f, 0.002f, vert0, vert1, color );*/

					cupEntity->addComponent( cup );
					level->addEntity( cupEntity );
				}
			} else if ( !type.compare( "course" ) ) {
				course = true;
				string course_name, numHoles;
				iss >> course_name;
				iss >> numHoles;
				level->maxSubLevels = atoi( numHoles.c_str() ) - 1;
			} else if ( !type.compare( "begin_hole" ) ) {
				if ( skip == holeID ) {
					begin_hole = true;
				} else {
					skip++;
				}
			} else if ( !type.compare( "name" ) ) { 

			} else if ( !type.compare( "par" ) ) {

			} else if ( !type.compare( "end_hole" ) ) {
				if ( begin_hole ) 
					end_hole = true;
			} else if ( !type.empty( ) ){
				cerr << "Found a unknown class type in " << filename << endl;
				//return NULL;
			}
		}
		return level;
	} 
	return NULL;
}

Mesh * ResManager::readObjFile( string filename ) {
	Mesh * out = new Mesh( );
	//out->setSmooth( true );

	string line;
	ifstream input;
	string filePath = "Assets/Mesh/";
	input.open(filePath + filename.c_str( ));

	if ( input.fail( ) ) {
		cerr << "Unable to open object file " << filename << endl;
	} else {
		vector<glm::vec3> vertVals;
		vector<glm::vec3> colorVals;
		for( int lineNum=0; !input.eof( ); lineNum++ ) {
			getline( input, line );
			istringstream iss(line);
			string type, str_x, str_y, str_z;
			iss >> type;
			if ( !type.compare( "v" ) ) {
				iss >> str_x;
				iss >> str_y;
				iss >> str_z;
				vertVals.push_back( glm::vec3( static_cast<float>(atof(str_x.c_str( ))), 
					static_cast<float>(atof(str_y.c_str( ))),
					static_cast<float>(atof(str_z.c_str( )))) );
			} else if ( !type.compare( "c" ) ) {
				iss >> str_x;
				iss >> str_y;
				iss >> str_z;
				colorVals.push_back( glm::vec3( static_cast<float>(atof(str_x.c_str( ))), 
					static_cast<float>(atof(str_y.c_str( ))),
					static_cast<float>(atof(str_z.c_str( )))) );
			} else if ( !type.compare( "f" ) ) {
				bool read = true;
				string index_str;
				int count = 0;
				int origin;
				int point1;
				int point2;
				while ( read ) { 
					read = iss >> index_str;
					if ( read ) {
						int index = atoi( index_str.c_str( ) ) - 1;
						if ( index < static_cast<int>(vertVals.size( )) ) {
							if ( count == 0 ) {
								origin = index;
								count++;
							} else if ( count == 1 ) {
								point1 = index;
								count++;
							} else {
								point2 = index;
								glm::vec3 vert0 = glm::vec3( vertVals.at( origin ).x, vertVals.at( origin ).y, vertVals.at( origin ).z );
								glm::vec3 vert1 = glm::vec3( vertVals.at( point1 ).x, vertVals.at( point1 ).y, vertVals.at( point1 ).z );
								glm::vec3 vert2 = glm::vec3( vertVals.at( point2 ).x, vertVals.at( point2 ).y, vertVals.at( point2 ).z );
								glm::vec3 tangent = vert1 - vert0;
								glm::vec3 bitangent = vert2 - vert0;
								glm::vec3 norm = glm::cross( tangent, bitangent );
								//vert0
								if ( origin < static_cast<int>(colorVals.size( )) ) {
									out->addVert( vertVals.at( origin ).x, vertVals.at( origin ).y, vertVals.at( origin ).z, 
										norm.x, norm.y, norm.z, 
										colorVals.at( origin ).x, colorVals.at( origin ).y, colorVals.at( origin ).z );
								} else {
									out->addVert( vertVals.at( origin ).x, vertVals.at( origin ).y, vertVals.at( origin ).z, 
										norm.x, norm.y, norm.z, 
										1, 1, 1 );
								}
								//vert1
								if ( point1 < static_cast<int>(colorVals.size( )) ) {
									out->addVert( vertVals.at( point1 ).x, vertVals.at( point1 ).y, vertVals.at( point1 ).z, 
										norm.x, norm.y, norm.z, 
										colorVals.at( point1 ).x, colorVals.at( point1 ).y, colorVals.at( point1 ).z );
								} else {
									out->addVert( vertVals.at( point1 ).x, vertVals.at( point1 ).y, vertVals.at( point1 ).z, 
										norm.x, norm.y, norm.z, 
										1, 1, 1 );
								}
								//vert2
								if ( point2 < static_cast<int>(colorVals.size( )) ) {
									out->addVert( vertVals.at( point2 ).x, vertVals.at( point2 ).y, vertVals.at( point2 ).z, 
										norm.x, norm.y, norm.z, 
										colorVals.at( point2 ).x, colorVals.at( point2 ).y, colorVals.at( point2 ).z );
								} else {
									out->addVert( vertVals.at( point2 ).x, vertVals.at( point2 ).y, vertVals.at( point2 ).z, 
										norm.x, norm.y, norm.z, 
										1, 1, 1 );
								}
								point1 = point2;
								count++;
							}
						}
					}
				}
			} 
		}
	}
	return out;
}
