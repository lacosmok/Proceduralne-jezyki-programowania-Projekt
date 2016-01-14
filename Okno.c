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
	float cost;
	float number;
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
	struct monster cel;

	strcpy_s(champ.name, _countof(champ.name), "wow");
	champ.str=1;
	champ.hit_per_click = 1;
	//budynki
	struct building stajnia;
	strcpy_s(stajnia.name, _countof(stajnia.name), "stajnia");
	stajnia.number = 0;
	stajnia.gold_per_sec = 0.1;
	struct building karczma;
	strcpy_s(karczma.name, _countof(karczma.name), "karczma");
	karczma.number = 0;
	karczma.gold_per_sec = 1;
	struct building warsztat;
	strcpy_s(warsztat.name, _countof(warsztat.name), "warsztat");
	warsztat.number = 0;
	warsztat.gold_per_sec = 10;
	struct building forteca;
	strcpy_s(forteca.name, _countof(forteca.name), "forteca");
	forteca.number = 0;
	forteca.gold_per_sec = 100;
	struct building gildia;
	strcpy_s(gildia.name, _countof(gildia.name), "gildia");
	gildia.number = 0;
	gildia.gold_per_sec = 1000;
	struct building kapitol;
	strcpy_s(kapitol.name, _countof(kapitol.name), "kapitol");
	kapitol.number = 0;
	kapitol.gold_per_sec = 50000;

	strcpy_s(cel.name, _countof(cel.name), "cel");
	cel.life= 2;
	cel.level = 1;
	//pomocnicy
	struct helper zbrojny;
	strcpy_s(zbrojny.name, _countof(zbrojny.name), "zbrojny");
	zbrojny.cost=10;
	zbrojny.number=0;
	zbrojny.hit_per_second=1;
	struct helper lucz;
	strcpy_s(lucz.name, _countof(lucz.name), "³uczniczka");
	lucz.cost = 10;
	lucz.number = 0;
	lucz.hit_per_second = 1;
	struct helper balista;
	strcpy_s(balista.name, _countof(balista.name), "balista");
	balista.cost = 10;
	balista.number = 0;
	balista.hit_per_second = 1;
	struct helper rycerz;
	strcpy_s(rycerz.name, _countof(rycerz.name), "rycerz");
	rycerz.cost = 10;
	rycerz.number = 0;
	rycerz.hit_per_second = 1;
	struct helper czarnoksieznik;
	strcpy_s(czarnoksieznik.name, _countof(czarnoksieznik.name), "czarnoksieznik");
	czarnoksieznik.cost = 10;
	czarnoksieznik.number = 0;
	czarnoksieznik.hit_per_second = 1;
	struct helper minister;
	strcpy_s(minister.name, _countof(minister.name), "minister");
	minister.cost = 10;
	minister.number = 0;
	minister.hit_per_second = 1;

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
	ALLEGRO_BITMAP *tlo = al_load_bitmap("tlo2.bmp");
	if (!tlo) {
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -4;
	}
	ALLEGRO_BITMAP *tlo2 = al_load_bitmap("tlo.jpg");
	if (!tlo2) {
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -5;
	}
	ALLEGRO_BITMAP *do_gry = al_load_bitmap("Do_Gry.bmp");
	if (!do_gry) {
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -5;
	}
	ALLEGRO_BITMAP *co_robie = al_load_bitmap("Co_robie.bmp");
	if (!co_robie) {
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -5;
	}
	ALLEGRO_FONT *font = al_load_ttf_font("GOTHIC.TTF", 36, 0);
	if (!font){
		fprintf(stderr, "Could not load 'pirulen.ttf'.\n");
		return -1;
	}
	//Zmienne u¿ywane w programie
	float points = 0;
	int tick=0;
	int gold_income=0;
	int licznik = 0;
	int zdrowie=cel.life;
	int sila = champ.str;
	int swap = 1;  //zmienna do zmieniania potworów
	int k = 1;
	int zabite = 0;
	bool ekran_powitalny = true; //zmienna do zmieniania ekranu
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
		//tutaj dzieje sie ca³a mechanika gry generalnie
		licznik = (licznik + 1);
		if (licznik % 60 == 0){
			licznik = 0;
			points = points + (stajnia.gold_per_sec*stajnia.number) + (karczma.gold_per_sec*karczma.number) + (warsztat.gold_per_sec*warsztat.number);
			points = points + (gildia.gold_per_sec*gildia.number) + (forteca.gold_per_sec*forteca.number) + (kapitol.gold_per_sec*kapitol.number);
			points = points + minister.number * 10000;
			//zdrowie = zdrowie - (zbrojny.number*zbrojny.hit_per_second);
			sila = sila+zbrojny.number+lucz.number*10+balista.number*50+rycerz.number*150+czarnoksieznik.number*350+minister.number*-500;
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
			//budynki
			if (events.mouse.button & 1 && x>310 && x<530 && y>110 && y<150 && points >= 10)
			{
				points = points - 10;
				stajnia.number++;
			}
			if (events.mouse.button & 1 && x>310 && x<530 && y>170 && y<210 && points >= 100)
			{
				points = points - 100;
				karczma.number++;
			}
			if (events.mouse.button & 1 && x>310 && x<530 && y>230 && y<270 && points >= 1000)
			{
				points = points - 1000;
				warsztat.number++;
			}
			if (events.mouse.button & 1 && x>310 && x<530 && y>290 && y<340 && points >= 10000)
			{
				points = points - 10000;
				forteca.number++;
			}
			if (events.mouse.button & 1 && x>310 && x<530 && y>360 && y<400 && points >= 100000)
			{
				points = points - 100000;
				gildia.number++;
			}
			if (events.mouse.button & 1 && x>310 && x<530 && y>420 && y<460 && points >= 1000000)
			{
				points = points - 1000000;
				kapitol.number++;
			}
		// tu sa juz helperzy
			if (events.mouse.button & 1 && x>650 && x<900 && y>110 && y<150 && points >= 5)
			{
				points = points - 5;
				zbrojny.number++;
			}
			if (events.mouse.button & 1 && x>650 && x<900 && y>170 && y<210 && points >= 20)
			{
				points = points - 20;
				lucz.number++;
			}
			if (events.mouse.button & 1 && x>650 && x<900 && y>230 && y<270 && points >= 50)
			{
				points = points - 50;
				balista.number++;
			}
			if (events.mouse.button & 1 && x>650 && x<900 && y>290 && y<340 && points >= 150)
			{
				points = points - 150;
				rycerz.number++;
			}
			if (events.mouse.button & 1 && x>650 && x<900 && y>360 && y<400 && points >= 350)
			{
				points = points - 350;
				czarnoksieznik.number++;
			}
			if (events.mouse.button & 1 && x>650 && x<900 && y>420 && y<460 && points >= 5000)
			{
				points = points - 5000;
				minister.number++;
			}
			//zmiana ekranów
			if (events.mouse.button & 1 && x>700 && x<990 && y>650 && y < 700 && ekran_powitalny == true)
			{
				ekran_powitalny = false;
			}
			else if (events.mouse.button & 1 && x>700 && x<990 && y>650 && y < 700 && ekran_powitalny == false)
			{
				ekran_powitalny = true;
			}
		}
		//zmiana zdrowia potworów
		if (zdrowie <= 0){
			zdrowie = cel.life;
			cel.life = cel.life + k;
			zabite = zabite + 1;
			if (zabite % 10 == 0){
				k++;
			}
			swap = swap + 1;
			points = points + 1000;

		}
		//a tu jest z kolei generowanie wszystkiego
		if (ekran_powitalny == true){  //tu jest ekran startowy
			al_draw_bitmap(tlo2, 0, 0, 0);
			al_draw_bitmap(do_gry, 700, 650, 0);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 500, 700, 0, "x,y %i,%i,%d", x, y,ekran_powitalny);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			
		}
		else        //a tu ekran w³aœciwej gry generalnie
		{
			al_draw_bitmap(tlo, 0, 0, 0);
			al_draw_bitmap(panel, 300, 50, 0);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 50, 700, 0, "Punktacja: %.2f", points);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 70, 330, 0, "zdrowie %i", zdrowie);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 500, 700, 0, "x,y %i,%i", x, y);
			//wyswietlanie budynkow
			al_draw_textf(font, al_map_rgb(255, 255, 255), 450, 110, 0, " %.0f", stajnia.number);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 450, 170, 0, " %.0f", karczma.number);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 450, 230, 0, " %.0f", warsztat.number);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 450, 290, 0, " %.0f", forteca.number);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 450, 350, 0, " %.0f", gildia.number);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 450, 410, 0, " %.0f", kapitol.number);

			al_draw_textf(font, al_map_rgb(255, 255, 255), 560, 110, 0, " %.0f", stajnia.gold_per_sec);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 560, 170, 0, " %.0f", karczma.gold_per_sec);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 560, 230, 0, " %.0f", warsztat.gold_per_sec);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 560, 290, 0, " %.0f", forteca.gold_per_sec);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 560, 350, 0, " %.0f", gildia.gold_per_sec);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 560, 410, 0, " %.0f", kapitol.gold_per_sec);
			//wyswietlanie pomocnikow
			al_draw_textf(font, al_map_rgb(255, 255, 255), 800, 110, 0, " %.0f", zbrojny.number);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 800, 170, 0, " %.0f", lucz.number);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 800, 230, 0, " %.0f", balista.number);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 800, 290, 0, " %.0f", rycerz.number);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 800, 350, 0, " %.0f", czarnoksieznik.number);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 800, 410, 0, " %.0f", minister.number);
			
			al_draw_textf(font, al_map_rgb(255, 255, 255), 900, 110, 0, " %.i", zbrojny.hit_per_second);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 900, 170, 0, " %.i", lucz.hit_per_second);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 900, 230, 0, " %.i", balista.hit_per_second);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 900, 290, 0, " %.i", rycerz.hit_per_second);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 900, 350, 0, " %.i", czarnoksieznik.hit_per_second);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 900, 410, 0, " %.i", minister.hit_per_second);

			al_draw_bitmap(co_robie, 700, 650, 0);
			if (swap % 2 == 0){
				al_draw_bitmap(monster2, 50, 50, 0);
				al_flip_display();
			}
			else
			al_draw_bitmap(monster, 50, 50, 0);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_shutdown_image_addon();
	return 0;
}