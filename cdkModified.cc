/*
 * Modified CDK file
 *  Anthony Tang, ajt161230, 3377.502
 *
 * (
 * Original
 * File:   example1.cc
 * Author: Stephen Perkins
 * Email:  stephen.perkins@utdallas.edu
 * )
 */

#include <iostream>
#include <stdint.h>
#include "cdk.h"
#include <fstream>

#define MATRIX_HEIGHT 5
#define MATRIX_WIDTH 3
#define BOX_WIDTH 15
#define MATRIX_NAME_STRING "Binary File Contents"
using namespace std;

//header class
class BinaryFileHeader{
public:
  uint32_t magicNumber; //feedface I hope
  uint32_t versionNumber;
  uint64_t numRecords;

};

class BinaryFileRecord{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

//create a constant for the max string length of the 
//bin input
const int maxRecordStringLength = 25;
//record stream
class BinaryFileRecord{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
  
};

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"C0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"C0", "a", "b", "c"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  /*
   * open the binary file cs3377.bin
   */
  
  ifstream binInFile ("cs3377.bin", ios::in | ios::binary);

  if(!binInFile.is_open()){
    cout << "Error opening the binary file. Exiting program" << endl;
    return 0;
  }


  //create instances of the header and record classes to read into
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  BinaryFileRecord *myRecord = new BinaryFileRecord();


  binInFile.read((char*) myHeader, sizeof(BinaryFileHeader));
  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  
  //setCDKMatrixCell(myMatrix, 1, 1, myHeader->magicNumber);
  for(int i = 2; i < 6; i++){
    setCDKMatrixCell(myMatrix, i, 1, "strlen: " + myRecord->strLength);
    setCDKMatrixCell(myMatrix, i, 2, ""+myRecord->stringBuffer;
  }
  setCDKMatrixCell(myMatrix, 2, 2, "Test Message");
  setCDKMatrixCell(myMatrix, 2, 3, "GREMLINS" );
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
