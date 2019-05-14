# FINAL PROJECT: GUITAR GUESSING GAME
\authors: César Villarreal Hernández         @4497cv,
	      Luís Fernando Rodríguez Gutiérrez  @LProtox,


Software Layers:
> Microcontroller Abstraction Layer: GPIO, UART, PIT, FlexTimer
> Hardware Abstraction Layer: Frequency_Decoder
> Application Abstraction Layer: system

PIN LAYOUT:
> Guitar Input pin: Port B, pin 2
> Sound output pin: Port B, pin 3
	
> Push button start: PORT C, pin 5
> Push button select: PORTC, pin 7

> LCD external reset: PORT D, pin 0
> LCD CLK: PORT D, pin 1
> LCD Serial Data Input (SDIN): PORT D, pin 2
> LCD DC: PORT D, pin 3

> Buzzer Port C bit 5


Hardware Used:
> Voltage to Frequency Converter: LM2907
> OP-AMPS TL082/TL083
> Guitar Amplifier

Callbacks configured
> PIT 0: defines the beats per second to the sound
> PIT 1: frequency sound
> PIT 2: adc sampling
> PIT 3: time interrupt