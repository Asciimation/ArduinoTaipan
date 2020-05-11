MIT License

Copyright (c) 2020 Simon Jansen 
https://www.asciimation.co.nz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

const int GENERIC = 1; // Flags for sea battles.
const int LI_YUEN = 2;
const int KEYPADPIN = 0; // Analog input pin that the keypad is attached to.
const int BUSY = 2; // Digital pin for busy flag on serial comms.

const int CHARBUFFERSIZE = 126; // Maximum size of the character buffer.
const int NUMBUFFERSIZE = 10; // Maximum size (decimal digits) of the number buffer.
const int LETTERTIME = 750; // How long to wait before selecting a letter (mS).
const int FIRMNAMESIZE = 15; // Maximum size of the firm name.
const int SHIPPOSITIONBUFFERSIZE = 40; // Ship position command buffer.

const int SHIPFIRSTROWX = 0; // First row of ships X position.
const int SHIPFIRSTROWY = 40; // First row of ships Y position.
const int SHIPSECONDROWX = 0; // Second row of ships X position.
const int SHIPSECONDROWY = 70; // Second row of ships Y position.
const int SHIPWIDTH = 24; // Ship width.
const int SHIPHEIGHT = 25; // Ship height.

// Buffers.
char charBuffer[CHARBUFFERSIZE + 1] = {};
char numBuffer[NUMBUFFERSIZE + 1] = {};
char firm[FIRMNAMESIZE + 1];

// The arrays of possible key values.  
prog_char key1[5] PROGMEM = { ' ','-','_','`','1' };
prog_char key2[4] PROGMEM = { 'A','B','C','2' };
prog_char key3[4] PROGMEM = { 'D','E','F','3' };
prog_char key4[4] PROGMEM = { 'G','H','I','4' };
prog_char key5[4] PROGMEM = { 'J','K','L','5' };
prog_char key6[4] PROGMEM = { 'M','N','O','6' };
prog_char key7[5] PROGMEM = { 'P','Q','R','S','7' };
prog_char key8[4] PROGMEM = { 'T','U','V','8' };
prog_char key9[5] PROGMEM = { 'W','X','Y','Z','9' };

// Cargo types.
prog_char it_1[] PROGMEM = "Opium\0";
prog_char it_2[] PROGMEM = "Silk\0";
prog_char it_3[] PROGMEM = "Arms\0";
prog_char it_4[] PROGMEM = "General Cargo\0";
const char* item[] PROGMEM = { it_1, it_2, it_3, it_4 };

// Locations.
prog_char lo_1[] PROGMEM = "At sea\0";
prog_char lo_2[] PROGMEM = "Hong Kong\0";
prog_char lo_3[] PROGMEM = "Shanghai\0";
prog_char lo_4[] PROGMEM = "Nagasaki\0";
prog_char lo_5[] PROGMEM = "Saigon\0";
prog_char lo_6[] PROGMEM = "Manila\0";
prog_char lo_7[] PROGMEM = "Singapore\0";
prog_char lo_8[] PROGMEM = "Batavia\0";
const char* location[] PROGMEM = { lo_1, lo_2, lo_3, lo_4, lo_5, lo_6, lo_7, lo_8 };

// Months.
prog_char mo_1[] PROGMEM =  "Jan \0";
prog_char mo_2[] PROGMEM =  "Feb \0";
prog_char mo_3[] PROGMEM =  "Mar \0";
prog_char mo_4[] PROGMEM =  "Apr \0";
prog_char mo_5[] PROGMEM =  "May \0";
prog_char mo_6[] PROGMEM =  "Jun \0";
prog_char mo_7[] PROGMEM =  "Jul \0";
prog_char mo_8[] PROGMEM =  "Aug \0";
prog_char mo_9[] PROGMEM =  "Sep \0";
prog_char mo_10[] PROGMEM = "Oct \0";
prog_char mo_11[] PROGMEM = "Nov \0";
prog_char mo_12[] PROGMEM = "Dec \0";
const char* months[] PROGMEM = { mo_1, mo_2, mo_3, mo_4, mo_5, mo_6, mo_7, mo_8, mo_9, mo_10, mo_11, mo_12 };

// Ships condition.
prog_char st_1[] PROGMEM = "Critical:\0";
prog_char st_2[] PROGMEM = "Poor:\0";
prog_char st_3[] PROGMEM = "Fair:\0";
prog_char st_4[] PROGMEM = "Good:\0";
prog_char st_5[] PROGMEM = "Prime:\0";
prog_char st_6[] PROGMEM = "Perfect:\0";
const char* st[] PROGMEM = { st_1, st_2, st_3, st_4, st_5, st_6 };

// Bleep commands.
prog_char bl_1[] PROGMEM = "[bl 1]^\0";
prog_char bl_2[] PROGMEM = "[bl 2]^\0";
prog_char bl_3[] PROGMEM = "[bl 3]^\0";
prog_char bl_4[] PROGMEM = "[bl 4]^\0";
prog_char bl_5[] PROGMEM = "[bl 5]^\0";
const char* bl[] PROGMEM = { bl_1, bl_2, bl_3, bl_4, bl_5 };

// Clear/position screen commands.
prog_char clearScreenText[] PROGMEM =    "[cs 0][cx 0][cy 0][cp 0]^\0";
prog_char reportPositionText[] PROGMEM = "[cx 0][cy 50][cp 0]^\0";
prog_char getFirmPosition1[] PROGMEM =   "[cx 0][cy 30][cp 0]^\0";
prog_char getFirmPosition2[] PROGMEM =   "[cx 44][cy 54][cp 0]^\0";

const char* text[] PROGMEM = { clearScreenText, 
                               reportPositionText, 
                               getFirmPosition1, 
                               getFirmPosition2 };

// Rectangle commands.
prog_char firmRectText[] PROGMEM =        "[rx 0][ry 20][rw 127][rh 50][rd 1]^\0";
prog_char stats1RectText[] PROGMEM =      "[rx 0][ry 14][rw 127][rh 30][rd 1]^\0";
prog_char stats2RectText[] PROGMEM =      "[rx 0][ry 47][rw 127][rh 25][rd 1]^\0";
prog_char stats3RectText[] PROGMEM =      "[rx 0][ry 0][rw 127][rh 25][rd 1]^\0";
prog_char clearRectText[] PROGMEM =       "[rx 0][ry 50][rw 127][rh 46][rd 0]^\0";
prog_char clearBattleRectText[] PROGMEM = "[rx 0][ry 0][rw 127][rh 33][rd 0]^\0";
prog_char score1RectText[] PROGMEM =      "[rx 0][ry 9][rw 127][rh 10][rd 1]^\0";
prog_char score2RectText[] PROGMEM =      "[rx 0][ry 21][rw 127][rh 10][rd 1]^\0";
prog_char score3RectText[] PROGMEM =      "[rx 0][ry 33][rw 127][rh 10][rd 1]^\0";
prog_char score4RectText[] PROGMEM =      "[rx 0][ry 45][rw 127][rh 10][rd 1]^\0";
prog_char score5RectText[] PROGMEM =      "[rx 0][ry 57][rw 127][rh 10][rd 1]^\0"; 

const char* rectangles[] PROGMEM = { firmRectText, 
                                     stats1RectText,
                                     stats2RectText,
                                     stats3RectText,
                                     clearRectText,
                                     clearBattleRectText,
                                     score1RectText,
                                     score2RectText,
                                     score3RectText,
                                     score4RectText,
                                     score5RectText };

// Float values.
float cash = 0;
float bank = 0;
float debt = 0;
float booty = 0;
float ec = 20; // Ememy ship strength modifier.
float ed = .5; // Damage modifier.

// Prices.
long price[4];
const prog_uint16_t base_price[4][8] PROGMEM = { { 1000, 11, 16, 15, 14, 12, 10, 13 },
                                                 { 100,  11, 14, 15, 16, 10, 13, 12 },
                                                 { 10,   12, 16, 10, 11, 13, 14, 15 },
                                                 { 1,    10, 11, 12, 13, 14, 15, 16 } };

// Warehouse/hold amounts.
unsigned int hkw_[4];
unsigned int hold_[4];

// General variables.
int hold = 0; // Nothing in the hold. 
int capacity = 60; // Capacity of ship (guns and hold combined).
int guns = 0; // Number of guns.
int bp = 0; // Modifies the chance of running into pirates.
int damage = 0; // Damage to ship.
byte month = 1; 
int year = 1860;
byte li = 0; // Li Yuen counter (only extorts when zero).
byte port = 1; // Initial starting port Hong Kong.
byte wu_warn = 0; // Flag to indicate if Brother Wu has warned us (he only does that once).
byte wu_bailout = 0; // Modifier for how likely Brother Wu is to bail us out.

////////////////////////////////////////////////////////////////////////////////
// Setup function.
////////////////////////////////////////////////////////////////////////////////
void setup()
{
  pinMode( BUSY, INPUT );
  Serial.begin( 38400 ); 

  // Show the memory use if needed.
  Serial.print("Free memory = " );
  Serial.println( freeMemory() );

  // For testing these are modified/uncommented.   
  // Testing transfer.
  // hkw_[2] = 9998;
  // hkw_[3] = 1;        
  
}

////////////////////////////////////////////////////////////////////////////////
// ClearBuffer();
////////////////////////////////////////////////////////////////////////////////
void ClearBuffer()
{
  memset( charBuffer, 0, CHARBUFFERSIZE );
}

////////////////////////////////////////////////////////////////////////////////
// Captain's Report.
////////////////////////////////////////////////////////////////////////////////
void CaptainsReport()
{
  SendCommand( GetCommandStringFromTable(94) ); // Captain's Report
}

////////////////////////////////////////////////////////////////////////////////
// Comprador's Report.
////////////////////////////////////////////////////////////////////////////////
void CompradorsReport()
{
  SendCommand( GetCommandStringFromTable(20) ); // Comprador's Report
}

////////////////////////////////////////////////////////////////////////////////
// Accept or decline?
////////////////////////////////////////////////////////////////////////////////
void AcceptOrDecline()
{
  SendCommand( GetCommandStringFromTable(0) ); // (A)ccept or (D)ecline
}

////////////////////////////////////////////////////////////////////////////////
// Clear the text under the port stats.
////////////////////////////////////////////////////////////////////////////////
void ClearText( int capOrComp = 0 )
{
  // Draw a blanking rectangle.
  delay( 20 );
  DrawRect( 5 ); 
  delay( 20 );
  
  // Set the correct cursor position.
  SetReportPosition();
  delay( 20 );
  
  // Draw the right heading.
  if ( capOrComp == 0 )
  {
    CompradorsReport();
  }
  else
  {
    CaptainsReport();  
  }
}

////////////////////////////////////////////////////////////////////////////////
// Clear the text above a battle.
////////////////////////////////////////////////////////////////////////////////
void ClearBattleText()
{
  // Draw a blanking rectangle.
  DrawRect( 6 );
  delay( 50 );
  
  // Set the correct cursor position.
  SendCommand("[cx 0][cy 0][cp 0]^");
  delay( 50 );
}

////////////////////////////////////////////////////////////////////////////////
// Sends a command to clear the screen and reposition the cursor top left.
////////////////////////////////////////////////////////////////////////////////
void ClearScreen ()
{   
  strcpy_P( charBuffer, (char*)pgm_read_word( &(text[0]) ) ); 
  SendCommand( charBuffer ); 
}

////////////////////////////////////////////////////////////////////////////////
// Sets the cursor to the Comprador/Captain report position.
////////////////////////////////////////////////////////////////////////////////
void SetReportPosition()
{ 
  strcpy_P( charBuffer, (char*)pgm_read_word( &(text[1]) ) ); 
  SendCommand( charBuffer );  
}

////////////////////////////////////////////////////////////////////////////////
// Sends a command to play the appropriate bleep.
////////////////////////////////////////////////////////////////////////////////
void SendBleep ( int bleep )
{
  // We -1 since bleeps are indexed from 1 but the command array is indexed from 0.
  strcpy_P( charBuffer, (char*)pgm_read_word( &(bl[bleep - 1]) ));
  SendCommand( charBuffer );  
}

////////////////////////////////////////////////////////////////////////////////
// Draw a rectangle based on index. We -1 from the index to 
// properly index the array.
////////////////////////////////////////////////////////////////////////////////
void DrawRect ( int rect )
{ 
  strcpy_P( charBuffer, (char*)pgm_read_word( &(rectangles[rect - 1]) ) );       
  SendCommand( charBuffer ); 
}

////////////////////////////////////////////////////////////////////////////////
// Sends a command via serial.
////////////////////////////////////////////////////////////////////////////////
void SendCommand( char* command )
{
  delay( 2 );
  while ( digitalRead( BUSY ) );   // Check the display is ready.
  Serial.print( command );
}

