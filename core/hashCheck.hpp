#include <string>

using namespace std;

/* hashing the string vector, compare to the key*/

/* BKDR Hash range(0, Int_max) */
int BKDRHash (string str) {
	int seed = 131;
	int hash = 0;
	for (auto i:str) {
		hash = hash * seed + int(i);
	}

	return (hash & 0x7FFFFFFF);
}

/* Acclerate the string vector, gain the sum, then compare to the key. */

bool checkSum (vector<string>& vec, unsigned int key) {
	long long hashSum = 0;
	int hashKey = 0;
	
	for (auto i:vec) {
		hashSum += BKDRHash(i);
	}

	hashKey = int(hashSum & 0x7FFFFFFF);

	if (hashKey < 0) 
		return false;

	if (hashKey == key)
		return true;
	return false;
} 

/* Check all querys */
/* Return the number of true answers */

unsigned int checkSumAll (vector<vector<string> >& mat, vector<unsigned int> keys) {
	unsigned int resultNum;
	for (int i = 0; i < keys.size(); i++) {
		if (checkSum(mat[i], keys[i])) {
			resultNum ++;
		}
	}
	return resultNum;
}