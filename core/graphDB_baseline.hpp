#ifndef MSTORE_H
#define MSTORE_H

#include "core/headers.hpp"

void debug(int tag) {
	cout << "-------" << tag << "-------" <<endl;
}

void debug(string tag) {
	cout << "-------" << tag << "-------" <<endl;
}

template<typename T>
void debugPrintVec(const vector<T> vec) {
	cout << "---------------" <<endl;
	for (auto i: vec) {
		cout << i << " ";
	}
	cout << endl;
}

template<typename T>
void debugPrintVecPair(const vector<pair<T, T> > vec) {
	cout << "---------------" <<endl;
	for (auto i: vec) {
		cout << i.first << " " << i.second <<endl;
	}
	// cout << endl;
}

template<typename T>
void debugPrintMat(const vector<vector<T> >& mat) {
	cout << "---------------" <<endl;
	int counter = 0;
	for (auto i: mat) {
		cout << counter++ << " :";
		for (auto j: i) {
			cout << j << " ";
		}
		cout << endl;
	}
}

class GraphDB{

	// data define {uid, mid, tag, time}
	typedef long long ll;
	typedef unsigned int uint;
	typedef uint uid;
	typedef uint mid;
	typedef uint tag;
	typedef uint time;
	typedef string uidstring;
	typedef string midstring;
	typedef string tagstring;
	typedef string timestring;

public:
	GraphDB();
	~GraphDB();
	/*public interface, don't modify!!*/
	/* will delete next time */
	int readEvent();
	int readFriendlist();
	int readMention();
	int readMicroblog();
	int readRetweet();
	int spliteTriple(string s, string& res1, string& res2, string& res3) const;
	int spliteTuple(string s, string& res1, string& res2) const;
	time string2Time(string s) const;
	vector<string> queryFiveSingle(string user, string beginTimeStr, string endTimeStr, int n);
	vector<string> queryFourSingle(string user, string beginTimeStr, string endTimeStr, int n);
	vector<string> queryOneSingle(string user, int n);
	vector<string> queryThreeSingle(string user, string beginTimeStr, string endTimeStr, int n);
	vector<string> queryTwoSingle(string user, int n);
	vector<uint> findFirstNMaxElement(map<uint, uint> counter, int n) const;

	/*Public interface
		@Return: Hash value list
	*/
	vector<vector<string> > queryOne(vector<tuple<string, int> > querys);
	vector<vector<string> > queryTwo(vector<tuple<string, int> > querys);
	vector<vector<string> > queryThree(vector<tuple<string, string, string, int> > querys);
	vector<vector<string> > queryFour(vector<tuple<string, string, string, int> > querys);
	vector<vector<string> > queryFive(vector<tuple<string, string, string, int> > querys);

private:
	/*Your private variables*/
	// counter var
	uid counterUid;
	mid counterMid;
	tag counterTag;
	// const data define
	const time_t baseSeconds = 60904886400;
	const string friendlistFileName = "data/friendlist.txt";
	const string microblogFileName = "data/microblog.txt";
	const string eventFileName = "data/event.txt";
	const string mentionFileName = "data/mention.txt";
	const string retweetFileName = "data/retweet.txt";
	//define mapper uidstring -> uid, midStr
	map<uidstring, uid> uidstring2UidMap;
	map<midstring, mid> midstring2MidMap;
	map<tagstring, tag> tagstring2TagMap;
	vector<uidstring> uid2UidstringMap;
	vector<midstring> mid2MidstringMap;
	vector<tagstring> tag2TagstringMap;
	//define uid -> uid,mid
	vector<vector<uid> > uid2FriendidAdjList;
	// vector<vector<uid> > friendid2UidAdjList;
	vector<vector<mid> > uid2MidAdjList;
	//define mid -> time,tag,uid,mid
	vector<pair<uid, time> > mid2UidAndTimeList;
	vector<vector<uid> > mid2MentionUidAdjList;
	vector<vector<mid> > mentionUid2MidAdjList;
	vector<vector<tag> > mid2TagAdjList;
	vector<mid> mid2RemidList;

private:
	/*Your private functions*/
	int initial();
	// int spliteTuple(string s, string& res1, string& res2) const;
	// int spliteTriple(string s, string& res1, string& res2, string& res3) const;	
	// vector<string> queryOneSingle(string user, int n);
	// vector<string> queryTwoSingle(string user, int n);
	// vector<string> queryThreeSingle(string user, string beginTime, string endTime, int n);
	// vector<string> queryFourSingle(string user, string beginTime, string endTime, int n);
	// vector<string> queryFiveSingle(string user, string beginTime, string endTime, int n);
};


