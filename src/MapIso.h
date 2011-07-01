/**
 * class MapIso
 *
 * Isometric map data structure and rendering
 *
 * @author Clint Bellanger
 * @license GPL
 */

#ifndef MAP_ISO_H
#define MAP_ISO_H

#include <fstream>
#include <string>
#include <queue>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Utils.h"
#include "TileSet.h"
#include "MapCollision.h"
#include "Settings.h"
#include "CampaignManager.h"
#include "EnemyGroupManager.h"
#include "InputState.h"

using namespace std;

struct Map_Enemy {
	string type;
	Point pos;
	int direction;
};

struct Map_Group {
	string category;
	Point pos;
	Point area;
	int levelmin;
	int levelmax;
	int number;
};

struct Map_NPC {
	string id;
	Point pos;
};

struct Map_Event {
	string type;
	SDL_Rect location;
	Event_Component components[8];
	int comp_num;
	SDL_Rect hotspot;
	string tooltip;
};

const int CLICK_RANGE = 3 * UNITS_PER_TILE;

class MapIso {
private:
	SDL_Surface *screen;
	InputState *inp;
	Mix_Music *music;

	// map events can play random soundfx
	Mix_Chunk *sfx;
	string sfx_filename;
	
	void executeEvent(int eid);
	void removeEvent(int eid);
	void playSFX(string filename);
	void push_enemy_group(Map_Group g);
		
	// map events
	Map_Event events[256];
	int event_count;
	
public:

	CampaignManager *camp;

	// functions
	MapIso(SDL_Surface *_screen, CampaignManager *_camp, InputState *_inp);
	~MapIso();
	void clearEnemy(Map_Enemy e);
	void clearNPC(Map_NPC n);
	void clearGroup(Map_Group g);

	int load(string filename);
	void loadMusic();
	void logic();
	void render(Renderable r[], int rnum);
	void checkEvents(Point loc);
	void checkEventClick();
	void clearEvents();

	// vars
	string title;
	int w;
	int h;
	Point cam;
	Point hero_tile;
	Point spawn;
	int spawn_dir;
	string tileset;
	string music_filename;
	bool new_music;
	TileSet tset;
	
	unsigned short background[256][256];
	unsigned short object[256][256];
	unsigned short collision[256][256];
	MapCollision collider;

	// enemy load handling
	queue<Map_Enemy> enemies;
	Map_Enemy new_enemy;
	Map_Group new_group;
	bool enemy_awaiting_queue;
	bool group_awaiting_queue;
	
	// npc load handling
	queue<Map_NPC> npcs;
	Map_NPC new_npc;
	bool npc_awaiting_queue;
	
	// event-created loot or items
	queue<Event_Component> loot;

	// teleport handling
	bool teleportation;
	Point teleport_destination;
	string teleport_mapname;
	string respawn_map;
	Point respawn_point;
	
	// message handling
	string log_msg;
	
	// shaky cam
	int shaky_cam_ticks;
	
};


#endif
