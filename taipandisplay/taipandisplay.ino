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

#include <MemoryFree.h>
#include <TVout.h>
#include <font4x6.h>
#include "Taipan.h"
#include "Ship0.h"
#include "Ship1.h"
#include "Ship2.h"
#include "Ship3.h"
#include "Ship4.h"

#include <pollserial.h>

TVout TV;
pollserial pserial;

int busy = 2; // Serial busy flag.

const int KEYPADPIN = 0; // Analog input pin that the keypad is attached to.
// Digital 7 = video
// Digital 9 = sync
// Digital 11 = audio.

uint8_t * heapptr, * stackptr;

const int SERIALBUFFERSIZE = 126;
char serialBuffer[SERIALBUFFERSIZE + 1];
int serialBufferIndex = 0;

const int COMMANDSIZE = 2;
char commandBuffer[COMMANDSIZE + 1];
int commandValueIndex = 0;

uint8_t bleep = 0;

uint8_t bm_x = 0;
uint8_t bm_y = 0;
uint8_t bm_p = 0;

uint8_t cur_x = 0;
uint8_t cur_y = 0;

uint8_t rect_x = 0;
uint8_t rect_y = 0;
uint8_t rect_w = 0;
uint8_t rect_h = 0;
uint8_t rect_col = 0;

uint8_t shift_a = 0;
uint8_t shift_d = 0;

uint8_t del = 0;

// Buffer to manipulate ship graphics in.
unsigned char Ship[152] = {24,25};

////////////////////////////////////////////////////////////////////////////////
// Shinking ship bitmap.
////////////////////////////////////////////////////////////////////////////////
void SinkingShipBitmap( int bitmapToDraw, int position )
{    
    memset ( Ship, 0, sizeof(Ship) );  
    Ship[0] = 24;
    Ship[1] = 25;
     
     
    byte width = (byte)(pgm_read_byte(Ship0));
    byte height = (byte)(pgm_read_byte(Ship0 + 1));
      
    if ( bitmapToDraw == 0 )
    {      
      memcpy ( (Ship + 2) + (position * 6) , Ship0 + 2, sizeof (Ship - (position * 6) - 2 ) );  
    }
    else if ( bitmapToDraw == 1 )
    {
      memcpy ( (Ship + 2) + (position * 6) , Ship1 + 2, sizeof (Ship - (position * 6) - 2 ) );  
    }
    else if ( bitmapToDraw == 2 )
    {
      memcpy ( (Ship + 2) + (position * 6) , Ship2 + 2, sizeof (Ship - (position * 6) - 2 ) );  
    }
    else if ( bitmapToDraw == 3 )
    {
      memcpy ( (Ship + 2) + (position * 6) , Ship3 + 2, sizeof (Ship - (position * 6) - 2 ) );  
    }
    else if ( bitmapToDraw == 4 )
    {
      memcpy ( (Ship + 2) + (position * 6) , Ship4 + 2, sizeof (Ship - (position * 6) - 2 ) );  
    } 
    
    for ( int i = 0; i < 25; i+6 )
    {
       Serial.print(Ship0[2 + i]);
       Serial.print(Ship0[2 +i+1]);
       Serial.print(Ship0[2 +i+2]);
       Serial.print(Ship0[2 +i+3]);
       Serial.print(Ship0[2 +i+4]);
       Serial.println(Ship0[2 +i+5]);       
    }

    Serial.println();
    
    for ( int j = 0; j < 25; j+6 )
    {
       Serial.print(Ship[2 + j]);
       Serial.print(Ship[2 +j+1]);
       Serial.print(Ship[2 +j+2]);
       Serial.print(Ship[2 +j+3]);
       Serial.print(Ship[2 +j+4]);
       Serial.println(Ship[2 +j+5]);       
    }
}

////////////////////////////////////////////////////////////////////////////////
// Bleep1
////////////////////////////////////////////////////////////////////////////////
void Bleep1()
{    
  TV.tone( 1000 );
  TV.delay( 75 );
  TV.noTone();
  TV.tone( 1500 );
  TV.delay( 75 );
  TV.noTone();
  TV.tone( 2000 );
  TV.delay( 75 );
  TV.noTone();
}

