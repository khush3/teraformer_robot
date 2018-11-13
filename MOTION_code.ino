/*
 *                 MOTION CONTROL
 *                 
 *                 top view
 *                    __
 *                 lf|  |rf
 *                   |  |
 *                 lg|  |rg
 */

#define lf 11
#define lg 10
#define rf 9
#define rg 6
int p = 0, q = 0;

void mvf();
void mvl();
void mvr();
void mvg();
void mvfl();
void mvfr();
void mvgl();
void mvgr();
void kill();

 
void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(5);
  pinMode(lf, OUTPUT);
  pinMode(lg, OUTPUT);
  pinMode(rf, OUTPUT);
  pinMode(rg, OUTPUT);
}

void loop() {
  
  char c;                                    //Mode variable
  String value = "";                         //For Speed Value
  
  while (Serial.available() > 0) 
  {
    String tmp = Serial.readString();        //Temporary string
    for(int i = 0 ;i < tmp.length(); i++)    //Itrate over temporary string for parsing input
    {
      int caracter = tmp[i];                 //Temporary character of string
      if (isDigit(caracter))                 //If integer store in speed variable
      {               
         value += (char)caracter;           
      }
      else if (caracter != '\n')             //If not integer check if its is mode
      {  
          c = caracter;          
      }
      else                                   //If garbage value stop parsing
      {
        break;
      }  
    }
  }

  switch(c){                                 //Choose mode
      case 'J': if(value != "")              //Speed Control_1
                {
                  p = value.toInt();
                  break;
                }  
      case 'K': if(value != "")              //Speed Control_2
                {
                  q = value.toInt();
                  break;
                } 
      case 'F':  mvf();    break;            //Move FORWARD
      case 'L':  mvl();    break;            //Move LEFT
      case 'R':  mvr();    break;            //Move RIGHT
      case 'G':  mvg();    break;            //Move REVERSE
      case 'Q':  mvfl();   break;            //Move FORWARD_LEFT
      case 'E':  mvfr();   break;            //Move FORWARD_RIGHT
      case 'Z':  mvgl();   break;            //Move REVERSE_LEFT
      case 'C':  mvgr();   break;            //Move REVERSE_RIGHT
      case 'S':  kill();   break;            //KILL MOTION 
  }
}
  

void mvf()
{
  analogWrite(lf, p);
  analogWrite(lg, 0);
  analogWrite(rf, p);
  analogWrite(rg, 0);
}
void mvl()
{
  analogWrite(lf, 0);
  analogWrite(lg, p);
  analogWrite(rf, p);
  analogWrite(rg, 0);
}
void mvr()
{
  analogWrite(lf, p);
  analogWrite(lg, 0);
  analogWrite(rf, 0);
  analogWrite(rg, p); 
}
void mvg()
{
  analogWrite(lf, 0);
  analogWrite(lg, p);
  analogWrite(rf, 0);
  analogWrite(rg, p);
}
void mvfl()
{
  analogWrite(lf, (p/2));
  analogWrite(lg, 0);
  analogWrite(rf, p);
  analogWrite(rg, 0);
}
void mvfr()
{
  analogWrite(lf, p);
  analogWrite(lg, 0);
  analogWrite(rf, (p/2));
  analogWrite(rg, 0); 
}
void mvgl()
{
  analogWrite(lf, 0);
  analogWrite(lg, (p/2));
  analogWrite(rf, 0);
  analogWrite(rg, p);
}
void mvgr()
{
  analogWrite(lf, 0);
  analogWrite(lg, p);
  analogWrite(rf, 0);
  analogWrite(rg, (p/2));  
}
void kill()
{
  analogWrite(lf, 0);
  analogWrite(lg, 0);
  analogWrite(rf, 0);
  analogWrite(rg, 0);  
}

