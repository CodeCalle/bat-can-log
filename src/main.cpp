#include "oledDisplay.hpp"
#include "can.h"
#include "blink.hpp"

uint32_t alerts = 0;
message msg;

void print_message_debug(message* msg) {
    Serial.printf("ID: %d : ", msg->id);
    Serial.printf("%#018llx : ", msg->data.raw);
    Serial.printf("%d\n", msg->data.raw);

    Serial.printf("---------------------------------------------------------------------\n");
}

void setup() {
  Serial.begin(115200);

  config_and_start_twai();
}

void loop() {
  alerts = twai_read_alerts(&alerts, 0);
  if ( (alerts & TWAI_ALERT_RX_DATA) != 0 ) {
    receive_can_message(&msg);
    print_message_debug(&msg);
    alerts = 0;
  }
}