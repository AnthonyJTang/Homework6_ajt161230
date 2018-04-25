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
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "cdk.h"

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

//constant for the char* read by record
const int maxRecordStringLength = 25;

//record class
class BinaryFileRecord{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

//main
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

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);
  
  //create instance of header class to read
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  binInFile.read((char*) myHeader, sizeof(BinaryFileHeader));
  
  //make string stream and convert uint32_t to string
  stringstream ss;
  string magicNumString;
   ss << (myHeader->magicNumber);
   ss >> magicNumString;
  magicNumString = "Magic: " + magicNumString;
  
  //clear string stream between uses
  ss.clear();
  string versionString;
   ss << (myHeader->versionNumber);
   ss >> versionString; 
  versionString = "Version: " + versionString;

  //clear string stream between uses
  ss.clear();
  string numRecordsString;
  ss << (myHeader->numRecords);
  ss >> numRecordsString;
  numRecordsString = "NumRecords: " + numRecordsString;

  setCDKMatrixCell(myMatrix, 1, 1, magicNumString.c_str() );
  setCDKMatrixCell(myMatrix, 1, 2, versionString.c_str() );
  setCDKMatrixCell(myMatrix, 1, 3, numRecordsString.c_str() );
 
  BinaryFileRecord *myRecord = new BinaryFileRecord();
  
  //string need to be out here
  string strlenTemp;
 
  //iterate through rows 2 though 5 and print the strlen and buffer
  for(int i = 2; i < 6; i++){
    //read with each iteration
    binInFile.read((char*) myRecord, sizeof(BinaryFileRecord));

    ss.clear();
    ss << unsigned(myRecord->strLength);
    ss >> strlenTemp;
    strlenTemp = "strlen: " + strlenTemp;    
    setCDKMatrixCell(myMatrix, i, 1, strlenTemp.c_str());
    
    ss.clear();
    setCDKMatrixCell(myMatrix, i, 2, (myRecord->stringBuffer));
  }
  drawCDKMatrix(myMatrix, true);    /* required  */
 
  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
