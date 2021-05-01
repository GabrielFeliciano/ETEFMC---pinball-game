#include <__cross_studio_io.h>
#include <stdbool.h> 

// Global variables --------------------------------

bool is_game_on = false;

bool is_motor_activated = false; // para lançar bola
bool ldr_status = true;

bool lazer_to_verify_ball = true;

bool bypassed_ldrs[3] = {true, true, true};

// bool lazers_goal[3] = {false, false, false};
// bool leds_points[3] = {false, false, false};

unsigned int score = 0;

// Macros ------------------------------------------

#define score_limit_to_add_another_ball 3

// getters

#define get_value_at_pin(pin) (false)

#define get_ldr1() (get_value_at_pin(1))
#define get_ldr2() (get_value_at_pin(2))
#define get_ldr3() (get_value_at_pin(3))

#define get_button_start_game() (get_value_at_pin(4))

// setters 

#define add_score() (score += 1)
#define startgame() (is_game_on = true)

// Global functions --------------------------------

void check_ldrs () {
  bypassed_ldrs[0] = get_ldr1();
  bypassed_ldrs[1] = get_ldr2();
  bypassed_ldrs[2] = get_ldr3();
}

bool is_game_over () {
  bool is_it = true;
  for (int i = 0; i < sizeof(bypassed_ldrs); i++) {
    bool val = bypassed_ldrs[i];
    is_it = is_it && bypassed_ldrs[i] && val;
  }
  return is_it;
}

void release_ball () {
    is_motor_activated = true;
}

void awaitGameStart () {
  bool button_start = get_button_start_game();
  while (true) if (button_start) {
      release_ball();
      break;
  }
}

void loop(void) {

  check_ldrs();
  if (is_game_over()) {
    add_score();
  }

}

void main(void)
{

  debug_printf("hello world\n");
  awaitGameStart();
  while (1) loop();
  debug_exit(0);

}
