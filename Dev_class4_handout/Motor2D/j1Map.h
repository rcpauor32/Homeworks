#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "p2DynArray.h"

// TODO 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!

struct TileSet {
	uint firstgid;
	char* name;
	uint tilewidth;
	uint tileheigth;
	uint spacing;
	uint margin;

};

// TODO 1: Create a struct needed to hold the information to Map node
struct MapLayer {
	char* name;
	uint width;
	uint height;
	struct Data {
		uint* tiles;
	}data;

	~MapLayer() {
		name = nullptr;
		width = NULL;
		height = NULL;
		data.tiles = nullptr;
	}

};

enum Orientation { Orthogonal = 0, Isometric, Isometric_staggered, Hexagonal_staggered };
enum RenderOrder { Right_down = 0, Right_up, Left_down, Left_up };

struct MapNode {
	float version;
	Orientation orientation;
	RenderOrder renderorder;
	uint width;
	uint heigth;
	uint tilewidth;
	uint tileheigth;
	uint nextobjectid;
};

// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

private:
	bool LoadMapNode();

	bool LoadTileSet();

public:

	// TODO 1: Add your struct for map info as public for now
	MapNode map_node;
	p2DynArray<TileSet> tilesets;

	p2DynArray<MapLayer> map_layers;
	
	SDL_Texture* Map1_texture = nullptr;

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__