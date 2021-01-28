#include <IRremote.h>
#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny87__) || defined(__AVR_ATtiny167__)
#include "ATtinySerialOut.h"
#endif
const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
IRsend irsend;

// On the Zero and others we switch explicitly to SerialUSB
#if defined(ARDUINO_ARCH_SAMD)
#define Serial SerialUSB
#endif
decode_results results;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);

  Serial.print(F("Ready to send IR signals at pin "));
  Serial.println(IR_SEND_PIN);
}

void loop(){
    if (irrecv.decode(&results)){
        if (results.value == 0x1000C || results.value == 0xC) { // Philips TV Powe ON-OFF command
            //Logitech Z906 Power ON-OFF command
            unsigned int irSignal[] = { 9027,4401,609,473,609,1585,609,478,605,477,609,474,608,478,604,478,605,478,609,473,609,478,604,478,604,478,609,473,609,1589,605,477,609,1589,605,477,609,474,608,478,605,477,609,473,609,478,604,478,609,1584,609,1585,608,1589,605,1589,609,1584,609,1589,605,1589,608,1585,609,469,608 };
            irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), 38);
            delay(50);
            irrecv.enableIRIn();
        }
        if(results.value == 0x10010) { // Philips TV Volume UP command
            //Logitech Z906 volume UP command
            unsigned int irSignal[] = { 9021,4404,609,478,600,1593,604,478,605,482,600,482,604,478,604,478,604,482,601,482,604,478,604,482,600,482,605,477,604,1589,610,476,605,1593,604,477,605,1589,609,478,600,1593,605,478,604,1589,608,478,604,1589,605,1589,604,478,605,1589,605,482,604,1589,605,477,604,1593,604,473,600 };
            for (int i = 0; i < 3; i++) {
                irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), 38);
                delay(50);
            }
            irrecv.enableIRIn();
        }
        if(results.value == 0x10011) { // Philips TV Volume DOWN command
            //Logitech Z906 volume DOWN command
            unsigned int irSignal[] = { 9024,4404,604,482,600,1590,608,478,604,478,605,478,604,482,601,481,605,478,604,478,605,482,600,482,605,477,605,477,605,1589,605,482,604,1590,608,480,603,1589,605,482,600,1590,609,478,604,1590,610,1583,605,482,604,1590,605,477,605,1590,604,478,605,1589,609,478,605,477,605,1580,609 };
            for (int i = 0; i < 3; i++) {
                irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), 38);
                delay(50);
            }
            irrecv.enableIRIn();
        }
        irrecv.resume();
    }
}
