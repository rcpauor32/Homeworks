#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1Scene.h"
#include "j1Fonts.h"

#define MAX_TABS 2

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	// TODO 3: Creating Elements ---------------------------

	//scroll_bar = (Image*)App->gui->Create_Element("scroll_bar", IMAGE, { 680, 360 }, { 974, 786, 10, 162 });
	//scroll_but = (Button*)App->gui->Create_Element("scroll_but", BUTTON, { 673, 355 }, { 1000, 430, 20, 30 });
	//button1 = (Button*)App->gui->Create_Element("button_1", BUTTON, { 400, 280 }, { 646, 170, 222, 64 });
	//but1_text = (Label*)App->gui->Create_Element("but1_text", LABEL, { 420, 302 }, { 0, 0, 0, 0 }, "Button", App->font->default);
	//window = (Window*)App->gui->Create_Element("window", WINDOW, { 300, 120 }, { 30, 544, 423, 454 });
	//win_title = (Label*)App->gui->Create_Element("win_title", LABEL, { 450, 150 }, { 0, 0, 0, 0 }, "Window Title", App->font->title);

	//char* text = "In literary theory, a text is any object that can be read, whether this object is a work of literature, a street sign, an arrangement of buildings on a city block, or styles of clothing.\n\n\n\n";
	//description = (Label*)App->gui->Create_Element("description", LABEL, { 350, 360 }, { 0, 0, 0, 0 }, text, App->font->title);
	//description->rect.h = 155;

	//EXERCISE 1
	Background = (Image*)App->gui->Create_Element("BackgroundImage", IMAGE, { 0, 0 }, { 0, 1600, 1024, 576 });
	window = (Window*)App->gui->Create_Element("window", WINDOW, { 252, 80 }, { 0, 512, 483, 512 });
	win_title = (Label*)App->gui->Create_Element("win_title", LABEL, { 400, 140 }, { 0, 0, 0, 0 }, "select Your Character", App->font->title);
	button1 = (Button*)App->gui->Create_Element("button_1", BUTTON, { 380, 480 }, { 645,165,229,69 });
	but1_text = (Label*)App->gui->Create_Element("but1_text", LABEL, { 410, 490 }, { 0, 0, 0, 0 }, "Continue", App->font->default);
	
	//EXERCISE 2
	champs = (Windowed_Image*)App->gui->Create_Element("champs", WINDOWED_IMAGE, { 0,  180 }, { 0, 1024, 1025, 287 });
	champs2 = (Windowed_Image*)App->gui->Create_Element("champs2", WINDOWED_IMAGE, { 1025,  180 }, { 0, 1311, 1025, 287 });
	
	scroll_but = (Button*)App->gui->Create_Element("scroll_but", BUTTON, { 410, 180 }, { 0, 0, 205, 287 });
	scroll_but->Attach(champs);
	scroll_but->Attach(champs2);

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	
	Background->Draw();
	window->Draw();
	win_title->Draw();
	button1->Draw();
	but1_text->Draw();
	

	champs->Draw();
	//champs->ChangeImage();
	champs2->Draw();

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
