#include <iostream>
#include <stdint.h>
#include <fstream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

class BinaryFileHeader{
  public:
  
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

const int maxRecordStringLength = 25;
class BinaryFileRecord{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];

};
int main(){

  BinaryFileHeader *myHeader = new BinaryFileHeader();
  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);
  
  if(binInfile.is_open()){
  
  binInfile.read((char*) myHeader, sizeof(BinaryFileHeader));


  cout << "Magic Number was : "<< myHeader->magicNumber << endl;
  cout << "Version Number was : " << myHeader -> versionNumber << endl;
  cout << "numRecords was : " << myHeader -> numRecords << endl;

  BinaryFileRecord *myRecord = new BinaryFileRecord();
  

  for(int i = 0; i < 4; i++){
    
      binInfile.read((char*) myRecord, sizeof(BinaryFileRecord));      
      cout << unsigned(myRecord->strLength) << " - " << myRecord->stringBuffer << endl; 
  } 
 

  }
  
  binInfile.close();
  return 0;

}
