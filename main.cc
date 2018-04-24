//Melquiades Parra
//map160330@utdallas.edu
//CS3377.002

#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "cdk.h"

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 30
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

class BinaryFileHeader
{
	public:
		uint32_t magicNumber;
		uint32_t versionNumber;
		uint64_t numRecords;
};

const int maxRecStrLen = 25;

class BinaryFileRecord
{
	public:
		uint8_t strLen;
		char strBuffer[maxRecStrLen];
};

int main()
{
	WINDOW* window;
	CDKSCREEN* screen;
	CDKMATRIX* myMatrix;

	const char* rowTitles[] = {"R0","R1","R2","R3","R4","R5"};
	const char* colTitles[] = {"C0","C1","C2","C3"};

	int boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
	int boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED, vMIXED, vMIXED};

	window = initscr();
	screen = initCDKScreen(window);

	initCDKColor();

	myMatrix = newCDKMatrix(screen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
				MATRIX_NAME_STRING, (char**) rowTitles, (char**) colTitles, boxWidths, boxTypes,
				1, 1, ' ', ROW, true, true, false);

	
	if(myMatrix == NULL)
	{
		cout << "Error creating matrix" << endl;
		_exit(1);
	}

	drawCDKMatrix(myMatrix, true);

	BinaryFileHeader* h = new BinaryFileHeader();
	BinaryFileRecord* r = new BinaryFileRecord();

	ifstream ifs("cs3377.bin", ios::in | ios::binary);

	ifs.read((char*) h, sizeof(BinaryFileHeader));
	
	stringstream strs;
	strs << "Magic: 0x" << std::hex << h->magicNumber;
	string temp = strs.str();
	char* magNum = (char*) temp.c_str();
	strs.str("");

	strs << "Version: " << std::dec << h->versionNumber;
	temp = strs.str();
	char* verNum = (char*) temp.c_str();
	strs.str("");

	strs << "NumRecords: " << h->numRecords << endl;
	temp = strs.str();
	char* numRec = (char*) temp.c_str();
	strs.str("");
	
	setCDKMatrixCell(myMatrix, 1, 1, magNum);
	setCDKMatrixCell(myMatrix, 1, 2, verNum);
	setCDKMatrixCell(myMatrix, 1, 3, numRec);

	for(int i = 0; i < 4; i++)
	{
		ifs.read((char*) r, sizeof(BinaryFileRecord));

		int l = r->strLen;
		strs << "strlen: " << l;
		temp = strs.str();
		char* strL = (char*) temp.c_str();
		strs.str("");

		setCDKMatrixCell(myMatrix, i+2, 1, strL);
		setCDKMatrixCell(myMatrix, i+2, 2, r->strBuffer);
	}

	drawCDKMatrix(myMatrix, true);

	unsigned char x;
	cin >> x;

	endCDK();

	return 0;
}
