

#include<math.h>;
//lcd
#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;
//motor de passo
#include <Stepper.h>
#define STEPS 48
#define ITENS_CONTA_MAX 10
Stepper motor(STEPS, 10, 12, 11, 13);
//bluetooth
char estado;
//declarando pinos
int pinLedArCond = 9;
int pinLedPorta = 7;
int pinLedJanela = 6;
int pinLedLuz = 3;
int pinAnalogTemperatura;
//variaveis
float temperatura = 25;
int luzLigada;

float resistance;
float leituraTemp;
int constTemperatura = 3975;
//controle da conta
float itensPreco[10];
int itensConsumidos=0;
float total=0;
//intensidadeLuz
int intensidade=255;
//feedBack
int comandos=0; //comandos executados
long int tempoInicial;
int minutos,segundos;
//porta inicia fechada
int porta=0;

//luz inicia apagada
int estadoLuz=0;
void setup(){
    //LCD
    lcd.begin(16, 2);
    //Motor de passo
    motor.setSpeed(30);
    //portas analogicas
    Serial.begin(9600);
    //portas digitais
    pinMode(pinLedPorta, OUTPUT);
    pinMode(pinLedJanela, OUTPUT);

    String fromHotel="Bem vindo ao nosso Hotel!";
    Serial.println(fromHotel);
}
void loop() {
    //comunicados do hotel
    
    //lcd
    String linha1 ="Bem vindo!";

    
    //leitura do controle do ar condicionado
    pinAnalogTemperatura = analogRead(0);
    resistance=(float)(1023-pinAnalogTemperatura)*10000/pinAnalogTemperatura; //get the resistance of the sensor;
    leituraTemp=1/(log(resistance/10000)/constTemperatura+1/298.15)-273.15;//convert to temperature via datasheet ;
    
    //controle temperauta
    if(leituraTemp >= temperatura + 1){
    digitalWrite(pinLedArCond, HIGH);
    
    }
    else
    if(leituraTemp <= temperatura - 1)
    digitalWrite(pinLedArCond, LOW);
    //lcd temperatura
    //Serial.println(leituraTemp);
    lcd.clear();
    lcd.print(linha1);//hora e conta na linha 1
    delay(400);
    if (Serial.available() > 0) {
        estado = Serial.read();
        comandos++;
        lcd.setCursor(0,1);//status na linha 2
        switch (estado) {
            case 'a':                                 //abrir porta
            digitalWrite(pinLedPorta, HIGH);
            digitalWrite(pinLedJanela, LOW);
            //lcd porta
            
            if(porta==0){
                lcd.print("porta abrindo");
                motor.step(48);
                digitalWrite(pinLedPorta, LOW);
                porta=1;
            }
            else{
                //fechar porta
                digitalWrite(pinLedPorta, HIGH);
                digitalWrite(pinLedJanela, LOW);
                //lcd porta
                lcd.print("porta fechando");
                motor.step(-48);
                digitalWrite(pinLedPorta, LOW);
                porta=0;
            }
            break;
            case 'c':                                //abriando janela
            digitalWrite(pinLedPorta, LOW);
            digitalWrite(pinLedJanela, HIGH);
            //lcd janela
            lcd.print("Janela Abrindo");
            motor.step(48);
            digitalWrite(pinLedJanela, LOW);
            break;
            case 'd':                                //fechando janela
            digitalWrite(pinLedPorta, LOW);
            digitalWrite(pinLedJanela, HIGH);
            //lcd janela
            lcd.print("Janela Fechando");
            motor.step(-48);
            digitalWrite(pinLedJanela, LOW);
            break;
            case 'e':                                //aumenta a temperatura
            temperatura++;
            //lcd temperatura
            lcd.print(temperatura);
            lcd.print("          ");
            delay(500);
            break;
            case 'f':                                //diminui a temperatura
            temperatura--;
            //lcd temperatura
            lcd.print(temperatura);
            lcd.print("          ");
            delay(500);
            break;
            
            
            case 'g':                                //liga a luz
            //lcd luz
            if(estadoLuz==0){  
              estadoLuz==1;
            }
            
            lcd.print("Aumentar Luz");
            if(intensidade<245){
                intensidade+=10;
            }

            analogWrite(pinLedLuz,intensidade);
           
            break;

            
            case 'h':
            //lcd luz
            if(estadoLuz==0){  
              estadoLuz==1;
            }
            
            lcd.print("diminuir luz");
            if(intensidade>10){
                intensidade-=10;
            }
            analogWrite(pinLedLuz,intensidade);
            break;

            
            case 'i': //comandos
            comandos--;
            lcd.print(comandos);
            lcd.print(" comandos");
            Serial.print(comandos);
            Serial.println(" comandos");

            break;
            case 'j': //tempo decorrido
            //lcd luz
            minutos=0;
            segundos=millis()/1000;
            minutos=segundos/60;
            if(minutos<1){
                lcd.print(segundos);
                lcd.print(" segundos");
                Serial.print(segundos);
                Serial.println(" segundos");
            }
            else{
                lcd.print(minutos);
                lcd.print(" minutos");
                Serial.print(minutos);
                Serial.println(" minutos");
            }
            break;
            
            case 'z': //comandos
            if(estadoLuz==0){  
              estadoLuz=1;
              analogWrite(pinLedLuz,intensidade);
            }
            else{
              estadoLuz=0;
              analogWrite(pinLedLuz,0);
            }
            
            break;
            default:                               
            lcd.print("ocioso");
            delay(500);
            break;
        }
    }
}