/*Interface implementation*/
GraphDB::GraphDB(){	
	// mid tempMid, counterMid = 1;
	// time tempTime;
	// tag tempTag, counterTag = 1;
	// pair<string, string> spliteTupleRes;
	// pair<string, pair<string, string> > spliteTripleRes;
	initial();
	readFriendlist();
	readMicroblog();
	// readEvent();
	// readMention();
	// readRetweet();
	thread firstThread([this] {this->readEvent();});
	thread secondThread([this] {this->readMention();});
	thread thirdThread([this] {this->readRetweet();});

	firstThread.join();
	secondThread.join();
	thirdThread.join();
	//TODO multiprocess	
}

GraphDB::time GraphDB::string2Time(string s) const {
	/*
		TODO: time string -> int 
	*/
	tm* test = new tm();
	test->tm_sec = atoi(s.substr(17, 2).c_str());
	test->tm_min = atoi(s.substr(14, 2).c_str());
	test->tm_hour = atoi(s.substr(11, 2).c_str());
	test->tm_mday = atoi(s.substr(8, 2).c_str());
	test->tm_mon = atoi(s.substr(5, 2).c_str()) - 1;
	test->tm_year = atoi(s.substr(0, 4).c_str());
	time_t resSeconds = mktime(test);
	return uint(resSeconds - baseSeconds);

}

int GraphDB::readFriendlist() {
	ifstream friendlistFile(friendlistFileName);
	string tempBuffer, tempStr1, tempStr2;
	uid tempUid1, tempUid2;
	double start_time = get_time();

	while (getline(friendlistFile, tempBuffer)) {
		spliteTuple(tempBuffer, tempStr1, tempStr2);
		if (uidstring2UidMap[tempStr1] == 0) {
			// cout<<tempStr1<<endl;
			uid2FriendidAdjList.push_back(vector<uid>());
			uidstring2UidMap[tempStr1] = counterUid;
			uid2UidstringMap.push_back(tempStr1);
			tempUid1 = counterUid;
			counterUid ++;
		} else {
			tempUid1 = uidstring2UidMap[tempStr1];
		}
		if (uidstring2UidMap[tempStr2] == 0) {
			// cout<<tempStr2<<endl;
			uid2FriendidAdjList.push_back(vector<uid>());
			uidstring2UidMap[tempStr2] = counterUid;
			uid2UidstringMap.push_back(tempStr2);
			tempUid2 = counterUid;
			counterUid ++;
		} else {
			tempUid2 = uidstring2UidMap[tempStr2];
		}
		uid2FriendidAdjList[tempUid1].push_back(tempUid2);
	}
	// debugPrintMat<uint>(uid2FriendidAdjList);
	double end_time = get_time();
	printf("It takes %.2fs\n", end_time - start_time);
	friendlistFile.close();
	cout << "reading friendlist finish." << endl;
	return 0;
}

int GraphDB::readMicroblog() {

	ifstream microblogFile(microblogFileName);
	string tempBuffer, tempStr1, tempStr2, tempStr3;
	mid tempMid;
	uid tempUid;
	time tempTime;
	double start_time = get_time();


	//init by using counter of users
	uid2MidAdjList = vector<vector<mid> >(counterUid);

	while (getline(microblogFile, tempBuffer)) {
		spliteTriple(tempBuffer, tempStr1, tempStr2, tempStr3);	

		midstring2MidMap[tempStr1] = counterMid;
		mid2MidstringMap.push_back(tempStr1);
		tempMid = counterMid;
		tempUid = uidstring2UidMap[tempStr2];
		tempTime = string2Time(tempStr3);
		mid2UidAndTimeList.push_back(make_pair(tempUid, tempTime));
		uid2MidAdjList[tempUid].push_back(tempMid);
		counterMid ++;
	}
	// debugPrintVecPair<uint>(mid2UidAndTimeList);
	// debugPrintMat<uint>(uid2MidAdjList);
	double end_time = get_time();
	printf("It takes %.2fs\n", end_time - start_time);
	microblogFile.close();
	cout << "reading microblog finish." << endl;
	return 0;
}

