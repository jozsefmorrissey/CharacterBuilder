#include <string>
#include <vector>
#include <jsoncpp/json/json.h>

#include "SqlInterface.h"

class DataBase : public SqlInterface{
	#define db1 "UserDB"
	#define db2 "InteractionDB"
	#define db3 "ThirdPartyDB"

	private:
		string dataBaseName;
		string allTableNames[3];
		string tableName;
		string elements;
	
	protected:
		int createDataBase();
		int createTable();
		int insert(string elemNames, string elemValues);		

		Json::Value getData(string elements, string ifStatment);
	
		bool tableExits();
		bool elementExists();		

		vector<SqlInterface::TableElement> getElements();


	public:
		DataBase(string tN, string elems){
			this->dataBaseName = "CharacterDB";
			this->allTableNames[0] = db1; 
			this->allTableNames[1] =  db2; 
			this->allTableNames[2] =  db3; 
			this->tableName = tN;
			this->elements = elems;
			createDataBase();
			createTable();
		}

		Json::Value getAllData();
		Json::Value getAllTableData();
		virtual void updateData();
		bool compare(string pElem, string nElem);
	
};
