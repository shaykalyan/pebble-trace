#include <pebble.h>
#include "animation.h"

/* appmessage + persist keys */
enum {
	KEY_INVERTED = 0,
	KEY_VIBRATE_5 = 1,
	KEY_FLICK = 2,
	KEY_FLICK_STYLE = 3
};

/* flick view styles */
enum {
	FLICK_STYLE_A = 0,
	FLICK_STYLE_B = 1,
	FLICK_STYLE_C = 2
};

/* period for which the date is visible on accelerometer flick (ms)*/ 
#define TIMER_DATE_DELAY 3000

/* prototypes */
void setHour(int hour);
void setMinute(int minute);
void setDay(struct tm *tick_time); 
void setTime(struct tm *tick_time);
void updateAll();
void invert_canvas_add();
void invert_canvas_remove();
void timer_callback(void *data);
void accel_tap_handler(AccelAxisType axis, int32_t direction);
void process_tuple(Tuple *t);
void in_received_handler(DictionaryIterator *iter, void *context) ;
void tick_handler(struct tm *tick_time, TimeUnits units_changed) ;
void day_layer_create();

Window *window;
AppTimer *timer;
GBitmap *bg_bitmap;
BitmapLayer *bg_layer;
TextLayer *time_layer, *day_layer, *date_layer;
InverterLayer *block_h_a, *block_h_b, *block_m_a, *block_m_b, *invert_canvas;
static char day_text[] = "XXXXXXXXX";
static char time_text[] = "XX:XX";
static char date_text[] = "XX-XX-XX";
bool isInverted, isVibrateOn, isFlickOn;
static int flickStyle;

/****************************
* Time + Date
****************************/

void tick_handler(struct tm *tick_time, TimeUnits units_changed) {	
	int minute = tick_time->tm_min;
	int hour = tick_time->tm_hour;
	int second = tick_time->tm_sec;
	
	// update on the minute
	if (second == 0) {
		if (minute % 5 == 0) {
			setMinute(minute);
			if (isVibrateOn) {
				vibes_short_pulse();
			}
			if (minute == 0) {
				// update hour
				setHour(hour);
				// update date
				setDay(tick_time);
			}
		}
		// update flick view time
		setTime(tick_time);
	}
}

