#include <pebble.h>

#define M1A GRect(103,6,35,7)
#define M1A_COLLAPSED GRect(138,6,0,7)
#define M1B GRect(131,13,7,13)
#define M1B_COLLAPSED GRect(131,13,7,0)
#define M2 GRect(131,26,7,39)
#define M3 GRect(131,65,7,38)
#define M4 GRect(131,103,7,39)
#define M5A GRect(131,142,7,20)
#define M5A_COLLAPSED GRect(131,162,7,0)
#define M5B GRect(103,155,28,7)
#define M5B_COLLAPSED GRect(131,155,0,7)
#define M6 GRect(41,155,62,7)
#define M7A GRect(6,155,35,7)
#define M7A_COLLAPSED GRect(6,155,0,7)
#define M7B GRect(6,142,7,13)
#define M7B_COLLAPSED GRect(6,155,7,0)
#define M8 GRect(6,103,7,39)
#define M9 GRect(6,65,7,38)
#define M10 GRect(6,26,7,39)
#define M11A GRect(6,6,7,26)
#define M11A_COLLAPSED GRect(6,6,7,0)
#define M11B GRect(13,6,28,7)
#define M11B_COLLAPSED GRect(13,6,0,7)
#define M12 GRect(41,6,62,7)
	
#define H1A GRect(97,19,28,7)
#define H1A_COLLAPSED GRect(125,19,0,7)
#define H1B GRect(118,26,7,8)
#define H1B_COLLAPSED GRect(118,26,7,0)
#define H2 GRect(118,34,7,36)
#define H3 GRect(118,70,7,28)
#define H4 GRect(118,98,7,36)
#define H5A GRect(118,134,7,15)
#define H5A_COLLAPSED GRect(118,149,7,0)
#define H5B GRect(97,142,21,7)
#define H5B_COLLAPSED GRect(118,142,0,7)
#define H6 GRect(47,142,50,7)
#define H7A GRect(19,142,28,7)
#define H7A_COLLAPSED GRect(19,142,0,7)
#define H7B GRect(19,134,7,8)
#define H7B_COLLAPSED GRect(19,142,7,0)
#define H8 GRect(19,89,7,36)
#define H9 GRect(19,70,7,28)
#define H10 GRect(19,34,7,36)
#define H11A GRect(19,19,7,15)
#define H11A_COLLAPSED GRect(19,19,7,0)
#define H11B GRect(26,19,21,7)
#define H11B_COLLAPSED GRect(26,19,0,7)
#define H12 GRect(47,19,50,7)
	
Window *window;
GBitmap *bg_bitmap;
BitmapLayer *bg_layer;
InverterLayer *block_h_a, *block_h_b, *block_m_a, *block_m_b;

void on_animation_stopped(Animation *anim, bool finished, void *context)
{
    // free the memory used by the Animation
    property_animation_destroy((PropertyAnimation*) anim);
}
 
void animate_layer(Layer *layer, GRect *start, GRect *finish, int duration, int delay)
{
    // declare animation
    PropertyAnimation *anim = property_animation_create_layer_frame(layer, start, finish);
     
    // set characteristics
    animation_set_duration((Animation*) anim, duration);
    animation_set_delay((Animation*) anim, delay);
     
    // set stopped handler to free memory
    AnimationHandlers handlers = {
        // the reference to the stopped handler is the only one in the array
        .stopped = (AnimationStoppedHandler) on_animation_stopped
    };
    animation_set_handlers((Animation*) anim, handlers, NULL);
     
    //Start animation!
    animation_schedule((Animation*) anim);
}

