#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 15       // Pino do DHT22
#define DHTTYPE DHT22   // Tipo de sensor
#define TRIG_PIN 12     // Pino TRIG do HC-SR04
#define ECHO_PIN 14     // Pino ECHO do HC-SR04
#define PIR_PIN 13      // Pino do sensor PIR
#define LDR_PIN 34      // Pino analógico do LDR

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
}

void loop() {
  // Leitura do DHT22
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Erro ao ler o DHT22!");
  } else {
    Serial.print("Umidade: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println(" *C");
  }

  // Leitura do HC-SR04
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;

  if (distance > 0) {
    Serial.print("Distância: ");
    Serial.print(distance);
    Serial.println(" cm");
  } else {
    Serial.println("Erro ao ler o HC-SR04!");
  }

  // Leitura do PIR
  int pirState = digitalRead(PIR_PIN);
  if (pirState == HIGH) {
    Serial.println("Movimento detectado!");
  } else {
    Serial.println("Sem movimento.");
  }

  // Leitura do LDR
  int ldrValue = analogRead(LDR_PIN);
  Serial.print("Luminosidade (LDR): ");
  Serial.println(ldrValue);

  // Aguarda 2 segundos antes de nova leitura
  delay(2000);
}
