#pragma once
int main();
int normal();
int oem();
namespace normalKeyGenUtil {
	BOOL checkPattern(int patternType, int pattern);
	char ValidateCDKey(char* szKey);
}