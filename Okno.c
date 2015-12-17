#include <stdio.h>
#include <allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_native_dialog.h> 
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

const float FPS = 60;
const int SCREEN_W = 1080;
const int SCREEN_H = 760;
const int BOUNCER_SIZE = 32;
enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
struct monster {
	char  name[50];
	int   life;
	int   level;
};  char   name;
struct building {
	char  name[50];
	float   gold_per_sec;
	float   number;
};
struct hero {
	char  name[50];
	int str;
	int hit_per_click;
};

struct helper {
	char  name[50];
	int cost;
	int number;
	int hit_per_second;
};
int main(int argc, char **argv)
{
	
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_TIMER *timer = NULL;
	bool key[4] = { false, false, false, false };
	bool redraw = true;
	bool doexit = false;
	//Tutaj bêd¹ zdefiniowane structury
	struct hero champ;
	struct building stajnia;
	struct monster cel;
	struct helper zbrojny;
	strcpy_s(champ.name, _countof(champ.name), "wow");
	champ.str=1;
	champ.hit_per_click = 1;

	strcpy_s(stajnia.name, _countof(stajnia.name), "stajnia");
	stajnia.number = 0;
	stajnia.gold_per_sec = 0.1;
	
	strcpy_s(cel.name, _countof(cel.name), "cel");
	cel.life= 2;
	cel.level = 1;
	strcpy_s(zbrojny.name, _countof(zbrojny.name), "zbrojny");
	zbrojny.cost=10;
	zbrojny.number=0;
	zbrojny.hit_per_second=1;

	al_init_font_addon();
	al_init_image_addon();
	al_init_ttf_addon();
	//sprawdzenie poszczególnych elementów
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -2;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}
	ALLEGRO_BITMAP *monster = al_load_bitmap("monster.bmp");
	al_convert_mask_to_alpha(monster, al_map_rgb(0, 0, 255));
	if (!monster) {
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -2;
	}
	ALLEGRO_BITMAP *monster2 = al_load_bitmap("monster2.bmp");
	al_convert_mask_to_alpha(monster2, al_map_rgb(0, 0, 255));
	if (!monster2) {
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -2;
	}
	ALLEGRO_BITMAP *panel = al_load_bitmap("guziki.bmp");
	if (!panel) {
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -3;
	}
	ALLEGRO_BITMAP *tlo = al_load_bitmap("tlo.jpg");
	if (!tlo) {
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -4;
	}
	ALLEGRO_FONT *font = al_load_ttf_font("GOTHIC.TTF", 36, 0);
	if (!font){
		fprintf(stderr, "Could not load 'pirulen.ttf'.\n");
		return -1;
	}

	float points = 0;
	int tick=0;
	int gold_income=0;
	int licznik = 0;
	int zdrowie=cel.life;
	int sila = champ.str;
	int swap = 1;
	bool done = false;
	int x = 10, y = 10, moveSpeed = 5;
	al_init_primitives_addon();
	al_install_mouse();
	//kolejka eventów
	ALLEGRO_EVENT_QUEUE  *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	ALLEGRO_COLOR electricalBlue = al_map_rgb(44, 117, 255);
	ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
	ALLEGRO_COLOR playerColor = al_map_rgb(44, 117, 255);
	//al_hide_mouse_cursor(display);
	al_start_timer(timer);
	while (!done)
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);
		licznik = (licznik + 1);
		if (licznik % 60 == 0){
			licznik = 0;
			points = points + (stajnia.gold_per_sec*stajnia.number);
			//zdrowie = zdrowie - (zbrojny.number*zbrojny.hit_per_second);
			sila = sila + zbrojny.number;
		}
		if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (events.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			x = events.mouse.x;
			y = events.mouse.y;
		}
		else if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			//tu te¿ jest potwór
			if (events.mouse.button & 1 && x > 50 && x<200 && y>50 && y<400)

				zdrowie = zdrowie - sila;
			//tu jest potwór	
			if (events.mouse.button & 2 && x>50 && x<200 && y>50 && y<400)
				points = points + sila;
			if (events.mouse.button & 1 && x>300 && x<400 && y>50 && y<150 && points>=10)
			{

				points = points - 10;
				stajnia.number++;
			}
			if (events.mouse.button & 1 && x>300 && x<550 && y>50 && y<100 && points >= 10)
			{

				points = points - 10;
				stajnia.number++;
			}
			if (events.mouse.button & 1 && x>600 && x<900 && y>50 && y<100 && points >= 20)
			{

				points = points - 20;
				zbrojny.number++;
			}
	
		}
		if (zdrowie <= 0){
			zdrowie = cel.life;
			swap = swap + 1;
			points = points + 1;
			
		}
		
		al_draw_bitmap(tlo, 0, 0, 0);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 50,700, 0, "Punktacja: %.2f",points);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 70, 330, 0, "zdrowie %i", zdrowie);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 500, 700, 0, "x,y %i,%i", x,y);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 500, 60, 0, " %.0f", stajnia.number);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 800, 60, 0, " %i",zbrojny.number);
		al_draw_bitmap(panel,300, 50, 0);
		if (swap % 2 == 0){
			al_draw_bitmap(monster2, 50, 50, 0);
			al_flip_display();
		}
		else
			al_draw_bitmap(monster, 50, 50, 0);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_shutdown_image_addon();
	return 0;
}