int GraphDB::readEvent() {
	string tempBuffer, tempStr1, tempStr2;
	ifstream eventFile(eventFileName);
	mid tempMid;
	tag tempTag;

	mid2TagAdjList = vector<vector<mid> >(counterMid);

	while (getline(eventFile, tempBuffer)) {
		spliteTuple(tempBuffer, tempStr1, tempStr2);
		tempMid = midstring2MidMap[tempStr1];
		if (tagstring2TagMap[tempStr2] == 0) {
			// cout<<tempStr1<<endl;
			tagstring2TagMap[tempStr2] = counterTag;
			tag2TagstringMap.push_back(tempStr2);
			tempTag = counterTag;
			counterTag ++;
		} else {
			tempTag = tagstring2TagMap[tempStr2];
		}
		mid2TagAdjList[tempMid].push_back(tempTag);
	}
	// debugPrintVec<string>(tag2TagstringMap);
	// debugPrintMat<uint>(mid2TagAdjList);
	eventFile.close();
	cout << "reading event finish." << endl;
	return 0;
}

int GraphDB::readMention() {
	string tempBuffer, tempStr1, tempStr2;
	ifstream mentionFile(mentionFileName);
	mid tempMid;
	uid tempUid;

	mid2MentionUidAdjList = vector<vector<uid> >(counterMid);
	mentionUid2MidAdjList = vector<vector<mid> >(counterUid);

	while (getline(mentionFile, tempBuffer)) {
		spliteTuple(tempBuffer, tempStr1, tempStr2);
		tempMid = midstring2MidMap[tempStr1];
		tempUid = uidstring2UidMap[tempStr2];
		mid2MentionUidAdjList[tempMid].push_back(tempUid);
		mentionUid2MidAdjList[tempUid].push_back(tempMid);
	}
	// debugPrintMat(mid2MentionUidAdjList);
	mentionFile.close();
	cout << "reading mention finish." << endl;
	return 0;
}

int GraphDB::readRetweet() {
	string tempBuffer, tempStr1, tempStr2;
	ifstream retweetFile(retweetFileName);
	mid tempMid, tempReMid;

	mid2RemidList = vector<mid>(counterMid);

	while (getline(retweetFile, tempBuffer)) {
		spliteTuple(tempBuffer, tempStr1, tempStr2);	
		tempMid = midstring2MidMap[tempStr1];
		tempReMid = midstring2MidMap[tempStr2];
		mid2RemidList[tempMid] = tempReMid;	
	}
	// debugPrintVec<uint>(mid2RemidList);
	retweetFile.close();
	cout << "reading retweet finish." << endl;
	return 0;
}

/* splite */
int GraphDB::spliteTuple(string s,  string& res1, string& res2) const {
	int pos1 = s.find_first_of(' ');
	res1 = s.substr(0, pos1);
	res2 = s.substr(pos1 + 1, s.length() - pos1 - 1);
	return 0;
	// return make_pair(s1, s2);
}
int GraphDB::spliteTriple(string s, string& res1, string& res2, string& res3) const {
	int pos1 = s.find_first_of(' ');
	int pos2 = s.find_last_of(' ');
	res1 = s.substr(0, pos1);
	res2 = s.substr(pos1 + 1, pos2 - pos1 - 1);
	res3 = s.substr(pos2 + 1, s.length() - pos2 - 1);
	return 0;
	// return make_pair(s1, make_pair(s2, s3) );
}

/* read files and tranfer data into container */
int GraphDB::initial() {
	/*------------------*/
	counterUid = 1; // the Uid need start from one
	uid2UidstringMap.push_back("");
	uid2FriendidAdjList.push_back(vector<uid>());
	/*------------------*/
	counterMid = 1;
	mid2MidstringMap.push_back("");
	mid2UidAndTimeList.push_back(make_pair(0U, 0U)); 
	/*------------------*/
	counterTag = 1;
	tag2TagstringMap.push_back("");
	/*------------------*/
	return 0;
}

