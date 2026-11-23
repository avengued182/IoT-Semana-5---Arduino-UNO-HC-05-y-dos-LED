/*
  Entrega 2 - Internet de las Cosas
  Control de dos LED mediante HC-05 (Bluetooth simulado en Mokxi)

  Comandos recibidos desde el telefono virtual:
    B: encender LED verde y apagar rojo
    R: encender LED rojo y apagar verde
    A: encender ambos LED
    0: apagar ambos LED
    Otros: comando no valido

  Conexion serial: HC-05 TXD -> Arduino D2 (RX)
                    Arduino D3 (TX) -> divisor -> HC-05 RXD
  Los LED se conectan a D8 (verde) y D9 (rojo).
*/
#include <SoftwareSerial.h>

const byte PIN_BLUETOOTH_RX = 2;
const byte PIN_BLUETOOTH_TX = 3;
const byte LED_VERDE = 8;
const byte LED_ROJO = 9;

SoftwareSerial bluetooth(PIN_BLUETOOTH_RX, PIN_BLUETOOTH_TX);

void responder(const char* mensaje) {
  Serial.println(mensaje);
  bluetooth.println(mensaje);
}

void ejecutarComando(char comando) {
  switch (comando) {
    case 'B':
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_ROJO, LOW);
      responder("OK: LED verde encendido, rojo apagado");
      break;
    case 'R':
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_ROJO, HIGH);
      responder("OK: LED rojo encendido, verde apagado");
      break;
    case 'A':
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_ROJO, HIGH);
      responder("OK: ambos LED encendidos");
      break;
    case '0':
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_ROJO, LOW);
      responder("OK: ambos LED apagados");
      break;
    default:
      responder("ERROR: comando no valido. Usa B, R, A o 0");
      break;
  }
}

void setup() {
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_ROJO, LOW);

  Serial.begin(9600);       // Monitor serial de Arduino
  bluetooth.begin(9600);   // HC-05 en modo de datos
  responder("Sistema listo. Comandos: B, R, A, 0");
}

void loop() {
  if (bluetooth.available() > 0) {
    char comando = bluetooth.read();
    // Ignorar los terminadores habituales de un terminal.
    if (comando != '\n' && comando != '\r') {
      ejecutarComando(comando);
    }
  }
}
