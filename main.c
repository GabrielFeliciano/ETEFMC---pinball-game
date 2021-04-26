#include <__cross_studio_io.h>
#include <stdbool.h> 

bool is_motor_activated = false; // para lançar bola
bool ldr_status = true;

bool lazer_to_verify_ball = true;

bool lazers_goal[3] = [false, false, false];
bool leds_points[3] = [false, false, false];

struct Sweepings = {
  
}

// bool sweepings_buttton = 


bool get_ldr_status () {
  bool newValue = true;
  ldr_status = newValue;
  return ldr_status;
}

void release_ball () {
    motor_acionado = true;
}

void loop(void) {

  if (get_ldr_status()) {
    release_ball();
  }

}

void main(void)
{

  debug_printf("hello world\n");
  while (1) loop();
  debug_exit(0);

}
