#ifndef MSTORE_H
#define MSTORE_H

#include "core/headers.hpp"

class GraphDB{

public:
	GraphDB();
	~GraphDB();
	
	/*public interface, don't modify!!*/
	/* will delete next time */
	vector<string> queryOneSingle(string user, int n);
	vector<string> queryTwoSingle(string user, int n);
	vector<string> queryThreeSingle(string user, string beginTime, string endTime, int n);
	vector<string> queryFourSingle(string user, string beginTime, string endTime, int n);
	vector<string> queryFiveSingle(string user, string beginTime, string endTime, int n);

	/*Public interface
		@Return: Hash value list
	*/
	vector<string> queryOne(vector<tuple<string, int> > users);

	vector<string> queryTwo(vector<tuple<string, int> > users);

	vector<string> queryThree(vector<tuple<string, string, string, int> > users);

	vector<string> queryFour(vector<tuple<string, string, string, int> > users);

	vector<string> queryFive(vector<tuple<string, string, string, int> > users);

private:
	/*Your private variables*/

private:
	/*Your private functions*/
	// vector<string> queryOneSingle(string user, int n);
	// vector<string> queryTwoSingle(string user, int n);
	// vector<string> queryThreeSingle(string user, string beginTime, string endTime, int n);
	// vector<string> queryFourSingle(string user, string beginTime, string endTime, int n);
	// vector<string> queryFiveSingle(string user, string beginTime, string endTime, int n);
};

/*Interface implementation*/
inline GraphDB::GraphDB(){

}

/* Query 1 */
inline vector<string> GraphDB::queryOne(vector<tuple<string, int> > users) {
	vector<string> result;
	return result;
}
/* Query 2 */
inline vector<string> GraphDB::queryTwo(vector<tuple<string, int> > users){
	vector<string> result;
	return result;
}
/* Query 3 */
inline vector<string> GraphDB::queryThree(vector<tuple<string, string, string, int> > users){
	vector<string> result;
	return result;
}
/* Query 4 */	
inline vector<string> GraphDB::queryFour(vector<tuple<string, string, string, int> > users){
	vector<string> result;
	return result;
}
/* Query 5 */	
inline vector<string> GraphDB::queryFive(vector<tuple<string, string, string, int> > users){
	vector<string> result;
	return result;
}

inline vector<string> GraphDB::queryOneSingle(string user, int n){
	vector<string> result;
	return result;
}

inline vector<string> GraphDB::queryTwoSingle(string user, int n){
	vector<string> result;
	return result;
}

inline vector<string> GraphDB::queryThreeSingle(string user, string beginTime, string endTime, int n){
	vector<string> result;
	return result;
}

inline vector<string> GraphDB::queryFourSingle(string user, string beginTime, string endTime, int n){
	vector<string> result;
	return result;
}

inline vector<string> GraphDB::queryFiveSingle(string user, string beginTime, string endTime, int n){
	vector<string> result;
	return result;
}

/*Private function*/
inline GraphDB::~GraphDB(){
}

#endif
