This repository contains the development history of the digital component of a synthesizer module. It utilizes the STM32F303CCT microcontroller as the brains of the operation. This allows us to take advantage of the STM32CubeMX toolchain, which generates the tedious and overwhelming setup code for the chip via a friendly GUI. We will highlight the relevant sections of user code required to make the chip do what we want it to do.  The software was co-authored by Jason Nanna and Will Mitchell, Jason being responsible for many of the good ideas and Will to be blamed for any poorly formatted code.

Some context: The module has an analog signal path that takes two inputs and essentially crossfades between them, with the position of the crossfader determined by a digital contour generator, implemented on the STM32. The digital brains of the module control a sample and hold at each of the inputs. These allow for greater flexibility when interconnecting multiple units at low frequency and sample rate reduction effects in the audio range.

The contour generator is geared for operation with this circuit. It is capable of operating at frequencies ranging from fractions of a hertz through audio rate. It is also defined by two slopes (akin to an attack/release envelope), one for fading from A to B, the other for fading from B to A (in most cases). It also has selectable behavior when triggered. 

The contour generator is driven by wavetable synthesis with linear interpolation. It implements a "wavestacking" technique wherin a "family" of wavetables is defined, and the user can "morph" through the family. In simple terms, the contour generator crossfades from one waveform to the next to the next (...etc) in the family according to the value of the "morph" parameter. This allows us to smoothly change the shape of CV modulation or the timbre of the tone produced from audio rate frequencies.

While this topology offers a wide range of gain shaping effects when used with continuous inputs, keep in mind that applying our contour generator to two DC signals is a nifty way of outputting the shape of the contour generator with scaling and bias according to the DC voltages at the inuts of the crossfader. A nice perk of the analog crossfader implementation is that the B input acts as as a true ring modulator for the oscillator. 

There are three knobs and three CV jacks to control the parameters of the contour generator. The jacks scale -5V to 5V eurorack full scale (ish) voltage to 0 - 3.3V, aka full scale voltage for the ADCs on the chip. 4 buttons are used to toggle the parameters that control the behavior of the contour generator, "speed", "retrigger", "loop", and "sample and hold". All combinations of these modes are valid and unique. Here is a brief overview of the different modes:

Rate:
- Audio (T1 is 1v/OCT, T2 is fine tune/linear FM except in drum mode)
- Envelope (T1 is attack time, T2 is release time)
- Sequence (T1 is attack time, T2 is release time)

Loop:
- One-shot
- Looping

Trig:
- No Retrigger
- Hard reset to beginning of waveform on retrigger (hard sync at audio rate)
- "AR" mode, only retrigger in release stage, return to full scale at attack speed (a softer sync)
- Gated mode, if gate off during attach, return to A at release speed. if gate on, stick at b. if retrigger while releasing, behave like AR mode (an even softer sync)
- Pendulum Mode, switch direction from A->B to B->A every trigger. If going A->B and reach B, stick at B, if going B->A and reach A, stick at A. If trigger while in transit between, reverse direction (a very particular kind of soft sync)

S&H modes:
- No S&H
- Sample A while moving from A to B, track A once B has been reached
- Resample B every time A is reached
- Sample A while moving from A to B, track A once B has been reached. Resample B every time A is reached
- Sample A at A, track once we have reached B. Sample B at B, track when we have reached A
- "Decimate mode" resample both A and B every time we reach either A or B

"Drum Mode" (audio rate and one shot)
- T1 still 1v/oct, T2 becomes decay speed for the drum envelope
- Trig modes determine modulation destinations of drum envelope as follows:
	- Pitch, Morph, Amp
	- Morph, Amp
	- Amp
	- Morph
	- Pitch, Morph

This is Will's first times using version control software, so the repository is very manic.

The most current code is in the "currentworkingthread" branch, and the firmware discussed here is in the "prototype" folder

User code can be found in in /inc/tables.h, /inc/main.h, /src/stm32f4xx_it.c, and /src/main.c

tables.h contains, surprise surprise, the definitions for the wavetables used by the synth.

