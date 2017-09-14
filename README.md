This repository contains the scatterbrained development process of the microcontroller code for a digitally controlled crossfader synthesizer module module in eurorack form factor. It utilizes the STM32 series of microcontrollers and takes advantage of the STM32CubeMX toolchain, which generates the nasty setup code for the chip via a rather friendly GUI.

The most current working version can be found in Documents/stm32 workspace/f4interpolator test

Within that folder, most of the code is generated from the STM32CubeMX app

User code is contained in inc/tables.h, src/stm32f4xx_it.c, and src/main.c

tables.h contains, surprise surprise, the definitions for the wavetables used by the synth 

main.c contains the initialization code and the UI handling functions

stm32f4xx_it.c contains the interrupt service routines which do most of the heavy lifting in our program

The architecture of the program is as follows: Timer 6 triggers an interrupt routine at 90khz. The primary oscillator is implemented within that interrupt service function, TIM6_DAC_IRQHandler()

The behavior of the ISR that supplies our DAC (TIM6_DAC_IRQHandler()) is beholden to a few global variables. A separate ISR (TIM2_IRQHandler()) sets a "trigger" flag high whenever it is called (which would indicate a rising edge at the "trigger in" jack). This sets the oscillator in motion, so to speak.

The oscillator checks conditionals at different points in the ISR for the state of 3 variables which indicate the current "mode" for 3 parameters: "speed", "loop", and "trigmode" (determined by functions found in main.c). More on the charateristics of these different modes can be found in the manual.

The oscillator raises a flag and sets a pending interrupt request (to be handled by EXTI15_10_IRQHandler()) whenever the phase pointer ("position") enters the release or attack phase.

EXTI15_10_IRQHandler() in turn sets the state of the two sample and holds which are part of the analog circuit associated with the microcontroller. The exact behavior of this interrupt is determined by a mode variable "samphold" as well as the particular flag that was raised along with the interrupt request ("intoattackfroml", "intoattackfromr", "intoreleasefroml", "intoreleasefromr")

The main loop sequentially checks for a button press on each of the mode change buttons and then updates the PWM channels of the relevant timers with the latest value of the oscillator and the current amount of "morph". If it detects a buttom press, it shows the current mode for that button on the 4 leds and blanks the RGB LED. On releasing the button, it changes the mode and shows the new mode for a second or so.
