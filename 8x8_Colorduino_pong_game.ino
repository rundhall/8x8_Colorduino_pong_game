/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

#include <Colorduino.h>

int button_a_status;
int button_b_status;
int button_c_status;
int button_d_status;


ColorRGB COLOR_BLACK = {0, 0, 0};
ColorRGB COLOR_RED = {255, 0, 0};
ColorRGB COLOR_GREEN = {0, 255, 0};
ColorRGB COLOR_BLUE = {0, 0, 255};
ColorRGB COLOR_YELLOW = {255, 255, 0};
ColorRGB COLOR_CYAN = {0, 255, 255};
ColorRGB COLOR_MAGENTA = {255, 0, 255};
ColorRGB COLOR_WHITE = {255, 255, 255};
  
#define BUTTON_A_PIN 18  //grean  SDA
#define BUTTON_D_PIN 1 //blue TXD
#define BUTTON_C_PIN   0   //blue RXD
#define BUTTON_B_PIN  19  //orange SCL

#define DEFAULT_LONGPRESS_LEN    25  // Min nr of loops for a long press
#define DELAY                    20  // Delay per loop in ms

//////////////////////////////////////////////////////////////////////////////

enum { EV_NONE=0, EV_LONGPRESS = 1 };

//////////////////////////////////////////////////////////////////////////////


// Class definition

class ButtonHandler {
  public:
  // Constructor
  ButtonHandler(int pin, int longpress_len=DEFAULT_LONGPRESS_LEN);

  // Initialization done after construction, to permit static instances
  void init();

  // Handler, to be called in the loop()
  int handle();

  protected:
  boolean was_pressed;     // previous state
  int pressed_counter;     // press running duration
  const int pin;           // pin to which button is connected
  const int longpress_len; // longpress duration
};

ButtonHandler::ButtonHandler(int p, int lp)
: pin(p), longpress_len(lp)
{
}

void ButtonHandler::init()
{
  pinMode(pin, INPUT);
  was_pressed = false;
  pressed_counter = 0;
}

int ButtonHandler::handle()
{
  int event;
  int now_pressed = digitalRead(pin);

  if (!now_pressed && was_pressed) {
    // handle release event
    if (pressed_counter > longpress_len)
    event = EV_LONGPRESS;
  }
  else
  event = EV_NONE;

  // update press running duration
  if (now_pressed)
  ++pressed_counter;
  else
  pressed_counter = 0;

  // remember state, and we're done
  was_pressed = now_pressed;
  return event;
}

//////////////////////////////////////////////////////////////////////////////

// Instanciate button objects
ButtonHandler button_a(BUTTON_A_PIN, DEFAULT_LONGPRESS_LEN*2);
ButtonHandler button_b(BUTTON_B_PIN, DEFAULT_LONGPRESS_LEN*2);
ButtonHandler button_c(BUTTON_C_PIN, DEFAULT_LONGPRESS_LEN*2);
ButtonHandler button_d(BUTTON_D_PIN, DEFAULT_LONGPRESS_LEN*2);



//Beginning of Auto generated function prototypes by Atmel Studio
float dist(float a, float b, float c, float d);
void plasma_morph();
void ColorFill(unsigned char R, unsigned char G, unsigned char B);

unsigned char plasma[8][8];
long paletteShift;


float dist(float a, float b, float c, float d)  {
  return sqrt((c-a)*(c-a)+(d-b)*(d-b));
}



void plasma_morph() {
  unsigned char x,y;
  float value;
  ColorRGB colorRGB;
  ColorHSV colorHSV;

  for(y = 0; y < 8; y++)
    for(x = 0; x < 8; x++) {
      {
  value = sin(dist(x + paletteShift, y, 128.0, 128.0) / 8.0)
    + sin(dist(x, y, 64.0, 64.0) / 8.0)
    + sin(dist(x, y + paletteShift / 7, 192.0, 64) / 7.0)
    + sin(dist(x, y, 192.0, 100.0) / 8.0);
  colorHSV.h=(unsigned char)((value) * 128)&0xff;
  colorHSV.s=255; 
  colorHSV.v=255;
  Colorduino.HSVtoRGB(&colorRGB, &colorHSV);
  
  Colorduino.SetPixel(x, y, colorRGB.r, colorRGB.g, colorRGB.b);
      }
  }
  paletteShift++;

  Colorduino.FlipPage(); // swap screen buffers to show it
}



