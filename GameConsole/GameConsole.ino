#include <LiquidCrystal.h>

// Constant for lcd size
#define LCDWIDTH 16
#define LCDHEIGHT 2

enum State
{
  HOME,
  TRIVIA,
  ADVENTURE
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
  delay(500);
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
  case TRIVIA:
    homeButton();
    triviaLoop();
    break;
  case ADVENTURE:
    homeButton();
    adventureLoop();
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
  if (homeState && !lastButtonState[0])
  {
    // Set it as pressed
    buttonState[0] = 1;
  }
  else if (homeState && lastButtonState[0])
  {
    // Set it as button hold
    buttonState[0] = 3;
  }
  else if (!homeState && lastButtonState[0])
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
  if (leftState && !lastButtonState[1])
  {
    // Set it as pressed
    buttonState[1] = 1;
  }
  else if (homeState && lastButtonState[0])
  {
    // Set it as button hold
    buttonState[1] = 3;
  }
  else if (!leftState && lastButtonState[1])
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
  if (rightState && !lastButtonState[2])
  {
    // Set it as pressed
    buttonState[2] = 1;
  }
  else if (homeState && lastButtonState[0])
  {
    // Set it as button hold
    buttonState[2] = 3;
  }
  else if (!rightState && lastButtonState[2])
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
    appData = 1;
  }
  // 1 = Trivia
  else if (appData == 1)
  {
    displayText("<    Trivia    >", "Test your mind", 1);
    // If left/right buttons are clicked, switch between apps
    if (buttonPress(leftBtn) || buttonPress(rightBtn))
    {
      delay(50);
      appData = 2;
    }
    // If home button is clicked, launch the app
    else if (buttonPress(homeBtn))
    {
      delay(50);
      appData = 0;
      consoleState = TRIVIA;
    }
  }
  // 2 = Adventure
  else if (appData == 2)
  {
    displayText("<   Adventure  >", "Go on a quest", 2);
    // If left/right buttons are clicked, switch between apps
    if (buttonPress(leftBtn) || buttonPress(rightBtn))
    {
      delay(50);
      appData = 1;
    }
    // If home button is clicked, launch the app
    else if (buttonPress(homeBtn))
    {
      delay(50);
      appData = 0;
      consoleState = ADVENTURE;
    }
  }
  // If something went wrong...
  else
  {
    displayText("Oops...", "Wrong Screen!", 3);
    appData = 1;
  }
}

