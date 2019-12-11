#include <IRremote.h> // Librería para el control remoto https://github.com/z3t0/Arduino-IRremote

int RECV_PIN = 3; // Pin conectado al sensor infrarrojo. La comunicación entre la arduino nano(master) y la arduino mega(slave) es a través de la conexión serial RX/TX
IRrecv irrecv(RECV_PIN);
decode_results results;
char command;
boolean understood = false;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    understood = true;
    switch(results.value) {
      case 0xF7C03F:
        command = 'A';
        break;
      case 0xF740BF:
        command = 'B';
        break;
      case 0xF7807F:
        command = 'C';
        break;
      case 0xF700FF:
        command = 'D';
        break;
      case 0xF7E01F:
        command = 'E';
        break;
      case 0xF7609F:
        command = 'F';
        break;
      case 0xF7A05F:
        command = 'G';
        break;
      case 0xF720DF:
        command = 'H';
        break;
      case 0xF7D02F:
        command = 'I';
        break;
      case 0xF750AF:
        command = 'J';
        break;
      case 0xF7906F:
        command = 'K';
        break;
      case 0xF710EF:
        command = 'L';
        break;
      case 0xF7F00F:
        command = 'M';
        break;
      case 0xF7708F:
        command = 'N';
        break;
      case 0xF7B04F:
        command = 'O';
        break;
      case 0xF730CF:
        command = 'P';
        break;
      case 0xF7C837:
        command = 'Q';
        break;
      case 0xF748B7:
        command = 'R';
        break;
      case 0xF78877:
        command = 'S';
        break;
      case 0xF708F7:
        command = 'T';
        break;
      case 0xF7E817:
        command = 'U';
        break;
      case 0xF76897:
        command = 'V';
        break;
      case 0xF7A857:
        command = 'W';
        break;
      case 0xF728D7:
        command = 'X';
        break;
      default:
        understood = false;
    }
    if (understood) Serial.println(command);
    irrecv.resume(); // Receive the next value
  }
}