vector<uint> GraphDB::findFirstNMaxElement(map<uint, uint> counter, int n) const {
	typedef pair<uint, uint> Pair;
	struct pairCompare {
		bool operator()(Pair x, Pair y) {
			return x.second > y.second;
		}
	};
	priority_queue<Pair, vector<Pair >, pairCompare> resPq;
	// resPq.push(make_pair(0U, 0U));
	for (auto keyAndCounter: counter) {

		if (resPq.size() < n) {
			resPq.push(keyAndCounter);
		} else {
			if (keyAndCounter.second > resPq.top().second) {
				resPq.pop();
				resPq.push(keyAndCounter);
			}
		}
	}

	vector<uint> result;
	while(!resPq.empty()) {
		result.push_back(resPq.top().first);
		resPq.pop();
	}
	return result;
}

/* Query 1 */
vector<vector<string> > GraphDB::queryOne(vector<tuple<string, int> > querys) {
	vector<vector<string> > result;
	for (auto query: querys) {
		string user;
		int n;
		tie(user, n) = query;
		result.push_back(queryOneSingle(user, n));
	}
	return result;
}
/* Query 2 */
vector<vector<string> > GraphDB::queryTwo(vector<tuple<string, int> > querys){
	vector<vector<string> > result;
	for (auto query: querys) {
		string user;
		int n;
		tie(user, n) = query;
		result.push_back(queryTwoSingle(user, n));
	}
	return result;
}
/* Query 3 */
vector<vector<string> > GraphDB::queryThree(vector<tuple<string, string, string, int> > querys){
	vector<vector<string> > result;
	for (auto query: querys) {
		string user;
		string beginTimeStr, endTimeStr;
		int n;
		tie(user, beginTimeStr, endTimeStr, n) = query;
		result.push_back(queryThreeSingle(user, beginTimeStr, endTimeStr, n));
	}
	return result;
}
/* Query 4 */	
vector<vector<string> > GraphDB::queryFour(vector<tuple<string, string, string, int> > querys){
	vector<vector<string> > result;
	for (auto query: querys) {
		string user;
		string beginTimeStr, endTimeStr;
		int n;
		tie(user, beginTimeStr, endTimeStr, n) = query;
		result.push_back(queryFourSingle(user, beginTimeStr, endTimeStr, n));
	}
	return result;
}
/* Query 5 */	
vector<vector<string> > GraphDB::queryFive(vector<tuple<string, string, string, int> > querys){
	vector<vector<string> > result;
	for (auto query: querys) {
		string user;
		string beginTimeStr, endTimeStr;
		int n;
		tie(user, beginTimeStr, endTimeStr, n) = query;
		result.push_back(queryFiveSingle(user, beginTimeStr, endTimeStr, n));
	}
	return result;
}

vector<string> GraphDB::queryOneSingle(string user, int n){
	typedef pair<uid, uint> Pair;
	vector<string> result;

	uid uidCenter;
	uidCenter = uidstring2UidMap[user];
	map<int, int> sameFriendSum;
	struct pairCompare {
		bool operator()(Pair x, Pair y) {
			return x.second > y.second;
		}
	};
	priority_queue<Pair, vector<Pair >, pairCompare> resPq;

	for (auto uidI: uid2FriendidAdjList[uidCenter]) {
		for (auto uidJ:uid2FriendidAdjList[uidI]) {
			if (find(uid2FriendidAdjList[uidJ].begin(), uid2FriendidAdjList[uidJ].end(), uidI) != uid2FriendidAdjList[uidJ].end() &&
				find(uid2FriendidAdjList[uidI].begin(), uid2FriendidAdjList[uidI].end(), uidCenter) != uid2FriendidAdjList[uidI].end() &&
				uidCenter != uidJ
				) {
				if (sameFriendSum[uidJ] == 0) {
					sameFriendSum[uidJ] = 1;
				} else {
					sameFriendSum[uidJ] ++;
				}
			}
		}
	}
	vector<Pair> resultPair(sameFriendSum.begin(), sameFriendSum.end());
	sort(resultPair.begin(), resultPair.end(), [](Pair x, Pair y){
		return x.second > y.second;
	});
	for (int i = 0; i < n && i < resultPair.size(); i ++) {
		result.push_back(uid2UidstringMap[resultPair[i].first]);
	}
	return result;
}

