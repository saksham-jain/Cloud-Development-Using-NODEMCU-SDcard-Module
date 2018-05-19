#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SPI.h>
#include <SD.h>
#include <stdlib.h>

#include "Gsender.h"
#include "webpage_front.h"
#include "webpage_otp.h"

String frontpage = webpage_front;
String otppage   = webpage_otp;
String s,list;

int otpsent;

const int chipSelect = 4;

const char *ssid = "androidAP";                //Enter the credentials of the Wifi Network 
const char *password = "qwerty111";

const char *ssid1 = "SRC-SERVER";         //Enter the credentials of the Access Point
const char *password1 = "12345678";       

ESP8266WebServer server(80);


/*
 * Used to display the Front Page.
 */
void handlefrontpage()
{
  server.send(200, "text/html", frontpage);
  Serial.println("Inside FrontPage");
}


/*
 * Used to compare the OTP entered by the user with the OTP sent.
 * If the OTP Matches the list of file is displayed by calling the filelist function.
 */
void handleotp()
{
  for ( uint8_t i = 0; i < server.args(); i++ )
  {
    if (server.argName(i) == "otp")
    {
      String otpreceived = server.arg(i);
      Serial.print("OTP Received = ");
      Serial.println(otpreceived);
      Serial.print("OTP Sent = ");
      Serial.println(otpsent);
      if (String(otpsent) == otpreceived) { filelist(); server.client().print (list);}
      else server.client().write("Enter the Correct OTP");
    }
  }
}


/*
 * Used to get the Email Address using the POST Method.
 * Also the OTP is sent to the Email ID
 */
void handleSubmit()
{
  if (server.args() > 0 )
  {
    for ( uint8_t i = 0; i < server.args(); i++ )
    {
      if (server.argName(i) == "id")
      {
        String emailid = server.arg(i);
        Serial.println(emailid);

        otpsent = random(10000, 99999);
        Serial.print("OTP Sent = ");
        Serial.println(otpsent);

        server.send(200, "text/html", otppage);

        Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
        String subject = "OTP For SRC-Network";
        if (gsender->Subject(subject)->Send(emailid, String(otpsent)))
          Serial.println("Message send.");
        else
        {
          Serial.print("Error sending message: ");
          Serial.println(gsender->getError());
        }
        delay(1);
      }
    }
  }
}


/*
 * Used to Display the list of files available on the SD Card.
 */
void filelist()
{
  File root;
  root = SD.open("/");
  printDirectory(root, 0);
  Serial.println("done!");
}

void printDirectory(File dir, int numTabs) {
  list = "<h1>LIST OF FILES</h1>";
  while (true) {
    
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      }
    list += "<p><a href=";
    list += entry.name();
    list += " target=\"_self\">";
    list += entry.name();
    list += "</a>";
    list += "\n";
    if (entry.isDirectory()) {
      printDirectory(entry, numTabs + 1);
    } else {
      }
    entry.close();
    
  }
  Serial.println(list);
}


/*
 * Called when an unknown URL is requested. 
 *We use it to get the filename which the User wants to download.
 */
void handlenotfound()    
  {
    String url1 = server.uri();
    char url2[20],url3[20];
    int l = url1.length();
    url1.toCharArray(url2,l+1);
    for(int i=1;i<=l;i++)
    {
      url3[i-1] = url2[i];
    }
    Serial.println(url1);
    
    if(url1 != "/favicon.ico") handleDownload(String(url3));
    server.client().print (list);
  }  
  

/*
 * This function is used to send the file to the User
 * Called from the handlenotfound function.
 * Takes the file name as an argument.
 */
  void handleDownload(String inc) {

  int32_t time = millis();
  File dataFile = SD.open(inc);
  int fsizeDisk = dataFile.size();
  Serial.print("fsizeDisk: "); Serial.println(fsizeDisk);

  String WebString = "";
  WebString += "HTTP/1.1 200 OK\r\n";
  WebString += "Content-Type: text/plain\r\n";
  WebString += "Content-Disposition: attachment; filename=";
  WebString += inc;
  WebString += "\r\n";
  WebString += "Content-Length: " + String(fsizeDisk) + "\r\n";
  WebString += "\r\n";
  server.sendContent(WebString);

  char buf[1024];
  int siz = dataFile.size();
  while (siz > 0) {
    size_t len = std::min((int)(sizeof(buf) - 1), siz);
    dataFile.read((uint8_t *)buf, len);
    server.client().write((const char*)buf, len);
    siz -= len;
  }
  Serial.print(siz);
  Serial.println(" Bytes left!");

  dataFile.close();
  time = millis() - time;
  Serial.print(time); Serial.println(" ms elapsed");
}


void setup() {
  delay(500);
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  WiFi.softAP(ssid1,password1);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.println("");
  

  // Start the server
  server.begin();
  Serial.println("server started");
  Serial.println(WiFi.localIP());

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("\nCard failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("\nCard Initialized.");

  server.on("/src", handlefrontpage);
  server.on("/submit", handleSubmit);
  server.on("/otp",       handleotp);
  
  server.onNotFound(handlenotfound);
  
  server.begin();

  Serial.println("HTTP server started");
}

void loop()
{
  server.handleClient();
}