////////////////////////////////////////////////////////////////////////////////
// Bleep2
////////////////////////////////////////////////////////////////////////////////
void Bleep2()
{ 
  for ( int i = 0; i < 3; i++ )
  {  
    TV.tone( 1900 );
    TV.delay( 80 );
    TV.noTone();
    TV.tone( 2100 );
    TV.delay( 80 );
    TV.noTone();
  }
}

////////////////////////////////////////////////////////////////////////////////
// Bleep3
////////////////////////////////////////////////////////////////////////////////
void Bleep3()
{ 
  for ( int i = 0; i < 2; i++ )
  { 
    TV.tone( 1700 );
    TV.delay( 70 );
    TV.noTone();
    TV.tone( 1800 );
    TV.delay( 50 );
    TV.noTone(); 
    TV.tone( 1700 );
    TV.delay( 70 );
    TV.noTone();
    TV.tone( 1800 );
    TV.delay( 50 );
    TV.noTone();
    TV.tone( 1900 );
    TV.delay( 90 );
    TV.noTone();
  }
}

////////////////////////////////////////////////////////////////////////////////
// Bleep4
////////////////////////////////////////////////////////////////////////////////
void Bleep4()
{  
  TV.tone( 1500 );
  TV.delay( 100 );
  TV.noTone();
}

////////////////////////////////////////////////////////////////////////////////
// Bleep5
////////////////////////////////////////////////////////////////////////////////
void Bleep5()
{ 
  for ( int i = 0; i < 3; i++ )
  {  
    TV.tone( 1800 );
    TV.delay( 60 );
    TV.noTone();
    TV.tone( 2000 );
    TV.delay( 60 );
    TV.tone( 2100 );
    TV.delay( 20 );
    TV.tone( 2200 );
    TV.delay( 20 );
    TV.noTone();
  }
}

////////////////////////////////////////////////////////////////////////////////
// DeleteChar.
////////////////////////////////////////////////////////////////////////////////
void DeleteChar( uint8_t c ) 
{    
  uint8_t x = 0;
  uint8_t  y = 0;
  
  for ( int i = 0; i < c; i++ )
  {
    TV.get_cursor(&x, &y);
    TV.set_cursor(x - 4, y);
    TV.print(" ");
    TV.set_cursor(x - 4, y);
  }
}

////////////////////////////////////////////////////////////////////////////////
// Clear the serial receive buffer.
////////////////////////////////////////////////////////////////////////////////
void ClearSerialBuffer() 
{
  memset (serialBuffer, 0, sizeof(serialBuffer));
  serialBufferIndex = 0;
}  

////////////////////////////////////////////////////////////////////////////////
// Set the busy flag.
////////////////////////////////////////////////////////////////////////////////
void SetBusy() 
{
  digitalWrite( busy, HIGH ); 
}  

////////////////////////////////////////////////////////////////////////////////
// Clear the busy flag.
////////////////////////////////////////////////////////////////////////////////
void ClearBusy() 
{
  digitalWrite( busy, LOW ); 
}  

////////////////////////////////////////////////////////////////////////////////
// Setup.
////////////////////////////////////////////////////////////////////////////////
void setup() 
{    
  pinMode(busy, OUTPUT);
  SetBusy();
  
  TV.begin( NTSC,128,96 );
  
  TV.select_font( font4x6 );
  TV.set_hbi_hook( pserial.begin( 38400 ) ); 
  
  TV.clear_screen();
  
  TV.print(" freeMemory() = " );
  TV.println( freeMemory() );
  
  ClearSerialBuffer();
  ClearBusy();
 
}

