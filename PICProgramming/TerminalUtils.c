
#define ASCII_ESC 27
/*******************************************************************
* DESCRIPTION :     Clears the screen 
*
* INPUTS : None
*
* OUTPUTS : None
*
* NOTES : None
*/ 
void CLRScreen (){
    putc(0x1b); // <ESC> Clear display
    putc(0x5b); // [
    putc(0x32); // 2
    putc(0x4a); // J
    putc(0x1b); // <ESC> Reset cursor position 
    putc(0x5b); // [
    putc(0x30); // 0
    putc(0x3b); // ;
    putc(0x30); // 0
    putc(0x48); // H
}
/*******************************************************************
* DESCRIPTION : Put the cursor in the absolute value given by x and y 
*
* INPUTS : None
*
* OUTPUTS : None
*
* NOTES : None
*/ 

void PutCursor (int x, int y) {
 int y1, y2, x1, x2 = 0;

 putc(0x1b); // <ESC>
 putc(0x5b); // [

 if(y>9) { // Testing to see if y > 9
  y2 = (y%10);
  y1 = (y-y2)/10;
  putc(48+y1);
  putc(48+y2);
 }
 else putc(48+y);

 putc(0x3b); // ;
 if(x>9) { // Testing to see if x > 9
  x2 = (x%10);
  x1 = (x-x2)/10;
  putc(48+x1);
  putc(48+x2);
 }
 else putc(48+x);
 putc(0x48); // H
}

/*******************************************************************
* DESCRIPTION :     Clears the currrent line 
*
* INPUTS : None
*
* OUTPUTS : None
*
* NOTES : None
*/ 

void CLRLine (){
 putc (0x1b ); // <ESC>
 putc (0x5b ); // [
 putc (0x32 ); // 2
 putc (0x4b ); // K
}

enum {
   BLACK=0,
   RED=1,
   GREEN=2,
   YELLOW=3,
   BLUE=4,
   MAGENTA=5,
   CYAN=6,
   YELLOW=7,
   DEF=9} colours;
   

