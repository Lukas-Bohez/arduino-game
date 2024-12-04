// Pin Definitions
int phase = 3;
int sup = 4;
int rgroen = 5;
int rblauw = 6;
int rrood = 7;
int buzzer = 8;
int button1 = 13;
int button2 = 14;
int Joseph = 9;   // Orange
int Yuno = 10;    // Green
int Edward = 11;  // Red
int Kilua = 12;   // Blue
int joystickX = A0; // Joystick X-axis
int joystickY = A1; // Joystick Y-axis

// Game Variables
int food = 5, water = 5, firewood = 5, medicine = 5; // Resource counters
int morale = 10;        // Group morale, range 0-10
String specialty = "";  // Chosen specialty
int selected = 0;       // Selected character (0=Joseph, 1=Yuno, 2=Edward, 3=Kilua)

unsigned long lastUpdateTime = 0; // For timing control

void setup() {
  // Initialize pins
  pinMode(phase, OUTPUT);
  pinMode(sup, OUTPUT);
  pinMode(rgroen, OUTPUT);
  pinMode(rblauw, OUTPUT);
  pinMode(rrood, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(Joseph, OUTPUT);
  pinMode(Yuno, OUTPUT);
  pinMode(Edward, OUTPUT);
  pinMode(Kilua, OUTPUT);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  unsigned long currentTime = millis();

  // Read button states
  int buttonState1 = digitalRead(button1);
  int buttonState2 = digitalRead(button2);

  // Joystick input
  int joyY = analogRead(joystickY);
  int joyX = analogRead(joystickX);

  // Update selected character based on joystick movement
  if (joyX > 700) { 
    selected = (selected + 1) % 4; // Cycle through characters
    delay(200); // Debounce
  } else if (joyX < 300) { 
    selected = (selected - 1 + 4) % 4; // Reverse cycle
    delay(200); // Debounce
  }

  // Trigger action with Button 1
  if (buttonState1 == LOW) {
    activeEvent(selected);
  }

  // Example of triggering specialty change (could be extended)
  if (buttonState2 == LOW) {
    setSpecialty();
  }

  // Light up LEDs based on selection
  light(selected);

  // Add additional game logic here
}

// Function to set the group specialty
void setSpecialty() {
  const String specialties[] = {"Cannibal", "Hunter", "Trader", "Children"};
  Serial.println("Choose a specialty:");
  Serial.println("1: Cannibal");
  Serial.println("2: Hunter");
  Serial.println("3: Trader");
  Serial.println("4: Children (Hardest)");

  int specialtyIndex = selected; // Use 'selected' to determine specialty
  specialty = specialties[specialtyIndex];

  Serial.print("You have chosen: ");
  Serial.println(specialty);
}

// Function to manage LED lights
void light(int selected) {
  int pins[] = {Joseph, Yuno, Edward, Kilua};
  for (int i = 0; i < 4; i++) {
    if (i == selected) {
      digitalWrite(pins[i], HIGH); // Turn on the selected LED
    } else {
      digitalWrite(pins[i], LOW);  // Turn off others
    }
  }
}

// Placeholder for event handling
void activeEvent(int selected) {
  Serial.print("Active event triggered for character: ");
  Serial.println(selected);
  // Add your event logic here
}