////////////////////////////////////////////////////////////////////////////////
// Process command.
////////////////////////////////////////////////////////////////////////////////
void ProcessCommand()
{
  // Now process the rest based on the command.
  if ( strcmp( commandBuffer, "cs" ) == 0 ) // Clear screen.
  {
      TV.clear_screen();
      cur_x = 0;
      cur_y = 0;
  }
  
  else if ( strcmp( commandBuffer, "bl" ) == 0 ) // Bleep!
  {
    bleep = atoi( &(serialBuffer[commandValueIndex]) );
    switch ( bleep )
    {
       case 1:
       {     
         Bleep1(); 
         break;
       }
       case 2:
       {     
         Bleep2(); 
         break;
       }
       case 3:
       {     
         Bleep3(); 
         break;
       }
       case 4:
       {     
         Bleep4(); 
         break;
       }
       case 5:
       {     
         Bleep5(); 
         break;
       }
    }
  }
  
  else if ( strcmp( commandBuffer, "bx" ) == 0 ) // Bitmap x position.
  {
    bm_x = atoi( &(serialBuffer[commandValueIndex]) );
  }
  
  else if ( strcmp( commandBuffer, "by" ) == 0 ) // Bitmap y position.
  {
    bm_y = atoi( &(serialBuffer[commandValueIndex]) );
  } 

  else if ( strcmp( commandBuffer, "bp" ) == 0 ) // Bitmap partial position.
  {
    bm_p = atoi( &(serialBuffer[commandValueIndex]) );
  }      
  
  else if ( strcmp( commandBuffer, "bt" ) == 0 ) // Bitmap Taipan!
  {       
      TV.bitmap( bm_x, bm_y, Taipan );          
  }
    
  else if ( strcmp( commandBuffer, "bs" ) == 0 ) // Bitmap ship.
  {
    int bitmapToDraw = atoi( &(serialBuffer[commandValueIndex]) );
    byte width = (byte)(pgm_read_byte(Ship0));
    byte height = (byte)(pgm_read_byte(Ship0 + 1));
    
    SinkingShipBitmap( bitmapToDraw, bm_p );
    
    if ( bitmapToDraw == 0 )
    {
      TV.bitmap( bm_x, bm_y + bm_p, Ship0 ); 
    }
    else if ( bitmapToDraw == 1 )
    {
      TV.bitmap( bm_x, bm_y + bm_p, Ship1 );
    }
    else if ( bitmapToDraw == 2 )
    {
      TV.bitmap( bm_x, bm_y + bm_p, Ship2 );
    }
    else if ( bitmapToDraw == 3 )
    {
      TV.bitmap( bm_x, bm_y + bm_p, Ship3 );
    }
    else if ( bitmapToDraw == 4 )
    {
      TV.bitmap( bm_x, bm_y + bm_p, Ship4 );
    }        

    TV.draw_rect( bm_x, bm_y, width, bm_p, 0, 0 );          
    TV.draw_rect( bm_x, bm_y + height, width, bm_p, 0, 0 );            
  }    

  else if ( strcmp( commandBuffer, "pr" ) == 0 ) // Print text.
  {              
    TV.print( &(serialBuffer[commandValueIndex]) );
  }
  
  else if ( strcmp( commandBuffer, "cx" ) == 0 ) // Set x cursor position.
  {
    cur_x = atoi( &(serialBuffer[commandValueIndex]) );
  }
  
  else if ( strcmp( commandBuffer, "cy" ) == 0 ) // Set y cursor position.
  {
    cur_y = atoi( &(serialBuffer[commandValueIndex]) );
  }
  
  else if ( strcmp( commandBuffer, "cp" ) == 0 ) // Move cursor to position set by x and y.
  {
    TV.set_cursor( cur_x, cur_y );
  }
    
  else if ( strcmp( commandBuffer, "dc" ) == 0 )  // Delete characters at current cursor position.
  {
    del = atoi( &(serialBuffer[commandValueIndex]) );
    DeleteChar( del );
  }
  
  else if ( strcmp( commandBuffer, "rx" ) == 0 )  // Rectangle x position.
  {
    rect_x = atoi( &(serialBuffer[commandValueIndex]) );
  }
  
  else if ( strcmp( commandBuffer, "ry" ) == 0 ) // Rectangle y position.
  {
    rect_y = atoi( &(serialBuffer[commandValueIndex]));
  }
  
  else if ( strcmp( commandBuffer, "rw" ) == 0 ) // Rectangle width.
  {
    rect_w = atoi( &(serialBuffer[commandValueIndex]) );
  }
  
  else if ( strcmp( commandBuffer, "rh" ) == 0 ) // Rectangle height.
  {
    rect_h = atoi( &(serialBuffer[commandValueIndex]) );
  }
  
  else if ( strcmp( commandBuffer, "rd" ) == 0 ) // Draw rectangle.
  {
    rect_col = atoi( &(serialBuffer[commandValueIndex]));
    if ( rect_col == 1 )
    {
      TV.draw_rect( rect_x, rect_y, rect_w, rect_h, WHITE );        
    }
    else
    {
      TV.draw_rect( rect_x, rect_y, rect_w, rect_h, BLACK, BLACK );        
    }
  }
  
  else if ( strcmp( commandBuffer, "iv" ) == 0 ) // Invert the screen.
  {
    TV.invert();        
  }
  
  else if ( strcmp( commandBuffer, "sa" ) == 0 ) // Shift amount.
  {
    shift_a = atoi( &(serialBuffer[commandValueIndex]) );        
  }
  
  else if ( strcmp( commandBuffer, "sd" ) == 0 ) // Shift direction.
  {
    shift_d = atoi( &(serialBuffer[commandValueIndex]) );        
  }
  
  else if ( strcmp( commandBuffer, "ss" ) == 0 ) // Shift screen.
  {
    int distance = 0;
    while ( distance <= shift_d )
    {
      TV.shift( shift_a, distance++ );        
      TV.delay(250);
    }
  }
  
  else
  {
   TV.printPGM("Command unknown: ");
   TV.println(commandBuffer);
  }
}

