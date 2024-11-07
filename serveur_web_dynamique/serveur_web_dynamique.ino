#include "wwifi.h"
#include "wweb.h"

void setup()
{
  Serial.begin(115200);

  init_wwifi();
  init_wweb();
}

void loop() {vTaskDelete(NULL);}
