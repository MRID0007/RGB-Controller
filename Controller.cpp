const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Set the RGB LED pins as outputs:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Turn off the RGB LED initially
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);

  Serial.println("Enter RGB values in the format R,G,B (0-255):");
}

void loop() {
  // Check if data is available to read
  if (Serial.available() > 0) {
    // Read the input as a string
    String input = Serial.readStringUntil('\n');

    // Parse the input string
    int commaIndex1 = input.indexOf(',');
    int commaIndex2 = input.lastIndexOf(',');

    if (commaIndex1 == -1 || commaIndex2 == -1 || commaIndex1 == commaIndex2) {
      Serial.println("Invalid input. Please enter RGB values in the format R,G,B (0-255):");
      return;
    }

    int redValue = input.substring(0, commaIndex1).toInt();
    int greenValue = input.substring(commaIndex1 + 1, commaIndex2).toInt();
    int blueValue = input.substring(commaIndex2 + 1).toInt();

    // Validate the RGB values
    if (redValue < 0 || redValue > 255 || greenValue < 0 || greenValue > 255 || blueValue < 0 || blueValue > 255) {
      Serial.println("Invalid input. Please enter RGB values in the range 0-255:");
      return;
    }

    // Set the RGB LED color
    analogWrite(redPin, redValue);
    analogWrite(greenPin, greenValue);
    analogWrite(bluePin, blueValue);

    Serial.print("RGB set to: ");
    Serial.print(redValue);
    Serial.print(", ");
    Serial.print(greenValue);
    Serial.print(", ");
    Serial.println(blueValue);
  }
}
