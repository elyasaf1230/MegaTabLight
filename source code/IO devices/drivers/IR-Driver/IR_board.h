/* 
   This driver should control the IR sensors board.
   It should be used to read B/W pics from the IR sensors board.

	Dependencies:
		This driver relies on 2 other drivers:
		- MCP3004 ADC (SPI) driver, to read values from the IR sensors.
		- select (GPIO) driver, to choose IR sensors and control them (select pins). 

   	Hardware:
   		Right now, the hardware is a matrix of 15X15 IR leds and IR photo transistors
   		which need to be choose via 8 GPIO ports (4 bits for row, 4 bits for column),
   		and another pin to enable/disable the IR led.
   		There is SPI ADC (MCP3004) which should be read in order to get the IR photo
   		transistor value.

   	Algorithm:
   		Basic idea:
	 	To assemble image we will need to write to the 8 GPIO pins to select pixel,
	 	read it's value from the ADC and place it in the array for the user.
		
		We missed something:
		IR light exist everywhere, so we will have to get rid of the 'ambient' IR light
		so the data we give the user will be as accurate as possible.

		In order to get rid of this ambient IR light, we will need to measure it.
		We will take 2 samples from the photo transistor;
		One with the IR LED off and one with the IR LED on and then take only the difference
		between the two samples.

		Previous tests:
		From tests we made with Arduino, it seems that there is importance to the delay
		between samples and turning on/off of the IR LED.

		Best algorithm right now:
		1. Choose pixel to read (write to the 8 GPIO).
		2. Turn off the IR lED.
		3. Wait T nano/micro/mili seconds.
		4. Read and store value from ADC.
		5. Turn on the IR LED.
		6. Wait T nano/micro/mili seconds.
		7. Read and store value from ADC.
		8. Calculate the wanted value from the two samples.
		Then repeat this proccess for each pixel.

   		Given the above algorithm, we can (roughly) 
   		calculate the time it takes to read one image:
		((W * 8 + W + T + R) * 2) * 225 = ((9W + T + R) * 2) * 225 = (9W + T + R) * 450
		
		W - Write time to GPIO pin.
		T - Delay time between turning on/off the IR LED and read the value from ADC.
		R - Read time from ADC.

		Assuming we can write to GPIO pin at 22MHz, W = 45.454545454545ns -> W = 46ns.
		Assuming we run the ADC at 100 ksps (SPI clock at 20 * 100k = 2Mhz), R =~ 5µs.
		At our last test we come to minimum delay of 10ns, lets assume more, T = 50ns.

		Time it takes to read one image:
		(9 * 46ns + 50ns + 5µs) * 450 = (5.5µs) * 450 = 2500µs = 2.5ms

		This mean that we can read 40 images at one second, which is not enough but
		it is a start. 
		The main drag is the reading, which depends on the ADC.
		We may success to run it at 200ksps so we can read almost 80 images per second.
*/
