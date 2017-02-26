#include <pebble.h>
#include "splash_window.h"
#include "main_window.h"
#include "error_window.h"
#include "sendText.h"

void launch_main_window(void *data){

  window_stack_push(main_window_get_window(), true);
}
int main(){
  splash_window_create();
  main_window_create();
  error_window_create();
  
  window_stack_push(splash_window_get_window(), true);
  app_timer_register(1500, launch_main_window, NULL);//miliseconds
 
  app_event_loop(); //excutes event loop of app
  
  splash_window_destroy();
  error_window_destroy();
  main_window_destroy();
}