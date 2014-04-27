#include <SoftwareSerial.h>
#define RED 10
#define GREEN 11
#define BAUD 9600
#define RX 0
#define TX 1

//commands
#define HELP 100
#define STATUS 101
#define BOTH 102
#define NOOP -1

SoftwareSerial bluetooth(RX, TX); // RX, TX
char bluetoothData;
String bluetoothCommand = "";

void setup() {
  bluetooth.begin(BAUD);
  bluetooth.println("Ready!");
  showHelp();
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void loop() {
  if (bluetooth.available())
  {
    bluetoothData = bluetooth.read();
    if (bluetoothData == '\n' && bluetoothCommand.length() > 0) {
      int result[3];  //command structure: 0 - led, 1 - high/low, 3 - non-led command
      parseCommand(bluetoothCommand, result);  //parse a string into a command structure
      executeCommand(result);                  //execute the command
      bluetoothCommand = "";                   //clean string for next command
    }
    else {
      bluetoothCommand += bluetoothData;       //add character to string
    }
  }
  delay(100);
}

void parseCommand(String command, int result[]) {
  command.trim();
  command.toLowerCase();
  bluetooth.println("Command received: " + command);
  if (command == "?" || command == "help")
    result[2] = HELP;
  else if (command == "status")
    result[2] = STATUS;
  else {
    result[0] = NOOP;
    result[1] = NOOP;
    result[2] = NOOP;
    int index = command.indexOf(' ');
    if (index > 0) {
      String led = command.substring(0, index);
      String op = command.substring(index + 1);
      bluetooth.println("LED: " + led + "  OP: " + op);

      if (led == "red")
        result[0] = RED;
      else if (led == "green")
        result[0] = GREEN;
      else if (led == "both")
        result[0] = BOTH;

      if (op == "on")
        result[1] = HIGH;
      else if (op == "off")
        result[1] = LOW;
    }
  }
}

void executeCommand(int result[]) {
  switch (result[2]) {
    case HELP:
      showHelp();
      break;
    case STATUS:
      showStatus();
      break;
    case NOOP:
      if (result[0] == NOOP || result[1] == NOOP) {
        bluetooth.println("Command error - try again");
      }
      else {
        if (result[0] == BOTH) {
          digitalWrite(RED, result[1]);
          digitalWrite(GREEN, result[1]);
        }
        else {
          digitalWrite(result[0], result[1]);
        }
      }
      break;
    default:
      break;
  }
}

void showHelp() {
  bluetooth.println("Available commands:\nRed On/Off\nGreen On/Off\nBoth On/Off\nStatus\n?/help - this help");
}

void showStatus() {
  bluetooth.print("Red LED: ");
  bluetooth.println((digitalRead(RED) == HIGH ? "On" : "Off"));
  bluetooth.print("Green LED: ");
  bluetooth.println((digitalRead(GREEN) == HIGH ? "On" : "Off"));
}