void setHour(int hour) {
	// convert hour to 12hour based
	if (hour > 12) {
		hour = hour - 12;
	}
	if (hour == 0) {
		hour = 12;
	}
	
	// animate transition to current hour
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
	// animate transition to current minute
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

void setDay(struct tm *tick_time) {
	switch (flickStyle) {
		case FLICK_STYLE_A: {
			strftime(day_text, sizeof("XXXXXXXXX"), "%a %d", tick_time);
			break;
		}
		case FLICK_STYLE_B: case FLICK_STYLE_C: {
			strftime(day_text, sizeof("XXXXXXXXX"), "%A", tick_time);
			break;
		}
	}
	text_layer_set_text(day_layer, day_text);
}

void setTime(struct tm *tick_time) {
	if (clock_is_24h_style()) {
		strftime(time_text, sizeof("XX:XX"), "%H:%M", tick_time);
	} else {
		strftime(time_text, sizeof("XX:XX"), "%I:%M", tick_time);
	}
	text_layer_set_text(time_layer, time_text);
}

void setDate(struct tm *tick_time) {
	switch(flickStyle) {
		case FLICK_STYLE_B: {
			strftime(date_text, sizeof("XX-XX-XX"), "%m-%d-%y", tick_time);
			break;
		}
		case FLICK_STYLE_C: {
			strftime(date_text, sizeof("XX-XX-XX"), "%d-%m-%y", tick_time);
			break;
		}
	}
	text_layer_set_text(date_layer, date_text);
}

void updateAll() {
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
	setDay(tick_time);
	setTime(tick_time);
	setDate(tick_time);
}

/****************************
* Invert Layer
****************************/

void invert_canvas_add() {
	layer_add_child(window_get_root_layer(window), (Layer*)invert_canvas);
}

void invert_canvas_remove() {
	layer_remove_from_parent((Layer*)invert_canvas);
}

/****************************
* Accelerometer Timer
****************************/

void timer_callback(void *data) {
	layer_remove_from_parent((Layer*)day_layer);
	if (flickStyle == FLICK_STYLE_B || flickStyle == FLICK_STYLE_C) {
		layer_remove_from_parent((Layer*)time_layer);
		layer_remove_from_parent((Layer*)date_layer);
	}
}

void accel_tap_handler(AccelAxisType axis, int32_t direction) {
  	// if inverter layer is present, insert rest below it
	if (isInverted) {
		layer_insert_below_sibling((Layer*)day_layer, (Layer*)invert_canvas);
		if (flickStyle == FLICK_STYLE_B || flickStyle == FLICK_STYLE_C) {
			layer_insert_below_sibling((Layer*)time_layer, (Layer*)invert_canvas);
			layer_insert_below_sibling((Layer*)date_layer, (Layer*)invert_canvas);
		}
	} else {
		layer_add_child(window_get_root_layer(window),(Layer*)day_layer);
		if (flickStyle == FLICK_STYLE_B || flickStyle == FLICK_STYLE_C) {
			layer_add_child(window_get_root_layer(window),(Layer*)time_layer);
			layer_add_child(window_get_root_layer(window),(Layer*)date_layer);
		}
	}
	// fire timer	
	timer = app_timer_register(TIMER_DATE_DELAY, (AppTimerCallback)timer_callback, NULL);
}

/****************************
* App Message
****************************/

void process_tuple(Tuple *t) {
	int key = t->key;
	int value = t->value->int32;
	char string_value[32];
	strcpy(string_value, t->value->cstring);
	
	switch(key) {
		case KEY_INVERTED: {
			if ( strcmp(string_value, "on") == 0) {
				invert_canvas_add();
				isInverted = true;
			} else {
				invert_canvas_remove();
				isInverted = false;
			} 
			break;
		} case KEY_VIBRATE_5: {
			isVibrateOn = (strcmp(string_value, "on") == 0) ? true : false;
			break;
		} case KEY_FLICK: {
			if ( strcmp(string_value, "on") == 0 ) {
				accel_tap_service_subscribe(&accel_tap_handler);
				isFlickOn = true;
			} else {
				if (isFlickOn) {
					accel_tap_service_unsubscribe();
				}
				isFlickOn = false;
			}
			break;
		} case KEY_FLICK_STYLE: {
			// get first character from string, subtract '0' (48 ascii value);
			flickStyle = (int)(string_value[0] - '0');
			// force recreate day later
			day_layer_create();
			break;
		}
	}
	updateAll();
}

void in_received_handler(DictionaryIterator *iter, void *context) {
	Tuple *t = dict_read_first(iter);
	if(t) {
		process_tuple(t);
	}
  	while(t != NULL) {
		t = dict_read_next(iter);
		if(t) {
      		process_tuple(t);
		}
	}
}

/****************************
* Window
****************************/

void day_layer_create() {	
	ResHandle font_handle_20 = resource_get_handle(RESOURCE_ID_FONT_IMAGINE_20);
	ResHandle font_handle_12 = resource_get_handle(RESOURCE_ID_FONT_IMAGINE_12);
	
	// if layer exists, destroy
	if (day_layer) {
			text_layer_destroy(day_layer);
	}
	
	// create layer
	if (flickStyle == FLICK_STYLE_A) {
		day_layer = text_layer_create(GRect(1,70,144,20));
		text_layer_set_font(day_layer, fonts_load_custom_font(font_handle_20));
	} else {
		day_layer = text_layer_create(GRect(1,76,144,20));
		text_layer_set_font(day_layer, fonts_load_custom_font(font_handle_12));
	}
	text_layer_set_background_color(day_layer, GColorClear);
	text_layer_set_text_color(day_layer, GColorBlack);
	text_layer_set_text_alignment(day_layer, GTextAlignmentCenter);
}

void window_load() {
	ResHandle font_handle_25 = resource_get_handle(RESOURCE_ID_FONT_IMAGINE_25);
	ResHandle font_handle_15 = resource_get_handle(RESOURCE_ID_FONT_IMAGINE_15);
	
	// background
	bg_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG);
	bg_layer = bitmap_layer_create(GRect(0,0,144,168));
	bitmap_layer_set_bitmap(bg_layer, bg_bitmap);
	layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(bg_layer));
	
	// travel blocks
	block_m_a = inverter_layer_create(GRect(0,0,0,0));
	block_m_b = inverter_layer_create(GRect(0,0,0,0));
	block_h_a = inverter_layer_create(GRect(0,0,0,0));
	block_h_b = inverter_layer_create(GRect(0,0,0,0));
	layer_add_child(window_get_root_layer(window), (Layer*) block_m_a);
	layer_add_child(window_get_root_layer(window), (Layer*) block_m_b);
	layer_add_child(window_get_root_layer(window), (Layer*) block_h_a);	
	layer_add_child(window_get_root_layer(window), (Layer*) block_h_b);
	
	// inverter layer
	invert_canvas = inverter_layer_create(GRect(0,0,144,168));
	if (isInverted) {
		invert_canvas_add();
	}
	
	// day layer
	day_layer_create();
	
	// time layer
	time_layer = text_layer_create(GRect(1,45, 144,40));
	text_layer_set_background_color(time_layer, GColorClear);
	text_layer_set_text_color(time_layer, GColorBlack);
	text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);
	text_layer_set_font(time_layer, fonts_load_custom_font(font_handle_25));
	
	// date layer
	date_layer = text_layer_create(GRect(1,93, 144,20));
	text_layer_set_background_color(date_layer, GColorClear);
	text_layer_set_text_color(date_layer, GColorBlack);
	text_layer_set_text_alignment(date_layer, GTextAlignmentCenter);
	text_layer_set_font(date_layer, fonts_load_custom_font(font_handle_15));

	// set time and date initially
	updateAll();
}

