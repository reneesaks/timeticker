/*
 * Define digital pins.
 * Pin 0 and 1 can not be connected while uploading the program.
 */
#define A  2 
#define B  3
#define C  4 
#define D  5 
#define E  6 
#define F  7   
#define G  8 
#define M1 9      
#define M2 10 
#define M3 11 
#define M4 12
#define BUTTON 14

/*
 * Assign global variables.
 */
// ## Assign segments to time positions ##
int minutePos1 = 1;
int minutePos2 = 2;
int secondPos1 = 3;
int secondPos2 = 4;

// ## Game time ##
int gameMinutes = 60;                       // + 60 seconds
int gameSeconds = gameMinutes * 60;

// ## Technical Variables ##
const int second = 1000;                    // Length of a second in ms
const int minute = 59;                      // Length of a minute in seconds (including 0)
const int normalRefreshRate = 4;            // Amount of time in ms the current number(segment) is displayed
const int stoppedRefreshRate = 40;          // Amount of time in ms the current number(segment) is displayed when time has stopped
int currentRefreshRate = normalRefreshRate; // Current refresh rate
int previousMillis = 0;                     // Keeping track of ms because one segment can be shown at once and sleep() pauses the whole program
int currentSecond = minute;                 // Assign starting point for seconds
int currentMinute = gameMinutes;            // Assign starting point for minutes
int buttonState = 0;                        // Current state of the button
bool timeStopped = false;                   // Check if game time has stopped

/*
 * Set up the pins.
 */
void setup()
{    
  pinMode(A, OUTPUT); 
  pinMode(B, OUTPUT); 
  pinMode(C, OUTPUT); 
  pinMode(D, OUTPUT); 
  pinMode(E, OUTPUT); 
  pinMode(F, OUTPUT); 
  pinMode(G, OUTPUT); 
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT); 
  pinMode(M3, OUTPUT); 
  pinMode(M4, OUTPUT);
  pinMode(BUTTON, INPUT);
}

/*
 * Main program loop.
 */
void loop()
{
  // Read the pushbutton input pin:
  buttonState = digitalRead(BUTTON);

  // If the current state is LOW then the button is off:
  if (buttonState == LOW) {
    resetTime();
  }
  
  // Check if time has stopped
  timeStopped = currentSecond == 0 && currentMinute == 0;

  // If time hasn't stopped
  // Else start blinking and wait for reset
  if (!timeStopped)
  {
    // Get the current program's run time
    int currentMillis = millis(); 

    // Get our digits from MM:ss format
    int firstDigit = (currentMinute / 10) % 10;
    int secondDigit = currentMinute % 10;
    int thirdDigit = (currentSecond / 10) % 10;
    int fourthDigit = currentSecond % 10;

    // Check the the amount of time that has passed
    // If second has passed count down a second or if minute has passed count down a minute and reset seconds (60)
    if (currentMillis - previousMillis >= second) {
      previousMillis = currentMillis; // Keep track of run time
      currentSecond--;
      
      if(currentSecond == -1)
      {
        currentSecond = minute;
        currentMinute--;
      }
    }

    // Show our time
    showTime(firstDigit, secondDigit, thirdDigit, fourthDigit);
  } else {
    flash();
  }
}

/*
 * Shows a number. First parameters specifies the position and second the number to be shown.
 */
void show(int module, int number)
{
  assignModule(module);
  
  switch (number) 
  {
  case 0:
    zero();
    break;
  case 1:
    one();
    break;
  case 2:
    two();
    break;
  case 3:
    three();
    break;
  case 4:
    four();
    break;
  case 5:
    five();
    break;
  case 6:
    six();
    break;
  case 7:
    seven();
    break;
  case 8:
    eight();
    break;
  case 9:
    nine();
    break;
  }
}

/*
 * Flashes screen to draw attention to it.
 */
 void flash()
 {
  currentRefreshRate = stoppedRefreshRate;
  showTime(0, 0, 0, 0);
 }

 /*
  * Reset the time and refresh rate.
  */
void resetTime()
{
  currentSecond = minute;
  currentMinute = gameMinutes;
  currentRefreshRate = normalRefreshRate;
}

/*
 * Clears the screen.
 */
void dump()
{
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  digitalWrite(M3, LOW);
  digitalWrite(M4, LOW);
}

/*
 * Shows four numbers(segments) at once(MM:ss).
 */
void showTime(int n1, int n2, int n3, int n4)
{
  show(minutePos1, n1);
  delay(currentRefreshRate);
  dump();
  show(minutePos2, n2);
  delay(currentRefreshRate);
  dump();
  show(secondPos1, n3);
  delay(currentRefreshRate);
  dump();
  show(secondPos2, n4);
  delay(currentRefreshRate);
  dump();
}

/*
 * Assign the position where the current number needs to be shown.
 */
void assignModule(int module)
{
  switch (module) 
  {
  case 1:
    digitalWrite(M1, HIGH);
    break;
  case 2:
    digitalWrite(M2, HIGH);
    break;
  case 3:
    digitalWrite(M3, HIGH);
    break;
  case 4:
    digitalWrite(M4, HIGH);
    break;
  }
}

/*
 * Functions to display numbers on segment.
 */
void zero()
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
}

void one()
{
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
}

void two()
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(D, HIGH);
}

void three()
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
}

void four()
{
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
}

void five()
{
  digitalWrite(A, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
}

void six()
{
  digitalWrite(A, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(G, HIGH);
}

void seven()
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
}

void eight()
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void nine()
{
  digitalWrite(F, HIGH);
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
}

