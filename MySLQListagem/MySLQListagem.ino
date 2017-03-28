#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
WiFiClient client;
MySQL_Connection conn(&client);

void setup() {
  IPAddress server_addr;
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

  // Obt�m o IP do servidor, pois a conex�o n�o aceita nomes...
  WiFi.hostByName("db4free.net", server_addr);

  Serial.println(server_addr);
  Serial.println("Conectando ...");
  // Ip do Servidor, porta, usu�rio e senha
  if (conn.connect(server_addr, 3306, "sergiool_iot", "iotiot256")) {
    delay(1000);
  }
  else
    Serial.println("Falha na conex�o");
}

void loop() {

  // Inicia as vari�veis
  MySQL_Cursor cur_mem(&conn);
  char SELECT_SQL[] = "SELECT * FROM iotiot.registro_temp";
  Serial.println("Consultando dados ...");

  // Executa a consulta
  cur_mem.execute(SELECT_SQL);

  // Obt�m o cabe�alho das colunas
  column_names *cols = cur_mem.get_columns();
  for (int f = 0; f < cols->num_fields; f++) {
    Serial.print(cols->fields[f]->name);
    if (f < cols->num_fields-1)
      Serial.print('|');
  }
  Serial.println();

  // Obt�m as linhas
  row_values *row = NULL;
  while (row = cur_mem.get_next_row()) {
    for (int f = 0; f < cols->num_fields; f++) { // Para cada linha
      Serial.print(row->values[f]);
      if (f < cols->num_fields-1)
        Serial.print('|');
    }
    Serial.println();
  }

  // Libera mem�ria. Importante devido �s limita��es dessa plataforma
  cur_mem.close();
  delay(2000);

}