////////////////////////////////////////////////////////////////////////////////
// Formats a floating number to be suitable to display in number/string
// format.
////////////////////////////////////////////////////////////////////////////////
void FormatFloatForDisplay( float number, int places ) 
{
  int i;
  int digit;
  float tens = 0.1;
  int tenscount = 0;
  int index = 0;

  // Clear the buffer.
  if ( number < 1000000L )
  {
    ltoa ( (long)number, charBuffer, 10 );
    return;
  }

  // Some magic copied from the original Apple code!
  int ii = log10( number );
  int ij = (int)( (ii / 3) ) * 3;  
  int ik = pow( 10, (ii - 2) );
  float value = ( ( number/ik + .5 ) * ik/pow( 10, (ij) ) );
  float tempfloat = value;

  if ( value < 0 )
  {
    tempfloat = tempfloat * -1.0;
  }

  while ( ( tens * 10.0 ) <= tempfloat ) 
  {
    tens = tens * 10.0;
    tenscount = tenscount++;
  }
  
  // Write out the negative if needed.
  if ( value < 0 ) charBuffer[index++] = '-';

  // Write a zero if needed.  
  if ( tenscount == 0 ) charBuffer[index++] = '0';

  // Now write the digits.
  for ( i = 0; i < tenscount; i++ ) 
  {
    digit = (int)( tempfloat/tens );
    charBuffer[index++] = digit + 0x30; // Convert to ASCII.
    tempfloat = tempfloat - ( (float)digit * tens );
    tens = tens / 10.0;
  }

  if ( places > 0 ) 
  {
    charBuffer[index++] = '.'; 
    int digitsum = 0;

    // Now write out each decimal place by shifting digits one by one 
    // into the ones place and writing the truncated value.
    for ( i = 0; i < places; i++ ) 
    {
      tempfloat = tempfloat * 10.0;
      digit = (int)tempfloat;
      digitsum = digitsum + digit;
      charBuffer[index++] = digit + 0x30; // Convert to ASCII. 
      // Once written, subtract off that digit.
      tempfloat = tempfloat - (float) digit;      
    }
    // If we didn't write any actual digits delete the zeros and '.' character.
    if ( digitsum == 0 ) 
    {
      index = index - places - 1;
    }
  }
  // Null terminate.
  charBuffer[index++] = '\0'; 

  // Append on the multiplier in text.
  if ( ij == 6 ) strcat( charBuffer, " Mil" );
  if ( ij == 9 ) strcat( charBuffer, " Bil" );
  if ( ij == 12 ) strcat( charBuffer, " Tril" );   

}

////////////////////////////////////////////////////////////////////////////////
// Get the string at the address given from the string table into the 
// EEPROM character buffer. Format as a command to send.
////////////////////////////////////////////////////////////////////////////////
char* GetCommandStringFromTable ( int index )
{
  int indexAddress = 0;
  int stringAddress = 0;
  int i = 4;    

  // Get the correct address to read from.
  indexAddress = index * sizeof( int );
  stringAddress = ( ee.readByte(indexAddress ) << 8 ) + ( ee.readByte( indexAddress + 1 ) );

  ClearBuffer();

  // Build a string print comand.  
  strcat( charBuffer, "[pr " );

  while ( 1 )
  { 
    charBuffer[ i++ ] = ee.readByte( stringAddress++ );
    if ( i == CHARBUFFERSIZE - 2 ) break; // Stop if the buffer is full. 
    if ( charBuffer[ i - 1 ] == 0 ) break; // Stop if we got the whole string. 
  }

  // Terminate the command.
  strcat( charBuffer, "]^" );

  return charBuffer;
}

////////////////////////////////////////////////////////////////////////////////
// Send a print command with the given text.
////////////////////////////////////////////////////////////////////////////////
void SendText ( char* text )
{
  int indexAddress = 0;
  int stringAddress = 0;
  int i = 4;    
  char buffer[ CHARBUFFERSIZE + 1 ];

  memset( buffer, 0, CHARBUFFERSIZE );

  // Build a string print comand.  
  strcat( buffer, "[pr " );

  while ( 1 )
  { 
    buffer[ i++ ] = text[ i - 4 ];    
    if ( i == CHARBUFFERSIZE - 2 ) break; // Stop if the buffer is full. 
    if ( buffer[ i - 1 ] == 0 ) break; // Stop if we got the whole string. 
  }

  // Terminate the command.
  strcat( buffer, "]^" );

  // Send the command.
  SendCommand ( buffer );
}

////////////////////////////////////////////////////////////////////////////////
// Read the keypad (called when a key press is detected).
////////////////////////////////////////////////////////////////////////////////
char ReadKeypad( )
{
  int keypadValue;
  char keyPressed;

  keypadValue = analogRead( KEYPADPIN ); // Read the value (from 0 - 1023).

  if ( keypadValue < 25 )
  {
    keyPressed = '0';
  }
  if ( ( keypadValue >= 25 ) && ( keypadValue < 67 ) )
  {
    keyPressed = '1';
  }
  if ( ( keypadValue >= 67 ) && ( keypadValue < 108 ) )
  {
    keyPressed = '2';
  }
  if ( ( keypadValue >= 108 ) && ( keypadValue < 162 ) )
  {
    keyPressed = '3';
  }
  if ( ( keypadValue >= 162 ) && ( keypadValue < 253 ) )
  {
    keyPressed = '4';
  }
  if ( ( keypadValue >= 253 ) && ( keypadValue < 361 ) )
  {
    keyPressed = '5';
  }
  if ( ( keypadValue >= 361 ) && ( keypadValue < 479 ) )
  {
    keyPressed = '6';
  }
  if ( ( keypadValue >= 479 ) && ( keypadValue < 619 ) )
  {
    keyPressed = '7';
  }
  if ( ( keypadValue >= 619 ) && ( keypadValue < 765 ) )
  {
    keyPressed = '8';
  }
  if ( ( keypadValue >= 765 ) && ( keypadValue < 819 ) )
  {
    keyPressed = '9';
  }
  if ( ( keypadValue >= 819 ) && ( keypadValue < 889 ) )
  {
    keyPressed = '*';
  }
  if ( ( keypadValue >= 889 ) && ( keypadValue < 945 ) )
  {
    keyPressed = '0';
  }
  if ( keypadValue >= 945 )
  {
    keyPressed = '#';
  }

  // Wait till the key is released.  
  while ( keypadValue > 25 ) 
  {
    delay ( 20 );
    keypadValue = analogRead( KEYPADPIN );
  }

  return keyPressed;   
}

////////////////////////////////////////////////////////////////////////////////
// Get a single key from the keypad. Will wait till key is pressed or till 
// the time given has passed when it return 0.
////////////////////////////////////////////////////////////////////////////////
char GetKey( unsigned long timeout = 0 )
{
  char key = 0;
  int keypadValue = 0;
  unsigned long initialTime = millis();
  boolean bTimedOut = false;

  // Poll the keypad until a key is presed or we time out.
  keypadValue = analogRead( KEYPADPIN ); // Read the keypad value (0 - 1023).
  while ( keypadValue < 25 )
  {
    // Check for timeout.
    if ( (timeout) && (millis() - initialTime > timeout) )
    {
      bTimedOut = true;
      break;
    }

    // Wait till a key is pressed.
    keypadValue = analogRead( KEYPADPIN ); 
    delay( 50 );
  }

  // Did we timeout waiting?
  if ( bTimedOut )
  {
    // No key was pressed.
    key = 0;
  }
  else
  {
    // Get which key it is.  
    key = ReadKeypad(); 
  }

  // Return the key.
  return key;
}   

////////////////////////////////////////////////////////////////////////////////
// Get a number from the keypad. Will wait till a # is entered then return
// the digits entered.
////////////////////////////////////////////////////////////////////////////////
unsigned long GetNumber()
{
  char key = 0;
  int index = 0;
  int keypadValue = 0;
  unsigned long returnNumber = 0;
  char command[8] = "[pr ?]^";

  while ( true )
  {
    // Poll the keypad. We keep polling till something is pressed. Read the value of the key and 
    // add it to the number buffer.
    keypadValue = analogRead( KEYPADPIN ); // Read the keypad value (0 - 1023).
    while ( keypadValue < 25 )
    {
      // Wait till a key is pressed.
      keypadValue = analogRead( KEYPADPIN ); 
      delay( 50 );
    }

    // Get the key.
    key = ReadKeypad(); 

    // Stop when we get a # sign.
    if ( key == '#' ) break;

    // Delete the last digit if we get a * sign.
    if ( key == '*' )
    {
      // Is there anything to delete?
      if ( index != 0 )
      {
        // Delete the last character.
        index--;
        numBuffer[index] = 0;
        SendCommand("[dc 1]^"); 
      }
    }

    // If it's a digit and the buffer isn't full we add it.
    if ( ( key != 0 ) && ( key != '*' ) && ( index < NUMBUFFERSIZE ) )
    { 
      command[4] = key; 
      SendCommand( command );      
      numBuffer[index] = key;
      index++;
    }    
  }

  // Null terminate the buffer.
  numBuffer[index] = 0;
  returnNumber = strtoul(&numBuffer[0], NULL, 10);
  return returnNumber;
}   

////////////////////////////////////////////////////////////////////////////////
// Get a letter from the keypad. Will wait till a key is pressed and a value 
// is returned.
////////////////////////////////////////////////////////////////////////////////
char GetLetter()
{
  int count = 0;
  char key = 0;
  char oldKey = 0;
  char letter = 0;
  int keypadValue;
  boolean bWaitingForKey = true;
  char command[8] = "[pr ?]^";

  unsigned long lastLetterTime = millis();

  while ( true )
  {
    // Poll the keypad. We keep polling till something is pressed. Once
    // a key is pressed we look at the timer. If it expires we return
    // the current key value. If a key is pressed again the timer resets.   
    keypadValue = analogRead( KEYPADPIN ); // Read the keypad value (0 - 1023).
    while ( keypadValue < 25 )
    {
      // Check the time.
      if ( ( letter != 0 ) && ( millis() - lastLetterTime > LETTERTIME ) )
      {
        bWaitingForKey = false;
        break;
      }
      // Wait till a key is pressed.
      keypadValue = analogRead(KEYPADPIN); 
      delay( 20 );
    }

    // If we aren't waiting anymore go with what we have already.
    if ( !bWaitingForKey ) break;

    // Get the key.
    key = ReadKeypad(); 

    // Is it the same key or a different one?  
    if ( key != oldKey )
    {  
      // Different key so reset the letter and count.
      count = 0;
      oldKey = key;
    }
    else
    {
      // Same key so increment the count.
      count = count++;
    }

    // Now return the appropriate letter based on key and count.
    if ( key == '1' )
    {
      if ( count >= sizeof(key1)/sizeof(char) ) 
      { 
        count = 0;
      }
      letter = pgm_read_byte(&(key1[count]));
    }

    if ( key == '2' )
    {
      if ( count >= sizeof(key2)/sizeof(char) ) 
      { 
        count = 0;
      }
      letter = pgm_read_byte(&(key2[count]));
    }

    if ( key == '3' )
    {
      if ( count >= sizeof(key3) / sizeof(char) )
      { 
        count = 0;
      }
      letter = pgm_read_byte(&(key3[count]));
    }

    if ( key == '4' )
    {
      if ( count >= sizeof(key4) / sizeof(char) )
      { 
        count = 0;
      }
      letter = pgm_read_byte(&(key4[count]));
    }

    if ( key == '5' )
    {
      if ( count >= sizeof(key5) / sizeof(char) )
      { 
        count = 0;
      }
      letter = pgm_read_byte(&(key5[count]));
    }

    if ( key == '6' )
    {
      if ( count >= sizeof(key6) / sizeof(char) )
      { 
        count = 0;
      }
      letter = pgm_read_byte(&(key6[count]));
    }

    if ( key == '7' )
    {
      if ( count >= sizeof(key7) / sizeof(char) )      
      { 
        count = 0;
      }
      letter = pgm_read_byte(&(key7[count]));
    }

    if ( key == '8' )
    {
      if ( count >= sizeof(key8) / sizeof(char) )     
      { 
        count = 0;
      }
      letter = pgm_read_byte(&(key8[count]));
    }

    if ( key == '9' )
    {
      if ( count >= sizeof(key9) / sizeof(char) )
      { 
        count = 0;
      }
      letter = pgm_read_byte(&(key9[count]));
    }

    if ( key == '*' ) letter = '*';    
    if ( key == '0' ) letter = '0';  
    if ( key == '#' ) letter = '_'; // Use a _ instead of # since this gets displayed.

    // Display the letter (if not a delete).
    if ( letter != '*')
    {
      SendCommand( "[dc 1]^" ); 
      command[4] = letter; 
      SendCommand( command ); 
      // Stop if the key was accept.
      if ( letter == '_') break;  
    }     

    // Reset the timer.
    lastLetterTime = millis();
  }

  // Reset the count. 
  count = 0;

  // Return the letter.       
  return letter;
}   