void window_unload() {
	gbitmap_destroy(bg_bitmap);
	bitmap_layer_destroy(bg_layer);
	inverter_layer_destroy(block_m_a);
	inverter_layer_destroy(block_m_b);
	inverter_layer_destroy(block_h_a);
	inverter_layer_destroy(block_h_b);
	inverter_layer_destroy(invert_canvas);
	text_layer_destroy(day_layer);
	text_layer_destroy(time_layer);
	text_layer_destroy(date_layer);
}

void init() {
	window = window_create();
	window_set_window_handlers(window, (WindowHandlers) {
		.load = window_load,
		.unload = window_unload
	});

	// subscribe to time 
	tick_timer_service_subscribe(SECOND_UNIT, (TickHandler) tick_handler);
	
	// register AppMessage events
	app_message_register_inbox_received(in_received_handler);           
	app_message_open(512, 512);
	
	// read current settings 
	isInverted = persist_exists(KEY_INVERTED) ? persist_read_bool(KEY_INVERTED) : false;
	isVibrateOn = persist_exists(KEY_VIBRATE_5) ? persist_read_bool(KEY_VIBRATE_5) : false;
	isFlickOn = persist_exists(KEY_FLICK) ? persist_read_bool(KEY_FLICK) : false;
	flickStyle = persist_exists(KEY_FLICK_STYLE) ? persist_read_int(KEY_FLICK_STYLE) : FLICK_STYLE_A;
	
	// subscribe to accelerometer for flick view
	if (isFlickOn) {
		accel_tap_service_subscribe(&accel_tap_handler);
	}
	
	window_stack_push(window, true);
}

void deinit() {
	window_destroy(window);
	tick_timer_service_unsubscribe();
	if (isFlickOn) {
		accel_tap_service_unsubscribe();
	}
	persist_write_bool(KEY_INVERTED, isInverted);
	persist_write_bool(KEY_VIBRATE_5, isVibrateOn);
	persist_write_bool(KEY_FLICK, isFlickOn);
	persist_write_int(KEY_FLICK_STYLE, flickStyle);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}