#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
#include "xprintf.h"


#define MY_UUID { 0xD7, 0x43, 0xFB, 0x14, 0xD7, 0x2A, 0x48, 0x44, 0x99, 0x2F, 0x42, 0xE6, 0xF3, 0xF1, 0x1E, 0x80 }
PBL_APP_INFO(MY_UUID,
             "Metronome", "Rick Schrader",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);


Window window;

#define DefaultBeatsPerMinute 120
#define DefaultBeatsPerMeasure 4

TextLayer _beatsPerMinuteLayer;
TextLayer _beatsPerMeasureLayer;
TextLayer _beatLayer;
int _beatsPerMinute = DefaultBeatsPerMinute;
int _beatsPerMeasure = DefaultBeatsPerMeasure;
int _beat = 1;

void DisplayBeat()
{
	char* beatString = "000";
	//Updating a character array based on pointer (theoretically pointing to a literal) is "undefined",
	//	but this is the only way I've gotten this to work correctly so far
	xsprintf(beatString, "%d", _beat);
	text_layer_set_text(&_beatLayer, beatString);
}

void DisplayBeatsPerMinute()
{
	char* beatsPerMinuteLabel = "BPM: ";
	char* beatsPerMinuteString = "BPM: 000";
	//Updating a character array based on pointer (theoretically pointing to a literal) is "undefined",
	//	but this is the only way I've gotten this to work correctly so far
	xsprintf(beatsPerMinuteString, "%d", _beatsPerMinute);
	text_layer_set_text(&_beatsPerMinuteLayer, beatsPerMinuteString);
}

void DisplayBeatsPerMeasure()
{
	char* beatsPerMeasureLabel = "Beats per measure:\n";
	char* beatsPerMeasureString = "Beats per measure:\n000";
	//Updating a character array based on pointer (theoretically pointing to a literal) is "undefined",
	//	but this is the only way I've gotten this to work correctly so far
	xsprintf(beatsPerMeasureString, "%d", _beatsPerMeasure);
	text_layer_set_text(&_beatsPerMeasureLayer, beatsPerMeasureString);
}

void up_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
	(void)recognizer;
	(void)window;

	
}


void down_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
	(void)recognizer;
	(void)window;

	
}


void select_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
	(void)recognizer;
	(void)window;

}


void select_long_click_handler(ClickRecognizerRef recognizer, Window *window) {
	(void)recognizer;
	(void)window;

}

void click_config_provider(ClickConfig **config, Window *window) {
	(void)window;

	config[BUTTON_ID_SELECT]->click.handler = (ClickHandler) select_single_click_handler;

	config[BUTTON_ID_SELECT]->long_click.handler = (ClickHandler) select_long_click_handler;

	config[BUTTON_ID_UP]->click.handler = (ClickHandler) up_single_click_handler;
	config[BUTTON_ID_UP]->click.repeat_interval_ms = 100;

	config[BUTTON_ID_DOWN]->click.handler = (ClickHandler) down_single_click_handler;
	config[BUTTON_ID_DOWN]->click.repeat_interval_ms = 100;
}


void handle_init(AppContextRef ctx) {
	(void)ctx;

	window_init(&window, "Metronome");
	window_stack_push(&window, true /* Animated */);
	window_set_background_color(&window, GColorBlack);

	//resource_init_current_app(&APP_RESOURCES);

	//Lets us easily setup each layer without having to change multiple lines if the layer name changes
	TextLayer currentLayer;

	currentLayer = _beatLayer;
	text_layer_init(&currentLayer, window.layer.frame);
	text_layer_set_text_color(&currentLayer, GColorWhite);
  	text_layer_set_background_color(&currentLayer, GColorClear);
  	layer_set_frame(&currentLayer.layer, GRect(0, 10, 144, 168-68));
  	text_layer_set_font(&currentLayer, fonts_get_system_font(FONT_KEY_GOTHAM_42_BOLD));
	text_layer_set_text_alignment(&currentLayer, GTextAlignmentCenter);
	layer_add_child(&window.layer, &currentLayer.layer);

	currentLayer = _beatsPerMinuteLayer;
	text_layer_init(&currentLayer, window.layer.frame);
	text_layer_set_text_color(&currentLayer, GColorWhite);
  	text_layer_set_background_color(&currentLayer, GColorClear);
  	layer_set_frame(&currentLayer.layer, GRect(0, 70, 144, 168-92));
  	text_layer_set_font(&currentLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_text_alignment(&currentLayer, GTextAlignmentCenter);
	layer_add_child(&window.layer, &currentLayer.layer);

	currentLayer = _beatsPerMeasureLayer;
	text_layer_init(&currentLayer, window.layer.frame);
	text_layer_set_text_color(&currentLayer, GColorWhite);
  	text_layer_set_background_color(&currentLayer, GColorClear);
  	layer_set_frame(&currentLayer.layer, GRect(0, 92, 144, 168-92));
  	text_layer_set_font(&currentLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_text_alignment(&currentLayer, GTextAlignmentCenter);
	layer_add_child(&window.layer, & currentLayer.layer);

	DisplayBeat();
	//DisplayBeatsPerMinute();
	//DisplayBeatsPerMeasure();
		
	// Attach our desired button functionality
	window_set_click_config_provider(&window, (ClickConfigProvider) click_config_provider);
}


void pbl_main(void *params) {
	PebbleAppHandlers handlers = {
		.init_handler = &handle_init
	};
	app_event_loop(params, &handlers);
}