////////////////////////////////////////////////////////////////////////////////
// Get the firm name. 
///////////////////////////////////////////////////////////////////////////////
void GetFirm()
{
  int index = 0;
  char letter = 0;

  SendCommand( "[pr _]^" ); 

  // Keep reading till we have some characters and we get an accept.
  while ( letter != '_' )
  {      
    // Get the next letter.
    letter = GetLetter();  

    // No characters yet but someone hits accept.
    if ( letter == '_' && index == 0 )
    {      
      SendBleep( 1 );
      letter = 0;
    }
    else
    {    
      // Are we deleting?
      if ( letter == '*')
      {
        // Is there anything to delete?
        if ( index != 0 )
        {        
          // Delete the last character.
          index--;
          firm[index] = 0;
          // Delete on the screen.
          SendCommand( "[dc 2]^" );
          SendCommand( "[pr _]^" );
        }
      }
      // Or if we aren't deleting and there is still space.
      else
      {  
        // Store the character.
        firm[index++] = letter;
        firm[index] = 0;         
        // Make sure we don't overrun the buffer.
        if ( index == FIRMNAMESIZE )
        {
          index--;
          SendCommand("[dc 1]^");
          if ( (letter != '*') && (letter != '_') )
          {           
            // Play warning bleep.
            SendBleep( 5 );     
          }
        }
        SendCommand( "[pr _]^" );        
      }    
    } 
  }
  // Remove the '_'.
  firm[index - 1] = 0;

}

////////////////////////////////////////////////////////////////////////////////
// Intro.
////////////////////////////////////////////////////////////////////////////////
void Intro()
{ 
  unsigned introTime = millis();  
  delay( 500 );
  ClearScreen();
  delay( 500 );
  ClearScreen();

  // Display the splash screen.
  SendCommand( "[bx 10][by 0][bt 0]^" );

  // Wait for a keypress.
  GetKey();

  // Seed the random number generator.
  randomSeed( millis() - introTime );    
}

////////////////////////////////////////////////////////////////////////////////
// Name firm.
////////////////////////////////////////////////////////////////////////////////
void NameFirm()
{ 
  ClearScreen();
  // Set cursor position 1.
  strcpy_P( charBuffer, (char*)pgm_read_word( &(text[2]) ) ); 
  SendCommand( charBuffer );   
  SendCommand( GetCommandStringFromTable(1) ); // Taipan, what will you name your firm:
  DrawRect( 1 );  

  // Set cursor position 2.
  strcpy_P( charBuffer, (char*)pgm_read_word( &(text[3]) ) ); 
  SendCommand( charBuffer );      

  // Get the firm name.
  GetFirm();  
} 

////////////////////////////////////////////////////////////////////////////////
// Cash or guns choice.
////////////////////////////////////////////////////////////////////////////////
void CashOrGuns()
{
  char choice = 0;

  ClearScreen();
  SendCommand( GetCommandStringFromTable(2) ); // Do you want to start . . . 1) With cash (and an debt)
  SendCommand( GetCommandStringFromTable(3) ); //                >> or <<   2) With five guns and no cash
  SendCommand( GetCommandStringFromTable(4) ); //                (But no debt!)

  while ( 1 )
  {
    choice = GetKey();
    if ( ( choice == '1') || (choice == '2') ) break;
    SendBleep( 4 );
  }

  if ( choice == '1' )
  {
    cash = 400;
    debt = 5000;
    hold = 60;
    guns = 0;
    li = 0;
    bp = 10;    
  } 
  else 
  {
    cash = 0;
    debt = 0;
    hold = 10;
    guns = 5;
    li = 1;
    bp = 7;
  }
  
  // For testing uncomment and modify these lines.
  //cash = 50000;
  //bank = 10000000;
  //debt = 30000;  
}

////////////////////////////////////////////////////////////////////////////////
// Set up the prices.
////////////////////////////////////////////////////////////////////////////////
void SetPrices()
{
  price[0] = pgm_read_byte( &(base_price[0][port]) ) / 2 * ( random(RAND_MAX) % 3 + 1 ) * pgm_read_byte( &(base_price[0][0]) );
  price[1] = pgm_read_byte( &(base_price[1][port]) ) / 2 * ( random(RAND_MAX) % 3 + 1 ) * pgm_read_byte( &(base_price[1][0]) );
  price[2] = pgm_read_byte( &(base_price[2][port]) ) / 2 * ( random(RAND_MAX) % 3 + 1 ) * pgm_read_byte( &(base_price[2][0]) );
  price[3] = pgm_read_byte( &(base_price[3][port]) ) / 2 * ( random(RAND_MAX) % 3 + 1 ) * pgm_read_byte( &(base_price[3][0]) );
}

////////////////////////////////////////////////////////////////////////////////
// Port stats.
////////////////////////////////////////////////////////////////////////////////
void PortStats( boolean bFull = false )
{
  int inUse = 0;
  int shipStatus = 100 - ( ( (float) damage / capacity ) * 100 );  

  ClearScreen();

  // Draw all the stats.
  if ( bFull )
  {     
    SendCommand( GetCommandStringFromTable(5) ); // Firm: 
    SendText( firm );
    SendCommand( GetCommandStringFromTable(6) ); // , Hong Kong. 

    SendCommand( GetCommandStringFromTable(8) ); // Location:
    strcpy_P(charBuffer, (char*)pgm_read_word(&(location[port])));
    SendText( charBuffer ); 

    SendCommand( GetCommandStringFromTable(7) ); // Date.
    strcpy_P( charBuffer, (char*)pgm_read_word( &( months[month - 1]) ) ); 
    SendText( charBuffer ); 
    itoa( year, charBuffer, 10 );
    SendText( charBuffer ); 

    SendCommand("[cx 5][cy 17][cp 0]^");
    SendCommand( GetCommandStringFromTable(10) ); // Hong Kong warehouse.

    SendCommand("[cx 5][cy 23][cp 0]^");
    SendCommand( GetCommandStringFromTable(11) ); // In use:        Vacant:
    SendCommand("[cx 37][cp 0]^");
    inUse = hkw_[0] + hkw_[1] + hkw_[2] + hkw_[3];
    itoa( inUse, charBuffer, 10 );    
    SendText( charBuffer ); 
    SendCommand("[cx 100][cp 0]^");
    itoa( 10000 - inUse, charBuffer, 10 );
    SendText( charBuffer );

    SendCommand("[cx 5][cy 31][cp 0]^"); 
    SendCommand( GetCommandStringFromTable(12) ); // Opium:        Silk: 
    SendCommand("[cx 37][cp 0]^"); 
    itoa( hkw_[0], charBuffer, 10 );
    SendText( charBuffer );    
    SendCommand("[cx 100][cp 0]^");
    itoa( hkw_[1], charBuffer, 10 );
    SendText( charBuffer );

    SendCommand("[cx 5][cy 37][cp 0]^"); 
    SendCommand( GetCommandStringFromTable(13) ); // Arms:        General: 
    SendCommand("[cx 37][cp 0]^");
    itoa( hkw_[2], charBuffer, 10 );     
    SendText( charBuffer );
    SendCommand("[cx 100][cp 0]^"); 
    itoa( hkw_[3], charBuffer, 10 );    
    SendText( charBuffer );

    DrawRect( 2 );
  }

  if ( bFull ) 
  {
    SendCommand("[cx 5][cy 50][cp 0]^");
  }
  else 
  {
    SendCommand("[cx 5][cy 3][cp 0]^");  
  }

  SendCommand( GetCommandStringFromTable(14) ); // Hold:        Guns:    

  if ( hold >= 0 )
  {
    SendCommand("[cx 37][cp 0]^");
    itoa( hold, charBuffer, 10 );
    SendText( charBuffer );
  } 
  else
  { 
    SendCommand("[cx 29][cp 0]^");   
    SendCommand( GetCommandStringFromTable(15) ); // Overload. 
  }

  SendCommand("[cx 100][cp 0]^"); 
  itoa( guns, charBuffer, 10 );
  SendText( charBuffer );  

  if ( bFull ) 
  {
    SendCommand("[cx 5][cy 58][cp 0]^"); 
  }
  else 
  {
    SendCommand("[cx 5][cy 12][cp 0]^"); 
  }
  SendCommand( GetCommandStringFromTable(12) ); // Opium:        Silk: 
  SendCommand("[cx 37][cp 0]^"); 
  itoa( hold_[0], charBuffer, 10 );
  SendText( charBuffer );  
  SendCommand("[cx 100][cp 0]^"); 
  itoa( hold_[1], charBuffer, 10 );
  SendText( charBuffer );

  if ( bFull )
  {
    SendCommand("[cx 5][cy 64][cp 0]^"); 
  }
  else 
  {
    SendCommand("[cx 5][cy 18][cp 0]^");
  }
  SendCommand( GetCommandStringFromTable(13) ); // Arms:        General: 
  SendCommand("[cx 37][cp 0]^"); 
  itoa( hold_[2], charBuffer, 10 );  
  SendText( charBuffer );
  SendCommand("[cx 100][cp 0]^"); 
  itoa( hold_[3], charBuffer, 10 );  
  SendText( charBuffer );

  // Draw rectangle.
  if ( bFull ){   
    DrawRect( 3 );
  }
  else 
  {
    DrawRect( 4 );
  }

  if ( bFull ) 
  {
    SendCommand("[cx 0][cy 77][cp 0]^");
  }
  else 
  {
    SendCommand("[cx 0][cy 31][cp 0]^");
  }
  SendCommand( GetCommandStringFromTable(16) ); // Cash:       Bank
  SendCommand("[cx 24][cp 0]^");
  FormatFloatForDisplay( cash, 1 );
  SendText( charBuffer ); 
  SendCommand("[cx 83][cp 0]^");
  FormatFloatForDisplay( bank, 1 );
  SendText( charBuffer );  

  if ( bFull ) 
  {
    SendCommand("[cx 0][cy 83][cp 0]^"); 
  }
  else 
  {
    SendCommand("[cx 0][cy 37][cp 0]^"); 
  }
  SendCommand( GetCommandStringFromTable(9) ); // Debt:       Ship:
  SendCommand("[cx 24][cp 0]^");
  FormatFloatForDisplay( debt, 1 );
  SendText( charBuffer );  
  SendCommand("[cx 83][cp 0]^");
  strcpy_P(charBuffer, (char*)pgm_read_word(&(st[shipStatus / 20])));
  SendText( charBuffer );
  itoa( shipStatus, charBuffer, 10 );
  SendText( charBuffer );    

  if ( bFull )
  {
    // Wait till they press a key.
    GetKey();          
    // Move screen.
    SendCommand("[sa 46][sd 0][ss 0]^");    
  } 
}

////////////////////////////////////////////////////////////////////////////////
// Li Yuen extortion.
////////////////////////////////////////////////////////////////////////////////
void LiYuenExtortion()
{
  int time = ( ( year - 1860 ) * 12 ) + month;
  char choice = 0;

  float i = 1.8;
  float j = 0;
  float amount = 0;

  if ( time > 12 )
  {
    j = random(RAND_MAX) % ( 1000 * time ) + ( 1000 * time );
    i = 1;
  }

  amount = ( (cash / i) * ( (float) random(RAND_MAX) / RAND_MAX) ) + j;

  SendCommand( GetCommandStringFromTable(17) ); // Li Yuen asks
  FormatFloatForDisplay( amount, 1 );
  SendText( charBuffer );
  SendCommand( GetCommandStringFromTable(18) ); // in donation to the temple of Tin Hau, the Sea Goddess. Will you pay?
  AcceptOrDecline();

  while ( 1 )
  {  
    choice = GetKey();
    if ( ( choice == '*' ) || ( choice == '#' ) ) break;
    SendBleep( 4 );
  }

  if ( choice == '#' ) // Accept.
  {
    if ( amount <= cash )
    {
      cash = cash - amount;
      li = 1;
    } 
    else
    {
      ClearScreen();
      SendCommand( GetCommandStringFromTable(19) ); // Taipan, you do not have enough cash!!
      SendBleep( 5 );
      GetKey( 3000 );
      SendCommand( GetCommandStringFromTable(20) ); // Do you want Elder Brother Wu to make up the difference for you?
      AcceptOrDecline();

      while ( 1 )
      {  
        choice = GetKey();
        if ( ( choice == '*' ) || ( choice == '#' ) ) break;
        SendBleep( 4 );
      }

      if ( choice == '#' ) // Accept.
      {
        amount = amount - cash;
        debt = debt + amount;
        cash = 0;
        li = 1;
        SendCommand( GetCommandStringFromTable(22) ); // Elder Brother has given Li Yuen the difference between what he wanted and your cash on hand
        SendCommand( GetCommandStringFromTable(23) ); // and added the same amount to your debt.
        SendBleep( 2 );
        GetKey( 5000 );
      } 
      else // Decline.
      {
        cash = 0;
        SendCommand( GetCommandStringFromTable(24) ); // Very well. Elder Brother Wu will not pay Li Yuen the difference.
        SendCommand( GetCommandStringFromTable(25) ); // I would be very wary of pirates if I were you, Taipan.
        GetKey( 5000 );
      }
    }
  }
  PortStats();
}

