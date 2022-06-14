

/*---------------------------------------------------------------------------------------------
  vestido esp32 by Leandro Munoz
  
  Based on file
  Open Sound Control (OSC) library for the ESP8266/ESP32

  Example for sending messages from the ESP8266/ESP32 to a remote computer
  The example is sending "hello, osc." to the address "/test".
  
  we acknowledge also use of Keypad library
  

--------------------------------------------------------------------------------------------- */

#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>


#include <Key.h>
#include <Keypad.h>


char ssid[] = "autonetwork";          // your network SSID (name)
char pass[] = "mer1vigl3oso";                    // your network password

WiFiUDP Udp;                                // A UDP instance to let us send and receive packets over UDP
const IPAddress outIp(192,168,137,1);        // remote IP of your computer
const unsigned int outPort = 10005;          // remote port to receive OSC
const unsigned int outPort2 = 10000;         // to processing
const unsigned int localPort = 8888;        // local port to listen for OSC packets (actually not used for sending)

///////////////////
//matriz de toques
///////////////////

const byte partes = 15;
                        // brader // braizq // legder   //legizq    //espalda
byte partes_pins [partes] = {15,2,4,  16,17,5,  18,19,21,3, 12,14,27,26, 25 };

const byte manos = 2;
                        //izq //der
byte manos_pins [manos] = {1,22};

char toques_vestido [manos][partes] = {
  ///////         no func
  {'a','b','c', '1','2','3', 'd','e','f','g', 'h','i','j','k', 'l'},
  {'A','B','C', '1','2','3', 'D','E','F','G', 'H','I','J','K', 'L'}
};

Keypad vestido = Keypad(makeKeymap(toques_vestido), manos_pins, partes_pins,manos, partes); 

int msg;



void setup() {
    Serial.begin(115200);

    // Connect to WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Starting UDP");
    Udp.begin(localPort);
    Serial.print("Local port: ");
#ifdef ESP32
    Serial.println(localPort);
#else
    Serial.println(Udp.localPort());
#endif

}

void loop() {

  
  OSCBundle mensa;
  
    if (vestido.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
        if (vestido.key[i].kchar != 98 || vestido.key[i].kchar != 0 ){
          
        
            if ( vestido.key[i].stateChanged )   // Only find keys that have changed state.
            {
                switch (vestido.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
                    msg = 1;
                break;
                    case HOLD:
                    msg = 5;
                break;
                    case RELEASED:
                    msg = 0;
                break;
                    case IDLE:
                    msg = 0;
                }
                /*Serial.print("Key ");
                Serial.print(kpd.key[i].kchar);
                Serial.println(msg);*/
                char tecla = (vestido.key[i].kchar);
                switch (tecla) {
                  case 'a':
                  mensa.add("/brader/mune").add(msg);
                  
                break;
                  case 'b':
                  mensa.add("/brader/codo").add(msg);
                  
                break;
                  case 'c':
                  mensa.add("/brader/hombro").add(msg);
                  
                break;
                  case 'd':
                  mensa.add("izq/legder/tobi").add(msg);
                  
                break;
                  case 'e':
                  mensa.add("izq/legder/panto").add(msg);
                  
                break;
                  case 'f':
                  mensa.add("izq/legder/muslo1").add(msg);
                  
                break;
                  case 'g':
                  mensa.add("izq/legder/muslo2").add(msg);
                  
                break;
                  case 'D':
                  mensa.add("der/legder/tobi").add(msg);
                 
                break;
                  case 'E':
                  mensa.add("der/legder/panto").add(msg);
                  
                break;
                  case 'F':
                  mensa.add("der/legder/muslo1").add(msg);
                  
                break;
                  case 'G':
                  mensa.add("der/legder/muslo2").add(msg);
                  
                break;
                  case 'h':
                  mensa.add("izq/legizq/tobi").add(msg);
                  
                break;
                  case 'i':
                  mensa.add("izq/legizq/panto").add(msg);
                  
                break;
                  case 'j':
                  mensa.add("izq/legizq/muslo1").add(msg);
                  
                break;
                  case 'k':
                  mensa.add("izq/legizq/muslo2").add(msg);
                  
                break;
                  case 'H':
                  mensa.add("der/legizq/tobi").add(msg);
                  
                break;
                  case 'I':
                  mensa.add("der/legizq/panto").add(msg);
                  
                break;
                  case 'J':
                  mensa.add("der/legizq/muslo1").add(msg);
                  
                break;
                  case 'K':
                  mensa.add("der/leizq/muslo2").add(msg);
                  
                break;
                  case 'l':
                  mensa.add("izq/espalda").add(msg);
                  
                break;
                  case 'L':
                  mensa.add("der/espalda").add(msg);
                  
                break; 
                }

                
            }
        }
        }
    }
    
    Udp.beginPacket(outIp, outPort2); 
    mensa.send(Udp);
    Udp.endPacket();
    mensa.empty();
 
  
    
}
