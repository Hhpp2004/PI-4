#include <Arduino.h>
#include <vector>
#include <WiFi.h>
#define MOTOR_PIN 15 // Pino conectado ao sinal do driver de motor
#define UV_SENSOR_ADDRESS 0x48 // Endereço I2C do sensor UV

Servo motor;
unsigned long startTimeCurve = 0;
unsigned long startTimeFollowLine = 0;
unsigned long endTimeCurve = 0;
unsigned long endTimeFollowLine = 0;

const char *rede = "BugKey";
const char *senha = "BugKey123";

void setup() {
  Wire.begin();
  Serial.begin(9600);
  motor.attach(MOTOR_PIN);
  motor.write(90); // Centraliza o motor

  Serial.begin(115200);
  Wifi.begin(rede,senha);

  // conexão com a rede  
  while(Wifi.status() != WL_CONNECTED)
  {
    delay(1000);
    serial.println("Conectando na rede WIFI");
  }
  serial.println("Conectado com sucesso");
}

void loop() {
  int uvValue = readUVSensor();
  if (uvValue > 100) { // Supondo que o sensor retorna um valor maior que 100 quando detecta luz UV
    startTimeCurve = millis(); // Registra o início da curva
    motor.write(180); // Mova o carrinho para a direita
    delay(1000); // Simula a duração da curva
    endTimeCurve = millis(); // Registra o fim da curva
    recordTime("curva", startTimeCurve, endTimeCurve);
    motor.write(90); // Retorna o motor ao centro
  } else {
    startTimeFollowLine = millis(); // Registra o início de seguir linha
    motor.write(0); // Mova o carrinho para a esquerda
    delay(1000); // Simula a duração de seguir linha
    endTimeFollowLine = millis(); // Registra o fim de seguir linha
    recordTime("seguir linha", startTimeFollowLine, endTimeFollowLine);
    motor.write(90); // Retorna o motor ao centro
  }
  delay(100); // Ajuste o tempo de resposta conforme necessário
}

int readUVSensor() {
  Wire.requestFrom(UV_SENSOR_ADDRESS, 1);
  if (Wire.available()) {
    return Wire.read(); // Lê o valor do sensor
  }
  return 0; // Valor padrão caso o sensor não retorne nada
}

void recordTime(const String &action, unsigned long start, unsigned long end) {
  unsigned long duration = end - start;
  Serial.print(action);
  Serial.print(": ");
  Serial.print(duration);
  Serial.println(" ms");
  // Aqui você pode adicionar o código para salvar esses tempos em um banco de dados
  struct res_tempo 
  {
    String acao;
    unsigned long inicio;
    unsigned long fim;
  }
  static std::vector<TimeRecord> records;
  records.push_bac({acao,inicio,end});

  for(const auto &records : records)
  {
    Serial.println(record.acao);
    Serial.println(": ");
    Serial.println(record.inicio - record.fim);
    Serial.println(" ms");
  }
  records.clear();
}

void sendPostRequest(String param1, String param2) {
  if ((WiFi.status() == WL_CONNECTED)) { 
    HTTPClient http;
    
    String serverPath = "D://PI_4//server_main.js"; // Caminho do servidor onde os dados serão enviados
    String postData = "param1=" + param1 + "&param2=" + param2; // Constrói a string de dados a partir dos parâmetros fornecidos
    
    http.begin(serverPath.c_str()); // Inicia uma nova solicitação HTTP
    http.addHeader("Content-Type", "http://localhost:3000"); // Define o tipo de conteúdo
    int httpResponseCode = http.POST(postData); // Envia os dados
    
    if(httpResponseCode > 0){
      String response = http.getString(); // Obtém a resposta do servidor
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Erro ao enviar dados: ");
      Serial.println(httpResponseCode);
    }
    http.end(); // Finaliza a solicitação HTTP
  }
}