////////////////////////////////////////////////////////////////////////////////
// McHenry ship repair.
////////////////////////////////////////////////////////////////////////////////
void McHenry()
{
  char choice = 0;
  unsigned long amount;

  ClearText();
  SendCommand( GetCommandStringFromTable(26) ); // Taipan, Mc Henry from the Hong Kong Shipyards has arrived!!
  GetKey( 5000 );
  ClearText();
  SendCommand( GetCommandStringFromTable(27) ); // He says, 'I see ye've a wee bit of damage to yer ship. Will ye be wanting repairs?
  AcceptOrDecline();

  while ( 1 )
  {  
    choice = GetKey();
    if ( ( choice == '*' ) || ( choice == '#' ) ) break;
    SendBleep( 4 );
  }

  if ( choice == '#' ) // Accept.
  {
    int  percent = ( (float) damage / capacity ) * 100;
    int  time = ( ( year - 1860 ) * 12 ) + month;

    long br = ( ( ( ( 60 * ( time + 3 ) / 4 ) * (float)random(RAND_MAX) / RAND_MAX) + 25 * ( time + 3 ) / 4 ) * capacity / 50 );
    long repair_price = ( br * damage ) + 1; 

    ClearText();
    SendCommand( GetCommandStringFromTable(28) ); // Och, 'tis a pity to be 
    itoa( percent, charBuffer, 10 );
    SendText( charBuffer ); 
    SendCommand( GetCommandStringFromTable(29) ); // damaged. 
    GetKey();   
    ClearText();
    SendCommand( GetCommandStringFromTable(30) ); // We can fix yer whole ship for 
    FormatFloatForDisplay( repair_price, 1 );
    SendText( charBuffer );   
    SendCommand( GetCommandStringFromTable(53) ); // or make partial repairs if you wish. How much will ye spend?

    while ( 1 )
    {        
      amount = GetNumber();
      if ( amount <= cash )
      {
        cash = cash - amount;        
        damage = damage - (int)( (amount / br ) + .5 );
        damage = ( damage < 0 ) ? 0 : damage;        
        break;
      }
    }
  }
  PortStats();
}

////////////////////////////////////////////////////////////////////////////////
// Elder Brother Wu's warning.
////////////////////////////////////////////////////////////////////////////////
void ElderBrotherWuWarning()
{

  int braves = random(RAND_MAX) % 100 + 50;

  ClearText();
  SendCommand( GetCommandStringFromTable(160) ); // Elder Brother Wu has sent 
  itoa ( braves, charBuffer, 10 ); 
  SendText( charBuffer );
  SendCommand( GetCommandStringFromTable(161) ); // braves to escort you to the Wu mansion, Taipan.
  GetKey( 5000 );
  ClearText();   
  SendCommand( GetCommandStringFromTable(162) ); // Elder Brother Wu reminds you of the Confucian ideal of personal worthiness, and how this 
  SendCommand( GetCommandStringFromTable(163) ); // applies to paying one's debts.
  GetKey( 5000 );
  ClearText();    
  SendCommand( GetCommandStringFromTable(164) ); // He is reminded of a fabled barbarian who came to a bad end, after not caring for his obligations.
  GetKey( 5000 );
  ClearText();   
  SendCommand( GetCommandStringFromTable(165) ); // He hopes no such fate awaits you, his friend, Taipan.    
  GetKey( 5000 );   
  wu_warn = 1;

}

////////////////////////////////////////////////////////////////////////////////
// Elder Brother Wu.
////////////////////////////////////////////////////////////////////////////////
void ElderBrotherWu()
{
  int  choice = 0;
  unsigned long wu = 0;

  ClearText();
  SendCommand( GetCommandStringFromTable(31) ); // Do you have business with Elder Brother Wu, the moneylender?
  AcceptOrDecline();

  while ( 1 )
  {
    while ( 1 )
    {  
      choice = GetKey();
      if ( ( choice == '*') || (choice == '#') ) break;
      SendBleep( 4 );
    }
    ClearText();

    if ( choice == '*' ) // Decline.
    {
      break;     
    } 
    else 
    {         
      if ( ( (int)cash == 0 ) && ( (int)bank == 0 ) && ( guns == 0 ) &&
        ( hold_[0] == 0 ) && ( hkw_[0] == 0 ) &&
        ( hold_[1] == 0 ) && ( hkw_[1] == 0 ) &&
        ( hold_[2] == 0 ) && ( hkw_[2] == 0 ) &&
        ( hold_[3] == 0 ) && ( hkw_[3] == 0 ) )
      {
        int i = random(RAND_MAX) % 1500 + 500;
        int j;

        wu_bailout++;
        j = random(RAND_MAX) % 2000 * wu_bailout + 1500;

        while ( 1 )
        {                              

          SendCommand( GetCommandStringFromTable(32) ); // Elder Brother is aware of your plight, Taipan. He is willing to
          SendCommand( GetCommandStringFromTable(33) ); // loan you an additional 
          itoa( i, charBuffer, 10 );
          SendText( charBuffer );
          SendCommand( GetCommandStringFromTable(34) ); // if you will pay back
          itoa( j, charBuffer, 10 );
          SendText( charBuffer );
          SendCommand( GetCommandStringFromTable(35) ); // Are you willing, Taipan?
          AcceptOrDecline();

          while ( 1 )
          {  
            choice = GetKey();
            if ( ( choice == '*') || (choice == '#') ) break;
            SendBleep( 4 );
          }

          ClearText();
          if ( choice == '*' )
          {
            SendCommand( GetCommandStringFromTable(36) ); // Very well, Taipan, the game is over!
            SendBleep( 3 );
            GetKey( 5000 );
            FinalStats();
          } 
          else
          {
            cash = cash + i;
            debt = debt + j;
            SendCommand( GetCommandStringFromTable(37) ); // Very well, Taipan. Good joss!!!
            SendBleep( 1 );
            GetKey( 5000 );
            PortStats();
            return;
          }
        }
      } 
      else if ( ( cash > 0 ) && ( debt != 0 ) ) 
      {
        while ( 1 )
        {               

          ClearText();
          SendCommand( GetCommandStringFromTable(38) ); // How much do you wish to repay him?                  
          wu = GetNumber();
          if ( wu <= cash )
          {
            cash = cash - wu;
            if ( ( wu > debt ) && ( debt > 0 ) )
            {
              debt = debt - ( wu + 1 );
            } 
            else 
            {
              debt = debt - wu;
            }
            break;
          } 
          else 
          {
            SendCommand( GetCommandStringFromTable(39) ); // Taipan, you only have
            FormatFloatForDisplay( cash, 1 );
            SendText( charBuffer );
            SendCommand( GetCommandStringFromTable(40) ); // in cash.
            // Not enough cash so bleep it!
            SendBleep( 5 ); 
            GetKey( 5000 );
            ClearText();
          }
        }
      }

      PortStats();
      while ( 1 )
      {   
        ClearText();
        SendCommand( GetCommandStringFromTable(41) ); // How much do you wish to borrow?

        wu = GetNumber();
        if ( wu <= ( cash * 2 ) )
        {
          cash = cash + wu;
          debt = debt + wu;
          break;
        } 
        else
        {

          SendCommand( GetCommandStringFromTable(42) ); // He won't loan you so much, Taipan!
          SendBleep( 5 ); 
          GetKey( 5000 );
          ClearText();
        }
      }
      break;
    }
  }

  PortStats();

  if ( (debt > 20000 ) && ( cash > 0 ) && ( rand() %5 == 0 ) )
  {
    int num = random(RAND_MAX) % 3 + 1;

    cash = 0;
    PortStats();
    SendCommand( GetCommandStringFromTable(43) ); // Bad Joss!!
    itoa( num, charBuffer, 10 );
    SendText( charBuffer ); 
    SendCommand( GetCommandStringFromTable(44) ); // of your bodyguards have been killed by cutthroats and you have been robbed of all
    SendCommand( GetCommandStringFromTable(45) ); // of your cash, Taipan!!
    SendBleep( 3 );
    GetKey( 5000 );
  }
}

////////////////////////////////////////////////////////////////////////////////
// Overload.
////////////////////////////////////////////////////////////////////////////////
void Overload()
{
  ClearText();
  SendCommand( GetCommandStringFromTable(46) ); // Your ship is overloaded, Taipan!!
  SendBleep( 5 );
  GetKey( 5000 );
  return;
}

////////////////////////////////////////////////////////////////////////////////
// New ship.
////////////////////////////////////////////////////////////////////////////////
void NewShip()
{
  int  choice = 0;
  int  time;
  float amount;

  time = ( ( year - 1860 ) * 12 ) + month;
  amount = random(RAND_MAX) % ( 1000 * ( time + 5 ) / 6 ) * ( capacity / 50 ) + 1000;

  if ( cash < amount )
  {
    return;
  }

  ClearText();
  SendCommand( GetCommandStringFromTable(47) ); // Do you wish to trade in your 

  if ( damage > 0 )
  {
    SendCommand( GetCommandStringFromTable(48) ); // damaged
  } 
  else
  {
    SendCommand( GetCommandStringFromTable(49) ); // fine
  }

  SendCommand( GetCommandStringFromTable(50) ); // ship for one with 50 more capacity by paying an additional "

  FormatFloatForDisplay( amount, 1 );
  SendText( charBuffer );
  SendCommand( GetCommandStringFromTable(51) ); // , Taipan?
  AcceptOrDecline();

  while ( 1 )
  {  
    choice = GetKey();
    if ( ( choice == '*' ) || ( choice == '#' ) ) break;
    SendBleep( 4 );
  }

  if ( choice == '#' )
  {
    cash = cash - amount;
    hold = hold + 50;
    capacity = capacity + 50;
    damage = 0;
  }

  PortStats();
  if ( (rand() %2 == 0) && ( guns < 1000 ) )
  {
    NewGun();
  }

  return;
}

////////////////////////////////////////////////////////////////////////////////
// New gun.
////////////////////////////////////////////////////////////////////////////////
void NewGun()
{
  int  choice = 0;
  int  time;
  float amount;

  time = ( ( year - 1860 ) * 12 ) + month;
  amount = random(RAND_MAX) % ( 1000 * ( time + 5 ) / 6 ) + 500;

  if ( cash < amount )
  {
    return;
  }

  ClearText();
  SendCommand( GetCommandStringFromTable(52) ); // Do you wish to buy a ship's gun for

  FormatFloatForDisplay( amount, 1 );
  SendText( charBuffer );
  SendCommand( GetCommandStringFromTable(54) ); // ,Taipan?
  AcceptOrDecline();

  while ( 1 ) 
  {  
    choice = GetKey();
    if ( ( choice == '*') || (choice == '#') ) break;
    SendBleep( 4 );
  }

  if (choice == '#')
  {
    if ( hold < 10 )
    {   
      ClearText();    
      SendCommand( GetCommandStringFromTable(173) ); // Your ship would be\noverburdened, Taipan!         
      SendBleep( 5 );
      GetKey( 5000 );  
    }
    else
    {
      cash = cash - amount;
      hold = hold - 10;
      guns = guns + 1;
    }
  }
  PortStats();
  return;
}

////////////////////////////////////////////////////////////////////////////////
// Good prices.
////////////////////////////////////////////////////////////////////////////////
void GoodPrices()
{

  int i = random( RAND_MAX ) % 4;
  int j = random( RAND_MAX ) % 2;

  ClearText();
  SendCommand( GetCommandStringFromTable(55) ); // Taipan!! The price of
  strcpy_P( charBuffer, (char*)pgm_read_word(&(item[i])) );
  SendText( charBuffer ); 

  if ( j == 0 )
  {
    price[i] = price[i] / 5;
    SendCommand( GetCommandStringFromTable(56) ); // has dropped to
    itoa( price[i], charBuffer, 10 );
    SendText( charBuffer );
  } 
  else
  {
    price[i] = price[i] * ( random( RAND_MAX ) % 5 + 5 );
    SendCommand( GetCommandStringFromTable(57) ); // has risen to
    itoa( price[i], charBuffer, 10 );
    SendText( charBuffer );
  }

  SendCommand( GetCommandStringFromTable(58) ); // !!
  SendBleep( 5 );
  GetKey( 3000 );
}

