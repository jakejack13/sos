/** 
 * General Pin Input/Output
 */

#ifndef _GPIO_H_
#define _GPIO_H_

/** Sets a GPIO pin to a value */
unsigned int gpio_set(unsigned int pin_number, unsigned int value);
/** Clears a GPIO pin to a value */
unsigned int gpio_clear(unsigned int pin_number, unsigned int value);
/** Sets the pull state of a GPIO pin to a value */
unsigned int gpio_pull(unsigned int pin_number, unsigned int value);
/** Sets the function of a GPIO to a value */
unsigned int gpio_function(unsigned int pin_number, unsigned int value);
/** Assigns a GPIO pin alternative function 5 (used for UART) */
void gpio_use_as_alt5(unsigned int pin_number);

#endif //_GPIO_H_