#include <pebble.h>
#include "main_window.h"
#include "error_window.h"

Window *mainWindow;
MenuLayer *mainMenuLayer;
Layer *stripe;


uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) { //menu later, data pointer reference
  return 3;
}

uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) { //section index: amount of rows, use in switch
  switch (section_index){
    case 0:
      return 1;
    case 1:
      return 1;
    case 2:
      return 1;
    default:
      return 0;
  } 
}

int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) { 
    return MENU_CELL_BASIC_HEADER_HEIGHT;
}

void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) { //section index: section drawing for
    switch(section_index){
      case 0:
        menu_cell_basic_header_draw(ctx, cell_layer, NULL);
        break;
      case 1:
        menu_cell_basic_header_draw(ctx, cell_layer, NULL);
        break;
    }
}
void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) { //menu draw row contact, menu index: struct that contains two members
    switch(cell_index->section){
      case 0:
        switch(cell_index->row){
          case 0:
          //menu_cell_basic_draw(ctx, cell_layer, "Red",NULL, NULL);//title, subtitle, pixel icon
          menu_cell_basic_draw(ctx, cell_layer, NULL,NULL, NULL); 
          break;
        }
        break;
      case 1:
          //menu_cell_basic_draw(ctx, cell_layer, "Yellow",NULL, NULL); //make subtitle null for bigger text
        menu_cell_basic_draw(ctx, cell_layer, NULL,NULL, NULL);  
        break;
      case 2:
         //menu_cell_basic_draw(ctx, cell_layer, "Green",NULL, NULL); //make subtitle null for bigger text
        menu_cell_basic_draw(ctx, cell_layer, NULL,NULL, NULL); 
        break;
    }  
}


void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) { //detect when someone clicks on menu layer
  //any time you click any row, displays error window 
 error_window_set_error("All Set!");
  error_window_show();
  
  DictionaryIterator *iter; //write vals to dictionary
  //????
  app_message_outbox_begin(&iter); //passing in dict it
  
  //checking that it exsits, if we do, reject request
  if(iter == NULL){
    APP_LOG(APP_LOG_LEVEL_ERROR, "Iter is null! Refusing to send");
    return;
  }
  dict_write_uint16(iter, 10000, 713);
  dict_write_end(iter);
  
  app_message_outbox_send();
}

void setup_menu_layer(Window *window) {
	Layer *window_layer = window_get_root_layer(window);

    mainMenuLayer = menu_layer_create(GRect(0, 0, 144, 168));
    menu_layer_set_callbacks(mainMenuLayer, NULL, (MenuLayerCallbacks){
        .get_num_sections = menu_get_num_sections_callback, //how many sections in menu failure
        .get_num_rows = menu_get_num_rows_callback, //number of rows 
        .get_header_height = menu_get_header_height_callback, //return menu cell, you might want to customize
        .draw_header = menu_draw_header_callback, 
        .draw_row = menu_draw_row_callback,
        .select_click = menu_select_callback, //when user clicks select on item
    });

    menu_layer_set_click_config_onto_window(mainMenuLayer, window);

    layer_add_child(window_layer, menu_layer_get_layer(mainMenuLayer));
}
void main_graphics_proc(Layer *layer, GContext *ctx){ //now layer and ctx can be played with
//   graphics_context_set_text_color(ctx, GColorOrange);
//   graphics_draw_text(ctx, currentErrorText[0], fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), GRect(0,0,144,50), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);

  graphics_context_set_stroke_color(ctx, GColorRed);
  graphics_context_set_stroke_width(ctx, 25);
  graphics_draw_line(ctx, GPoint(20, 35), GPoint(124, 35));
  
  graphics_context_set_stroke_color(ctx, GColorYellow);
  graphics_context_set_stroke_width(ctx, 25);
  graphics_draw_line(ctx, GPoint(20, 80), GPoint(124, 80));
  
  graphics_context_set_stroke_color(ctx, GColorGreen);
  graphics_context_set_stroke_width(ctx, 25);
  graphics_draw_line(ctx, GPoint(40, 140), GPoint(124, 140));
}
void process_tuple(Tuple *t){
    int key = t->key;
    int value = t->value->int32;
  
    APP_LOG(APP_LOG_LEVEL_INFO, "Got key %d with value %d", key, value);
}

void message_inbox(DictionaryIterator *iter, void *context){ //called when you get message from js
    Tuple *t = dict_read_first(iter);
    if(t){
        process_tuple(t); //if exists, send it over
    }
    while(t != NULL){
        t = dict_read_next(iter);
        if(t){
            process_tuple(t);
        }
    }
}

void message_inbox_dropped(AppMessageResult reason, void *context){ //called if pebble gives up
    APP_LOG(APP_LOG_LEVEL_INFO, "Message dropped, reason %d.", reason);
}
void main_window_load(Window *window){
  setup_menu_layer(window);
  Layer *window_layer = window_get_root_layer(window);
  
  app_message_register_inbox_received(message_inbox);
  app_message_register_inbox_dropped(message_inbox_dropped);
  app_message_open(256, 256);
  
  stripe = layer_create(GRect(0,0, 144, 168));
  layer_set_update_proc(stripe, main_graphics_proc); //for this layer, this is update procedure
  layer_add_child(window_layer, stripe);

}
void main_window_unload(Window *window){
  menu_layer_destroy(mainMenuLayer);
}
void main_window_create(){
  mainWindow = window_create();
  window_set_window_handlers(mainWindow, (WindowHandlers){//when pushed onto display
    .load = main_window_load,
    .unload = main_window_unload
  });
}
void main_window_destroy(){
  window_destroy(mainWindow);
}
Window *main_window_get_window(){
  //convience function that returns spalsh window to us
  return mainWindow;
}