////////////////////////////////////////////////////////////////////////////////
// Port choices.
////////////////////////////////////////////////////////////////////////////////
char PortChoices()
{
  char choice = 0;

  ClearText();
  SendCommand( GetCommandStringFromTable(59) ); // Taipan, present prices per unit here are
  SendCommand( GetCommandStringFromTable(60) ); // Opium:
  itoa( price[0], charBuffer, 10 );
  SendText( charBuffer );
  SendCommand( GetCommandStringFromTable(61) ); // Silk: 
  itoa( price[1], charBuffer, 10 );
  SendText( charBuffer );
  SendText( "\n" );
  SendCommand( GetCommandStringFromTable(62) ); // Arms: 
  itoa( price[2], charBuffer, 10 );
  SendText( charBuffer );
  SendCommand( GetCommandStringFromTable(63) ); // General: 
  itoa( price[3], charBuffer, 10 );
  SendText( charBuffer );
  GetKey();   

  while ( 1 )
  {
    ClearText();
    if ( port == 1 )
    {
      if ( ( cash + bank ) >= 1000000 )
      {            
        SendCommand( GetCommandStringFromTable(64) ); // Shall I 1) Buy, 2) Sell, 3) Visit bank, 4) Transfer cargo, 5) Quit trading or 6) Retire? 
        choice = GetKey();
        if ( ( choice == '1' ) ||
          ( choice == '2' ) ||
          ( choice == '3' ) ||
          ( choice == '4' ) ||
          ( choice == '5' ) ||
          ( choice == '6' ) )
        {
          break;
        }
      } 
      else 
      {
        SendCommand( GetCommandStringFromTable(65) ); // Shall I 1) Buy, 2) Sell, 3) Visit bank, 4) Transfer cargo, 5) Quit trading?            
        choice = GetKey();
        if ( ( choice == '1' ) ||
          ( choice == '2' ) ||
          ( choice == '3' ) ||
          ( choice == '4' ) ||
          ( choice == '5' ) )
        {
          break;
        }
      }
    } 
    else
    {
      SendCommand( GetCommandStringFromTable(66) ); // Shall I 1) Buy, 2) Sell, 3) Quit trading?
      choice = GetKey();
      if ( ( choice == '1' ) ||
        ( choice == '2' ) ||
        ( choice == '3' ) )
      {
        if ( choice == '3' ) choice = '5';
        break;
      }
    }
    // Invalid choice so bleep it!
    SendBleep( 4 ); 
  }
  return choice;
}

////////////////////////////////////////////////////////////////////////////////
// Buy.
////////////////////////////////////////////////////////////////////////////////
void Buy()
{
  char key = 0;
  int choice = 0;
  unsigned long afford;
  unsigned long amount;

  while ( 1 )
  {
    ClearText();
    SendCommand( GetCommandStringFromTable(67) ); // What do you wish me to buy,\nTaipan? 1) Opium, 2) Silk,\n3) Arms or 4) General Cargo

    key = GetKey();
    if ( key == '1' )
    {
      choice = 0;
      break;
    } 
    else if ( key == '2' ) 
    {
      choice = 1;
      break;
    } 
    else if ( key == '3' ) 
    {
      choice = 2;
      break;
    } 
    else if ( key == '4' ) 
    {
      choice = 3;
      break;
    }
    // Invalid choice so bleep it!
    SendBleep( 4 );

  }

  while ( 1 )
  { 
    ClearText(); 
    afford = cash / price[choice];  
    SendCommand( GetCommandStringFromTable(68) ); // How much
    strcpy_P( charBuffer, ( char* )pgm_read_word( &( item[choice] ) ) );
    SendText( charBuffer ); 
    SendCommand( GetCommandStringFromTable(69) ); // shall I buy, Taipan?  You can afford
    ltoa( afford, charBuffer, 10 );
    SendText( charBuffer );
    SendText( "\n" ); 
    amount = GetNumber();

    // Check if we can afford that much.
    if ( amount <= afford )
    {
      break;
    }
    // Invalid amount so bleep it!
    SendBleep( 4 );    
  }

  // Deduct the amount from cash and add it to the hold.
  // Reduce the hold space.
  cash = cash - ( amount * price[choice] );
  hold_[choice] = hold_[choice] + amount;
  hold = hold - amount; 

  return;
}

////////////////////////////////////////////////////////////////////////////////
// Sell.
////////////////////////////////////////////////////////////////////////////////
void Sell()
{
  char key = 0;
  int choice = 0;
  unsigned long amount;

  while ( 1 )
  {
    ClearText();
    SendCommand( GetCommandStringFromTable(70) ); // What do you wish me to sell,\nTaipan? 1) Opium, 2) Silk,\n3) Arms or 4) General Cargo
    key = GetKey();
    if ( key == '1' )
    {
      choice = 0;
      break;
    } 
    else if ( key == '2' )
    {
      choice = 1;
      break;
    } 
    else if ( key == '3' ) 
    {
      choice = 2;
      break;
    } 
    else if ( key == '4' ) 
    {
      choice = 3;
      break;
    }
    // Invalid choice so bleep it!
    SendBleep( 4 ); 
  }

  while ( 1 )
  {
    ClearText();
    SendCommand( GetCommandStringFromTable(71) ); // How much
    strcpy_P(charBuffer, (char*)pgm_read_word(&(item[choice])));
    SendText( charBuffer );
    SendCommand( GetCommandStringFromTable(72) ); // shall I sell, Taipan?\n
    amount = GetNumber();

    // Check we have that much.
    if ( hold_[choice] >= amount )
    {
      hold_[choice] = hold_[choice] - amount;
      break;
    }
    // Invalid amount so bleep it!
    SendBleep( 4 );       
  }

  cash = cash + ( amount * price[choice] );
  hold = hold + amount;

  return;
}

////////////////////////////////////////////////////////////////////////////////
// Visit Bank.
// First we can deposit cash into the bank then we can withdraw.
////////////////////////////////////////////////////////////////////////////////
void VisitBank()
{
  unsigned long amount = 0;

  PortStats();
  while ( 1 )
  {
    ClearText();
    SendCommand( GetCommandStringFromTable(73) ); // How much will you deposit?      
    amount = GetNumber();

    // Check the amount.
    if ( amount <= cash )
    {
      cash = cash - amount;
      bank = bank + amount;
      PortStats();
      break;
    } 
    else
    {
      SendCommand( GetCommandStringFromTable(74) ); // Taipan, you only have 
      FormatFloatForDisplay( cash, 1 );
      SendText( charBuffer );
      SendCommand( GetCommandStringFromTable(75) ); // in cash.
      // Not enough cash bleep it!
      SendBleep( 5 ); 
      GetKey( 5000 );
      ClearText();
    }
  }   

  while ( 1 )
  {      
    ClearText();
    SendCommand( GetCommandStringFromTable(76) ); // How much will you withdraw?      
    amount = GetNumber();

    // Check we have that much in the bank.
    if ( amount <= bank )
    {
      cash = cash + amount;
      bank = bank - amount;
      break;
    } 
    else 
    {
      SendCommand( GetCommandStringFromTable(77) ); // Taipan, you only have 
      FormatFloatForDisplay( bank, 1 );
      SendText( charBuffer );
      SendCommand( GetCommandStringFromTable(78) ); // in the bank.
      // Not enough cash bleep it!
      SendBleep( 5 ); 
      GetKey( 5000 );
      ClearText();
    }
  }

  return;
}

////////////////////////////////////////////////////////////////////////////////
// Transfer.
// First we transfer from teh ship to the warehouse then we transfer from
// the warehouse to the ship.
////////////////////////////////////////////////////////////////////////////////
void Transfer()
{
  int i;
  int in_use;

  unsigned long amount = 0;

  if ( ( hkw_[0] == 0 ) && ( hold_[0] == 0 ) &&
    ( hkw_[1] == 0 ) && ( hold_[1] == 0 ) &&
    ( hkw_[2] == 0 ) && ( hold_[2] == 0 ) &&
    ( hkw_[3] == 0 ) && ( hold_[3] == 0 ) )
  {
    ClearText();      
    SendCommand( GetCommandStringFromTable(79) ); // You have no cargo, Taipan.
    SendBleep( 5 );
    GetKey( 5000 );
    return;
  }

  // Loop through for each item type.
  for ( i = 0; i < 4; i++ )
  {
    // If there is any in the hold we can transfer it.
    if ( hold_[i] > 0 )
    {
      while ( 1 )
      {            
        PortStats( true );
        ClearText();  
        SendCommand( GetCommandStringFromTable(80) ); // How much
        strcpy_P( charBuffer, (char*)pgm_read_word(&(item[i])) );
        SendText( charBuffer ); 
        SendCommand( GetCommandStringFromTable(81) ); // shall I move to the warehouse, Taipan? 
        amount = GetNumber();

        // Check the amount. 
        if ( amount <= hold_[i] )
        {
          // If there is warehouse space there we can transfer.
          in_use = hkw_[0] + hkw_[1] + hkw_[2] + hkw_[3];
          if ( ( in_use + amount ) <= 10000 )
          {
            hold_[i] = hold_[i] - amount;
            hkw_[i] = hkw_[i] + amount;
            hold = hold + amount;
            break;
          } 
          // If the warehouse is full we can't transfer.
          else if ( in_use == 10000 ) 
          {
            SendCommand( GetCommandStringFromTable(82) ); // Your warehouse is full, Taipan!
            SendBleep( 5 );
            GetKey( 5000 );
          }
          // If not full but we are trying to transfer too much warn of this.
          else
          {
            SendCommand( GetCommandStringFromTable(83) ); // Your warehouse will only hold an additional
            itoa( 10000 - in_use, charBuffer, 10 );
            SendText( charBuffer );
            SendCommand( GetCommandStringFromTable(84) ); // , Taipan.
            SendBleep( 5 );
            GetKey( 5000 );
          }
        } 
        else
        {
          // We don't have that much in the hold to transfer.
          SendCommand( GetCommandStringFromTable(85) ); // You have only 
          itoa( hold_[i], charBuffer, 10 );
          SendText( charBuffer );
          SendCommand( GetCommandStringFromTable(86) ); // ,Taipan
          SendBleep( 2 );
          GetKey( 5000 );
        }
      }         
    }

    if ( hkw_[i] > 0 )
    {
      while ( 1 )
      {
        PortStats( true );
        ClearText();              
        SendCommand( GetCommandStringFromTable(87) ); // How much        
        strcpy_P( charBuffer, (char*)pgm_read_word( &(item[i])) );
        SendText( charBuffer ); 
        SendCommand( GetCommandStringFromTable(88) ); // shall I move aboard ship, Taipan? 
        amount = GetNumber();

        // Check the amount.
        if ( amount <= hkw_[i] )
        {
          // If there was some in the warehouse we can transfer.
          hold_[i] = hold_[i] + amount;
          hkw_[i] = hkw_[i] - amount;
          hold = hold - amount;
          break;
        } 
        // We don't have that much to transfer from the warehouse.
        else
        {               
          SendCommand( GetCommandStringFromTable(89) ); // You have only
          itoa( hkw_[i], charBuffer, 10 );
          SendText( charBuffer );
          SendCommand( GetCommandStringFromTable(90) ); // , Taipan
          SendBleep( 2 );
          GetKey( 5000 );
        }
      }
    }
  }
  return;
}


