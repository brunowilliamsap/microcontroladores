#include <SoftwareSerial.h>// import the serial library

SoftwareSerial celular(10, 11); // RX, TX
int ledpin=13; // led on D13 will show blink on / off
byte BluetoothData[2]; // the data given from Computer

void setup() {
  // put your setup code here, to run once:
  celular.begin(9600);
  celular.println("Bluetooth On please press 1 or 0 blink LED ..");
  pinMode(ledpin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
	if(celular.avaiable()){
		celular.ReadBytes(BluetoothData,2);
	}
	
	if(celular[0]=='1'){
		digitalWrite(ledpin,HIGH)
	}
	
	if(celular[0]=='2'){
		digitalWrite(ledpin,LOW)
	}
  
}