////////////////////////////////////////////////////////////////////////////////
// Main loop.
////////////////////////////////////////////////////////////////////////////////
void loop() 
{
  char character;  
  
  // If there is serial data.
  if (pserial.available()) 
  {  
    // Store the data in the buffer.  
    character = (char)pserial.read();
    serialBuffer[serialBufferIndex] = character;
    serialBufferIndex++;
    
    // Keep going till we get a terminator or the buffer is full.
    if ( ( character == '^' ) || ( serialBufferIndex >= SERIALBUFFERSIZE ) )
    {
      
      SetBusy(); // Set the busy flag.   
      
      // Remove half commands in case of buffer overflow.
      if ( serialBufferIndex >= SERIALBUFFERSIZE )
      {
        for ( int i = SERIALBUFFERSIZE - 3; i >= 0; i-- )
        {
          if (serialBuffer[i] == ']')
          {
            serialBuffer[i+1] = 0;
            break; 
          }        
        }              
      }
      // Reset to the start of the buffer.      
      serialBufferIndex = 0;
      
      // While we still have characters in the serial buffer to process.
      while (1)
      { 
        // Break if we have all the data or have run out of buffer.
        if ( (serialBuffer[serialBufferIndex] == 0) || (serialBufferIndex > SERIALBUFFERSIZE) ) 
        {
          break;
        }
                  
        // If the character is a [ we have a new command.
        if ( serialBuffer[serialBufferIndex] == '[' )
        {    
          // Next two characters are the command.
          commandBuffer[0] = serialBuffer[++serialBufferIndex];
          commandBuffer[1] = serialBuffer[++serialBufferIndex];
          commandBuffer[2] = 0; // Null terminate.
          // Next character is a space for readability.
          serialBufferIndex = serialBufferIndex + 2;          
          commandValueIndex = serialBufferIndex; // This is the index of the next command value.

          // Now find the end of this command and null terminate.
          while ( serialBuffer[serialBufferIndex] != ']') 
          {
            serialBufferIndex++;
          }
          serialBuffer[serialBufferIndex] = 0;
          
          //pserial.print("SerialBuffer: "); pserial.println(serialBuffer);
          //pserial.print("Command: "); pserial.println(commandBuffer);
          //pserial.print("Value: "); pserial.println(&(serialBuffer[commandValueIndex]));
          
          // Process the command.
          ProcessCommand();          
        }
        // Increment the buffer index.
        serialBufferIndex++;
           
      }
      ClearSerialBuffer();  // Clear the serial buffer. 
      ClearBusy(); // Clear the busy flag.      
    }     
    
  }
}     