void setHour(int hour) {
	// convert hour to 12hour based
	if (hour > 12) {
		hour = hour - 12;
	}
	if (hour == 0) {
		hour = 12;
	}
	switch (hour)
	{
		case 1: 
		{
			GRect start = H12;
			GRect end = H1A;
			animate_layer((Layer*)block_h_a, &start, &end, 300, 0);
			GRect start_b = H1B_COLLAPSED;
			GRect end_b = H1B;
			animate_layer((Layer*)block_h_b, &start_b, &end_b, 100, 400);
			break;
		}
		case 2:
		{
			GRect start = H1A;
			GRect end = H1A_COLLAPSED;
			animate_layer((Layer*)block_h_a, &start, &end, 100, 0);
			GRect start_b = H1B;
			GRect end_b = H2;
			animate_layer((Layer*)block_h_b, &start_b, &end_b, 300, 100);
			break;
		}case 3:
		{
			GRect start = H2;
			GRect end = H3;
			animate_layer((Layer*)block_h_b, &start, &end, 300, 0);
			break;
		}
		case 4:
		{
			GRect start = H3;
			GRect end = H4;
			animate_layer((Layer*)block_h_b, &start, &end, 300, 0);
			break;
		}
		case 5:
		{
			GRect start = H4;
			GRect end = H5A;
			animate_layer((Layer*)block_h_b, &start, &end, 300, 0);
			GRect start_b = H5B_COLLAPSED;
			GRect end_b = H5B;
			animate_layer((Layer*)block_h_a, &start_b, &end_b, 100, 400);
			break;
		}
		case 6:
		{
			GRect start = H5A;
			GRect end = H5A_COLLAPSED;
			animate_layer((Layer*)block_h_b, &start, &end, 100, 0);
			GRect start_b = H5B;
			GRect end_b = H6;
			animate_layer((Layer*)block_h_a, &start_b, &end_b, 300, 100);
			break;
		}
		case 7:
		{
			GRect start = H6;
			GRect end = H7A;
			animate_layer((Layer*)block_h_a, &start, &end, 300, 0);
			GRect start_b = H7B_COLLAPSED;
			GRect end_b = H7B;
			animate_layer((Layer*)block_h_b, &start_b, &end_b, 100, 400);
			break;
		}
		case 8:
		{
			GRect start = H7A;
			GRect end = H7A_COLLAPSED;
			animate_layer((Layer*)block_h_a, &start, &end, 100, 0);
			GRect start_b = H7B;
			GRect end_b = H8;
			animate_layer((Layer*)block_h_b, &start_b, &end_b, 300, 100);
			break;
		}
		case 9:
		{
			GRect start = H8;
			GRect end = H9;
			animate_layer((Layer*)block_h_b, &start, &end, 300, 0);
			break;
		}
		case 10:
		{
			GRect start = H9;
			GRect end = H10;
			animate_layer((Layer*)block_h_b, &start, &end, 300, 0);
			break;
		}
		case 11:
		{
			GRect start = H10;
			GRect end = H11A;
			animate_layer((Layer*)block_h_b, &start, &end, 300, 0);
			GRect start_b = H11B_COLLAPSED;
			GRect end_b = H11B;
			animate_layer((Layer*)block_h_a, &start_b, &end_b, 100, 400);
			break;
		}
		case 12:
		{
			GRect start = H11A;
			GRect end = H11A_COLLAPSED;
			animate_layer((Layer*)block_h_b, &start, &end, 100, 0);
			GRect start_b = H11B;
			GRect end_b = H12;
			animate_layer((Layer*)block_h_a, &start_b, &end_b, 300, 100);
			break;
		}
	}
}

