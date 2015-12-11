

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
int intensidade;
float resistance;
float leituraTemp;
int constTemperatura = 3975;
//controle da conta
float itensPreco[10];
int itensConsumidos=0;
float total=0;
//intensidadeLuz
int intensidadeLuz=255;
//feedBack
int comandos=0; //comandos executados
long int tempoInicial;
int minutos,segundos;
//porta inicia fechada
int porta=0;
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
}
void loop() {
    //comunicados do hotel
    String fromHotel="Bem vindo ao nosso Hotel!";
    Serial.print(fromHotel);
    //lcd
    String linha1 ="Hora:";
    int hora=2;
    linha1.concat(hora);
    linha1.concat("Conta:");
    linha1.concat(total);
    //leitura do controle do ar condicionado
    pinAnalogTemperatura = analogRead(0);
    resistance=(float)(1023-pinAnalogTemperatura)*10000/pinAnalogTemperatura; //get the resistance of the sensor;
    leituraTemp=1/(log(resistance/10000)/constTemperatura+1/298.15)-273.15;//convert to temperature via datasheet ;
    //controle temperauta
    if(leituraTemp >= temperatura + 1)
    digitalWrite(pinLedArCond, HIGH);
    else
    if(leituraTemp <= temperatura - 1)
    digitalWrite(pinLedArCond, LOW);
    //lcd temperatura
    //Serial.println(leituraTemp);
    lcd.clear();
    lcd.print(linha1);//hora e conta na linha 1
    lcd.setCursor(1,0);//status na linha 2
    if (Serial.available() > 0) {
        estado = Serial.read();
        comandos++;
        switch (estado) {
            case 'a':                                 //abrir porta
            digitalWrite(pinLedPorta, HIGH);
            digitalWrite(pinLedJanela, LOW);
            //lcd porta
            lcd.print("porta           ");
            if(porta==0){
                motor.step(48);
                digitalWrite(pinLedPorta, LOW);
                porta==1;
            }
            else{
                //fechar porta
                digitalWrite(pinLedPorta, HIGH);
                digitalWrite(pinLedJanela, LOW);
                //lcd porta
                lcd.print("porta              ");
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
            lcd.print("Aumentar Luz");
            if(intensidade<245){
                intensidade+=10;
            }
            analogWrite(pinLedLuz,intensidade);
            break;
            case 'h':
            //lcd luz
            lcd.print("diminuir luz");
            if(intensidade>10){
                intensidade-=10;
            }
            analogWrite(pinLedLuz,intensidade);
            break;
            case 'i': //comandos
            lcd.print(comandos);
            lcd.print(" comandos");
            Serial.print(comandos);
            Serial.print(" comandos");
            case 'j': //tempo decorrido
            //lcd luz
            segundos=millis()*1000;
            minutos=segundos/60;
            if(minutos==0){
                lcd.print(segundos);
                lcd.print(" segundos");
                Serial.print(segundos);
                Serial.print(" segundos");
            }
            else{
                lcd.print(minutos);
                lcd.print(" minutos");
                Serial.print(minutos);
                Serial.print(" minutos");
            }
            break;
            default:                                //diminui a intensidade da luz
            //lcd intensidade da luz
            lcd.print("ocioso");
            delay(500);
            break;
        }
    }
}