////////////////////////////////////////////////////////////////////////////////
// Quit port.
// Ask where to travel to next.
////////////////////////////////////////////////////////////////////////////////
void QuitPort()
{
  char choice = 0;
  int iChoice = 0;
  int nextPort = 0;
  int result = 0;   

  while ( 1 )
  {    
    ClearText(); 
    SendCommand( GetCommandStringFromTable(91) ); // Taipan, do you wish me to go to: 1) Hong Kong, 2) Shanghai, 3) Nagasaki, 4) Saigon, 
    SendCommand( GetCommandStringFromTable(92) ); // 5) Manila, 6) Singapore, or 7) Batavia ?
    choice = GetKey();
    if ( choice == '1' ) iChoice = 1;
    else if ( choice == '2' ) iChoice = 2;
    else if ( choice == '3' ) iChoice = 3;
    else if ( choice == '4' ) iChoice = 4;
    else if ( choice == '5' ) iChoice = 5;
    else if ( choice == '6' ) iChoice = 6;
    else if ( choice == '7' ) iChoice = 7;
    else iChoice = 0;

    // Are we already there?
    if ( iChoice == port )
    {
      ClearText();
      SendCommand( GetCommandStringFromTable(93) ); // You're already here, Taipan.
      SendBleep( 5 );
      GetKey( 5000 );
      ClearText();   
    } 
    // If it's a valid port we go there.
    else if ( ( iChoice >= 1 ) && ( iChoice <= 7 ) )
    {
      port = 0; // At sea.
      nextPort = iChoice;
      break;
    }
    else
    {
      // Invalid choice.        
      SendBleep( 4 );          
    }
  }

  PortStats();  

  // Pirates!
  // if ( 1 ) // Uncomment for testing.
  if ( random(RAND_MAX) % bp == 0 )
  {
    int num_ships = random(RAND_MAX) % ( ( capacity / 10 ) + guns ) + 1;
    // num_ships = 15; // Uncomment for testing.
    
    ClearText( 1 );
    // Can only ever be attacked by 9999 ships!
    if ( num_ships > 9999 )
    {
      num_ships = 9999;
    }
    itoa( num_ships, charBuffer, 10 );
    SendText( charBuffer );
    SendCommand( GetCommandStringFromTable(95) ); // hostile ships approaching, Taipan!
    SendBleep( 3 ); 
    GetKey();
    result = SeaBattle( GENERIC, num_ships );
  }

  // Li Yuens pirates drove off the ships.
  if ( result == 2 )
  { 
    PortStats();
    SendCommand( GetCommandStringFromTable(96) ); // Li Yuen's fleet drove them off!
    GetKey( 3000 );
  }

  // Do Li Yuen's pirates attack us?
  if ( (( result == 0 ) && ( ( random(RAND_MAX) % ( 4 + ( 8 * li ) ) ) == 0 )) || ( result == 2 ) )
  {
    PortStats();
    ClearText( 1 );
    SendCommand( GetCommandStringFromTable(97) ); // Li Yuen's pirates, Taipan!!       
    SendBleep( 1 );
    GetKey();

    // Did we pay tribute to Li Yuen?
    if ( li > 0 )
    {
      // Yes so they let us be.
      SendCommand( GetCommandStringFromTable(98) ); // Good joss!! They let us be!!
      SendBleep( 1 );
      GetKey( 3000 );
      return;
    } 
    else
    {
      // Didn't pay so they attack!
      int num_ships = random(RAND_MAX) % ( ( capacity / 5 ) + guns ) + 5;
      ClearText ( 1 );
      itoa( num_ships, charBuffer, 10 );
      SendText( charBuffer );
      SendCommand( GetCommandStringFromTable(99) ); // ships of Li Yuen's pirate fleet, Taipan!!
      SendBleep( 3 );     
      GetKey( 3000 );
      SeaBattle( LI_YUEN, num_ships );
    }
  }

  if ( result > 0 )
  {
    PortStats();
    ClearText( 1 );

    if ( result == 1 ) 
    {
      // We fought and won.
      SendCommand( GetCommandStringFromTable(100) ); // We captured some booty.
      SendCommand( GetCommandStringFromTable(101) ); // It's worth 
      FormatFloatForDisplay( booty, 1 );
      SendText( charBuffer );
      cash = cash + booty;
      SendBleep( 2 ); 
    } 
    else if ( result == 3 ) 
    {
      // We bravely ran away and made it.
      SendCommand( GetCommandStringFromTable(102) ); // We made it!
      SendBleep( 5 );  
    } 
    else
    {
      // We got knackered. Game over man, game over!
      SendCommand( GetCommandStringFromTable(103) ); // The buggers got us, Taipan!!! It's all over, now!!!
      GetKey( 5000 );
      FinalStats();
      return;
    }
    GetKey();
    ClearText();
  }

  // Storm. 1/10 chance.
  if ( random(RAND_MAX) % 10 == 0 )
  {
    ClearText( 1 );
    SendCommand( GetCommandStringFromTable(104) ); // Storm, Taipan!!
    SendBleep( 1 );
    GetKey( 3000 );

    // 1/30 chance of sinking.
    if ( random(RAND_MAX) % 30 == 0 )
    {
      SendCommand( GetCommandStringFromTable(105) ); // I think we're going down!!
      GetKey(); 

      // Chance of sinking depends on damage.
      if ( ((damage / capacity * 3) * ( (float)random(RAND_MAX) / RAND_MAX)) >= 1 )
      {
        SendCommand( GetCommandStringFromTable(106) ); // We're going down, Taipan!!
        SendBleep( 3 );
        GetKey( 5000 );
        FinalStats();
      }
    }

    // Made it OK!
    SendCommand( GetCommandStringFromTable(107) ); // We made it!!
    SendBleep( 1 );
    GetKey( 3000 );
    ClearText( 1 );

    // Did we go off course? 
    if ( random(RAND_MAX) % 3 == 0 )
    {
      int orig = nextPort;

      // Choose a new random destination. 
      while ( nextPort == orig )
      {
        nextPort = random (RAND_MAX) % 7 + 1;
      }                   
      ClearText( 1 );
      SendCommand( GetCommandStringFromTable(108) ); // We've been blown off course to
      strcpy_P( charBuffer, (char*)pgm_read_word(&(location[nextPort])) );
      SendText( charBuffer );
      GetKey( 3000 );
    }
  }

  // Time advances.
  month++;
  if ( month == 13 )
  {
    month = 1;
    year++;
    // Increment the strength of enemy ships. 
    ec = ec + 10;
    // Increment the amount of damage caused to us.
    ed = ed + .5;
  }

  // Inflation!
  debt = debt + (debt * .1);
  bank = bank + (bank * .005);

  // Go to the next port and set the prices.
  port = nextPort;
  SetPrices();

  ClearText( 1 );
  SendCommand( GetCommandStringFromTable(109) ); // Arriving at
  strcpy_P( charBuffer, (char*)pgm_read_word( & ( location[port] ) ) );
  SendText( charBuffer); 
  SendText( "..." );
  GetKey( 3000 );

  return;
}

////////////////////////////////////////////////////////////////////////////////
// FightStats.
// Display the current fight information.
////////////////////////////////////////////////////////////////////////////////
void FightStats( int ships, int orders )
{
  char ch_orders[13];

  if ( orders == 0 )
  {
    strcpy( ch_orders, "\n" );
  } 
  else if ( orders == 1 ) {
    strcpy( ch_orders, "Fight\n" );
  } 
  else if ( orders == 2 ) {
    strcpy( ch_orders, "Run\n" );
  } 
  else {
    strcpy( ch_orders, "Throw Cargo\n" );
  }

  ClearBattleText();

  itoa( ships, charBuffer, 10 );
  SendText( charBuffer );

  if ( ships == 1 )
  {
    SendCommand( GetCommandStringFromTable(113) ); // ship attacking, Taipan!
  } 
  else 
  {
    SendCommand( GetCommandStringFromTable(114) ); // ships attacking, Taipan!
  }
  SendCommand( GetCommandStringFromTable(115) ); // We have
  itoa( guns, charBuffer, 10 );
  SendText( charBuffer );
  SendCommand( GetCommandStringFromTable(116) ); // guns Your orders are to:  
  SendText ( ch_orders );
  return;
}

////////////////////////////////////////////////////////////////////////////////
// Draw a ship.
//////////////////////////////////////////////////////////////////////////////// 
void DrawShip ( int shipBitmap, int ship, boolean bInverse = false )
{

  char shipPositionBuffer1[SHIPPOSITIONBUFFERSIZE] = "[bp 0][bx \0";
  char *shipPositionBuffer2 = "][by \0";
  char *shipPositionBuffer3 = "][bs \0";
  char *shipPositionBuffer4 = "]^\0";
  int x = 0;
  int y = 0;

  // Work out the x and y for that particular ship.  
  x = ( ship < 5 ) ? ( ( ship ) * ( SHIPWIDTH + 2 ) ) : ( ( ship - 5 ) * ( SHIPWIDTH + 2 ) );
  y = ( ship < 5 ) ? SHIPFIRSTROWY : SHIPSECONDROWY;

  // Build the command to draw the ship.
  itoa( x, charBuffer, 10 );
  strcat ( shipPositionBuffer1, charBuffer );
  strcat ( shipPositionBuffer1, shipPositionBuffer2 ); 
  itoa( y, charBuffer, 10 );
  strcat ( shipPositionBuffer1, charBuffer );
  strcat ( shipPositionBuffer1, shipPositionBuffer3 );
  if ( bInverse )
  {
    itoa( 4, charBuffer, 10 );
  }
  else 
  {
    itoa( shipBitmap, charBuffer, 10 );
  }
  strcat ( shipPositionBuffer1, charBuffer );
  strcat ( shipPositionBuffer1, shipPositionBuffer4 );

  // Send the command to draw it.
  SendCommand ( shipPositionBuffer1 );      
}

////////////////////////////////////////////////////////////////////////////////
// Sink a ship.
//////////////////////////////////////////////////////////////////////////////// 
void SinkShip ( int ships[10][2], int ship )
{

  char shipPositionBuffer1[SHIPPOSITIONBUFFERSIZE] = "[bx \0";
  char *shipPositionBuffer2 = "][by \0";
  char *shipPositionBuffer3 = "][bp \0";
  char *shipPositionBuffer4 = "][bs \0";
  char *shipPositionBuffer5 = "]^\0";

  int x = 0;
  int y = 0;

  // Work out the x and y for that particular ship.  
  x = ( ship < 5 ) ? ( ( ship ) * ( SHIPWIDTH + 2 ) ) : ( ( ship - 5 ) * ( SHIPWIDTH + 2 ) );
  y = ( ship < 5 ) ? SHIPFIRSTROWY : SHIPSECONDROWY;

  // In a loop draw the ship a little lower each time.
  for ( int pos = 0; pos < SHIPHEIGHT; pos++ )
  {
    itoa( x, charBuffer, 10 );
    strcat ( shipPositionBuffer1, charBuffer );
    strcat ( shipPositionBuffer1, shipPositionBuffer2 );         
    itoa( y, charBuffer, 10 );
    strcat ( shipPositionBuffer1, charBuffer );
    strcat ( shipPositionBuffer1, shipPositionBuffer3 );
    itoa( pos, charBuffer, 10 );
    strcat ( shipPositionBuffer1, charBuffer );
    strcat ( shipPositionBuffer1, shipPositionBuffer4 );
    itoa( ships[ship][1], charBuffer, 10 );
    strcat ( shipPositionBuffer1, charBuffer );
    strcat ( shipPositionBuffer1, shipPositionBuffer5 );
    SendCommand ( shipPositionBuffer1 ); 

    // Terminate the buffer after the first command so we can reuse it.
    shipPositionBuffer1[4] = 0;   

    // Small delay.
    delay( 100 );
  }   
}

////////////////////////////////////////////////////////////////////////////////
// Clear a ship.
//////////////////////////////////////////////////////////////////////////////// 
void ClearShip ( int ship )
{

  char blankingBuffer[10] = "[rx \0";
  int x = 0;
  int y = 0;

  // Work out the x and y for that particular ship.  
  x = ( ship < 5 ) ? ( ( ship ) * ( SHIPWIDTH + 2 ) ) : ( ( ship - 5 ) * ( SHIPWIDTH + 2 ) );
  y = ( ship < 5 ) ? SHIPFIRSTROWY : SHIPSECONDROWY;

  // Set x co-ord.
  itoa( x, charBuffer, 10 );
  strcat ( blankingBuffer, charBuffer );
  strcat ( blankingBuffer, "]^" );
  SendCommand ( blankingBuffer );

  // Reset the buffer.
  blankingBuffer[2] = 'y';
  blankingBuffer[3] = ' ';
  blankingBuffer[4] = 0;

  // Set y co-ord.
  itoa( y, charBuffer, 10 );
  strcat ( blankingBuffer, charBuffer );
  strcat ( blankingBuffer, "]^" );
  SendCommand ( blankingBuffer );

  // Draw a blanking rectangle.
  SendCommand( "[rw 24][rh 25][rd 0]^" ); // SHIPWIDTH, SHIPHEIGHT
}

////////////////////////////////////////////////////////////////////////////////
// Ship hit screen flash.
////////////////////////////////////////////////////////////////////////////////
void ShipHit ()
{
  for ( int i = 0; i < 8; i++ )
  {
    SendCommand("[iv 0]^");
    delay(50);
  }
}

////////////////////////////////////////////////////////////////////////////////
// Get current orders.
// We wait the time given for new orders to be given. If the time expires 
// and the orders haven't changed we return the old orders.
////////////////////////////////////////////////////////////////////////////////  
int GetOrders ( int wait, int oldOrders )
{ 

  // If no order was given continue with the old one. 
  int newOrders = oldOrders;

  // Get orders.
  char input = GetKey( wait );  

  if ( input == '1' )
  {
    newOrders = 1; // Fight.
  } 
  else if ( input == '2' )
  {
    newOrders = 2; // Run
  } 
  else if ( input == '3' )
  {
    newOrders = 3; // Throw cargo.
  }    

  return newOrders;  
}