void setMinute(int minute) {
	switch (minute) 
	{
		case 5: 
		{
			GRect start = M12;
			GRect end = M1A;
			animate_layer((Layer*)block_m_a, &start, &end, 300, 0);
			GRect start_b = M1B_COLLAPSED;
			GRect end_b = M1B;
			animate_layer((Layer*)block_m_b, &start_b, &end_b, 100, 400);
			break;
		}		
		case 10: 
		{
			GRect start = M1A;
			GRect end = M1A_COLLAPSED;
			animate_layer((Layer*)block_m_a, &start, &end, 100, 0);
			GRect start_b = M1B;
			GRect end_b = M2;
			animate_layer((Layer*)block_m_b, &start_b, &end_b, 300, 100);
			break;
		}
		case 15: 
		{
			GRect start = M2;
			GRect end = M3;
			animate_layer((Layer*)block_m_b, &start, &end, 300, 0);
			break;
		}
		case 20: 
		{
			GRect start = M3;
			GRect end = M4;
			animate_layer((Layer*)block_m_b, &start, &end, 300, 0);
			break;
		}
		case 25: 
		{
			GRect start = M4;
			GRect end = M5A;
			animate_layer((Layer*)block_m_b, &start, &end, 300,0);
			GRect start_b = M5B_COLLAPSED;
			GRect end_b = M5B;
			animate_layer((Layer*)block_m_a, &start_b, &end_b, 100, 400);
			break;
		}
		case 30: 
		{
			GRect start = M5A;
			GRect end = M5A_COLLAPSED;
			animate_layer((Layer*)block_m_b, &start, &end, 100, 0);
			GRect start_b = M5B;
			GRect end_b = M6;
			animate_layer((Layer*)block_m_a, &start_b, &end_b, 300, 100);
			break;
		}
		case 35: 
		{
			GRect start = M6;
			GRect end = M7A;
			animate_layer((Layer*)block_m_a, &start, &end, 300, 0);
			GRect start_b = M7B_COLLAPSED;
			GRect end_b = M7B;
			animate_layer((Layer*)block_m_b, &start_b, &end_b, 100, 400);
			break;
		}
		case 40: 
		{
			GRect start = M7A;
			GRect end = M7A_COLLAPSED;
			animate_layer((Layer*)block_m_a, &start, &end, 100, 0);
			GRect start_b = M7B;
			GRect end_b = M8;
			animate_layer((Layer*)block_m_b, &start_b, &end_b, 300, 100);
			break;
		}
		case 45:
		{
			GRect start = M8;
			GRect end = M9;
			animate_layer((Layer*)block_m_b, &start, &end, 300, 0);
			break;
		}
		case 50: 
		{
			GRect start = M9;
			GRect end = M10;
			animate_layer((Layer*)block_m_b, &start, &end, 300, 0);
			break;
		}
		case 55:
		{
			GRect start = M10;
			GRect end = M11A;
			animate_layer((Layer*)block_m_b, &start, &end, 300, 0);
			GRect start_b = M11B_COLLAPSED;
			GRect end_b = M11B;
			animate_layer((Layer*)block_m_a, &start_b, &end_b, 100, 400);
			break;
		}
		case 0: 
		{
			GRect start = M11A;
			GRect end = M11A_COLLAPSED;
			animate_layer((Layer*)block_m_b, &start, &end, 100, 0);
			GRect start_b = M11B;
			GRect end_b = M12;
			animate_layer((Layer*)block_m_a, &start_b, &end_b, 300, 100);
			break;
		}	
	}
}

void tick_handler(struct tm *tick_time, TimeUnits units_changed) {	
	int minute = tick_time->tm_min;
	int hour = tick_time->tm_hour;
	int second = tick_time->tm_sec;
	
	// update on the minute
	if (second == 0) {
		if (minute % 5 == 0) {
			setMinute(minute);
			if (minute == 0) {
				setHour(hour);
			}
		}
	}
}

void window_load() {
	// set background
	bg_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG);
	bg_layer = bitmap_layer_create(GRect(0,0,144,168));
	bitmap_layer_set_bitmap(bg_layer, bg_bitmap);
	layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(bg_layer));
	
	// create and add travelling blocks to trace outlines
	block_m_a = inverter_layer_create(GRect(0,0,0,0));
	block_m_b = inverter_layer_create(GRect(0,0,0,0));
	block_h_a = inverter_layer_create(GRect(0,0,0,0));
	block_h_b = inverter_layer_create(GRect(0,0,0,0));
	
	layer_add_child(window_get_root_layer(window), (Layer*) block_m_a);
	layer_add_child(window_get_root_layer(window), (Layer*)block_m_b);
	layer_add_child(window_get_root_layer(window), (Layer*) block_h_a);	
	layer_add_child(window_get_root_layer(window), (Layer*)block_h_b);
	
	// set time initially
	struct tm *tick_time;
	time_t temp;
	temp = time(NULL);
	tick_time = localtime(&temp);
	int minute = tick_time->tm_min;
	int hour = tick_time->tm_hour;	
	
	// round minute down to the nearest 5;
	int remainder = minute % 5;
	minute = minute - remainder;
	
	setMinute(minute);
	setHour(hour);
}

void window_unload() {
	gbitmap_destroy(bg_bitmap);
	bitmap_layer_destroy(bg_layer);
	inverter_layer_destroy(block_m_a);
	inverter_layer_destroy(block_m_b);
	inverter_layer_destroy(block_h_a);
	inverter_layer_destroy(block_h_b);
}

void init() {
	window = window_create();
	window_set_window_handlers(window, (WindowHandlers) {
		.load = window_load,
		.unload = window_unload
	});
	tick_timer_service_subscribe(SECOND_UNIT, (TickHandler) tick_handler);
	window_stack_push(window, true);
}

void deinit() {
	window_destroy(window);
	tick_timer_service_unsubscribe();
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}