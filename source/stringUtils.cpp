
#include "../include/hamLibs.h"

//Functions for String Encryption, base-0 version
/*
	this version is designed to use the ASCII characters
	of a single 'char' from a value of 0-255
 
   it is recommended to store the return values of these
   functions in a binary file. This would make it easier to
   retrieve the values for later
*/

namespace hamLibs {
namespace stringUtils {
using namespace std;

void encodeStr(const string& encryptKey, string& inputToEncrypt) {
	if (inputToEncrypt.length() == 0) return;
	
	//preliminary remainder check initialization
	int remainder = 0; //zero value
	int keyCount = 0;
	
	//variables used to determine when to stop counting numbers
	size_t keyPos = 0;
	size_t strPos = 0;

	//begin numerical addition. stop once the end of both strings is reached
	while (strPos < inputToEncrypt.length()) {
		keyCount = (strPos < inputToEncrypt.length()) ? inputToEncrypt[strPos] : 0;
		
		//take advantage of signed-char overflow to calculate current value
		remainder += encryptKey[keyPos] + keyCount;
		inputToEncrypt[strPos] = remainder;
		
		//check if there is a remainder to be tabulated
		remainder = (remainder > 255) ? 1 : 0;
		++strPos;
		++keyPos;
		if (keyPos == encryptKey.size()) keyPos = 0;
		
		//add 1 to the strPos if there is a remainder at the end of keyNum
		if (strPos >= inputToEncrypt.length() && remainder != 0) {
			inputToEncrypt.push_back('\0');
		}
	}
}

void decodeStr(const string& decryptKey, string& inputToDecrypt) {
	if (inputToDecrypt.length() == 0) return;
	//preliminary remainder check initialization
	int remainder = 0;
	
	//variables used to determine when to stop counting numbers
	size_t keyPos = 0;
	size_t strPos = 0;
	
	//make sure the program exits before the number necomes negative
	while (strPos < inputToDecrypt.length()) {
		//take advantage of signed-char overflow to calculate current value
		remainder += inputToDecrypt[strPos] - decryptKey[keyPos];
		inputToDecrypt[strPos] = remainder;
		
		//check if there is a remainder to be tabulated
		remainder = (remainder > 255) ? 1 : 0;
		++strPos;
		++keyPos;
		if (keyPos == decryptKey.size()) keyPos = 0;
	}
}

//---------------------------------------------------------------------
//			File Encryption
//---------------------------------------------------------------------
void encodeFile(const string& encryptKey, const char* fileName) {
	printf("Opening file \"%s\"...", fileName);
	if (fileName == HL_NULL) return;
	FILE* fileToEncrypt = fopen(fileName, "r+b");
	if (ferror(fileToEncrypt)) {
		printf("Failed.\n");
		return;
	}
	printf("Success.\n");
	
	//preliminary remainder check initialization
	int remainder = 0; //zero value
	int keyCount = 0;
	
	//variables used to determine when to stop counting numbers
	fseek(fileToEncrypt, 0, SEEK_END);
	size_t keyPos = 0;
	size_t filePos = 0;
	size_t strPos = 0;
	size_t strEndPos = ftell(fileToEncrypt);
	rewind(fileToEncrypt);
	
	printf("Encoding %s...", fileName);
	//begin numerical addition. stop once the end of both strings is reached
	while (strPos < strEndPos) {
		filePos = ftell(fileToEncrypt);
		rewind(fileToEncrypt);
		fseek(fileToEncrypt, filePos, SEEK_SET);
		
		keyCount = getc(fileToEncrypt);
		if (strPos >= strEndPos) keyCount = 0;
		
		//take advantage of signed-char overflow to calculate current value
		remainder += encryptKey[keyPos] + keyCount;
		filePos = ftell(fileToEncrypt) - 1;
		rewind(fileToEncrypt);
		fseek(fileToEncrypt, filePos, SEEK_SET);
		putc(remainder, fileToEncrypt);
		
		remainder = 0;
		++strPos;
		++keyPos;
		if (keyPos == encryptKey.size()) keyPos = 0;
		
		//add 1 to the strPos if there is a remainder at the end of keyNum
		if (strPos == strEndPos && remainder != 0) {
			putc(0, fileToEncrypt);
			++strEndPos; //variables used to avoid integer overflow
		}
		fflush(fileToEncrypt);
	}
	fclose(fileToEncrypt);
	printf("Done.\n");
}

void decodeFile(const string& decryptKey, const char* fileName) {
	printf("Opening file \"%s\"...", fileName);
	if (fileName == HL_NULL) return;
	FILE* fileToDecrypt = fopen(fileName, "r+b");
	if (ferror(fileToDecrypt)) {
		return;
		printf("Failed.\n");
	}
	printf("Success.\n");
	
	//preliminary remainder check initialization
	int remainder = 0; //zero value
	int keyCount = 0;
	
	//variables used to determine when to stop counting numbers
	fseek(fileToDecrypt, 0, SEEK_END);
	size_t keyPos = 0;
	size_t filePos = 0;
	size_t strPos = 0;
	size_t strEndPos = ftell(fileToDecrypt);
	rewind(fileToDecrypt);
	
	printf("Decoding %s...", fileName);
	//make sure the program exits before the number necomes negative
	while (strPos < strEndPos) {
		filePos = ftell(fileToDecrypt);
		rewind(fileToDecrypt);
		fseek(fileToDecrypt, filePos, SEEK_SET);
		keyCount = getc(fileToDecrypt);
		
		//take advantage of signed-char overflow to calculate current value
		remainder += keyCount - decryptKey[keyPos];
		filePos = ftell(fileToDecrypt) - 1;
		fseek(fileToDecrypt, filePos, SEEK_SET);
		putc(remainder, fileToDecrypt);
		
		//check if there is a remainder to be tabulated
		remainder = (remainder > 255) ? 1 : 0;
		++strPos;
		++keyPos;
		if (keyPos == decryptKey.size()) keyPos = 0;
		fflush(fileToDecrypt);
	}
	fclose(fileToDecrypt);
	printf("Done.\n");
}

} //end stringUtils namespace
} //end hamLibs namespace
