/*
	This driver controls the select pins of the IR board,
	in order to choose which pair of IR LED - photo transistor
	will be used right now, and turn on/off the IR lED.

	Dependencies:
		- GPIO driver.

	Hardware:
		Our hardware is based on 3 analog muxes (CD74HC4067 like).
		Each mux has 1 input, 16 outputs, 4 selects pins and 1 'enable' pin.
		There is 1 mux that has 5V as it's input,
		and 2 muxes that has GND as it's input, and their selects
		hooked up to the same 4 selects pins.
		That mean we can refer to those 2 muxes as 1 mux.

		The mux with the 5V as it's input controls the choosen row.
		The mux(es) with the GND as input controls the choosen column.
		The combination of those two muxes (column and row) 
		choose on pixel on board.

		The 9th select pin controls one of the 'enable' GND muxes,
		which turn on and off the IR LED of the choosen pair.

	Improvements:
		To improve perfomance, we will save the current states and write 
		only to the changed selects.
*/