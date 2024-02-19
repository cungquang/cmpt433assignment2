#ifndef _LED_P921_H_
#define _LED_P921_H_

int led_getPeriod();
int let_getDutyCycle();
void led_init();
void led_enable();
void led_disable();
void led_writeToDutyCycle(int value);
void led_writeToPeriod(int value);

#endif