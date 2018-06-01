#include <LiquidCrystal.h>

// Constant for lcd size
#define LCDWIDTH 16
#define LCDHEIGHT 2

enum State
{
  HOME,
  TRIVIA,
  GUIDE
};

// Constant pins
const int homeBtn = 8;
const int rightBtn = 13;
const int leftBtn = 7;

// Which app is the console currently in
State consoleState = HOME;
// The app gets one int to store all of it's data. Use it wisely
int appData;
// Used by the displayText function to prevent displaying the same text
int lastTextId;
// Used by the button manager to figure out buttonPress and buttonRelease
int buttonState[3];
int lastButtonState[3];

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  consoleState = HOME;
  Serial.begin(9600);
  Serial.println("Initializing Hardware...");

  // Buttons
  pinMode(homeBtn, INPUT);
  pinMode(rightBtn, INPUT);
  pinMode(leftBtn, INPUT);

  // Setup LCD
  lcd.begin(LCDWIDTH, LCDHEIGHT);
  lcd.clear();
  displayText("Hello World!", "Starting...", 1);

  // Reset Variables
  lastTextId = 0;
  appData = 0;
  consoleState = HOME;

  // Finish everything
  delay(750);
  Serial.println("Done intializing.");
}

void loop()
{
  // Button Press logic
  buttonManager();

  switch (consoleState)
  {
  case HOME:
    homeLoop();
    break;
  case GUIDE:
    homeButton();
    guideLoop();
    break;
  case TRIVIA:
    homeButton();
    triviaLoop();
    break;
  default:
    homeLoop();
  }
}

#pragma region Button Manager &Press / Release System

void buttonManager()
{
  // Home Btn check
  int homeState = digitalRead(homeBtn);
  // If currently pressed and wasn't pressed earlier
  if (homeState && lastButtonState[0] == 0)
  {
    // Set it as pressed
    buttonState[0] = 1;
  }
  else if (homeState && lastButtonState[0] == 1)
  {
    // Set it as button hold
    buttonState[0] = 3;
  }
  else if (!homeState && lastButtonState[0] == 1)
  {
    // Set it as button release
    buttonState[0] = 2;
  }
  else
  {
    buttonState[0] = 0;
  }
  lastButtonState[0] = homeState;

  // Left Btn check
  int leftState = digitalRead(leftBtn);
  // If currently pressed and wasn't pressed earlier
  if (leftState && lastButtonState[1] == 0)
  {
    // Set it as pressed
    buttonState[1] = 1;
  }
  else if (leftState && lastButtonState[1] == 1)
  {
    // Set it as button hold
    buttonState[1] = 3;
  }
  else if (!leftState && lastButtonState[1] == 1)
  {
    // Set it as button release
    buttonState[1] = 2;
  }
  else
  {
    buttonState[1] = 0;
  }
  lastButtonState[1] = leftState;

  // Right Btn check
  int rightState = digitalRead(rightBtn);
  // If currently pressed and wasn't pressed earlier
  if (rightState && lastButtonState[2] == 0)
  {
    // Set it as pressed
    buttonState[2] = 1;
  }
  else if (rightState && lastButtonState[2] == 1)
  {
    // Set it as button hold
    buttonState[2] = 3;
  }
  else if (!rightState && lastButtonState[2] == 1)
  {
    // Set it as button release
    buttonState[2] = 2;
  }
  else
  {
    buttonState[2] = 0;
  }
  lastButtonState[2] = rightState;
}

// Currently pressed, last loop iteration was not pressed
int buttonPress(int btnId)
{
  if (btnId == homeBtn)
  {
    return buttonState[0] == 1;
  }
  else if (btnId == leftBtn)
  {
    return buttonState[1] == 1;
  }
  else if (btnId == rightBtn)
  {
    return buttonState[2] == 1;
  }
  else
  {
    Serial.print("No button found with id ");
    Serial.println(btnId);
  }
}

// Currently pressed, last loop iteration was pressed
int buttonHold(int btnId)
{
  if (btnId == homeBtn)
  {
    return buttonState[0] == 3;
  }
  else if (btnId == leftBtn)
  {
    return buttonState[1] == 3;
  }
  else if (btnId == rightBtn)
  {
    return buttonState[2] == 3;
  }
  else
  {
    Serial.print("No button found with id ");
    Serial.println(btnId);
  }
}

// Currently not pressed, last loop iteration was pressed
int buttonRelease(int btnId)
{
  if (btnId == homeBtn)
  {
    return buttonState[0] == 2;
  }
  else if (btnId == leftBtn)
  {
    return buttonState[1] == 2;
  }
  else if (btnId == rightBtn)
  {
    return buttonState[2] == 2;
  }
  else
  {
    Serial.print("No button found with id ");
    Serial.println(btnId);
  }
}