vector<string> GraphDB::queryTwoSingle(string user, int n){
	typedef pair<mid, time> Pair;
	vector<string> result;

	uid uidCenter;
	uidCenter = uidstring2UidMap[user];
	
	struct pairCompare {
		bool operator()(Pair x, Pair y) {
			return x.second < y.second;
		}
	};
	priority_queue<Pair, vector<Pair >, pairCompare> resPq;

	for (auto uidI: uid2FriendidAdjList[uidCenter]) {
		for (auto tempMid: uid2MidAdjList[uidI]) {
			time tempTime = mid2UidAndTimeList[tempMid].second;
			if (resPq.size() < n) {
				resPq.push(make_pair(tempMid, tempTime));
			} else {
				if (tempTime > resPq.top().second) {
					resPq.pop();
					resPq.push(make_pair(tempMid, tempTime));
				}
			}
		}
		for (auto uidJ: uid2FriendidAdjList[uidI]) {
			for (auto tempMid: uid2MidAdjList[uidJ]) {
				time tempTime = mid2UidAndTimeList[tempMid].second;
				if (resPq.size() < n) {
					resPq.push(make_pair(tempMid, tempTime));
				} else {
					if (tempTime > resPq.top().second) {
						resPq.pop();
						resPq.push(make_pair(tempMid, tempTime));
					}
				}
			}
		}
	}
	// debug(resPq.size());
	while (!resPq.empty()) {
		result.push_back(mid2MidstringMap[resPq.top().first]);
		resPq.pop();
	}

	// reverse(result.begin(), result.end());

	return result;
}

vector<string> GraphDB::queryThreeSingle(string user, string beginTimeStr, string endTimeStr, int n){
	vector<string> result;
	set<uid> mentionUidSet;
	map<uid, uint> transUserCounter;
	uid uidCenter = uidstring2UidMap[user];
	time beginTime = string2Time(beginTimeStr);
	time endTime = string2Time(endTimeStr);

	for (auto tempMid: uid2MidAdjList[uidCenter]) {
		for (auto tempMentionUid: mid2MentionUidAdjList[tempMid]) {
			mentionUidSet.insert(tempMentionUid);
		}
	}

	for (auto tempMentionUid: mentionUidSet) {
		for (auto tempMid: mentionUid2MidAdjList[tempMentionUid]) {
			time tempTime = mid2UidAndTimeList[tempMid].second;
			if (tempTime <= endTime && tempTime >= beginTime) {
				uid tempUid = mid2UidAndTimeList[tempMid].first;
				if (transUserCounter[tempUid] == 0) {
					transUserCounter[tempUid] = 1;
				} else {
					transUserCounter[tempUid] ++;
				}
			}
		}
	}

	auto tempResult = findFirstNMaxElement(transUserCounter, n);

	for (auto tempUid: tempResult) {
		result.push_back(uid2UidstringMap[tempUid]);
	}
	// reverse(result.begin(), result.end());

	return result;
}

