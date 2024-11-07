#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

const size_t bufferSize = 200 * 1024; // 200 Ko pour chaque fichier
String htmlBuffers[5]; // Buffers pour les 5 pages HTML (utilisation de String)
String cssBuffer;      // Buffer pour la page CSS
String jsBuffer;       // Buffer pour la page JS

void init_wweb() {
  // Page principale pour l'upload
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html; charset=utf-8",
      "<h1>Upload de fichiers</h1>"
      "<form method='POST' action='/upload' enctype='multipart/form-data'>"
      "Sélectionnez la page : "
      "<select name='page'>"
      "<option value='html_1'>html_1</option>"
      "<option value='html_2'>html_2</option>"
      "<option value='html_3'>html_3</option>"
      "<option value='html_4'>html_4</option>"
      "<option value='html_5'>html_5</option>"
      "<option value='css'>css</option>"
      "<option value='js'>js</option>"
      "</select>"
      "<br><input type='file' name='file'>"
      "<br><input type='submit' value='Upload'>"
      "</form>");
  });

  // Gestion de l'upload de fichiers
  server.on("/upload", HTTP_POST, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html; charset=utf-8", "Upload terminé");
  }, 
  [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
    String* buffer = nullptr;
    String page = request->getParam("page", true)->value();

    if (page == "html_1") buffer = &htmlBuffers[0];
    else if (page == "html_2") buffer = &htmlBuffers[1];
    else if (page == "html_3") buffer = &htmlBuffers[2];
    else if (page == "html_4") buffer = &htmlBuffers[3];
    else if (page == "html_5") buffer = &htmlBuffers[4];
    else if (page == "css") buffer = &cssBuffer;
    else if (page == "js") buffer = &jsBuffer;
    else {
      Serial.println("Erreur: Page non reconnue.");
      return;
    }

    if (index == 0) {
      buffer->clear();
      buffer->reserve(bufferSize);
      Serial.printf("Début de l'upload : %s\n", filename.c_str());
    }

    buffer->concat((const char*)data, len);

    if (final) {
      Serial.printf("Upload terminé : %s, taille totale : %u octets\n", filename.c_str(), index + len);
    }
  });

  // Routes pour servir les fichiers
  server.on("/html_1", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (htmlBuffers[0].length() > 0) {
      request->send(200, "text/html; charset=utf-8", htmlBuffers[0]);
    } else {
      request->send(404, "text/plain", "Aucun contenu pour cette page.");
    }
  });

  server.on("/html_2", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (htmlBuffers[1].length() > 0) {
      request->send(200, "text/html; charset=utf-8", htmlBuffers[1]);
    } else {
      request->send(404, "text/plain", "Aucun contenu pour cette page.");
    }
  });

  server.on("/html_3", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (htmlBuffers[2].length() > 0) {
      request->send(200, "text/html; charset=utf-8", htmlBuffers[2]);
    } else {
      request->send(404, "text/plain", "Aucun contenu pour cette page.");
    }
  });

  server.on("/html_4", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (htmlBuffers[3].length() > 0) {
      request->send(200, "text/html; charset=utf-8", htmlBuffers[3]);
    } else {
      request->send(404, "text/plain", "Aucun contenu pour cette page.");
    }
  });

  server.on("/html_5", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (htmlBuffers[4].length() > 0) {
      request->send(200, "text/html; charset=utf-8", htmlBuffers[4]);
    } else {
      request->send(404, "text/plain", "Aucun contenu pour cette page.");
    }
  });

  server.on("/css", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (cssBuffer.length() > 0) {
      request->send(200, "text/css; charset=utf-8", cssBuffer);
    } else {
      request->send(404, "text/plain", "Aucun contenu CSS.");
    }
  });

  server.on("/js", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (jsBuffer.length() > 0) {
      request->send(200, "application/javascript; charset=utf-8", jsBuffer);
    } else {
      request->send(404, "text/plain", "Aucun contenu JavaScript.");
    }
  });

  server.begin();
}
