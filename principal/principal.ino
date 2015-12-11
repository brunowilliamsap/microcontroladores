//motor de passo
#include <Stepper.h>
#define STEPS 48
#define ITENS_CONTA_MAX 10

//variaveis do controle BT
#include <SoftwareSerial.h>
byte comando[2]; // primeiro byte o que fazer, segundo parâmetro
//SoftwareSerial celular(10,11);


#include <math.h>

Stepper stepper(STEPS, 8, 12, 9, 13);

//lcd
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;


//constantes pinos
int pinLedMotorPorta = 7;       //MOTOR PORTA
int pinLedMotorJanela = 6;       //MOTOR JANELA
int pinLedLuz = 5;       //luz do quarto
int pinLedArCond = 5;
int pinAnalogTemperatura;

//variaveis

float resistance;
float leituraTemp;

int b = 3975;                   //b value of the thermistor
int estado = 0;                 //ESTADO = 0 -> EM ESPERA, ESTADO = 1 -> PORTA , ESTADO = 2 -> JANELA, ESTADO = 3 -> COFRE
int abrirPorta = 1;
int fecharPorta = 0;
int abrirJanela = 1;
int fecharJanela = 0;
int abrirCofre = 1;
int fecharCofre = 0;
int segurancaCofre = 1;
int temperatura;


//ar condicionado fictício
int temperaturaAr= 20; //inicia em 20 graus

//controle da conta

String itensDescricao[10]={ "uno", "duo", "tri" };;
float itensPreco[10];
int itensConsumidos=0;
float total=0;

//
int porta = 0;//porta fechada



void setup() {
    
  // inicializações
    
  lcd.begin(16, 2);
  Serial.begin(9600);  
  
    //PINOS DE SAIDA
    pinMode(pinLedMotorPorta, OUTPUT);
    pinMode(pinLedMotorJanela, OUTPUT);
    
    pinMode(pinLedArCond, OUTPUT);

    //Motor de passo 
    stepper.setSpeed(30);
	Serial.print("funciona");
       
}

void loop() {
  
  //atualizacao da conta
  /*
  while (Serial.available() > 0) {
    itensDescricao[itensConsumidos]=Serial.readStringUntil(';');
    itensPreco[itensConsumidos]=Serial.parseFloat();
    itensConsumidos++;
    total+=itensPreco[itensConsumidos];
   

   
    if (Serial.read() == '\n') {
     //A MODIFICAR
    }
  }
  */
  
    String linha1 ="Hora:";
    int hora=2;
    linha1.concat(hora);
    linha1.concat("Conta:");
    linha1.concat(total);
    //controle de temperatura
    pinAnalogTemperatura = analogRead(0);
    
    resistance=(float)(1023-pinAnalogTemperatura)*10000/pinAnalogTemperatura; //get the resistance of the sensor;
    leituraTemp=1/(log(resistance/10000)/b+1/298.15)-273.15;//convert to temperature via datasheet ;
    if(leituraTemp >= temperatura + 1)
      digitalWrite(pinLedArCond, HIGH);
    else
      if(leituraTemp <= temperatura - 1)
       digitalWrite(pinLedArCond, LOW);
    Serial.println(leituraTemp);
    lcd.clear();
    lcd.print(leituraTemp);
    delay(500);
     
    //controle de estado  l
	Serial.print("olha isso bruno");
    
  if (Serial.available())
  { 
     while(Serial.available())
     {
       Serial.readBytes(comando,2); 
     } 
   
  } 
  

     switch (comando[0]){
      case 1:
        digitalWrite( pinLedMotorPorta, HIGH);
        digitalWrite( pinLedMotorJanela, LOW);
      
		if(porta==0){
			stepper.step(48);
			porta==1;
		}
		else{
			stepper.step(-48);
			porta==1;
			
		}
        lcd.clear();
        lcd.print("porta");
        delay(500);
        break;  
        
      case 2:
        digitalWrite( pinLedMotorPorta, LOW);
        digitalWrite( pinLedMotorJanela, HIGH);
        
      lcd.clear();
        //gerenciamento do motor
        if(comando[1] == 1){
      stepper.step(48);
      lcd.print("Janela : <<"); 
    }
        else{
      stepper.step(-48);
      lcd.print("Janela : >>");
     }
        
        delay(500);
        break;
        
  case 3:
    if(comando[1]==1) {
      temperatura++;
      
      
    }
    else{
      temperatura--;
    }
    
    lcd.print("Temperatura:"); 
    lcd.print(temperaturaAr);
     
        delay(500);
        break;  
    
    
     case 4:
    analogWrite(pinLedLuz,comando[1]);
        lcd.clear();
        lcd.print("Ajustando luz");
        delay(500);
        break;
        
     default:
        digitalWrite( pinLedMotorPorta, LOW);
        digitalWrite( pinLedMotorJanela, LOW);

        lcd.clear();
        lcd.print("em espera");
        delay(500);
        break;
        
    }
    
}
