#include <pebble.h>
#include "splash_window.h"

Window *splashWindow;
GBitmap *splashImage;
BitmapLayer *splashImageLayer;
TextLayer *splashImageTitle;

void splash_window_load(Window *window){
  //where we put layer 'magic'
  //set up image
    //create a gbit map from resource of kitten
      //pass that gbit map on gbit layer
  Layer *window_layer = window_get_root_layer(window);  
  
  splashImage = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SPLASH);
  //set up text layer
  splashImageLayer = bitmap_layer_create(GRect(0,0,144,120)); //x coord,y coord, width, height
  
  bitmap_layer_set_bitmap(splashImageLayer, splashImage);
  bitmap_layer_set_compositing_mode(splashImageLayer, GCompOpSet);
  layer_add_child(window_layer, bitmap_layer_get_layer(splashImageLayer)); //add something ontop of deepest layer

  splashImageTitle = text_layer_create(GRect(0,120, 144, 50)); //always draw from top to bottom
  text_layer_set_text(splashImageTitle, "Time Out");
  text_layer_set_text_alignment(splashImageTitle, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(splashImageTitle));
}
void splash_window_unload(Window *window){
  //when taken off stack, distroy resources
  gbitmap_destroy(splashImage);
  bitmap_layer_destroy(splashImageLayer);
  text_layer_destroy(splashImageTitle);
}
void splash_window_create(){
  splashWindow = window_create();
  window_set_window_handlers(splashWindow, (WindowHandlers){//when pushed onto display
    .load = splash_window_load,
    .unload = splash_window_unload
  });
}
void splash_window_destroy(){
  window_destroy(splashWindow);
}
Window *splash_window_get_window(){
  //convience function that returns spalsh window to us
  return splashWindow;
}