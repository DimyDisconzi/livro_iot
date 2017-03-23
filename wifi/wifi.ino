#include <ESP8266WiFi.h>

const char* ssid = "dd-wrt";
const char* senha = "kedma256";

void setup() {
  Serial.begin(115200);
  delay(10);

  // Iniciando a conex�o WiFi

  Serial.print("Conectando para a rede  ");
  Serial.println(ssid);

  WiFi.begin(ssid, senha);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endere�o IP: ");
  Serial.println(WiFi.localIP());
}

void loop(){

}
