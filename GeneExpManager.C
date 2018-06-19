
/*
Arboretum: An algorithm to cluster functional genomesomics data from multiple species
    Copyright (C) 2013 Sushmita Roy sushroy@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "GeneExpManager.H"


GeneExpManager::GeneExpManager()
{

}

GeneExpManager::~GeneExpManager()
{

}

/*
 * Reads expression from tab-delimited text. 
 * Able to handle files with or without column headers. If no column headers,
 * then will print out with "Col$n" as the header name for each column n.
 */
int 
GeneExpManager::readExpression(const char* aFName)
{
	ifstream inFile(aFName);
	char* buffer=NULL;
	int bufflen=0;
	string buffstr;
	int linecnt=0;
	
	while(inFile.good())
	{
		getline(inFile,buffstr);
		if(buffstr.length()<=0)
		{
			continue;
		}
	
		if(bufflen <=buffstr.length())
		{
			bufflen=buffstr.length()+1;
			if(buffer!=NULL)
			{
				delete[] buffer;
			}
			buffer=new char[bufflen];
		}
		strcpy(buffer,buffstr.c_str());
		
		// try to read a header line
		if (linecnt==0)
		{
			char* headbuff=new char[bufflen];
			strcpy(headbuff, buffstr.c_str());

			bool foundHeader=readOrMakeHeader(headbuff);
			if (foundHeader)
			{
				cout << "Found header row: " << headbuff << endl;
				linecnt++;
				continue; // Move to next line
			}
			else
			{
				cout << "Auto-generated header row" << endl;
			}
		}

		int tokCnt=0;
		char* tok=strtok(buffer,"\t");
		string geneName;
		vector<double>* expr=NULL;


		// process the line as a string followed by double data columns
		while(tok!=NULL)
		{
			if(tokCnt==0)
			{
				geneName.append(tok);
				expr=new vector<double>;
				exprSet[geneName]=expr;
			}
			else
			{
				expr->push_back(atof(tok));
			}
			tokCnt++;
			tok=strtok(NULL,"\t");
		}
		linecnt++;
	}	
	inFile.close();
	return 0;
}

/*
 * Tries to read a header row from the buffer. 
 * If the first token is one of a set of keywords, then we interpret the row
 * as a header, save it to colNames (data member), and return true.
 * Otherwise, we generate artificial column names, save them to colNames,
 * and return false.
 * Header keywords (case ignored): Gene, Region, Pair, Sample
 */
bool
GeneExpManager::readOrMakeHeader(char* buffer)
{
	int tokCnt=0;
	char* tok=strtok(buffer,"\t");
	string first;

	bool foundHeader=false;

	// save some keywords to compare to our first item
	vector<string> keywords;
	keywords.push_back("GENE");
	keywords.push_back("PAIR");
	keywords.push_back("REGION");
	keywords.push_back("SAMPLE");

	while(tok!=NULL)
	{
		if(tokCnt==0)
		{
			first.append(tok);
			// convert to all caps
			for (int i=0; i<first.size(); i++)
			{
				first.at(i)=toupper(first.at(i));
			}	

			// now compare to each string and stop if we match
			for (int i=0; i<keywords.size();i++)
			{
				if (first.compare(keywords[i])==0)
				{
					foundHeader=true;		
				}	
			}
		}
		else	// for all other columns, either read the column name or save a placeholder
		{
			string cname;
			if (foundHeader)
			{
				cname.append(tok);
			}
			else
			{			
				ostringstream result; //="Col";
				result << "Col" << tokCnt;
				cname=result.str();
			}
			cout << "Saving column name " << cname << endl;	// DEBUG
			colNames.push_back(cname);
		}
		tokCnt++;
		tok=strtok(NULL,"\t");
	}	
	return foundHeader;
}

/*
 * Access column names vector
 *
 */
vector<string>& 
GeneExpManager::getColNames()
{
	return colNames; 
}

vector<double>* 
GeneExpManager::getExp(const string& geneKey)
{
	if(exprSet.find(geneKey)==exprSet.end())
	{
		return NULL;
	}
	vector<double>* expr=exprSet[geneKey];
	return expr;
}

map<string,vector<double>*>&
GeneExpManager::getGeneSet()
{
	return exprSet;
}

