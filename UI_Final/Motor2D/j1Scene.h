#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;

class Image;
class Label;
class Text_Box;
class Button;
class Window;
class Selector;
class Windowed_Image;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

private:

	SDL_Texture* debug_tex;

	Window* window;
	Label* win_title;

	Button* button1;
	Label* but1_text;
	Image* scroll_bar;
	Button* scroll_but;
	Label* description;

	Image* box_name;
	Text_Box* type_name;

	uint ActiveTab = 1;

	Image* Background;
	Selector* P1Selector;
	Selector* P2Selector;

	Windowed_Image* champs;
	Windowed_Image* champs2;

	Image* champ1;
	Image* champ2;
	Image* champ3;	
	Image* champ4;
	Image* champ5;
	Image* champ6;
	Image* champ7;
	Image* champ8;
	Image* champ9;
	Image* champ10;



};

#endif // __j1SCENE_H__