#pragma endregion

// Checks if the home btn was pressed and goes to home if so
void homeButton()
{
  if (buttonPress(homeBtn))
  {
    delay(50);
    appData = 0;
    consoleState = HOME;
  }
}

// Home are id 0-99
void homeLoop()
{
  // 0 = immediately move to Trivia
  if (appData == 0)
  {
    displayText("< Game Console >", "", 1);
    delay(100);
    // If left/right buttons are clicked, switch between apps
    if (buttonPress(leftBtn))
    {
      delay(50);
      appData = 3;
    }
    if (buttonPress(rightBtn))
    {
      delay(50);
      appData = 1;
    }
  }
  // 1 = Guide
  else if (appData == 1)
  {
    displayText("<    Guide     >", "Learn to use it", 2);
    delay(100);
    // If left/right buttons are clicked, switch between apps
    if (buttonPress(leftBtn))
    {
      delay(50);
      appData = 0;
    }
    if (buttonPress(rightBtn))
    {
      delay(50);
      appData = 2;
    }
    // If home button is clicked, launch the app
    else if (buttonPress(homeBtn))
    {
      delay(50);
      appData = 0;
      consoleState = GUIDE;
    }
  }
  // 2 = Trivia
  else if (appData == 2)
  {
    displayText("<    Trivia    >", "Test your mind", 3);
    delay(100);
    // If left/right buttons are clicked, switch between apps
    if (buttonPress(leftBtn))
    {
      delay(50);
      appData = 1;
    }
    if (buttonPress(rightBtn))
    {
      delay(50);
      appData = 3;
    }
    // If home button is clicked, launch the app
    else if (buttonPress(homeBtn))
    {
      delay(50);
      appData = 0;
      consoleState = TRIVIA;
    }
  }
  // 3 = Credits
  else if (appData == 3)
  {
    displayText("Made by Reva", "Miguel, Sohail", 4);
    delay(100);
    // If left/right buttons are clicked, switch between apps
    if (buttonPress(leftBtn))
    {
      delay(50);
      appData = 2;
    }
    if (buttonPress(rightBtn))
    {
      delay(50);
      appData = 0;
    }
  }
  // If something went wrong...
  else
  {
    displayText("Oops...", "Wrong Screen!", 99);
    delay(1000);
    appData = 0;
  }
}

// Trivia are id 100-199
void triviaLoop()
{
  if (appData == 0)
  {
    displayText("Welcome 2 Trivia", "Press [L] or [R]", 100);
    delay(100);
    if (buttonPress(leftBtn) || buttonPress(rightBtn))
    {
      delay(50);
      appData = 1;
    }
  }
  else if (appData == 1)
  {
    displayText("Queen's age?", "[92]        [73]", 101);
    delay(100);
    if (buttonPress(leftBtn))
    {
      delay(50);
      appData = 2;
    }
    if (buttonPress(rightBtn))
    {
      delay(50);
      appData = 3;
    }
  }
  else if (appData == 2)
  {
    displayText("Correct!", "", 102);
    delay(100);
    if (buttonPress(leftBtn) || buttonPress(rightBtn))
    {
      delay(50);
      appData = 4;
    }
  }
  else if (appData == 3)
  {
    displayText("Wrong!", "", 103);
    delay(100);
    if (buttonPress(leftBtn) || buttonPress(rightBtn))
    {
      delay(50);
      appData = 4;
    }
  }
  else if (appData == 4)
  {
    displayText("# of US States?", "[9]         [50]", 104);
    delay(100);
    if (buttonPress(leftBtn))
    {
      delay(50);
      appData = 5;
    }
    if (buttonPress(rightBtn))
    {
      delay(50);
      appData = 6;
    }
  }
  else if (appData == 5)
  {
    displayText("Wrong!", "", 105);
    delay(100);
    if (buttonPress(leftBtn) || buttonPress(rightBtn))
    {
      delay(50);
      appData = 7;
    }
  }
  else if (appData == 6)
  {
    displayText("Correct!", "", 106);
    delay(100);
    if (buttonPress(leftBtn) || buttonPress(rightBtn))
    {
      delay(50);
      appData = 7;
    }
  }
  else if (appData == 7)
  {
    displayText("Sohail's fave #", "[100]        [0]", 107);
    delay(100);
    if (buttonPress(leftBtn))
    {
      delay(50);
      appData = 8;
    }
    if (buttonPress(rightBtn))
    {
      delay(50);
      appData = 9;
    }
  }
  else if (appData == 8)
  {
    displayText("Correct!", "", 108);
    delay(100);
    if (buttonPress(leftBtn) || buttonPress(rightBtn))
    {
      delay(50);
      appData = 10;
    }
  }
  else if (appData == 9)
  {
    displayText("Wrong!", "", 109);
    delay(100);
    if (buttonPress(leftBtn) || buttonPress(rightBtn))
    {
      delay(50);
      appData = 10;
    }
  }
  
  else if (appData == 10)
  {
    displayText("x+7x=8", "[2]        [1]", 110);
    delay(100);
    if (buttonPress(leftBtn))
    {
      delay(50);
      appData = 11;
    }
    if (buttonPress(rightBtn))
    {
      delay(50);
      appData = 12;
    }
  }
  else if (appData == 11)
  {
    displayText("Wrong :(", "", 111);
    delay(100);
    if (buttonPress(leftBtn) || buttonPress(rightBtn))
    {
      delay(50);
      appData = 13;
    }
  }
  else if (appData == 12)
  {
    displayText("Correct!", "", 112);
    delay(100);
    if (buttonPress(leftBtn) || buttonPress(rightBtn))
    {
      delay(50);
      appData = 13;
    }
  }
  else if (appData == 13)
  {
    displayText("2(x+4)=9", "[1/2]        [1]", 110);
    delay(100);
    if (buttonPress(leftBtn))
    {
      delay(50);
      appData = 14;
    }
    if (buttonPress(rightBtn))
    {
      delay(50);
      appData = 15;
    }
  }
  else if (appData == 14)
  {
    displayText("Correct!", "", 111);
    delay(100);
    if (buttonPress(leftBtn) || buttonPress(rightBtn))
    {
      delay(50);
      appData = 16;
    }
  }
  else if (appData == 15)
  {
    displayText("Wrong :(", "", 112);
    delay(100);
    if (buttonPress(leftBtn) || buttonPress(rightBtn))
    {
      delay(50);
      appData = 16;
    }
  }
  // If something went wrong...
  else
  {
    displayText("Oops...", "Wrong Screen!", 199);
    delay(1000);
    appData = 0;
  }
}