/********************************************************
Name: ColorFill
Function: Fill the frame with a color
Parameter:R: the value of RED.   Range:RED 0~255
          G: the value of GREEN. Range:RED 0~255
          B: the value of BLUE.  Range:RED 0~255
********************************************************/
void ColorFill(unsigned char R,unsigned char G,unsigned char B) {
  ColorRGB *p = Colorduino.GetPixel(0,0);
  for (unsigned char y=0;y<8;y++) {
    for(unsigned char x=0;x<8;x++) {
      p->r = R;
      p->g = G;
      p->b = B;
      p++;
    }
  }
  
  Colorduino.FlipPage();
}


unsigned long time_previous;

unsigned long time_previous_for_button;
//End of Auto generated function prototypes by Atmel Studio


/*End of auto generated code by Atmel studio */


//Beginning of Auto generated function prototypes by Atmel Studio
void gameOver();
void restartGame();
void updateBall();
void buzz();
void update();
void draw();
void updateScore();
//End of Auto generated function prototypes by Atmel Studio

unsigned long lastRefreshTime = 0;
int refreshInterval = 1;
unsigned long lastMoveTime = 0;
int moveInterval;
int rowPins[8] = {0,1,2,3,4,5,6,7};
int colPins[3] = {8,9,10};
int speakerPin = 11;
unsigned long now = 0;
unsigned long overTime = 100000000;
int currentColumn = 0;
int ballX;
int ballY;
int player1Score, player2Score;
int player1Position, player2Position;
boolean ballMovingUp = true;
boolean ballMovingLeft = true;
boolean isGameOn = true;
/*int shape[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
};*/

ColorRGB shape[8][8] = {
  {COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK},
  {COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK},
  {COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK},
  {COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK},
  {COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK},
  {COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK},
  {COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK},
  {COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK},
};



void setup(){
 
   // init buttons pins;
   button_a.init();
   button_b.init();
   button_c.init();
   button_d.init();

   Colorduino.Init(); // initialize the board
   time_previous = millis();
   
   // compensate for relative intensity differences in R/G/B brightness
   // array of 6-bit base values for RGB (0~63)
   // whiteBalVal[0]=red
   // whiteBalVal[1]=green
   // whiteBalVal[2]=blue
   unsigned char whiteBalVal[3] = {36,63,63}; // for LEDSEE 6x6cm round matrix
   Colorduino.SetWhiteBal(whiteBalVal);
   
   
   // start with morphing plasma, but allow going to color cycling if desired.
   paletteShift=128000;
   unsigned char bcolor;

   //generate the plasma once
   for(unsigned char y = 0; y < 8; y++)
   for(unsigned char x = 0; x < 8; x++) {
     //the plasma buffer is a sum of sines
     bcolor = (unsigned char)
     (128.0 + (128.0 * sin(x*8.0 / 16.0)) +
     128.0 + (128.0 * sin(y*8.0 / 16.0))) / 2;
     plasma[x][y] = bcolor;
   }
   
   // to adjust white balance you can uncomment this line
   // and comment out the plasma_morph() in loop()
   // and then experiment with whiteBalVal above
   // ColorFill(255,255,255);
   for(int i=0;i<50;i++)
     plasma_morph();
   
    ColorFill(0,0,0); 
  //Serial.begin(9600);
  player1Score = 0; 
  player2Score = 0;
  restartGame();
}
 
