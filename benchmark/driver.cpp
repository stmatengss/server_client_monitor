// #include "core/graphDB.hpp"
#include "core/graphDB_baseline.hpp"
#include "core/hashCheck.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

const int readLineBufferSize = 100;

int main(int argc, char ** argv){
	string input = "";
	double timeSum = 0;
	int answerSum = 0;

	int opt = 0;
	while ((opt = getopt(argc, argv, "i:")) != -1) {
		switch(opt) {
			case 'i':
				input = optarg;
			break;
			
		}
	}

	if (input == "") {
		fprintf(stderr, "driver -i [input file path]\n");
		exit(-1);
	}
	GraphDB graphDB;

	ifstream casesFile(input);

	if (!casesFile) {
		fprintf(stderr, "test file error\n");
		exit(-1);
	}

	// 
	int queryType;
	int queryNum;
	int timeRange;
	int topN;
	int hashKey;
	char readLineBuffer[256];
	char userIdBuffer[64];
	char beginTimeBuffer[64];
	char endTimeBuffer[64];
	double runStartTime;
	double runEndTime;
	string userId;
	string beginTime;
	string endTime;

	while (!casesFile.eof()) {
		casesFile.getline(readLineBuffer, 10);
		sscanf(readLineBuffer, "%d %d", &queryType, &queryNum);
		vector<vector<string> > result;

		if (queryType <= 2) {
			vector<tuple<string, int> > dataIn; 
			for (int i = 0; i < queryNum; i ++) {
				casesFile.getline(readLineBuffer, readLineBufferSize);
				sscanf(readLineBuffer, "%s %d", userIdBuffer, &topN);
				userId = userIdBuffer;
				dataIn.push_back(make_tuple(userId, topN));
			}
			if (queryType == 1) {
				runStartTime = get_time();
				result = graphDB.queryOne(dataIn);
				runEndTime = get_time();
				printf("Query One time is %.2lf\n", runEndTime - runStartTime);
			}
			if (queryType == 2) {
				runStartTime = get_time();
				result = graphDB.queryTwo(dataIn);
				runEndTime = get_time();
				printf("Query Two time is %.2lf\n", runEndTime - runStartTime);
			}
		} else {
			vector<tuple<string, string, string, int> > dataIn; 
			for (int i = 0; i < queryNum; i ++) {
				casesFile.getline(readLineBuffer, readLineBufferSize);
				sscanf(readLineBuffer, "%s %s %s %d", userIdBuffer, beginTimeBuffer, endTimeBuffer, &topN);
				userId = userIdBuffer;
				beginTime = beginTimeBuffer;
				endTime = endTimeBuffer;
				dataIn.push_back(make_tuple(userId, beginTime, endTime, topN));
			}

			if (queryType == 3) {
				runStartTime = get_time();
				result = graphDB.queryThree(dataIn);
				runEndTime = get_time();
				printf("Query Three time is %.2lf\n", runEndTime - runStartTime);
			}
			if (queryType == 4) {
				runStartTime = get_time();
				result = graphDB.queryFour(dataIn);
				runEndTime = get_time();
				printf("Query Four time is %.2lf\n", runEndTime - runStartTime);
			}		
			if (queryType == 5) {
				runStartTime = get_time();
				result = graphDB.queryFive(dataIn);
				runEndTime = get_time();
				printf("Query Five time is %.2lf\n", runEndTime - runStartTime);
			}		
		}
		timeSum += (runEndTime - runStartTime);
	}
	return 0;
}
				// runStartTime = get_time();
				// sscanf(readLineBuffer, "%s %s %s %d %d", userIdBuffer, beginTimeBuffer, endTimeBuffer, &topN, &hashKey);
				// userId = userIdBuffer;
				// beginTime = beginTimeBuffer;
				// endTime = endTimeBuffer;
				// vector<string> queryFourRes = graphDB.queryFourSingle(userId, beginTime, endTime, topN);
				// timeSum += (get_time() - runStartTime);
				// if (checkSum(queryFourRes, hashKey)) answerSum++;
				// printf("Query Four time is %.2lf\n", get_time() - runStartTime);
				// break;
