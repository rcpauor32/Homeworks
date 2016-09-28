#pragma once
#include "Module.h"
#include "Globals.h"

class b2World;
class b2BodyDef;
class b2Body;
class b2CircleShape;

class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

private:
	b2World* world = nullptr;
	b2BodyDef* groundBodyDef;
	b2Body* groundBody = nullptr;
	b2CircleShape* groundCircle;
	bool debug;
	float timestep = 1.0f / 60.0f;
	int velocity_iterations = 8;
	int position_iterations = 3;

};