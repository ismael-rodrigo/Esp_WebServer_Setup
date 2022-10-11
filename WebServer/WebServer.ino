#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

//-------------------VARIABLES GLOBALES--------------------------
int contconexion = 0;


char ssid[25];      
char pass[25];
char broker[25];
char configs[25];


const char *ssidConf = "IoT_Setup";
const char *passConf = "12345678";

String mensaje = "";

//-----------CODIGO HTML PAGINA DE CONFIGURACION---------------
extern String pagina;
extern String alert;

String paginafin = "</div></form></body></html>";

WiFiClient espClient;
ESP8266WebServer server(80);


//------------------------SETUP-----------------------------
void setup() {

  pinMode(13, OUTPUT); // D7 

  Serial.begin(115200);
  Serial.println("");

  EEPROM.begin(512);

  pinMode(14, INPUT);  //D5
  if (digitalRead(14) == 0) {
    Serial.println("Modo config iniciado");
    modoconf();
  }

  leer(0).toCharArray(ssid, 25);
  leer(25).toCharArray(pass, 25);
  leer(50).toCharArray(broker,25);
  leer(75).toCharArray(configs,25);





  setup_wifi();
  server.on("/teste", teste);
  server.begin();
}

void loop() {
  server.handleClient();
  delay(1);
}

void teste(){
  digitalWrite(13,!digitalRead(13));
}


