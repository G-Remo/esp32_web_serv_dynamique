#include <WiFi.h>
#include <ArduinoOTA.h>

const char *ssid = "mon ssid";
const char *password = "mon mdp";
const char *hote = "Serveur Web";

IPAddress staticIP(192, 168, 1, 20);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress DNS(8, 8, 8, 8);

void task_ota(void *t)
{
  // Configuration de l'OTA
  ArduinoOTA.onStart([]() {
    Serial.println("Début de la mise à jour OTA...");
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\nFin de la mise à jour OTA");
  });

  static unsigned int lastProgress = 0;  // Variable pour stocker le dernier pourcentage affiché

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    unsigned int currentProgress = (progress * 100) / total;

    // Afficher uniquement tous les 10%
    if (currentProgress >= lastProgress + 10) {
      Serial.printf("Progression: %u%%\n", currentProgress);
      lastProgress = currentProgress;
    }
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Erreur [%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Erreur d'authentification");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Erreur de début");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Erreur de connexion");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Erreur de réception");
    else if (error == OTA_END_ERROR) Serial.println("Erreur de fin");
  });

  ArduinoOTA.setHostname(hote);
  ArduinoOTA.begin();
  Serial.println("OTA démarré");

  TickType_t xLastWakeTime, xFrequency = 2000;
  xLastWakeTime = xTaskGetTickCount();

  for (;;) {
    vTaskDelayUntil(&xLastWakeTime, xFrequency);

    Serial.printf("RAM: %u, PSRAM: %u\n", ESP.getFreeHeap(), ESP.getFreePsram());
    ArduinoOTA.handle();

  }
}

void init_wwifi()
{
  // Connexion WiFi
  WiFi.setHostname(hote);
  WiFi.config(staticIP, gateway, subnet, DNS);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connecté à WiFi! Adresse IP: ");
  Serial.println(WiFi.localIP());

  xTaskCreate( task_ota, "task_ota", 2048, NULL, 1, NULL);
}
