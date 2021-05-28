#include <__cross_studio_io.h>
#include <stdbool.h>
#include "gpio/gpio.h"

// Global variables --------------------------------

bool bypassed_ldrs[3] = {false, false, false};

bool game_over_handled = false;

unsigned int score = 0;

// Pins --------------------------------------------

#define pin_ldr1 6 //b6
#define pin_ldr2 7 //b7
#define pin_ldr3 8 //b8
#define pin_ldr_end_game 1 //b1

#define pin_start_game_button 4 //a4

#define pin_led1 13 //b13
#define pin_led2 14 //b14
#define pin_led3 15 //b15


// Macros ------------------------------------------

#define score_limit_to_add_another_ball 3

// getters

#define get_ldr1() (gpio_pin_read(GPIOB, pin_ldr1))
#define get_ldr2() (gpio_pin_read(GPIOB, pin_ldr2))
#define get_ldr3() (gpio_pin_read(GPIOB, pin_ldr3))

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

  gpio_pin_write(GPIOB, pin_led1, bypassed_ldrs[0]);
  gpio_pin_write(GPIOB, pin_led2, bypassed_ldrs[1]);
  gpio_pin_write(GPIOB, pin_led3, bypassed_ldrs[2]);
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
  debug_printf("Uma bola foi solta!\n");
}

void game_over_win () {
  debug_printf("Voce passou por todos os pontos, parabens!!\n");
}

void game_over_lose () {
  debug_printf("Voce perdeu o jogo!\n");
}

void awaitGameStart () {
  while (true) {
    bool bt = gpio_pin_read(GPIOA, pin_start_game_button);
    if (bt) break;
  }
  release_ball();
}

bool check_if_player_missed_ball () {
  return gpio_pin_read(GPIOB, pin_ldr_end_game);
}

void configure () {
  gpio_init();

  gpio_pin_mode(GPIOB, pin_ldr1, gpio_mode_input_pupd);
  gpio_pin_mode(GPIOB, pin_ldr2, gpio_mode_input_pupd);
  gpio_pin_mode(GPIOB, pin_ldr3, gpio_mode_input_pupd);

  gpio_pin_mode(GPIOB, pin_ldr_end_game, gpio_mode_input_pupd);

  gpio_pin_mode(GPIOA, pin_start_game_button, gpio_mode_input_pupd);

  gpio_pin_write(GPIOB, pin_ldr1, 0);
  gpio_pin_write(GPIOB, pin_ldr2, 0);
  gpio_pin_write(GPIOB, pin_ldr3, 0);

  gpio_pin_write(GPIOB, pin_ldr_end_game, 0);

  gpio_pin_write(GPIOA, pin_start_game_button, 0);

  gpio_pin_mode(GPIOB, pin_led1, gpio_mode_output_PP_2MHz);
  gpio_pin_mode(GPIOB, pin_led2, gpio_mode_output_PP_2MHz);
  gpio_pin_mode(GPIOB, pin_led3, gpio_mode_output_PP_2MHz);
}

void main(void)
{

  configure();
  debug_printf("Começando o jogo!\n");
  awaitGameStart();

  while (true) {
    check_ldrs();
    if (check_if_player_missed_ball()) {
      game_over_lose();
      break;
    }
    if (is_game_over() && !game_over_handled) {
      game_over_handled = true;
      game_over_win();
      release_ball(); // release another ball
    }
  }

  debug_exit(0);

}
