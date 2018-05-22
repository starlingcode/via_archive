#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"

// larger functions for different mode behavior that don't fit inline in a case statement can go here
// the handler function called in the signal parser can be a pointer to these functions