void loop(){
   button_a_status = button_a.handle();
   button_b_status = button_b.handle();
   button_c_status = button_c.handle();
   button_d_status = button_d.handle();
   //Player 1 button left
   if((button_b_status==1) ){
     
      if(player2Position>4)
        player2Position = 5;
      else
        player2Position++;
          //update player positions
   }
   //Player 1 button right
   if((button_a_status==1)){
      if(player2Position<1)
        player2Position = 0;
      else
        player2Position--;
   }
   //Player 2 button left
   if((button_c_status==1)){
      if(player1Position>4)
      player1Position = 5;
      else
      player1Position++;
   }
   //Player 2 button right
   if( (button_d_status==1)){
      if(player1Position<1)
      player1Position = 0;
      else
      player1Position--;

   }
  now = millis();
  if(isGameOn){
    update();
  }else{
    updateScore(); 
  }
  draw();
}

void gameOver(){
    isGameOn = false;
    overTime = now;
    player1Score %= 7;
    player2Score %= 7;
    ColorFill(0,0,0); 
    int note[] = {700, 600, 500, 400, 300, 200};
      delay(200);
   
}

void restartGame(){
  moveInterval = 700;
  ballX = now % 8;
  if(ballX == 0)
    ballX =1;

  if((now % 2)==0)
  {
     ballY = 6; 
    ballMovingUp = true;
     
  }
  else
  {
      ballY = 1;
    ballMovingUp = false;
  }
  ballMovingLeft = true;
  

  isGameOn = true;
}

void updateBall(){
  if(ballMovingLeft)
    ballX--;
  else
    ballX++;
  if(ballX == 0)
    ballMovingLeft = false;
  else if (ballX == 7)
    ballMovingLeft = true;
    
  if(ballMovingUp)
    ballY--;
  else
    ballY++;

  if(ballY == 1 && ballX >= player2Position && ballX < player2Position + 3){
    ballMovingUp = false;
    moveInterval -= 20;
  }
  else if(ballY == 6 && ballX >= player1Position && ballX < player1Position + 3){
    ballMovingUp = true;
    moveInterval -= 20;
  }
    if(ballY == 0 && ballX >= player2Position && ballX < player2Position + 3){
      ballMovingUp = false;
      moveInterval -= 20;
    }
    else if(ballY == 7 && ballX >= player1Position && ballX < player1Position + 3){
      ballMovingUp = true;
      moveInterval -= 20;
    } else if(ballY == 0){
      player1Score++;
      gameOver();
      }else if (ballY == 7){
      player2Score++;
      gameOver();
    }

      
}

void update(){
  //clear table;
  if(now - lastMoveTime > moveInterval){
    for(int i = 0; i < 8; i++){
      for(int j = 0; j < 8; j++){
        shape[i][j] = COLOR_BLACK;
      }
    }
    
   
    for(int i = 0; i < 8; i++){
      if(i >= player1Position && i < player1Position + 3){
        shape[7][i] = COLOR_RED;
      }else{
        shape[7][i] = COLOR_BLACK;
      }
      if(i >= player2Position && i < player2Position + 3){
        shape[0][i] = COLOR_RED;
      }else{
        shape[0][i] = COLOR_BLACK;
      }
    }
    //update the ball
    updateBall();
    //draw the ball
    shape[ballY][ballX] = COLOR_GREEN;
    lastMoveTime = now;
  }
}

void displayColorRGBData(ColorRGB data[8][8])
{
  for(int w = 0; w < 8; w++){
    for(int h = 0; h < 8; h++){
      Colorduino.SetPixel(h, w, data[w][h].r, data[w][h].g, data[w][h].b);
    }
  }
  Colorduino.FlipPage();
}

void draw(){
  if(now - lastRefreshTime >= refreshInterval){
  
  displayColorRGBData(shape);
    lastRefreshTime = now; 
  }
}

void updateScore(){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      shape[i][j] = COLOR_BLACK;
    }
  }
  
  for(int i = 0; i < player2Score; i++){
    for(int j = 0; j < i + 1; j++){
      shape[j][6 - i] = COLOR_BLUE;
    }
  }
  
  for(int i = 0; i < player1Score; i++){
    for(int j = 0; j < i + 1; j++){
      shape[7 - j][i + 1] = COLOR_GREEN;
    }
  }
  if(now - overTime > 3000)
    restartGame();
}


