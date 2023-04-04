#ifndef NewPing_h
#define NewPing_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else
	#include <WProgram.h>
	#include <pins_arduino.h>
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

#define MAX_SENSOR_DISTANCE 500 
#define US_ROUNDTRIP_IN 146    
#define US_ROUNDTRIP_CM 57     
#define DISABLE_ONE_PIN false 

#define NO_ECHO 0               
#define MAX_SENSOR_DELAY 18000  
#define ECHO_TIMER_FREQ 24     
#define PING_MEDIAN_DELAY 29

#define NewPingConvert(echoTime, conversionFactor) (max((echoTime + conversionFactor / 2) / conversionFactor, (echoTime ? 1 : 0)))

class NewPing {
	public:
		NewPing(uint8_t trigger_pin, uint8_t echo_pin, int max_cm_distance = MAX_SENSOR_DISTANCE);
		unsigned int ping();
		unsigned int ping_in();
		unsigned int ping_cm();
		unsigned int ping_median(uint8_t it = 5);
		unsigned int convert_in(unsigned int echoTime);
		unsigned int convert_cm(unsigned int echoTime);
		void ping_timer(void (*userFunc)(NewPing *));
		boolean check_timer();

		unsigned long ping_result;
        void *user_data; // allows to store custom user data, primarily for userFunc callbacks

	/* internal */
		void timer_us(unsigned int frequency, void (*userFunc)(NewPing *));
		void timer_ms(unsigned long frequency, void (*userFunc)(NewPing *));
		static void timer_stop();
	private:
		boolean ping_trigger();
		boolean ping_wait_timer();
		uint8_t _triggerBit;
		uint8_t _echoBit;
		volatile uint8_t *_triggerOutput;
		volatile uint8_t *_triggerMode;
		volatile uint8_t *_echoInput;
		unsigned int _maxEchoTime;
		unsigned long _max_time;
		static void timer_setup();
		static void timer_ms_cntdwn();
		static void call_user_func();
};


#endif