////////////////////////////////////////////////////////////////////////////////
// SeaBattle.
////////////////////////////////////////////////////////////////////////////////
int SeaBattle( int id, int num_ships )
{
  int orders = 0;
  int num_on_screen = 0;
  int ships_on_screen[10][2];
  unsigned int time = ( (year - 1860) * 12 ) + month;
  int s0 = num_ships;
  int ok = 0; // Modifier for getting away by running or throwing cargo.
  int ik = 1;
  int x = 0;
  int y = 0;
  int i = 0;
  int iStatus;   
  int bHanShotFirst = 1;

  // Work out how much sweet booty we get if we win.
  booty = ( time / 4 * 1000 * num_ships ) + random(RAND_MAX) % 1000 + 250;

  // Clear the ship array.
  for ( i = 0; i <= 9; i++ )
  {
    ships_on_screen[i][0] = 0;
    ships_on_screen[i][1] = 0;
  }

  ClearScreen();
  FightStats( num_ships, orders  );

  // Main fighting loop. Keep going while there are still ships or we're 
  // not sunk!
  while ( num_ships > 0 )
  {

    // Work out out current damage level.
    iStatus = 100 - ( ( (float) damage / capacity ) * 100 );
    if ( iStatus <= 0 )
    {
      // Sunk!
      return 4;
    }    

    // Print out current damage level.
    SendCommand( GetCommandStringFromTable(117) ); // Current seaworthiness: 
    strcpy_P( charBuffer, (char*)pgm_read_word( &(st[(iStatus / 20)]) ) );
    SendText( charBuffer );
    SendText( " " );
    itoa( iStatus, charBuffer, 10 );
    SendText( charBuffer );

    // Draw the ships.      
    x = SHIPFIRSTROWX;
    y = SHIPFIRSTROWY;
    
    // Check the ships on screen.
    for ( i = 0; i <= 9; i++ )
    {
    
      // Are there more than 10?
      if ( num_ships > num_on_screen )
      {
        // If there is no ship in this position...
        if ( ships_on_screen[i][0] == 0 )
        {
          // Add a new one.
          if ( i == 5 ) // Second row.
          {  
            x = SHIPSECONDROWX;
            y = SHIPSECONDROWY;
          }
      
          DrawShip ( ships_on_screen[i][1], i );
          // Small delay between drawing ships. 
          delay( 150 ); 
          x = x + SHIPWIDTH + 2;  
   
          // Give it a strength value.
          ships_on_screen[i][0] = (int)((ec * ( (float)random(RAND_MAX) / RAND_MAX) ) + 20 );
          num_on_screen++;
        
        }           
      }
    }      

    // Draw a + if more than 10 ships.
    SendCommand( "[cx 122][cy 34][cp 0]^" );
    if ( num_ships > num_on_screen )
    {         
      SendText( "+" );
    } 
    else 
    {       
      SendText( " " );
    }      

    // Get orders.
    orders = GetOrders ( 3000, orders ); 

    // No order yet so prompt.
    if ( orders == 0 )
    {
      ClearBattleText();
      SendCommand( GetCommandStringFromTable(118) ); // Taipan, what shall we do?? 1) Fight, 2) Run, 3) Throw cargo
      SendBleep( 3 ); 

      // Keep prompting.
      while ( orders == 0 )
      {
        orders = GetOrders( 2000, orders );
        SendBleep( 3 ); 
      }         
      // Too slow, don't get to shoot first.
      bHanShotFirst = 0;
    }

    // Update the stats.
    FightStats( num_ships, orders );

    // If orders are to fight and have guns.
    if ( ( orders == 1 ) && ( guns > 0 ) && ( bHanShotFirst == 1 ) )
    {  
      int targeted;
      int sunk = 0;
      ok = 3;
      ik = 1;

      SendCommand( GetCommandStringFromTable(119) ); // Aye, we'll fight 'em, Taipan.         
      orders = GetOrders ( 1000, orders );
      SendCommand("[cx 0][cy 18][cp 0]^");
      SendCommand( GetCommandStringFromTable(120) ); // We're firing on 'em, Taipan!
      orders = GetOrders ( 1000, orders );         

      // For each gun we attack a ship.
      for ( i = 1; i <= guns; i++ )
      {
        // If there are no ships at all add more.
        if ( ( ships_on_screen[0][0] == 0 ) && ( ships_on_screen[1][0] == 0 ) &&
           ( ships_on_screen[2][0] == 0 ) && ( ships_on_screen[3][0] == 0 ) &&
           ( ships_on_screen[4][0] == 0 ) && ( ships_on_screen[5][0] == 0 ) &&
           ( ships_on_screen[6][0] == 0 ) && ( ships_on_screen[7][0] == 0 ) &&
           ( ships_on_screen[8][0] == 0 ) && ( ships_on_screen[9][0] == 0 ) )
        {
          int j;
          x = SHIPFIRSTROWX;
          y = SHIPFIRSTROWY;

          for ( j = 0; j <= 9; j++ )
          {
            // Are we still drawing ships?
            if ( num_ships > num_on_screen )
            {
              if ( ships_on_screen[j][0] == 0 )
              {
                if ( j == 5 ) // Second row.
                {  
                  x = SHIPSECONDROWX;
                  y = SHIPSECONDROWY;
                }
                DrawShip( ships_on_screen[j][1], j );
                delay( 150 );  
                x = x + SHIPWIDTH + 2;         
              
                // Give it a strength value. 
                ships_on_screen[j][0] = (int)( (ec * ( (float) random(RAND_MAX) / RAND_MAX ) ) + 20 );
                num_on_screen++;   
              }
            }
          }  
        }

        // Draw a + if more than 10 ships attacking.
        SendCommand( "[cx 122][cy 34][cp 0]^" );
        if ( num_ships > num_on_screen )
        {         
          SendText( "+" );
        } 
        else 
        {       
          SendText( " " );
        }      

        // Randomly target a ship.
        targeted = random( RAND_MAX ) % 10;
        while ( ships_on_screen[targeted][0] == 0 )
        {
          // No ship in that slot, choose another.
          targeted = random( RAND_MAX ) % 10;
        }

        // Draw the blast on that ship.
        for ( int b = 0; b < 6; b++ )
        {                
          DrawShip( ships_on_screen[targeted][1], targeted, true );
          orders = GetOrders ( 50, orders );
          DrawShip( ships_on_screen[targeted][1], targeted );
          orders = GetOrders ( 50, orders );
        }             

        // Work out damage to ship.
        ships_on_screen[targeted][0] = ships_on_screen[targeted][0] - ( random( RAND_MAX ) % 30 + 10 );

        // Choose a damage graphic for it if not already one.
        if ( ships_on_screen[targeted][1] == 0 )
        {
          ships_on_screen[targeted][1] = ( random( RAND_MAX ) % 3 ) + 1;
          DrawShip ( ships_on_screen[targeted][1], targeted );
        }

        // Did we do enough damage to sink it?  
        if ( ships_on_screen[targeted][0] <= 0 )
        {
          num_on_screen--;
          num_ships--;
          sunk++;               
          SinkShip ( ships_on_screen, targeted );
          ships_on_screen[targeted][0] = 0;
          ships_on_screen[targeted][1] = 0; 
          FightStats( num_ships, orders );
        }

        // If we sunk all ships we stop firing.
        if ( num_ships == 0 )
        {
          i = i + guns;
        }

        // Check for new orders.
        orders = GetOrders ( 500, orders );

      } // End attacks.

      // Say how many we sunk if we sunk any.
      if ( sunk > 0 )
      {  
        ClearBattleText();          
        SendCommand( GetCommandStringFromTable(121) ); // Sunk
        itoa( sunk, charBuffer, 10 );
        SendText( charBuffer ); 
        SendCommand( GetCommandStringFromTable(122) ); // of the buggers, Taipan!
        SendBleep( 1 );            
      } 
      else 
      {
        ClearBattleText();
        SendCommand( GetCommandStringFromTable(123) ); // Hit 'em, but didn't sink 'em, Taipan!
      } 

      // Get new orders.
      orders = GetOrders ( 2000, orders );

      // Did any ships run away?
      if ( ( random(RAND_MAX) % s0 > ( num_ships * .6 / id) ) && ( num_ships > 2) )
      {
        // Yes, but how many?
        int ran = ( random(RAND_MAX) % ( num_ships / 3 / id ) ) + 1;

        num_ships = num_ships - ran;
        ClearBattleText();
        itoa( ran, charBuffer, 10 );
        SendText( charBuffer ); 
        SendCommand( GetCommandStringFromTable(124) ); // ran away, Taipan!
        SendBleep( 1 );

        // Draw the ships minus those that ran away.
        if ( num_ships <= 10 )
        {
          for ( i = 9; i >= 0; i-- )
          {
            if ( ( num_on_screen > num_ships ) && ( ships_on_screen[i][0] > 0 ) )
            {
              ships_on_screen[i][0] = 0;
              ships_on_screen[i][1] = 0;
              num_on_screen--;
              ClearShip ( i );
            }
          }
          // Clear any plus sign that was there.
          if ( num_on_screen == num_ships )
          {                 
            SendCommand( "[cx 122][cy 34][cp 0]^" );             
            SendText( " " );         
          }
        }
        // Check for new orders.
        orders = GetOrders ( 2000, orders ); 
      } // End if any ran away.

    } // End if orders are to fight and have guns.

    // If the orders were to fight but we have no guns!   
    if ( ( orders == 1 ) && ( guns == 0 ) && ( bHanShotFirst == 1 ) ) 
    {                 
      SendCommand( GetCommandStringFromTable(125) ); // We have no guns, Taipan!!
      // Get new orders.
      orders = GetOrders ( 2000, orders );
    } 

    // Are we throwing cargo?
    if ( ( orders == 3 ) && ( bHanShotFirst == 1 ) ) 
    {

      int  choice = 0;
      long amount = 0;
      long total = 0;

      ClearBattleText();
      SendCommand( GetCommandStringFromTable(126) ); // You have the following on board, Taipan:
      SendCommand( GetCommandStringFromTable(127) ); // 1) Opium: 
      itoa( hold_[0], charBuffer, 10 );         
      SendText( charBuffer );
      SendText( " " );
      SendCommand( GetCommandStringFromTable(128) ); // 2) Silk:
      itoa( hold_[1], charBuffer, 10 );
      SendText( charBuffer );
      SendText( "\n" );
      SendCommand( GetCommandStringFromTable(129) ); // 3) Arms: 
      itoa( hold_[2], charBuffer, 10 );         
      SendText( charBuffer );
      SendText( " " );
      SendCommand( GetCommandStringFromTable(130) ); // 4) General:
      itoa( hold_[3], charBuffer, 10 );
      SendText( charBuffer ); 
      SendCommand( GetCommandStringFromTable(131) ); // What shall I throw overboard?

      while ( ( choice != '1' ) && 
        ( choice != '2' ) && 
        ( choice != '3' ) && 
        ( choice != '4' ) && 
        ( choice != '#' ) )
      {
        choice = GetKey();
      }

      if ( choice == '1' ) 
      {
        choice = 0;
      } 
      else if ( choice == '2' )
      {
        choice = 1;
      } 
      else if ( choice == '3' ) 
      {
        choice = 2;
      } 
      else if ( choice == '4' ) 
      {
        choice = 3;
      } 
      else
      {
        choice = 4;
      }

      // Did we choose a specific cargo?
      if ( choice < 4 )
      {   
        ClearBattleText();           
        SendCommand( GetCommandStringFromTable(133) ); // How much, Taipan?
        amount = GetNumber();
        if ( amount > hold_[choice] )
        {
          amount = hold_[choice];
        }
        total = hold_[choice];
      } 
      // Or do we just chuck it all!
      else 
      {
        total = hold_[0] + hold_[1] + hold_[2] + hold_[3];
      }

      // Was there anything to thrown overboard?
      if ( total > 0 )
      {
        SendCommand( GetCommandStringFromTable(134) ); // Let's hope we lose 'em, Taipan!
        if ( choice < 4 )
        {
          // Thrown just the choosen cargo.
          hold_[choice] = hold_[choice] - amount;
          hold = hold + amount;
          ok = ok + ( amount / 10 ); // Escape modifier.
        } 
        else 
        {
          // Throw it all.
          hold_[0] = 0;
          hold_[1] = 0;
          hold_[2] = 0;
          hold_[3] = 0;
          hold = hold + total;
          ok = ok + ( total / 10 ); // Escape modifier.
        }
        SendBleep( 1 );
        GetKey( 3000 );
      } 
      else
      {
        ClearBattleText();
        SendCommand( GetCommandStringFromTable(135) ); // There's nothing there, Taipan!
        SendBleep( 5 );
        GetKey( 3000 );
      }
    }

    // If we are running or throwing cargo.
    if ( (( orders == 2 ) || ( orders == 3 )) && ( bHanShotFirst == 1 ) )
    {
      // Run!
      if ( orders == 2 )
      {
        SendCommand( GetCommandStringFromTable(136) ); // Aye, we'll run, Taipan!
        orders = GetOrders ( 3000, orders );
      }

      ok = ok + ik++; // Escape modifier.

      // Did we get away?
      if ( random(RAND_MAX) % ok > random(RAND_MAX) % num_ships )
      {
        // Escaped.
        SendCommand( GetCommandStringFromTable(137) ); // We got away from 'em, Taipan! 
        SendBleep( 5 );            
        GetKey( 3000 );
        num_ships = 0;
      } 
      else
      {
        // Didn't escape.
        SendCommand( GetCommandStringFromTable(138) ); // Couldn't lose 'em.

        // Check for new orders.
        orders = GetOrders ( 3000, orders );

        // Did we get away from any of them? 
        if ( ( num_ships > 2 ) && ( random(RAND_MAX) % 5 == 0 ) )
        {
          int lost = ( random(RAND_MAX) % num_ships / 2 ) + 1;

          num_ships = num_ships - lost;
          FightStats( num_ships, orders );

          SendCommand( GetCommandStringFromTable(139) ); // But we escaped from
          itoa( lost, charBuffer, 10 );
          SendText( charBuffer );
          SendCommand( GetCommandStringFromTable(140) ); // of 'em!

          // Draw the ships minus those gone.
          if ( num_ships <= 10 )
          {
            for ( i = 9; i >= 0; i-- )
            {
              if ( ( num_on_screen > num_ships ) && ( ships_on_screen[i][0] > 0 ) )
              {
                ships_on_screen[i][0] = 0;
                ships_on_screen[i][1] = 0;
                num_on_screen--;
                ClearShip ( i );
              }
            }
            // Clear any plus sign that was there.
            if (  num_on_screen == num_ships)
            {                 
              SendCommand( "[cx 122][cy 34][cp 0]^" );             
              SendText( " " );         
            }
          }                
          // Check for new orders.
          orders = GetOrders ( 2000, orders );
        }
      }
    }

    // If there are enemy ships remaining they shoot at us.
    if ( num_ships > 0 )
    {         
      FightStats( num_ships, orders );         
      SendCommand( GetCommandStringFromTable(141) ); // They're firing on us, Taipan!
      ShipHit();
      SendBleep( 3 );

      // Check for new orders.
      orders = GetOrders ( 2000, orders );                    

      // Draw the ships on screen.
      for ( i = 0; i <= 9; i++ )
      {
        if ( i == 5 ) // Second row.
        {  
          x = SHIPSECONDROWX;
          y = SHIPSECONDROWY;
        }
        // If there is a ship in this position...
        if ( ships_on_screen[i][0] > 0 )
        {
          DrawShip ( ships_on_screen[i][1], i );
          delay( 150 ); 
        }             
        x = x + SHIPWIDTH + 2;         
      }      

      // Draw a + if more than 10 ships.
      SendCommand( "[cx 122][cy 34][cp 0]^" );
      if (num_ships > num_on_screen)
      {         
        SendText( "+" );
      } 
      else {       
        SendText( " " );
      }

      ClearBattleText(); 
      SendCommand( GetCommandStringFromTable(142) ); // We've been hit, Taipan!!
      SendBleep( 3 );
      orders = GetOrders ( 2000, orders );

      // Was a gun hit?
      i = ( num_ships > 15 ) ? 15 : num_ships;
      if ( ( guns > 0 ) && ( (random( RAND_MAX ) % 100 < ( ( (float) damage / capacity ) * 100 ) ) ||
        ( ( ( (float) damage / capacity ) * 100) > 80 ) ) )
      {
        i = 1;
        guns--;
        hold = hold + 10;
        FightStats( num_ships, orders );

        SendCommand( GetCommandStringFromTable(143) ); // The buggers hit a gun, Taipan!!
        SendBleep( 3 );
        FightStats( num_ships, orders );
        orders = GetOrders ( 2000, orders );
      }

      // Calculate damage to our ship.
      damage = damage + ( ( ed * i * id ) * ( (float) random( RAND_MAX ) / RAND_MAX ) ) + ( i / 2 );

      // Did Li Yuen's pirates arrive?
      if ( ( id == GENERIC ) && ( random( RAND_MAX ) % 20 == 0 ) )
      {
        return 2;
      }
    }

    // Now we get to shoot if we didn't before.
    bHanShotFirst = 1;

  } // End while ships left to fight.

  // If we fought...
  if ( orders == 1 )
  {      
    SendCommand( GetCommandStringFromTable(144) ); // We got 'em all, Taipan!
    SendBleep( 1 );
    GetKey( 3000 );
    return 1; // We won.
  } 
  else
  {
    return 3; // We escaped.
  }
}

