// ------------
// Blink an LED
// ------------

/*-------------
This program will blink an led on and off every second.
It blinks the D7 LED on your Particle device. If you have an LED wired to D0, it will blink that LED as well.
-------------*/


// First, we're going to make some variables.
int led = D0; // Instead of writing D0 over and over again, we'll write led1
// You'll need to wire an LED to this one to see it blink.
const int blinkTime = 200;
//int led2 = D7; // Instead of writing D7 over and over again, we'll write led2
// This one is the little blue LED on your board. On the Photon it is next to D7, and on the Core it is next to the USB jack.

byte mac[6];
int temp = 0;
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
int delayTime = 0;
int blinking = false;

void setup() {

  // We are going to tell our device that D0 and D7 (which we named led1 and led2 respectively) are going to be output
  // It's important you do this here, inside the setup() function rather than outside it or in the loop function.

  //pinMode(led1, OUTPUT);
  pinMode(led, OUTPUT);
  Particle.variable("tempValue", temp);
  temp = blinkTime;

/*
  WiFi.on();
  Serial.begin(9600);
  while (!Serial.available()) Particle.process();

  WiFi.macAddress(mac);

  for (int i=0; i<6; i++){
      if (i) Serial.print(":");
      Serial.print(mac[i], HEX);
  }
*/

}

// Next we have the loop function, the other essential part of a microcontroller program.
// Note: Code that blocks for too long (like more than 5 seconds), can make weird things happen (like dropping the network connection).
//The built-in delay function shown below safely interleaves required background activity, so arbitrarily long delays can safely be done if you need them.

void loop() {
  /*
  // To blink the LED, first we'll turn it on...
  //digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);

  // We'll leave it on for 1 second...
  delay(blinkTime);

  // Then we'll turn it off...
  //digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);

  // Wait 1 second...
  delay(blinkTime);
  */
  //temp = temp+1;
  temp = WiFi.RSSI();
  // And repeat!

  // set the brightness of pin 9:
  analogWrite(led, brightness);

  // change the brightness for next time through the loop:
  if (blinking == false) {
    brightness = brightness + fadeAmount;
  }

  if (brightness == 255 && blinking == false) {
    blinking = true;
  }

  if (blinking == true && delayTime < 40) {
    delayTime++;
    if (brightness == 255) {
      brightness = 0;
    } else {
      brightness = 255;
    }
  } else if (blinking == true || blinking == false && brightness == 0) {
    delayTime = 0;
    fadeAmount = -fadeAmount;
    blinking = false;
  }

  // wait for 30 milliseconds to see the dimming effect
  delay(60);
}
