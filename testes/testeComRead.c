#include <SoftwareSerial.h>// import the serial library

SoftwareSerial celular(10, 11); // RX, TX
int ledpin=13; // led on D13 will show blink on / off
int BluetoothData; // the data given from Computer

void setup() {
  // put your setup code here, to run once:
  celular.begin(9600);
  celular.println("Bluetooth On please press 1 or 0 blink LED ..");
  pinMode(ledpin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   if (celular.available()){
		BluetoothData=celular.read();
   if(BluetoothData=='2'){   // if number 1 pressed ....
   digitalWrite(ledpin,1);
   Genotronex.println("LED  On D13 ON ! ");
   }
  if (BluetoothData=='1'){// if number 0 pressed ....
  digitalWrite(ledpin,0);
   Genotronex.println("LED  On D13 Off ! ");
  }
}
delay(100);// prepare for next data ...
}