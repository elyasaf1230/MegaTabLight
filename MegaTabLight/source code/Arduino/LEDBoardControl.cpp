#include <FastLED.h>

#define NUM_LEDS 300
#define DATA_PIN 6

CRGB leds[NUM_LEDS];

char place1[2];
char place2[2];
char direction1to2;

void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
	//FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	//FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
	pinMode(DATA_PIN, OUTPUT);
}

void loop() {
	// put your main code here, to run repeatedly:
	if (Serial.available() > 0) {
		Serial.readBytes(place1, 2);
		Serial.readBytes(&direction1to2, 1);
		Serial.readBytes(place2, 2);

		switch (direction1to2)
		{
		case '>':
			leds[atoi(place2)] = leds[atoi(place1)];
			break;
		case '<':
			leds[atoi(place1)] = leds[atoi(place2)];
			break;
		case '=':
			if (strcmp(place2, "rd") == 0)
				leds[atoi(place1)] = CRGB::Red;
			else if (strcmp(place2, "bl") == 0)
				leds[atoi(place1)] = CRGB::Blue;
			else if (strcmp(place2, "gr") == 0)
				leds[atoi(place1)] = CRGB::Green;
			break;
		case '!':
			for (int i = 0; i < NUM_LEDS; i++)
				leds[i] = CRGB::Black;
			break;
		case '*':
			for (int i = 0; i < NUM_LEDS; i++)
				leds[i] = atoi(place2);
			break;
		}
		/* for (int i = 0; i < NUM_LEDS; i++)
		Serial.print("%d,", i);
		Serial.print("\n");*/
		FastLED.show();
	}

	/* // Turn the first led red for 1 second
	leds[99] = CRGB::Red;
	FastLED.show();
	delay(100);

	// Set the first led back to black for 1 second
	leds[99] = CRGB::Black;
	FastLED.show();
	delay(100);
	*/
}