

//------------------------SETUP WIFI-----------------------------
void setup_wifi() {

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED and contconexion <50) { 
    ++contconexion;
    delay(250);
    Serial.print(".");
    digitalWrite(13, HIGH);
    delay(250);
    digitalWrite(13, LOW);
  }
  if (contconexion <50) {   
      Serial.println("");
      Serial.println("WiFi conectado");
      Serial.println(WiFi.localIP());
      digitalWrite(13, HIGH);  
  }
  else { 
      Serial.println("");
      Serial.println("Error !");
      digitalWrite(13, LOW);
  }
}


//-------------------PAGINA DE CONFIG--------------------
void paginaconf() {
  server.send(200, "text/html", pagina + mensaje + paginafin); 
}

//------------------ CONFIGURANDO DEVICE ----------------------


void modoconf() {
   
  delay(100);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);

  WiFi.softAP(ssidConf, passConf);
  IPAddress myIP = WiFi.softAPIP(); 
  Serial.print("IP del acces point: ");
  Serial.println(myIP);
  Serial.println("WebServer iniciado...");

  server.on("/", paginaconf);

  server.on("/guardar_conf", guardar_conf);

  
  server.begin();

  while (true) {
      server.handleClient();
  }
}

//---------------------GUARDAR CONFIGURACION-------------------------
void guardar_conf() {
  
  Serial.println(server.arg("ssid"));
  gravar(0,server.arg("ssid"));
  
  Serial.println(server.arg("pass"));
  gravar(25,server.arg("pass"));
  
  Serial.println(server.arg("broker"));
 
  String a = server.arg("1") + server.arg("2") + server.arg("3")+ server.arg("4")+ server.arg("5");


  
  gravar(50,server.arg("broker"));
  gravar(75,a);


  mensaje = "Configuração salva com sucesso!";
  paginaconf();

  delay(4000);
  ESP.reset();

}


//----------------Función para grabar en la EEPROM-------------------
void gravar(int addr, String a) {
  int tamano = a.length(); 
  char inchar[25]; 
  a.toCharArray(inchar, tamano+1);
  for (int i = 0; i < tamano; i++) {
    EEPROM.write(addr+i, inchar[i]);
  }
  for (int i = tamano; i < 25; i++) {
    EEPROM.write(addr+i, 255);
  }
  EEPROM.commit();
}

//--------------------- ler EEPROM------------------------
String leer(int addr) {
   byte lectura;
   String strlectura;
   for (int i = addr; i < addr+25; i++) {
      lectura = EEPROM.read(i);
      if (lectura != 255) {
        strlectura += (char)lectura;
      }
   }
   return strlectura;
}
