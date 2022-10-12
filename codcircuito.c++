#include <Servo.h>

void monitorar_umd(float sinal);

//Pino Sensor de Umidade

#define sensor_umidade A0

Servo servo;

//Pinos LED RGB
const int vermelho = 8;
const int amarelo = 9;
const int verde = 10;

//posicao
int posicao = 0;

unsigned long tempoAnterior = 0; // Variável utilizada para guardar o tempo anterior
unsigned long intervalo = 1000; // Intervalo de tempo em MS para cada leituraa


void setup() {
 
  Serial.begin(9600);
 
  //Servo
  servo.attach(11, 500, 2500);
 
  //Definir pinos de saída
  pinMode(vermelho, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(verde, OUTPUT);

 
}

void loop() {

  //Ler do sinal do sensor
  int sinal_umd = analogRead(sensor_umidade);
 
  unsigned long tempoAtual = millis(); // Leitura atual do tempo em que o Arduino Nano está ligado
 
  if (tempoAtual-tempoAnterior > intervalo){ // realiza leituras temporizadas sem parar o microcontrolador
      tempoAnterior =tempoAtual; // Guarda o tempo anterior como o ultimo intervalo de tempo lido
       
  monitorar_umd(sinal_umd);
  }
 
}

void monitorar_umd(float sinal) {
 
  //Transformar o valor analógico recebido em porcentagem
  //int umidade = map(sinal, 1023, 0, 0, 100);
  int umidade = sinal;
 
  Serial.print("UMD: ");
  Serial.println(umidade);
 
  if(umidade<=1023 && umidade>=682) {
   
     
    digitalWrite(vermelho, LOW);
    digitalWrite(amarelo, LOW);
    digitalWrite(verde, HIGH);
   
      //Desligar sistema de irrigação
  servo.write(0);
   
  }
 
  else if(umidade<=681 && umidade>=340){
   
    digitalWrite(vermelho, LOW);
    digitalWrite(amarelo, HIGH);
    digitalWrite(verde, LOW);
   
      //Desligar sistema de irrigação
  servo.write(0);
   
  }
 
  else if(umidade<=339 && umidade>=0) {
   
    digitalWrite(vermelho, HIGH);
    digitalWrite(amarelo, LOW);
    digitalWrite(verde, LOW);
   
      //Acionar sistema de irrigação
      servo.write(90);
      Serial.println("Irrigando...");
   
 
    }else{
      Serial.println("Erro de leitura...");
    }
 
  return;
}

