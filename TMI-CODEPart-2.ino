
// LDR pin connections
int ldrld = A0; // Bottom Left LDR
int ldrrd = A3; // Bottom Right LDR
int ldrlt = A1; // Top Left LDR
int ldrrt = A2; // Top Right LDR

void setup() {
  Serial.begin(9600);
  Serial.println("xxxxxxxxxxxxxxxxxxxx");
}

void loop() {
  int lt = analogRead(ldrlt); // Top left
  int rt = analogRead(ldrrt); // Top right
  int ld = analogRead(ldrld); // Bottom left
  int rd = analogRead(ldrrd); // Bottom right
  // Serial.print("ldrlt: ");
  // Serial.println(lt);
  // Serial.print("ldrrt: ");
  // Serial.println(rt);
  // Serial.print("ldrld: ");
  // Serial.println(ld);
  // Serial.print("ldrrd: ");
  // Serial.println(rd);

  int dtime = 10;  
  int tol = 30; // Tolerance value for adjustment

  int avt = (lt + rt) / 2; // Average value of top sensors
  int avd = (ld + rd) / 2; // Average value of bottom sensors
  int avl = (lt + ld) / 2; // Average value of left sensors
  int avr = (rt + rd) / 2; // Average value of right sensors

  int dvert = avt - avd; // Difference between top and bottom
  int dhoriz = avl - avr; // Difference between left and right

  if (abs(dvert) > tol) {  
    if (avt > avd) {
      Serial.println("move to top");
    } else {
      Serial.println("move to bottom");
    }
  }

  if (abs(dhoriz) > tol) {  
    if (avl > avr) {
      Serial.println("move to left");
    } else {
      Serial.println("move to right");
    }
  }

  delay(dtime);
}