// Guide are id 200-299
void guideLoop()
{
  if (appData == 0)
  {
    displayText("Console Guide", "Press [R]", 200);
    delay(100);
    if (buttonPress(rightBtn))
    {
      delay(50);
      appData = 1;
    }
  }
  else if (appData == 1)
  {
    displayText("[L] = Back", "[R] = Next", 201);
    delay(100);
    if (buttonPress(leftBtn))
    {
      delay(50);
      appData = 0;
    }
    if (buttonPress(rightBtn))
    {
      delay(50);
      appData = 2;
    }
  }
  else if (appData == 2)
  {
    displayText("[L] and [R] are", "app buttons,", 202);
    delay(100);
    if (buttonPress(leftBtn))
    {
      delay(50);
      appData = 1;
    }
    if (buttonPress(rightBtn))
    {
      delay(50);
      appData = 3;
    }
  }
  else if (appData == 3)
  {
    displayText("they are used", "to navigate ", 203);
    delay(100);
    if (buttonPress(leftBtn))
    {
      delay(50);
      appData = 2;
    }
    if (buttonPress(rightBtn))
    {
      delay(50);
      appData = 4;
    }
  }
  else if (appData == 4)
  {
    displayText("through an app", "like this one.", 204);
    delay(100);
    if (buttonPress(leftBtn))
    {
      delay(50);
      appData = 3;
    }
    if (buttonPress(rightBtn))
    {
      delay(50);
      appData = 5;
    }
  }
  else if (appData == 5)
  {
    displayText("The middle btn", "is [Home]", 205);
    delay(100);
    if (buttonPress(leftBtn))
    {
      delay(50);
      appData = 4;
    }
    if (buttonPress(rightBtn))
    {
      delay(50);
      appData = 6;
    }
  }
  else if (appData == 6)
  {
    displayText("You can go back", "to home screen", 206);
    delay(100);
    if (buttonPress(leftBtn))
    {
      delay(50);
      appData = 5;
    }
    if (buttonPress(rightBtn))
    {
      delay(50);
      appData = 7;
    }
  }
  else if (appData == 7)
  {
    displayText("Press [Home] now", "to exit this app", 207);
  }
  // If something went wrong...
  else
  {
    displayText("Oops...", "Wrong Screen!", 299);
    delay(1000);
    appData = 0;
  }
}

#pragma region Display Utilities
// Display Text, use textId to prevent the same text from refreshing multiple times
void displayText(char topLine[], char botLine[], int textId)
{
  if (textId != lastTextId)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(topLine);
    lcd.setCursor(0, 1);
    lcd.print(botLine);
    lastTextId = textId;
  }
}

#pragma endregion
