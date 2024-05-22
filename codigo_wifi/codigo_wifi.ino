#include <Wifi.h>

const char *rede = "BugKey";
const char *senha = "BugKey123";

void setup ()
{
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

void loop()
{
  int valor_sensor = leitura_sensor();
  String acao = calcularacao(valor_sensor);
  sendActionToServer(acao);
  delay(1000);
}