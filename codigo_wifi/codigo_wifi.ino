#include <Wifi.h>



void setup ()
{
  
}

void loop()
{
  int valor_sensor = leitura_sensor();
  String acao = calcularacao(valor_sensor);
  sendActionToServer(acao);
  delay(1000);
}