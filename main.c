#include <__cross_studio_io.h>
#include <stdbool.h>
#include "gpio/gpio.h"

// Global variables --------------------------------

bool is_motor_activated = false; // para lançar bola

bool bypassed_ldrs[3] = {false, false, false};

bool teste;

unsigned int score = 0;

// Macros ------------------------------------------

#define score_limit_to_add_another_ball 3

// getters

#define get_value_at_pin(pin) (false)

#define get_ldr1() (gpio_pin_read(GPIOB, 13))
#define get_ldr2() (gpio_pin_read(GPIOB, 14))
#define get_ldr3() (gpio_pin_read(GPIOB, 15))

#define get_button_start_game() (get_value_at_pin(4))

// setters 

#define add_score() (score += 1)
#define startgame() (is_game_on = true)

// Global functions --------------------------------

void check_ldrs () {
  bool ldr1 = get_ldr1();
  bool ldr2 = get_ldr2();
  bool ldr3 = get_ldr3();

  if (
    ldr1 && !bypassed_ldrs[0] ||
    ldr2 && !bypassed_ldrs[1] ||
    ldr3 && !bypassed_ldrs[2]
  ) {
    add_score();
  }
  bypassed_ldrs[0] |= ldr1;
  bypassed_ldrs[1] |= ldr2;
  bypassed_ldrs[2] |= ldr3;
}

bool is_game_over () {
  bool is_it = true;
  for (int i = 0; i < sizeof(bypassed_ldrs); i++) {
    bool val = bypassed_ldrs[i];
    is_it &= val;
  }
  return is_it;
}

void release_ball () {
    is_motor_activated = true;
}

void game_over () {
  gpio_pin_write(GPIOB, 12, 0);
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
    game_over();
    release_ball(); // release another ball
  }

}

void configure () {
  gpio_init();
  gpio_pin_mode(GPIOB, 12, gpio_mode_output_PP_10MHz);
  gpio_pin_mode(GPIOB, 13, gpio_mode_input_pupd);
  gpio_pin_mode(GPIOB, 14, gpio_mode_input_pupd);
  gpio_pin_mode(GPIOB, 15, gpio_mode_input_pupd);

  gpio_pin_write(GPIOB, 13, 0);
  gpio_pin_write(GPIOB, 14, 0);
  gpio_pin_write(GPIOB, 15, 0);
}

void main(void)
{

  configure();
  debug_printf("hello world\n");
  awaitGameStart();
  while (1) loop();
  debug_exit(0);

}
