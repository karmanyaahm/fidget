// Define the pin numbers for the three phases
const int phaseAEnable = 2; // Enable pin for Phase A
const int phaseADir = 3;    // Direction pin for Phase A
const int phaseBEnable = 4; // Enable pin for Phase B
const int phaseBDir = 5;    // Direction pin for Phase B
const int phaseCEnable = 6; // Enable pin for Phase C
const int phaseCDir = 7;    // Direction pin for Phase C

int currentStep = 0;

// Lookup table for the commutation steps
const int commutationTable[6][6] = {
  //  AEn, ADi, BEn, BDi, CEn, CDi
  { HIGH, HIGH, HIGH, LOW,  LOW,  LOW  }, // Step 1: A+ B- C (Disabled)
  { HIGH, HIGH, LOW,  LOW,  HIGH, LOW  }, // Step 2: A+ C- B (Disabled)
  { LOW,  LOW,  HIGH, HIGH, HIGH, LOW  }, // Step 3: B+ C- A (Disabled)
  { HIGH, LOW,  HIGH, HIGH, LOW,  LOW  }, // Step 4: B+ A- C (Disabled)
  { HIGH, LOW,  LOW,  LOW,  HIGH, HIGH }, // Step 5: C+ A- B (Disabled)
  { LOW,  LOW,  HIGH, LOW,  HIGH, HIGH }  // Step 6: C+ B- A (Disabled)
};

void setup() {
  // Set the phase pins as outputs
  pinMode(phaseAEnable, OUTPUT);
  pinMode(phaseADir, OUTPUT);
  pinMode(phaseBEnable, OUTPUT);
  pinMode(phaseBDir, OUTPUT);
  pinMode(phaseCEnable, OUTPUT);
  pinMode(phaseCDir, OUTPUT);

  // Initialize serial communication
  Serial.begin(9600);

  // Print the table header
  Serial.println("Step\tPhase A (Enable, Dir)\tPhase B (Enable, Dir)\tPhase C (Enable, Dir)");
}
const int limit = 5000;
unsigned long del = 70000;
void loop() {
//  // Check if data is available on Serial
//  if (Serial.available()) {
//    // Read the incoming byte
//    char incomingByte = Serial.read();
//
//    // If a newline character is received, advance the commutation step
//    if (incomingByte == '\n') {
//      advanceCommutation();
//    }
//  }
                  // speed step every 600ms
for (int i = 0; i < (600000l/del); i ++) {
advanceCommutation();
delay(del/1000l);
}

if (del < 10000) del = (long) (del / 1.01);
else            del = (long)(del / 1.03 );

if (del < limit) del = limit;

Serial.print(10000000l / del/ 2);
Serial.print(' ');
Serial.println(del);

}

void advanceCommutation() {
  currentStep = (currentStep % 6); // Advance to the next step

  // Set the pins according to the lookup table
  digitalWrite(phaseAEnable, commutationTable[currentStep][0]);
  digitalWrite(phaseADir, commutationTable[currentStep][1]);
  digitalWrite(phaseBEnable, commutationTable[currentStep][2]);
  digitalWrite(phaseBDir, commutationTable[currentStep][3]);
  digitalWrite(phaseCEnable, commutationTable[currentStep][4]);
  digitalWrite(phaseCDir, commutationTable[currentStep][5]);

 // printState(currentStep + 1);

  currentStep++;
}

void printState(int step) {
  int phaseAEnableState = digitalRead(phaseAEnable);
  int phaseADirState = digitalRead(phaseADir);
  int phaseBEnableState = digitalRead(phaseBEnable);
  int phaseBDirState = digitalRead(phaseBDir);
  int phaseCEnableState = digitalRead(phaseCEnable);
  int phaseCDirState = digitalRead(phaseCDir);

  Serial.print(step);
  Serial.print("\t");

  // Print Phase A state
  if (phaseAEnableState == HIGH) {
    Serial.print("HIGH");
    Serial.print(", ");
    Serial.print(phaseADirState == HIGH ? "HIGH" : "LOW");
  } else {
    Serial.print("LOW, -");
  }
  Serial.print("\t\t");

  // Print Phase B state
  if (phaseBEnableState == HIGH) {
    Serial.print("HIGH");
    Serial.print(", ");
    Serial.print(phaseBDirState == HIGH ? "HIGH" : "LOW");
  } else {
    Serial.print("LOW, -");
  }
  Serial.print("\t\t");

  // Print Phase C state
  if (phaseCEnableState == HIGH) {
    Serial.print("HIGH");
    Serial.print(", ");
    Serial.print(phaseCDirState == HIGH ? "HIGH" : "LOW");
  } else {
    Serial.print("LOW, -");
  }

  Serial.println();
}