vector<string> GraphDB::queryFourSingle(string user, string beginTimeStr, string endTimeStr, int n){
	vector<string> result;
	map<mid, uint> remidCounter;
	map<uid, uint> userMidCounter;
	uid uidCenter = uidstring2UidMap[user];
	time beginTime = string2Time(beginTimeStr);
	time endTime = string2Time(endTimeStr);

	for (auto uidFriend: uid2FriendidAdjList[uidCenter]) {
		for (auto tempMid: uid2MidAdjList[uidFriend]) {
			time tempTime = mid2UidAndTimeList[tempMid].second;
			mid tempRemid = mid2RemidList[tempMid];
			if (tempTime <= endTime && 
				tempTime >= beginTime && 
				tempRemid != 0) {
				if (remidCounter[tempRemid] == 0) {
					remidCounter[tempRemid] = 1;
				} else {
					remidCounter[tempRemid] ++;
				}
			}
		}
	}
	for (auto midAndCounterPair: remidCounter) {
		mid tempRemid = midAndCounterPair.first;
		uid tempReuid = mid2UidAndTimeList[tempRemid].first;
		if ( userMidCounter[tempReuid] = 0) {
			userMidCounter[tempReuid] = midAndCounterPair.second;
		} else {
			userMidCounter[tempReuid] += midAndCounterPair.second;
		}
	}

	// typedef pair<uid, uint> Pair;
	// struct pairCompare {
	// 	bool operator()(Pair x, Pair y) {
	// 		return x.second < y.second;
	// 	}
	// };
	// priority_queue<Pair, vector<Pair >, pairCompare> resPq;
	// resPq.push(make_pair(0U, 0U));

	// for (auto uidAndCounter: userMidCounter) {
	// 	if (resPq.size() < n) {
	// 		resPq.push(uidAndCounter);
	// 	} else {
	// 		if (uidAndCounter.second > resPq.top().second) {
	// 			resPq.pop();
	// 			resPq.push(uidAndCounter);
	// 		}
	// 	}
	// }

	// while(!resPq.empty()) {
	// 	result.push_back(uid2UidstringMap[resPq.top().first]);
	// 	resPq.pop();
	// }

	auto tempResult = findFirstNMaxElement(userMidCounter, n);
	for (auto tempUid: tempResult) {
		result.push_back(uid2UidstringMap[tempUid]);
	}
	// reverse(result.begin(), result.end());

	return result;
}

vector<string> GraphDB::queryFiveSingle(string user, string beginTimeStr, string endTimeStr, int n){
	vector<string> result;
	uid uidCenter;
	uidCenter = uidstring2UidMap[user];
	map<tag, uint> tagCounter;
	time beginTime = string2Time(beginTimeStr);
	time endTime = string2Time(endTimeStr);
	// debug(beginTime);
	// debug(endTime);

	for (auto uidI: uid2FriendidAdjList[uidCenter]) {
		for (auto tempMid: uid2MidAdjList[uidI]) {
			time tempTime = mid2UidAndTimeList[tempMid].second;
			if (tempTime <= endTime && tempTime >= beginTime) {
				for (auto tempTag: mid2TagAdjList[tempMid]) {
					if (tagCounter[tempTag] == 0) {
						tagCounter[tempTag] = 1;
					} else {
						tagCounter[tempTag] ++;
					}
				}
			}
		}
		for (auto uidJ:uid2FriendidAdjList[uidI]) {
			for (auto tempMid: uid2MidAdjList[uidI]) {
				time tempTime = mid2UidAndTimeList[tempMid].second;
				if (tempTime <= endTime && tempTime >= beginTime) {
					for (auto tempTag: mid2TagAdjList[tempMid]) {
						if (tagCounter[tempTag] == 0) {
							tagCounter[tempTag] = 1;
						} else {
							tagCounter[tempTag] ++;
						}
					}
				}
			}
		}
	}

	// typedef pair<tag, uint> Pair;
	// struct pairCompare {
	// 	bool operator()(Pair x, Pair y) {
	// 		return x.second < y.second;
	// 	}
	// };
	// priority_queue<Pair, vector<Pair >, pairCompare> resPq;
	// resPq.push(make_pair(0U, 0U));

	// for (auto tagAndCounter: tagCounter) {
	// 	if (resPq.size() < n) {
	// 		resPq.push(tagAndCounter);
	// 	} else {
	// 		if (tagAndCounter.second > resPq.top().second) {
	// 			resPq.pop();
	// 			resPq.push(tagAndCounter);
	// 		}
	// 	}
	// }

	// while(!resPq.empty()) {
	// 	result.push_back(tag2TagstringMap[resPq.top().first]);
	// 	resPq.pop();
	// }

	auto tempResult = findFirstNMaxElement(tagCounter, n);
	for (auto tempTag: tempResult) {
		result.push_back(tag2TagstringMap[tempTag]);
	}
	// reverse(result.begin(), result.end());

	return result;
}

/*Private function*/
GraphDB::~GraphDB(){
}

#endif