////////////////////////////////////////////////////////////////////////////////
// Retire.
////////////////////////////////////////////////////////////////////////////////
void Retire()
{
  PortStats();
  ClearText();
  SendCommand( GetCommandStringFromTable(145) ); // You're a millionaire!
  GetKey( 5000 );
  FinalStats();
}

////////////////////////////////////////////////////////////////////////////////
// Final stats.
////////////////////////////////////////////////////////////////////////////////
void FinalStats()
{ 

  int years = year - 1860;
  int time = ((year - 1860) * 12) + month;
  char choice = 0;

  cash = cash + bank - debt;

  ClearScreen();
  SendCommand( GetCommandStringFromTable(146) ); // Your final status: Net cash:
  FormatFloatForDisplay( cash, 1 );
  SendText( charBuffer );

  SendCommand( GetCommandStringFromTable(147) ); // Ship size: 
  itoa ( capacity, charBuffer, 10 ); 
  SendText( charBuffer );

  SendCommand( GetCommandStringFromTable(148) ); //  units with 
  itoa ( guns, charBuffer, 10 ); 
  SendText( charBuffer );

  SendCommand( GetCommandStringFromTable(149) ); //  guns. You traded for  
  itoa ( years, charBuffer, 10 ); 
  SendText( charBuffer );
  SendCommand( GetCommandStringFromTable(150) ); // year
  if ( years != 1 )
  {
    SendCommand( GetCommandStringFromTable(151) ); // s
  }   
  SendCommand( GetCommandStringFromTable(152) ); // and
  itoa ( month, charBuffer, 10 ); 
  SendText( charBuffer );
  SendCommand( GetCommandStringFromTable(153) ); // month
  if ( month > 1 )
  {
    SendCommand( GetCommandStringFromTable(154) ); // s
  }

  cash = cash / 100 / time;
  SendCommand( GetCommandStringFromTable(155) ); // Your score is 
  FormatFloatForDisplay( cash, 1 );
  SendText( charBuffer );

  if ( ( cash < 100 ) && ( cash >= 0 ) )
  {     
    SendCommand( GetCommandStringFromTable(156) ); // Have you considered a land based job?
  } 
  else if ( cash < 0 ) 
  {
    SendCommand( GetCommandStringFromTable(157) ); // The crew has requested that you stay on shore for their safety!!
  }

  GetKey();

  ClearScreen();
  SendCommand( GetCommandStringFromTable(158) ); // Your Rating: Ma Tsu 50,000 and over Master Taipan 8,000 to 49,999
  SendCommand( GetCommandStringFromTable(159) ); // Taipan 1,000 to 7,999 Compradore 500 to 999 Galley Hand less than 500 

  // cash = 50000; Uncomment and change this to test the end display.

  // Draw rectangle around appropriate score.
  if ( cash >= 50000 )
  {
    DrawRect( 7 );
  } 
  else if ( ( cash < 50000 ) && ( cash >= 8000 ) )
  {     
    DrawRect( 8 );
  }
  else if ( ( cash < 8000 ) && ( cash >= 1000 ) )
  {
    DrawRect( 9 );
  }
  else if ( ( cash < 1000 ) && ( cash >= 499 ) )
  {
    DrawRect( 10 );
  }   
  else // if ( cash < 500 )
  {    
    DrawRect( 11 );
  }     

  while(1); // Game ends here.
}

////////////////////////////////////////////////////////////////////////////////
// Main loop.
////////////////////////////////////////////////////////////////////////////////
void loop()
{ 
  char choice = '0';  

  Intro();
  NameFirm();
  CashOrGuns();
  SetPrices();

  // Main game loop.
  while ( 1 )
  {  
    PortStats( true );

    // If in Hong Kong and we haven't paid tribute for a while and we have some cash.
    if ( ( port == 1 ) && ( li == 0 ) && ( cash > 0 ) )
    {
      LiYuenExtortion();
    }

    // If in Hong Kong and the ship is damaged McHenry arrives.
    if ( ( port == 1 ) && ( damage > 0 ) )
    {
      McHenry();
    }

    // If in Hong Kong and we have enough debt and we haven't been 
    // warned already show Elder brother Wu's warning.
    if ( ( port == 1 ) && ( debt >= 10000 ) && ( wu_warn == 0 ) )
    {
      ElderBrotherWuWarning();
    }

    // If in Hong Kong we visit Ender Brother Wu.
    if ( port == 1 )
    {
      ElderBrotherWu();
    }

    // New ship or gun.
    if ( random(RAND_MAX) % 4 == 0 )
    {
      if ( random(RAND_MAX) % 2 == 0 )
      {
        NewShip();
      }
      // Maximum of 1000 guns! 
      else if ( guns < 1000 ) 
      {
        NewGun();
      }
    }

    // Opium seizure if not in Hong Kong.
    if ( ( port != 1 ) && ( random(RAND_MAX) % 18 == 0 ) && ( hold_[0] > 0 ) )
    {
      // Calculate the fine. 
      float fine = ( ( cash / 1.8 ) * ( (float) random(RAND_MAX) / RAND_MAX ) ) + 1;

      // Remove the cargo and the fine cash.
      hold = hold + hold_[0];
      hold_[0] = 0;
      cash = cash - fine;

      ClearText();
      SendCommand( GetCommandStringFromTable(166) ); // Bad Joss!! The local authorities have seized your Opium cargo and have also fined you 
      FormatFloatForDisplay( fine, 1 );
      SendCommand( GetCommandStringFromTable(167) ); // , Taipan!
      SendBleep( 3 );
      GetKey( 5000 );
      PortStats();
    }

    // Warehouse theft. 1/50 chance.
    if ( ( random(RAND_MAX) % 50 == 0 ) && ( ( hkw_[0] + hkw_[1] + hkw_[2] + hkw_[3] ) > 0 ) )
    {
      int i;
      for ( i = 0; i < 4; i++ )
      {
        hkw_[i] = ( ( hkw_[i] / 1.8 ) * ( (float) random(RAND_MAX) / RAND_MAX ) );
      }
      ClearText();
      SendCommand( GetCommandStringFromTable(168) ); // Messenger reports large theft from warehouse, Taipan.
      SendBleep( 3 );
      GetKey( 5000 );
      PortStats();
    }

    // Li Yuen extortion. 1/20 chance.
    if ( random(RAND_MAX) % 20 == 0 )
    {
      // This counter is incremented by chance. But there is 
      // delay built in by letting the count go to 4 before
      // we get extorted again (when the counter is 0).
      if ( li > 0 ) 
      {          
        li++; 
      }
      if ( li == 4 ) 
      { 
        // Can be extorted again now.
        li = 0; 
      }
    }

    // If not in Hong Kong and Li Yuen wants to extort us there is a 
    // 1 in 4 chance he calls us back to Hong Kong.
    if ( ( port != 1 ) && ( li == 0 ) && ( random(RAND_MAX) %4 != 0 ) )
    {
      ClearText();
      SendCommand( GetCommandStringFromTable(169) ); // Li Yuen has sent a Lieutenant, Taipan. He says his admiral wishes to see you in Hong
      SendCommand( GetCommandStringFromTable(170) ); // Kong, posthaste!
      SendBleep( 1 );
      GetKey( 3000 );
    }

    // Good prices. 1 in 9 chance.
    if ( random (RAND_MAX) % 9 == 0 )
    {
      GoodPrices();
    }

    // If cash is greater than 25000 there is a 1 in 20 chance we get robbed.
    if ( ( cash > 25000 ) && ( random(RAND_MAX) % 20 == 0 ) )
    {
      // Robbed!
      float robbed = ((cash / 1.4) * ((float) random(RAND_MAX) / RAND_MAX));
      cash = cash - robbed;

      ClearText();
      SendCommand( GetCommandStringFromTable(171) ); // Bad Joss!! You've been beaten up and robbed of
      FormatFloatForDisplay( robbed, 1 );
      SendText( charBuffer ); 
      SendCommand( GetCommandStringFromTable(172) ); //  in cash, Taipan!
      SendBleep( 3 );
      GetKey( 5000 );
      PortStats();
    }    

    // Port choices, what do we do here?
    while ( 1 )
    {
      // Get choice.
      while ( choice != '5' )
      {
        switch ( choice = PortChoices() )
        {
        case '1':               
          {   
            Buy();
            break;
          }
        case '2':
          {
            Sell();
            break;
          }
        case '3':
          {
            VisitBank();
            break;
          }
        case '4':
          {
            Transfer();
            break;
          }
        case '6':
          {
            Retire();
            break;
          }               
        default:
          {                 
          }                  
        } // End switch.

        PortStats();

      } // End while not a valid choice.

      choice = '0';

      // If the hold isn't overloaded we can leave.
      if ( hold >= 0 )
      {
        QuitPort();
        break;
      } 
      else
      {
        // Ship overloaded.
        Overload();
      }

    } // End while 1 port choices.

  } // End while 1 main game loop.

} 
