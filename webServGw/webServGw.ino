/*--------------------------------------------------------------
  Modified Program updated 18 Feb 2019

  --------------------------------------------------------------*/

#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>

// MAC address from Ethernet shield sticker under board
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 103); // IP address, may need to change depending on network
EthernetServer server(80);      // create a server at port 80

File webFile;

String readString = "?";
int vhfCurrent = 1;             //This variable stores the state of the VHF pre-Amp
int uhfCurrent = 1;             //This variable stores the state of the UHF pre-Amp
int shfCurrent = 1;              //This variable stores the state of the SW pre-Amp

//*********************************************************************************
void setup()
{
  Ethernet.begin(mac, ip);      // initialize Ethernet device
  server.begin();               // start to listen for clients
  Serial.begin(9600);           // for debugging
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  //Row 1
  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(30, OUTPUT);
  //Row 2
  pinMode(23, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(29, OUTPUT);
  pinMode(31, OUTPUT);
  //Row 3
  pinMode(32, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(40, OUTPUT);
  Serial.println("Pins 22,23,24,25,26,27,28,29,30,31,32,34,36,38,40 set to OUTPUT");

  // initialize SD card
  Serial.println("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("ERROR - SD card initialization failed!");
    return;    // init failed
  }
  Serial.println("SUCCESS - SD card initialized.");

  // check for STAGE.htm file
  if (!SD.exists("STAGE.HTM")) {
    Serial.println("ERROR - Can't find STAGE.HTM file!");
    return;  // can't find index file
  }
  Serial.println("SUCCESS - Found STAGE.HTM file.");
}
//**********************************************************************
void loop()
{
  EthernetClient client = server.available();  // try to get client

  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        if (readString.length() < 100) {
          readString += c;                    //Creating the string readString
          readString.trim();                  //removing white spaces and end characters
          readString.remove(12);
        }
        //*****************Controlling LED's****Row1*******************
        if (c == '\n') {
          Serial.println(readString);

          //Using readString for Identifying the buttons
          if (readString == "?POST/VHF_1H") {
            Serial.println("Button  1 found");
            digitalWrite(22, HIGH);
            digitalWrite(24, LOW );
            digitalWrite(26, LOW );
            digitalWrite(28, LOW );
          }

          if (readString == "?POST/VHF_2H") {
            Serial.println("Button  2 found");
            digitalWrite(22, LOW );
            digitalWrite(24, HIGH);
            digitalWrite(26, LOW );
            digitalWrite(28, LOW );
          }

          if (readString == "?POST/VHF_3H") {
            Serial.println("Button  3 found");
            digitalWrite(22, LOW );
            digitalWrite(24, LOW );
            digitalWrite(26, HIGH);
            digitalWrite(28, LOW );
          }

          if (readString == "?POST/VHF_4H") {
            Serial.println("Button  4 found");
            digitalWrite(22, LOW );
            digitalWrite(24, LOW );
            digitalWrite(26, LOW );
            digitalWrite(28, HIGH);
          }
          //Toggling the VHF pre-Amp
          if (readString == "?POST/VHF_13") {
            Serial.println("Button  5(13) found");
            if (vhfCurrent == 1) {            /*Checking current status*/
              digitalWrite(30,  HIGH );
              vhfCurrent = 0;                 /*reversing status*/
            }

            else {
              digitalWrite(30,  LOW );
              vhfCurrent = 1;                 /*reversing status*/
            }
          }
          //**************************Row 2***********************************
          if (readString == "?POST/UHF_6H") {
            Serial.println("Button  6 found");
            digitalWrite(23, HIGH);
            digitalWrite(25, LOW );
            digitalWrite(27, LOW );
            digitalWrite(29, LOW );
          }

          if (readString == "?POST/UHF_7H") {
            Serial.println("Button  7 found");
            digitalWrite(23, LOW );
            digitalWrite(25, HIGH);
            digitalWrite(27, LOW );
            digitalWrite(29, LOW );
          }

          if (readString == "?POST/UHF_8H") {
            Serial.println("Button  8 found");
            digitalWrite(23, LOW );
            digitalWrite(25, LOW );
            digitalWrite(27, HIGH);
            digitalWrite(29, LOW );
          }

          if (readString == "?POST/UHF_9H") {
            Serial.println("Button  9 found");
            digitalWrite(23, LOW );
            digitalWrite(25, LOW );
            digitalWrite(27, LOW );
            digitalWrite(29, HIGH);
          }
          //Toggling the UHF pre-Amp
          if (readString == "?POST/UHF_14") {
            Serial.println("Button  10(14) found");
            if (uhfCurrent == 1) {            /*Checking current status*/
              digitalWrite(31,  HIGH );
              uhfCurrent = 0;                 /*reversing status*/
            }

            else {
              digitalWrite(31,  LOW );
              uhfCurrent = 1;                 /*reversing status*/
            }
          }
          //**************************Row3*********************************
          if (readString == "?POST/SHF_11") {
            Serial.println("Button  11 found");
            digitalWrite(32, HIGH);
            digitalWrite(34, LOW );
            digitalWrite(36, LOW );
            digitalWrite(38, LOW );
          }

          if (readString == "?POST/SHF_12") {
            Serial.println("Button  12 found");
            digitalWrite(32, LOW );
            digitalWrite(34, HIGH);
            digitalWrite(36, LOW );
            digitalWrite(38, LOW );
          }

          if (readString == "?POST/SHF_13") {
            Serial.println("Button  13 found");
            digitalWrite(32, LOW );
            digitalWrite(34, LOW );
            digitalWrite(36, HIGH);
            digitalWrite(38, LOW );
          }

          if (readString == "?POST/SHF_14") {
            Serial.println("Button  14 found");
            digitalWrite(32, LOW );
            digitalWrite(34, LOW );
            digitalWrite(36, LOW );
            digitalWrite(38, HIGH);
          }
          //Toggling the SHF pre-Amp
          if (readString == "?POST/SHF_15") {
            Serial.println("Button  15(15) found");
            if (shfCurrent == 1) {            /*Checking current status*/
              digitalWrite(40,  HIGH );
              shfCurrent = 0;                 /*reversing status*/
            }

            else {
              digitalWrite(40,  LOW );
              shfCurrent = 1;                 /*reversing status*/
            }
          }
          //************************************************************************
          client.println("<HTTP/1.1 200 OK>");
          client.println("<Connection-Type: text/html>");
          client.println("<Connection:close>");
          client.println();
          //******************************************************************

          // send web page
          webFile = SD.open("STAGE.HTM");        // open web page file
          if (webFile) {
            while (webFile.available()) {
              client.write(webFile.read()); // send web page to client
            }
            webFile.close();
          }
          break;

        }
      }
    }
  }
  delay(3);
  client.stop();

  readString = "?"; //resetting the variable
}
