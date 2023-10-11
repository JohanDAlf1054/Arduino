//Definicion del pin 13 como salida para el led 
int led = 13;
//Definicion del pin 3 como salida para el buzzer
int buzzer = 3;
//Definicion de la valirable para tomar el valor del sensor 
int valorSensor = 0;
//Definicion del pin para el boton
int button = 4;
//Definicion de varibale para el estado del boton 
int buttonstate = 0;
//Definicion de la variable i para poder comenzar el ciclo FOR
int i = 0;

//Incluir la libreria para el sensor de temperatura
#include "DHT.h"
//Definir el pin 2 como entrada de la informacion.
#define DHTPIN 2 
//Definir el sensor que estamos utilizando
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


void setup(){
  //Inicio del puerto serial 
  Serial.begin(9600);
  //Declarar el led y buzzer como salida 
  pinMode(led, OUTPUT);
  pinMode (buzzer, OUTPUT);
  //Declarar el boton como entrada
  pinMode(button, INPUT);
  
  //Comenzar el testo hacia el sensor
  Serial.println("DHTxx test!");
  dht.begin();
  }

void loop() {
  //SENSOR DE FUEGO
  // Leer el valor del sensor 
  valorSensor = analogRead(A0);
  //Mostrar el siguiente mensaje hacia la consola
  Serial.println("El valor del sesnsor de fuego es de: " );
  //Mostrar el valor del sensor
  Serial.println(valorSensor);


  // Activacion del buzzer
  if (valorSensor < 500){
    //Mostrara el sisguiente mensaje cuando el sesnor de fuego tenga un valor menor que 500
    Serial.print("Hay fuego en el lugar por favor EVACUE");
    //Iniciar un ciclo for para encender el led y hacer sonar el buzzer
    for(i=0; i<10; i++){
      //Encender el led 
      digitalWrite(led, HIGH);
      delay(100);
      //Desactivar el LED 
      digitalWrite(led, LOW);
      delay(50);
      //Encender el buzzer
      tone(buzzer, 1000);
      delay(100);
      //Desactivar el buzzer
      noTone(buzzer);
      delay(100);
      
    }
    
  }
delay(2000);
//Definir las siguiente variables como flotatantes para los valores del sensor de temperatura
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  //Sentencia para revisar que elsensor este funcionando con la placa Arduino
  if (isnan(h) || isnan(t) || isnan(f)) {
  Serial.println("Failed to read from DHT sensor!");
  return;
  }
  //Guardar los datos en las siguientes varaibles
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  //Mostara por consola los siguientes datos obtenidos por el sensor
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  //Lectura del boton.
  buttonstate = digitalRead(button);
  //Sentencia para cuando el boton sea oprimido.
  if(buttonstate == LOW){
    //Mostrar el siguiente mensaje en consola
      Serial.print("Hay fuego en el lugar por favor EVACUE");
      //Iniciar el ciclo for para el bombillo led y el buzzer
      for(i=0; i<50; i++){
      //Activiar el led
      digitalWrite(led, HIGH);
      delay(100);
      //Desactivar el LED 
      digitalWrite(led, LOW);
      delay(50);
      //Activar el buzzer
      tone(buzzer, 1000);
      delay(1000);
      //Desactivar el buzzer
      noTone(buzzer);
      delay(50);
    }
  }
}
