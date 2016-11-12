#include "core/headers.hpp"

#define PERSONCOUNT 100000000

#define random(x) (rand() % x)

typedef long long ll;

class GenDataset{
private:
	std::string output;
	ll persons;
public:
	GenDataset(std::string _output, ll persons);
	~GenDataset();
	void run();
private:
	std::tuple<int, int, int> randomInfo();
	int randomCityID();
	int randomAge();
	int randomIncome(); 
};

GenDataset::GenDataset(std::string _output, ll _persons){
	this->output = _output;
	this->persons = _persons;
}

GenDataset::~GenDataset(){

}

void GenDataset::run(){
	int cityID, age, income;
	srand(1);//Don't modify
	FILE * fp;
	if ((fp = fopen(this->output.c_str(), "w")) == NULL) {
		fprintf(stderr, "Can't open this file!\n");
		exit(-1);
	}
	for (ll i = 0; i < this->persons; i++) {
		std::tie(cityID, age, income) = randomInfo();
		fprintf(fp, "%d %d %d\n", cityID, age, income);
	}
	fclose(fp);
}

std::tuple<int, int, int> GenDataset::randomInfo(){
	int cityID = this->randomCityID();
	int age = this->randomAge();
	int income = this->randomIncome();
	return make_tuple(cityID, age, income);
}

int GenDataset::randomCityID(){
	int cityID = 1000;
	float cityRatio = (float)rand() / (float)RAND_MAX;
	if (0 <= cityRatio && cityRatio < 0.1) cityID = 1000;
	else if (0.1 <= cityRatio && cityRatio < 0.15) cityID = 1001;
	else if (0.15<= cityRatio && cityRatio < 0.2) cityID = 1002;
	else if (0.2<= cityRatio && cityRatio < 0.3) cityID = 1003 + random(5);
	else cityID = 1008 + random(92);

	return cityID;
}

int GenDataset::randomAge(){
	return random(43) + 18;
}

int GenDataset::randomIncome(){
	int income = 0;
	float incomeRatio = (float)rand() / (float)RAND_MAX;
	if (0 <= incomeRatio && incomeRatio < 0.69) income = 10000 + random(90000);
	else if (0.69 <= incomeRatio && incomeRatio < 0.99) income = 100000 + random(900000);
	else income = 1000000 + random(9000000);
	return income;
}

int main(int argc, char ** argv) {
	int opt = 0;
	std::string output = "";
	ll persons = PERSONCOUNT;
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
	printf("It generates %lld items and takes %.2fs\n", persons, end_time - start_time);
	return 0;
}
