
#ifndef TILE_H
#define TILE_H

#include <string>
#include <vector>

#include "Edge.h"
using namespace std;
/**
  * class Tile
  * 
  */

/******************************* Abstract Class ****************************
Tile does not have any pure virtual methods, but its author
  defined it as an abstract class, so you should not use it directly.
  Inherit from it instead and create only objects from the derived classes
*****************************************************************************/

class Tile
{
public:

    // Constructors/Destructors
    //  


    /**
     * Empty Constructor
     */
    Tile ( );

    /**
     * Empty Destructor
     */
    virtual ~Tile ( );

    // Static Public attributes
    //  

    // Public attributes
    //  


    // Public attribute accessor methods
    //  


    // Public attribute accessor methods
    //  


protected:

    // Static Protected attributes
    //  

    // Protected attributes
    //  

public:


    // Protected attribute accessor methods
    //  

protected:

public:


    // Protected attribute accessor methods
    //  

protected:


private:

    // Static Private attributes
    //  

    // Private attributes
    //  

    vector<Edge> edges;
public:


    // Private attribute accessor methods
    //  

private:

public:


    // Private attribute accessor methods
    //  


    /**
     * Set the value of edges
     * @param new_var the new value of edges
     */
    void setEdges ( vector<Edge> new_var )     {
            edges = new_var;
    }

    /**
     * Get the value of edges
     * @return the value of edges
     */
    vector<Edge> getEdges ( ) {
        return edges;
    }
private:


    void initAttributes ( ) ;

};

#endif // TILE_H
