#include <IRremote.h>
#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny87__) || defined(__AVR_ATtiny167__)
#include "ATtinySerialOut.h"
#endif
#define IR_RECEIVE_PIN 7
#define IR_SEND_PIN 9

// On the Zero and others we switch explicitly to SerialUSB
#if defined(ARDUINO_ARCH_SAMD)
#define Serial SerialUSB
#endif

void setup(){
    Serial.begin(9600);
    IrSender.begin(IR_SEND_PIN, ENABLE_LED_FEEDBACK);
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}


uint16_t logitechZ906Address = 0xA002;
uint8_t sendRepeats= 0;

void loop(){
    if (IrReceiver.decode()) {
      IRData inputCommand = IrReceiver.decodedIRData;
      if (inputCommand.command == 16) {
        IrReceiver.stop();
        Serial.println("VOL UP");
        uint8_t sCommand = 0xAA;
        IrSender.sendNEC(logitechZ906Address, sCommand, sendRepeats);
        delay(50);
      }
      if (inputCommand.command == 17) {
        IrReceiver.stop();
        Serial.println("VOL DOWN");
        uint8_t sCommand = 0x6A;
        IrSender.sendNEC(logitechZ906Address, sCommand, sendRepeats);
        delay(50);
      }
      if (inputCommand.command == 12 || inputCommand.command == 13) {
        IrReceiver.stop();
        Serial.println("POWER ON/OFF, MUTE/UNMUTE");
        uint8_t sCommand = 0x80;
        IrSender.sendNEC(logitechZ906Address, sCommand, sendRepeats);
        delay(50);
      }
      delay(50);
      IrReceiver.start(); // Enable receiving of the next value
  }
}
