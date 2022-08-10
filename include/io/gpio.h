#ifndef _GPIO_H_
#define _GPIO_H_

unsigned int gpio_set(unsigned int pin_number, unsigned int value);
unsigned int gpio_clear(unsigned int pin_number, unsigned int value);
unsigned int gpio_pull(unsigned int pin_number, unsigned int value);
unsigned int gpio_function(unsigned int pin_number, unsigned int value);
void gpio_use_as_alt5(unsigned int pin_number);

#endif //_GPIO_H_