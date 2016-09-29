#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1FileSystem.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;

	// TODO 6: Iterate all tilesets and draw all their 
	// images in 0,0 (you should have only one tileset for now)
	for (int i = 0; i < tilesets.Count(); i++) {
		App->render->Blit(Map1_texture, 0, 0);
	}

}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map

	map_layers.Clear();

	// Remove all tilesets
	tilesets.Clear();

	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	char* buf;
	int size = App->fs->Load(tmp.GetString(), &buf);
	pugi::xml_parse_result result = map_file.load_buffer(buf, size);

	RELEASE(buf);

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	if(ret == true)
	{
		// TODO 3: Create and call a private function to load and fill
		// all your map data
		if (LoadMapNode() == 0) 
			LOG("Error Loading MapNode");
		
	}

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!
	if (LoadTileSet() == 0) 
		LOG("Error Loading TileSet");
	

	// TODO 5: LOG all the data loaded
	// iterate all tilesets and LOG everything

	map_loaded = ret;

	return ret;
}

bool j1Map::LoadMapNode()
{
	bool ret = true;

	map_node.version = map_file.child("map").attribute("version").as_float();
	if (map_file.child("map").attribute("orientation").as_string() == "orthogonal") {
		map_node.orientation = Orthogonal;
	} else
	if (map_file.child("map").attribute("orientation").as_string() == "isometric") {
		map_node.orientation = Isometric;
	}
	
	if (map_file.child("map").attribute("renderorder").as_string() == "right-up") {
		map_node.renderorder = Right_up;
	} else
	if (map_file.child("map").attribute("renderorder").as_string() == "right-down") {
		map_node.renderorder = Right_down;
	} else 
	if (map_file.child("map").attribute("renderorder").as_string() == "left-up") {
		map_node.renderorder = Left_up;
	} else
	if (map_file.child("map").attribute("renderorder").as_string() == "left-down") {
		map_node.renderorder = Left_down;
	}

	map_node.width = map_file.child("map").attribute("width").as_int();
	map_node.heigth = map_file.child("map").attribute("height").as_int();
	map_node.tilewidth = map_file.child("map").attribute("tilewidth").as_int();
	map_node.tileheigth = map_file.child("map").attribute("tileheight").as_int();
	map_node.nextobjectid = map_file.child("map").attribute("nextobjectid").as_int();

	Map1_texture = App->tex->Load("maps/tmw_desert_spacing.png");

	return ret;
}

bool j1Map::LoadTileSet()
{
	bool ret = true;

	TileSet newTS;
	
	newTS.firstgid = map_file.child("tileset").attribute("firstgid").as_uint();
	newTS.name = (char*)map_file.child("tileset").attribute("name").as_string();
	newTS.tilewidth = map_file.child("tileset").attribute("tilewidth").as_uint();
	newTS.tileheigth = map_file.child("tileset").attribute("tileheigth").as_uint();
	newTS.spacing = map_file.child("tileset").attribute("spacing").as_uint();
	newTS.margin = map_file.child("tileset").attribute("margin").as_uint();
	
	tilesets.PushBack(newTS);

	return ret;
}


