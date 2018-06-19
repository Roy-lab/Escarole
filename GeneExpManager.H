#ifndef _GENEEXPMGR_
#define _GENEEXPMGR_

#include <map>
#include <string>
#include <vector>

using namespace std;

class GeneExpManager
{
	public:
	GeneExpManager();
	~GeneExpManager();
	int readExpression(const char* aFName);
	vector<double>* getExp(const string&);
	vector<string>& getColNames();	// Gets column names 
	map<string,vector<double>*>& getGeneSet();
	

	private:
	// Either reads the colNames from the current buffer and returns true, or 
	// generates an automatic set of colNames and returns false.
	bool readOrMakeHeader(char* buffer);

	map<string,vector<double>*> exprSet;
	vector<string> colNames; // DC added to store column names
};
#endif
