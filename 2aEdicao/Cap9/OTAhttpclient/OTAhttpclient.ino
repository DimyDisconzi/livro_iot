#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <EEPROM.h>

void setup() {
  Serial.begin(115200);
  delay(10);
    // Conecta � rede WiFi
  WiFi.begin("ssid", "senha");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }

  // Imprime o endere�o IP
  Serial.println(WiFi.localIP());

  EEPROM.begin(4); // Inicializa a EEPROM para a vers�o
}

void loop() {
  HTTPClient http;
  http.begin("sergiool.esy.es", 80, "/versao.txt");
    // inicio da conexao HTTP e envio do header
  if(http.GET() == 200) {
  uint8_t versao = EEPROM.read(0);
  uint8_t versaoSite = http.getString().toInt();
    Serial.printf("Vers�o Local: %d, Vers�o Remota: %d\n", versao, versaoSite);
    if (versaoSite != versao){
      EEPROM.write(0, versaoSite);
      EEPROM.commit();
      t_httpUpdate_return ret;
ret = ESPhttpUpdate.update("http://sergiool.esy.es/teste.bin");
      if (ret != HTTP_UPDATE_OK) {
        Serial.print("Falha na atualiza��o: ");
  Serial.print(ESPhttpUpdate.getLastError());
        Serial.println(ESPhttpUpdate.getLastErrorString());
      }
    }
  }
  http.end();
}