// Trivia are id 100-199
void triviaLoop()
{
  // AppData 0 = Intro
  if (appData == 0)
  {
    displayText("Welcome 2 Trivia", "Press [L] or [R]", 100);
    if (buttonPress(leftBtn) || buttonPress(rightBtn))
    {
      delay(50);
      appData = 1;
    }
  }
  // AppData 1 = Question 1
  else if (appData == 1)
  {
    lcd.clear();
    pinAndScrollText((char *)F("[1]  [Home]  [2]"), 1, (char *)F("What is the capital of Djibouti? 1. Djibouti 2. Addis Ababa"), 0, 300, 2, 3);
  }
  // AppData 2 = Wrong Answer 1
  else if (appData == 2)
  {
    displayText("Correct!", "", 101);
    if (buttonPress(leftBtn) || buttonPress(rightBtn))
    {
      delay(50);
      appData = 4;
    }
  }
  // AppData 3 = Correct Answer 1
  else if (appData == 3)
  {
    displayText("Wrong!", "", 102);
    if (buttonPress(leftBtn) || buttonPress(rightBtn))
    {
      delay(50);
      appData = 4;
    }
  }
  // AppData 4 = Question 2
  else if (appData == 4)
  {
    lcd.clear();
    pinAndScrollText((char *)F("[1] [Home] [2]"), 1, (char *)F("What year was McDonald’s founded? 1. 1930 2. 1955"), 0, 300, 5, 6);
  }
  // AppData 5 = Wrong Answer 2
  else if (appData == 5)
  {
    displayText("Wrong!", "", 103);
    if (buttonPress(leftBtn) || buttonPress(rightBtn))
    {
      delay(50);
      appData = 7;
    }
  }
  // AppData 6 = Correct Answer 2
  else if (appData == 6)
  {
    displayText("Correct!", "", 104);
    if (buttonPress(leftBtn) || buttonPress(rightBtn))
    {
      delay(50);
      appData = 7;
    }
  }
  // AppData 7 = Question 3
  else if (appData == 7)
  {
    lcd.clear();
    pinAndScrollText((char *)F("[1] [Home] [2]"), 1, (char *)F("How long was the life sentence in Finland in 2012? 1. 29 2. 17"), 0, 300, 8, 9);
  }
  // AppData 8 = Wrong Answer 3
  else if (appData == 8)
  {
    displayText("Wrong!", "", 105);
    if (buttonPress(leftBtn) || buttonPress(rightBtn))
    {
      delay(50);
      appData = 10;
    }
  }
  // AppData 9 = Correct Answer 3
  else if (appData == 9)
  {
    displayText("Correct!", "", 106);
    if (buttonPress(leftBtn) || buttonPress(rightBtn))
    {
      delay(50);
      appData = 10;
    }
  }
  // AppData 10 = Question 4
  else if (appData == 10)
  {
    lcd.clear();
    pinAndScrollText((char *)F("[1] [Home] [2]"), 1, (char *)F("What animal lives the longest? 1. Ocean Quahog 2. Galapagos Turtoise"), 0, 300, 11, 12);
  }
  // AppData 11 = Correct Answer 4
  else if (appData == 11)
  {
    displayText("Correct!", "", 107);
    if (buttonPress(leftBtn) || buttonPress(rightBtn))
    {
      delay(50);
      appData = 13;
    }
  }
  // AppData 12 = Wrong Answer 4
  else if (appData == 12)
  {
    displayText("Wrong!", "", 108);
    if (buttonPress(leftBtn) || buttonPress(rightBtn))
    {
      delay(50);
      appData = 13;
    }
  }
}

  // Adventure are id 200-299
  void adventureLoop()
  {
    displayText("Adventure App", "TODO", 200);
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

#pragma region Pin and Scroll Text
  /***** Using a sketch found online https://forum.arduino.cc/index.php?topic=216486.0 *****/

  /* This procedure pins a given text in the center of a desired row while scrolling from right to left another given text on another desired row.
    Parameters:
    char * pinnedText: pinned char string
    int pinnedRow: desired row for pinned String
    char * scrollingText: scrolling char string
    int scrollingRow: desired row for scrolling String
    int v = scrolling speed expressed in milliseconds
*/
  void pinAndScrollText(char *pinnedText, int pinnedRow, char *scrollingText, int scrollingRow, int v, int leftData, int rightData)
  {
    if (pinnedRow == scrollingRow || pinnedRow < 0 || scrollingRow < 0 || pinnedRow >= LCDHEIGHT || scrollingRow >= LCDHEIGHT || strlen(pinnedText) > LCDWIDTH || v < 0)
    {
      lcd.clear();
      lcd.print(F("Error pinScroll"));
      while (1)
        ;
    }
    int l = strlen(pinnedText);
    int ls = strlen(scrollingText);
    int x = LCDWIDTH;
    int n = ls + x;
    int i = 0;
    int j = 0;
    char c[ls + 1];
    flashCharSubstring(pinnedText, c, 0, l);
    lcd.setCursor(l % 2 == 0 ? LCDWIDTH / 2 - (l / 2) : LCDWIDTH / 2 - (l / 2) - 1, pinnedRow);
    lcd.print(c);
    int wait = 0;
    while (n > 0)
    {
      wait += 1;
      if (wait > 5) {
        // Refresh button status
        buttonManager();
        // Check for Button press to exit it
        if (buttonPress(homeBtn))
        {
          delay(50);
          appData = 0;
          consoleState = HOME;
          break;
        }
        // Check for left btn press
        if (buttonPress(leftBtn))
        {
          delay(50);
          appData = leftData;
          break;
        }
        // Check for right btn press
        if (buttonPress(rightBtn))
        {
          delay(50);
          appData = rightData;
          break;
        }
      }

      // Regular logic
      if (x > 0)
      {
        x--;
      }
      lcd.setCursor(x, scrollingRow);
      if (n > LCDWIDTH)
      {
        j++;
        i = (j > LCDWIDTH) ? i + 1 : 0;
        flashCharSubstring(scrollingText, c, i, j);
        lcd.print(c);
      }
      else
      {
        i = i > 0 ? i + 1 : 0;
        if (n == ls)
        {
          i++;
        }
        flashCharSubstring(scrollingText, c, i, j);
        lcd.print(c);
        lcd.setCursor(n - 1, scrollingRow);
        lcd.print(' ');
      }
      n--;
      if (n > 0)
      {
        delay(v);
      }
    }
  }

  /* This procedure makes a char substring based on indexes from a given char string stored in progmem.
   The caller have to set its own buffer and pass its reference
   to the procedure. The procedure will fill the buffer with
   desired substring based on given indexes. Caller buffer size have
   to be at least big as desired substring length (plus null terminating char) of course.
   As a general rule, caller buffer should be: char buf[strlen(str) + 1].
   Example:
   char * string = (char*)F("Hello world!"); // or char string[] = (char[])F("Hello world!");
   char buf[strlen(string) + 1];
   flashCharSubstring(string, buf, 0, 5);
   Serial.println(buf); // output: "Hello"
    Parameters:
    const char *str: string from where to extract the substring
    char *buf: reference of the caller buffer.
    int inf: lower bound, included
    int sup: upper bound, excluded
*/
  void flashCharSubstring(const char *str, char *buf, int inf, int sup)
  {
    int l = sup - inf;
    for (int i = 0; i < l; i++)
    {
      buf[i] = pgm_read_byte_near(&str[i + inf]);
    }
    buf[l] = '\0';
  }

#pragma endregion
