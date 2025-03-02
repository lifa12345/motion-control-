#include <WiFi.h>
#include <ThingSpeak.h>

const char *ssid = "CSF2.4";               // Remplace par le nom de ton réseau Wi-Fi
const char *password = "Zk6AvFv6";       // Remplace par ton mot de passe Wi-Fi
unsigned long myChannelNumber = 2853904;  // Remplace par le numéro de ton canal ThingSpeak
const char *myWriteAPIKey = "DLY35W2ETGA3VN65";   // Remplace par ta clé API d'écriture ThingSpeak

WiFiClient client;

int joystickXPin = 34; // Broche X du joystick (GPIO34)
int joystickYPin = 35; // Broche Y du joystick (GPIO35)

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Connexion au réseau Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au Wi-Fi...");
  }

  Serial.println("Connecté au Wi-Fi");
  ThingSpeak.begin(client);  // Initialiser ThingSpeak
}

void loop() {
  // Lire les valeurs analogiques du joystick
  int joystickX = analogRead(joystickXPin); // Valeur de l'axe X
  int joystickY = analogRead(joystickYPin); // Valeur de l'axe Y

  // Normaliser les valeurs (de 0 à 1023) à un range de 0 à 255 ou 0 à 1000
  int normalizedX = map(joystickX, 0, 4095, 0, 255);
  int normalizedY = map(joystickY, 0, 4095, 0, 255);

  // Envoyer les valeurs à ThingSpeak
  ThingSpeak.setField(1, normalizedX); // Champ 1 : X
  ThingSpeak.setField(2, normalizedY); // Champ 2 : Y

  // Envoyer les données à ThingSpeak
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  // Attendre 15 secondes avant d'envoyer à nouveau les données
  delay(15000);
}

