#include "core/headers.hpp"

#define PERSONCOUNT 10000

#define random(x) (rand() % x)

// typedef long long ll;

class GenDataset{
private:
	std::string output;
	int persons;
public:
	GenDataset(std::string _output, int persons);
	~GenDataset();
	void run();
private:
	void runFriendlist();
	void runMicroblog();
	void runEvent();
	void runMention();
	void runRetweet();
	function<string (int)> int2String = [](int num) {
		string s = "";
		if(num < 10) {
			s = "0";
			s += char((int)'0' + num);
		} else {
			s += char((int)'0' + num / 10); 
			s += char((int)'0' + num % 10); 
		}
		return s;
	};
	// std::tuple<int, int> randomInfo(int id);
	// int randomCityID();
	// int randomAge();
	// int randomIncome(); 
};

GenDataset::GenDataset(std::string _output, int _persons){
	this->output = _output;
	this->persons = _persons;
}

GenDataset::~GenDataset(){

}

void GenDataset::runFriendlist() {
	int id, friendid;
	srand(1);//Don't modify
	FILE * fp;
	if ((fp = fopen((output + "_friendlist").c_str(), "w")) == NULL) {
		fprintf(stderr, "Can't open this file!\n");
		exit(-1);
	}
	for (int i = 0; i < persons; i++) {
		int friendidMax = int(pow(4, random(persons + 1) - persons) * (persons) / 1.2);
		set<int>idSet;
		for(int j = 0; j < max(1, friendidMax); j++) {
			id = i;
			char idStr[] = "user0000000";
			char friendStr[] = "user0000000";
			// cout<<dateStr<<endl;

			do{
				friendid = random(persons);
			} while (idSet.find(friendid) != idSet.end() && friendid != id);
			idSet.insert(friendid);
			// cout << id << " " << friendid << endl;
			for(int k = 10; k >= 4; k --) {
				idStr[k] = '0' + (id % 100);
				id /= 10;
				friendStr[k] = '0' + (friendid % 10);
				friendid /= 10;
			}
			// printf("%s", dateStr.c_str());
			fprintf(fp, "%s %s\n", idStr, friendStr);
		}
		// fprintf(fp, "%d %d %d\n", id, age, income);
	}
	fclose(fp);
}

void GenDataset::runMicroblog() {
	int mid, uid;
	srand(1);//Don't modify
	FILE * fp;
	if ((fp = fopen((output+"_micorblog").c_str(), "w")) == NULL) {
		fprintf(stderr, "Can't open this file!\n");
		exit(-1);
	}
	for (int i = 0; i < persons * 10; i++) {
		mid = i;
		uid = random(persons);
		char midStr[] = "w0000000000";
		char uidStr[] = "user0000000";
		string dateStr = "2012-11-22T33:44:55Z";
		dateStr.replace(5, 2, int2String(random(12)));
		dateStr.replace(8, 2, int2String(random(28) + 1));
		dateStr.replace(11, 2, int2String(random(24)));
		dateStr.replace(14, 2, int2String(random(60)));
		dateStr.replace(17, 2, int2String(random(60)));
		char dateBuffer;
		// cout << id << " " << friendid << endl;
		for(int k = 10; k >= 4; k --) {
			midStr[k] = '0' + (mid % 10);
			mid /= 10;
			uidStr[k] = '0' + (uid % 10);
			uid /= 10;
		}

		fprintf(fp, "%s %s %s\n", midStr, uidStr, dateStr.c_str());
		// fprintf(fp, "%d %d %d\n", id, age, income);
	}
	fclose(fp);	
}

void GenDataset::runEvent() {

}

void GenDataset::runMention() {

}

void GenDataset::runRetweet() {

}


void GenDataset::run(){
	this->runFriendlist();
	this->runMicroblog();
	this->runEvent();
	this->runMention();
	this->runRetweet();

}

// std::tuple<int, int> GenDataset::randomInfo(){
	
// 	int uid = this->randomCityID();
// 	int friendid = this->randomAge();
// 	return make_tuple(uid, friendid);
// }

// int GenDataset::randomCityID(){
// 	int cityID = 1000;
// 	float cityRatio = (float)rand() / (float)RAND_MAX;
// 	if (0 <= cityRatio && cityRatio < 0.1) cityID = 1000;
// 	else if (0.1 <= cityRatio && cityRatio < 0.15) cityID = 1001;
// 	else if (0.15<= cityRatio && cityRatio < 0.2) cityID = 1002;
// 	else if (0.2<= cityRatio && cityRatio < 0.3) cityID = 1003 + random(5);
// 	else cityID = 1008 + random(92);

// 	return cityID;
// }

// int GenDataset::randomAge(){
// 	return random(43) + 18;
// }

// int GenDataset::randomIncome(){
// 	int income = 0;
// 	float incomeRatio = (float)rand() / (float)RAND_MAX;
// 	if (0 <= incomeRatio && incomeRatio < 0.69) income = 10000 + random(90000);
// 	else if (0.69 <= incomeRatio && incomeRatio < 0.99) income = 100000 + random(900000);
// 	else income = 1000000 + random(9000000);
// 	return income;
// }

int main(int argc, char ** argv) {
	int opt = 0;
	std::string output = "";
	int persons = PERSONCOUNT;
	bool help = false;
	while( (opt = getopt(argc, argv, "o:n:hH")) != -1 ) {
		switch (opt) {
			case 'o':
				output = optarg;
			break;
			case 'n':
				persons = atol(optarg);
			break;
			case 'h':
			case 'H':
				help = true;
			break;
		}
	}

	if (help || output == "") {
		fprintf(stderr, "gen -o [output file path] -n [Optional: number of persons(default=100000000)]\n");
		exit(-1);
	}

	GenDataset gen(output, persons);
	double start_time = get_time();
	gen.run();
	double end_time = get_time();
	printf("It generates %d items and takes %.2fs\n", persons, end_time - start_time);
	return 0;
}
