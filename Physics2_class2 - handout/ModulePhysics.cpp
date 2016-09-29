#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "math.h"

#include "Box2D/Box2D/Box2D.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));

	// big static circle as "ground" in the middle of the screen
	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 1.5f;
	int diameter = SCREEN_WIDTH / 2;

	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(diameter) * 0.5f;

	b2FixtureDef fixture;
	fixture.shape = &shape;
	b->CreateFixture(&fixture);

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	// On space bar press, create a circle on mouse position
	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		CreateCircle(25);
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		// TODO 1: When pressing 2, create a box on the mouse position
		CreateBox(1.0f, 0.5f);
		// TODO 2: To have the box behave normally, set fixture's density to 1.0f
	}

	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// TODO 3: Create a chain shape using those vertices
		// remember to convert them from pixels to meters!
		
		int points[24] = {
			-38, 80,
			-44, -54,
			-16, -60,
			-16, -17,
			19, -19,
			19, -79,
			61, -77,
			57, 73,
			17, 78,
			20, 16,
			-25, 13,
			-9, 72
		};

		CreateLoopChain(points, 24);

		//int rick_head[74] = {
		//	46, 133,
		//	34, 139,
		//	38, 127,
		//	21, 126,
		//	30, 115,
		//	8, 103,
		//	24, 91,
		//	-1, 77,
		//	27, 62,
		//	11, 35,
		//	41, 38,
		//	42, 21,
		//	40, -1,
		//	60, 13,
		//	74, 30,
		//	81, 18,
		//	88, 1,
		//	94, 18,
		//	94, 38,
		//	114, 33,
		//	105, 58,
		//	109, 63,
		//	119, 66,
		//	109, 74,
		//	110, 85,
		//	105, 93,
		//	110, 99,
		//	103, 105,
		//	101, 116,
		//	108, 121,
		//	105, 127,
		//	99, 127,
		//	96, 139,
		//	83, 148,
		//	70, 149,
		//	56, 145,
		//	46, 133
		//};
		//
		//CreateLoopChain(rick_head, 74);

	}

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				// Draw circles ------------------------------------------------
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// Draw polygons ------------------------------------------------
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
					int32 count = polygonShape->GetVertexCount();
					b2Vec2 prev, v;

					for(int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->GetVertex(i));
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->GetVertex(0));
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
				}
				break;

				// Draw chains contour -------------------------------------------
				case b2Shape::e_chain:
				{
					b2ChainShape* shape = (b2ChainShape*)f->GetShape();
					b2Vec2 prev, v;

					for(int32 i = 0; i < shape->m_count; ++i)
					{
						v = b->GetWorldPoint(shape->m_vertices[i]);
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
				}
				break;

				// Draw a single segment(edge) ----------------------------------
				case b2Shape::e_edge:
				{
					b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
					b2Vec2 v1, v2;

					v1 = b->GetWorldPoint(shape->m_vertex0);
					v1 = b->GetWorldPoint(shape->m_vertex1);
					App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
				}
				break;
			}
		}
	}

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}

void ModulePhysics::CreateCircle(float new_radius = 0)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	float radius = PIXEL_TO_METERS(new_radius);
	body.position.Set(PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = radius;
	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);
}

void ModulePhysics::CreateBox(float width, float heigth)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()));

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape shape;
	shape.SetAsBox(width, heigth);
	b2FixtureDef fixture;
	fixture.shape = &shape;

	fixture.density = 1.0f;
	b->CreateFixture(&fixture);
}

void ModulePhysics::CreateLoopChain(int * points, uint size)
{

	uint vec_size = size / 2;

	b2Vec2* vectors = new b2Vec2[vec_size];

	b2ChainShape chain;
	
	uint point_it = 0;

	for (uint i = 0; i < vec_size; i++) {
		vectors[i].Set(PIXEL_TO_METERS(points[point_it++]), PIXEL_TO_METERS(points[point_it++]));
	}
	
	chain.CreateLoop(vectors, 12);

	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()));

	b2Body* b = world->CreateBody(&body);

	b2FixtureDef fixture;
	fixture.shape = &chain;

	b->CreateFixture(&fixture);

}

void ModulePhysics::CreateLoopChain(float * points, uint size)
{
	b2Vec2* vectors = new b2Vec2[size];

	b2ChainShape chain;

	uint point_it = 0;

	for (uint i = 0; i < size / 2; i++) {
		vectors[i].Set(points[point_it++], points[point_it++]);
	}

	chain.CreateLoop(vectors, 12);

	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()));

	b2Body* b = world->CreateBody(&body);

	b2FixtureDef fixture;
	fixture.shape = &chain;

	b->CreateFixture(&fixture);
}

/*
// Pivot 0, 0
int rick_head[74] = {
46, 133,
34, 139,
38, 127,
21, 126,
30, 115,
8, 103,
24, 91,
-1, 77,
27, 62,
11, 35,
41, 38,
42, 21,
40, -1,
60, 13,
74, 30,
81, 18,
88, 1,
94, 18,
94, 38,
114, 33,
105, 58,
109, 63,
119, 66,
109, 74,
110, 85,
105, 93,
110, 99,
103, 105,
101, 116,
108, 121,
105, 127,
99, 127,
96, 139,
83, 148,
70, 149,
56, 145,
46, 133
};

// Pivot 0.000000, 0.000000
float rick_head[74] = {
0.393162f, 0.886667f,
0.290598f, 0.926667f,
0.324786f, 0.846667f,
0.179487f, 0.840000f,
0.256410f, 0.766667f,
0.068376f, 0.686667f,
0.205128f, 0.606667f,
-0.008547f, 0.513333f,
0.230769f, 0.413333f,
0.094017f, 0.233333f,
0.350427f, 0.253333f,
0.358974f, 0.140000f,
0.341880f, -0.006667f,
0.512821f, 0.086667f,
0.632479f, 0.200000f,
0.692308f, 0.120000f,
0.752137f, 0.006667f,
0.803419f, 0.120000f,
0.803419f, 0.253333f,
0.974359f, 0.220000f,
0.897436f, 0.386667f,
0.931624f, 0.420000f,
1.017094f, 0.440000f,
0.931624f, 0.493333f,
0.940171f, 0.566667f,
0.897436f, 0.620000f,
0.940171f, 0.660000f,
0.880342f, 0.700000f,
0.863248f, 0.773333f,
0.923077f, 0.806667f,
0.897436f, 0.846667f,
0.846154f, 0.846667f,
0.820513f, 0.926667f,
0.709402f, 0.986667f,
0.598291f, 0.993333f,
0.478632f, 0.966667f,
0.393162f, 0.886667f
};
*/
