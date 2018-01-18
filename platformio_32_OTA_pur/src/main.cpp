/******************************************************************************
 * platformio_32_OTA_pur
 * Dieses Projekt soll die Vorlage für alle ESP32 - Projekte sein
 * Es beinhaltet OTA
 * ***************************************************************************/

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* ssid = "RegQuadFritz";
const char* password = "Arabella, die grosse Katze.";
uint64_t chipid;

//*********************************************************************
void setup_OTA(void){
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.println("Connection Failed! Rebooting...");
      delay(5000);
      ESP.restart();
    }  
    // Port defaults to 3232
    // ArduinoOTA.setPort(3232);
  
    // Hostname defaults to esp3232-[MAC]
    // ArduinoOTA.setHostname("ESP32");
  
    // No authentication by default
    // ArduinoOTA.setPassword("admin");
  
    // Password can be set with it's md5 value as well
    // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
    // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");
  
    ArduinoOTA.onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";
  
// NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    });
    ArduinoOTA.onStart([]() { Serial.printf("\nS T A R T  OTA-Uebertragung"); });
    //jetzt die Ausgabe der einzelnen Prozentwerte
    /*ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });*/
    ArduinoOTA.onEnd([]() { Serial.printf("\rE N D E  OTA-Uebertragung\r\n"); });
      ArduinoOTA.onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });
    ArduinoOTA.begin();
    Serial.printf("Ready");
    Serial.printf("\rIP address : "); Serial.print(WiFi.localIP());
    Serial.printf("\rmacAdresse : "); Serial.print(WiFi.macAddress()); 
	Serial.printf("\rsubnetMask : "); Serial.print(WiFi.subnetMask());
	Serial.printf("\rHostname   : "); Serial.print( ArduinoOTA.getHostname());
    Serial.printf("\rSPI-FLASH-SIZE : "); Serial.print(spi_flash_get_chip_size());
    chipid = ESP.getEfuseMac();       //The chip ID is essentially its MAC address(length: 6 bytes).
    Serial.printf("\rESP32 Chip ID  : %04X--%08X\r", (uint16_t)(chipid >> 32), (uint32_t)chipid);//print High 2 bytes
}//ende setup_OTA()
//*********************************************************************
void setup() {
  Serial.begin(115200);
  Serial.println("Booting 09.01.2018 sy");
  setup_OTA();
}
//*********************************************************************
//#####################################################################
void loop() {
  ArduinoOTA.handle();
}
//#####################################################################

//eof