main.h includes a lot of crucial defines to represent specific register operations in a legible fas. It also has a set of bitwise operations on a variable "flagword" that is used to efficiently pass around global booleans.

main.c contains some initialization code drudgery to get the timers, DAC, and ADC up and running as well as the UI handling functions

stm32f4xx_it.c contains the interrupt service routines (ISR) which do most of the work in our program. For those who are unfamiliar, an "interrupt" is a block of code that can take precendence over the main loop at run time. This is ideal for digital audio, which requires us to update the DAC (digital to analog converter) at a precise rate. Essentially, whenver its time to come up with the next sample value in our signal, the processor pauses whatever it had been doing and completes the routine needed to come up with the next sample. Once that is complete, it goes back to what it had been doing (usually watching our UI for button presses and lighting up the RGB indicator). This also allows it to react in almost real time to its control inputs.

The architecture of the program is as follows: Timer 6 triggers an interrupt routine at roughly 64khz. The contour generator is implemented within that interrupt service function, TIM6_DAC_IRQHandler(). The behavior of that ISR is beholden to a few global variables, namely the variables that hold the current mode, the ADC readings (knobs and jacks, which always live in the arrays ADCReadings1, ADCReadings2, and ADCReadings3  thanks to DMA), and a flag word that passes around the logic needed to maintain mode switches. The same interrupt also drives our RGB indicator, writing the current morph value to the green LED. The blue LED is on when moving from A to B, and red flips on when moving from B to A. The brightness of the blue and red LEDs is determined by how close we are to morph.

In this interrupt, we look for a change in "PHASE_STATE" wherin we travel from attack to release or vice versa. This sets a pending interrupt for EXTI15_10_IRQHandler, which outputs an appropriate logic signal over the logic out jacks and also implements our sample and hold behavior. The sample and holds use two timers as well as their respective interrupts (TIM7 and TIM8) to handle the somewhat tricky task of letting a sample and hold track breifly to get to a new value and then sampling it again a ms or so later so that we can "resample" one of the inputs without letting it fully track for a cycle.

A separate ISR (TIM2_IRQHandler()) handles the rising and falling edges at our trigger input jack. It signals various flags to the other interrupt. The vast majority of our "retriggering" logic is implemented there. 

A single cycle of an audio rate waveform can be useful but we thought this an apt time to add a bonus mode for the intuitive extension of a one shot at audio rate, a drum. Thus, when when "speed" is audio and "loop" is in one shot mode, we activate drum mode. This uses the 1v/oct lookup table to generate an exponential decay curve, the length of which is controlled by the time 2 knob and CV. That drum envelope can be applied to one of three possible modualtion destinations, the frequency of the oscillator, the morph parameter, and the amplitude of the signal (how far we are able to get towards B). The "trig" button lets us cycle through 5 combinations of modulation destination directions as detailed above.

Drum mode uses an additional timer and interrupt, TIM3. This generates the time base for our lookup from the expo table. We want to figure out how to replace the software counter implemented for the "attack" portion of the drum with a hardware timer to reduce code overhead, but that has proved tricky when retriggering.

The main loop basically handles our UI. It looks to see if our retrigger button has been pressed and activates our trigger ISR if so. It then performs the aquisition for our touch sensors. Once that is complete, it looks to see if any of our sensors have entered detect state. If so, it disables the runtime display and shows the current mode for that button on the LEDs as follows:

O is on, x is off

1:

O   	x


x   	x



2:

x   	O


x   	x




3:

x   	x


O   	x




4:

x   	x


x   	O




5:

O   	O


x   	x




6:

x   	x


O 	  O

Families are indicated by the color of the RGB. We also initate a timer to keep track of how long we have had our finger on the sensor. Once that sensor enters "release state", we check the timer. If it is below the timeout threshold, we call a function to change the mode that is associated with the sensor that was just pressed. We then show that mode for about a second before returning to our runtime display. If we have exceeded our timer threshold, we return immediately to the runtime display without changing modes. The mode change function also does some extra initialization of our boolean flags to ensure that the mode we are switching to behaves as we would expect and no vestiges of the last mode remain.

More nuance in the comments, contact liquidcitymotors@gmail.com if this doesn't have what you need!
