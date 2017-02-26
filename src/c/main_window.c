#include <pebble.h>
#include "main_window.h"

Window *mainWindow;
MenuLayer *mainMenuLayer;
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
            menu_cell_basic_draw(ctx, cell_layer, "Red",NULL, NULL);//title, subtitle, pixel icon
            break;
        }
        break;
      case 1:
        menu_cell_basic_draw(ctx, cell_layer, "Yellow",NULL, NULL); //make subtitle null for bigger text
        break;
      case 2:
         menu_cell_basic_draw(ctx, cell_layer, "Green",NULL, NULL); //make subtitle null for bigger text
        break;
    }  
}

void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) { //detect when someone clicks on menu layer
	
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
void main_window_load(Window *window){
  setup_menu_layer(window);
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