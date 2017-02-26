#include <pebble.h>
#include "splash_window.h"
#include "main_window.h"

int main(){
  splash_window_create();
  main_window_create();
  window_stack_push(splash_window_get_window(), true);
  app_event_loop(); //excutes event loop of app
  splash_window_destroy();
}