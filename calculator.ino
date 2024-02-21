#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

#define BUTTON_PIN_0 0
#define BUTTON_PIN_1 1
#define BUTTON_PIN_2 2
#define BUTTON_PIN_3 3
#define BUTTON_PIN_4 4
#define BUTTON_PIN_5 5
#define BUTTON_PIN_6 6
#define BUTTON_PIN_7 7
#define BUTTON_PIN_8 8
#define BUTTON_PIN_9 9
#define BUTTON_PIN_PLUS A0
#define BUTTON_PIN_MINUS 13
#define BUTTON_PIN_MULTIPLY 12
#define BUTTON_PIN_DIVIDE 11
#define BUTTON_PIN_EQUAL 10
#define SWITCH_PIN A1

char operand1[10] = "";
char operand2[10] = "";
char operation = ' ';
bool isFirstOperand = true;
bool isSwitchedOn = false;

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(BUTTON_PIN_0, INPUT_PULLUP);
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(BUTTON_PIN_3, INPUT_PULLUP);
  pinMode(BUTTON_PIN_4, INPUT_PULLUP);
  pinMode(BUTTON_PIN_5, INPUT_PULLUP);
  pinMode(BUTTON_PIN_6, INPUT_PULLUP);
  pinMode(BUTTON_PIN_7, INPUT_PULLUP);
  pinMode(BUTTON_PIN_8, INPUT_PULLUP);
  pinMode(BUTTON_PIN_9, INPUT_PULLUP);
  pinMode(BUTTON_PIN_PLUS, INPUT_PULLUP);
  pinMode(BUTTON_PIN_MINUS, INPUT_PULLUP);
  pinMode(BUTTON_PIN_MULTIPLY, INPUT_PULLUP);
  pinMode(BUTTON_PIN_DIVIDE, INPUT_PULLUP);
  pinMode(BUTTON_PIN_EQUAL, INPUT_PULLUP);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(SWITCH_PIN) == LOW) {
    isSwitchedOn = !isSwitchedOn;
    delay(200); 
    lcd.clear();
    if (!isSwitchedOn) {
      lcd.print("Calculator OFF");
    }
  }

  if (isSwitchedOn) {
    char buttonPressed = getButtonPressed();
    if (buttonPressed != '\0') {
      if (buttonPressed >= '0' && buttonPressed <= '9') {
        if (isFirstOperand) {
          if (strlen(operand1) < 9) {
            strcat(operand1, &buttonPressed);
            lcd.setCursor(0, 0);
            lcd.print(operand1);
          }
        } else {
          if (strlen(operand2) < 9) {
            strcat(operand2, &buttonPressed);
            lcd.print(operand2);
          }
        }
      } else if (buttonPressed == '+' || buttonPressed == '-' || buttonPressed == '*' || buttonPressed == '/') {
        operation = buttonPressed;
        isFirstOperand = false;
        lcd.print(operation);
      } else if (buttonPressed == '=') {
        if (operation != ' ' && strlen(operand1) > 0 && strlen(operand2) > 0) {
          float result = 0;
          float num1 = atof(operand1);
          float num2 = atof(operand2);
          lcd.print('=');
          switch (operation) {
            case '+':
              result = num1 + num2;
              break;
            case '-':
              result = num1 - num2;
              break;
            case '*':
              result = num1 * num2;
              break;
            case '/':
              if (num2 != 0) {
                result = num1 / num2;
              } else {
                lcd.setCursor(0, 0);
                lcd.print("Error: Divide by 0");
                delay(2000);
              }
              break;
          }
          lcd.setCursor(0, 1);
          lcd.print((int)result);
          memset(operand1, 0, sizeof(operand1));
          memset(operand2, 0, sizeof(operand2));
          operation = ' ';
          isFirstOperand = true;
        }
      }
    }
  }
}

char getButtonPressed() {
  if (digitalRead(BUTTON_PIN_0) == LOW) {
    delay(200); 
    return '0';
  } else if (digitalRead(BUTTON_PIN_1) == LOW) {
    delay(200); 
    return '1';
  } else if (digitalRead(BUTTON_PIN_2) == LOW) {
    delay(200); 
    return '2';
  } else if (digitalRead(BUTTON_PIN_3) == LOW) {
    delay(200); 
    return '3';
  } else if (digitalRead(BUTTON_PIN_4) == LOW) {
    delay(200); 
    return '4';
  } else if (digitalRead(BUTTON_PIN_5) == LOW) {
    delay(200); 
    return '5';
  } else if (digitalRead(BUTTON_PIN_6) == LOW) {
    delay(200); 
    return '6';
  } else if (digitalRead(BUTTON_PIN_7) == LOW) {
    delay(200); 
    return '7';
  } else if (digitalRead(BUTTON_PIN_8) == LOW) {
    delay(200); 
    return '8';
  } else if (digitalRead(BUTTON_PIN_9) == LOW) {
    delay(200); 
    return '9';
  } else if (digitalRead(BUTTON_PIN_PLUS) == LOW) {
    delay(200); // debounce
    return '+';
  } else if (digitalRead(BUTTON_PIN_MINUS) == LOW) {
    delay(200); 
    return '-';
  } else if (digitalRead(BUTTON_PIN_MULTIPLY) == LOW) {
    delay(200); 
    return '*';
  } else if (digitalRead(BUTTON_PIN_DIVIDE) == LOW) {
    delay(200); 
    return '/';
  } else if (digitalRead(BUTTON_PIN_EQUAL) == LOW) {
    delay(200); 
    return '=';
  }else {
    return '\0'; // Toto se vrátí, pokud žádné tlačítko není stisknuto
  }
}
