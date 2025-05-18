// Define pins for ultrasonic sensor
const int trigPin = 9;  // Trig pin connected to D9
const int echoPin = 8;  // Echo pin connected to D8

// Define pins for LEDs (traffic light)
const int greenLED = 2;
const int yellowLED = 3;
const int redLED = 4;
const int flashLED = 5;  // Flashing LED
const int buzzer = 6;    // Buzzer pin

// Variables for ultrasonic sensor
long duration;
float distance;

// Variables for smoothing
const int numReadings = 5;
float readings[numReadings];  // the readings from the sensor
int readIndex = 0;            // the index of the current reading
float total = 0;              // the running total
float averageDistance = 0;    // the average

void setup() {
  // Set up pins for ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set up pins for traffic light (LEDs) and buzzer
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(flashLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Initialize all readings to 0
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  // Start Serial Monitor
  Serial.begin(9600);

  // Start with Green Light ON
  digitalWrite(greenLED, HIGH);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(flashLED, LOW);
  digitalWrite(buzzer, LOW);
}

void loop() {
  // Clear trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin with timeout (50ms)
  duration = pulseIn(echoPin, HIGH, 50000);

  // If no echo received, skip this reading
  if (duration == 0) {
    Serial.println("No echo received - check sensor connection");
    delay(100);
    return;
  }

  // Calculate the distance (in cm) using standard speed of sound at 20°C (343 m/s)
  distance = duration * 0.0343 / 2;

  // Discard obviously wrong readings (outside sensor's reliable range)
  if (distance < 2.0 || distance > 400.0) {
    Serial.println("Invalid reading discarded");
    delay(50);
    return;
  }

  // Smoothing - subtract the last reading
  total = total - readings[readIndex];
  
  // Add new reading to array and total
  readings[readIndex] = distance;
  total = total + readings[readIndex];
  readIndex = (readIndex + 1) % numReadings;

  // Calculate the average distance
  averageDistance = total / numReadings;

  // Print debug information
  Serial.print("Raw Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Avg Distance: ");
  Serial.print(averageDistance);
  Serial.println(" cm");

  // System Behavior Logic
  if (averageDistance > 100.0) {
    // Green Light (Safe) — No one is near
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(buzzer, LOW);
    digitalWrite(flashLED, LOW);
  }
  else if (averageDistance > 50.0 && averageDistance <= 100.0) {
    // Yellow Light (Warning) — Someone approaching
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);
    
    // Slow Buzzer Beep (Warning)
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
    digitalWrite(flashLED, LOW);
  }
  else if (averageDistance <= 30.0) {
    // Red Light and Alarm (Danger) — Someone very close!
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);
    
    // Fast Buzzer Beep (Danger)
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    
    // Flashing LED
    digitalWrite(flashLED, HIGH);
    delay(100);
    digitalWrite(flashLED, LOW);
    delay(100);
  }
  else {
    // For distances between 30-50cm (maintain previous state)
    // You could add specific behavior here if needed
  }

  delay(50);  // Short delay for more responsive system
}
