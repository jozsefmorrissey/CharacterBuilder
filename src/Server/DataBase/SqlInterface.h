#include <string>
#include <vector>
#include <jsoncpp/json/json.h>

using namespace std;

class SqlInterface{

	public:
		class TableElement{
			public:
				string field;
				string type;
				string null;
				string key;
				string defaultVal;
			
				TableElement(){this->field = this->type = this->null = this->key = this->defaultVal = "";}
				TableElement(string f, string t){this->field = f; this->type = t; this->null = this->key = this->defaultVal = "";}
				TableElement(string f, string t, bool n, bool prime, string dVal){
					this->field = f; 
					this->type = t; 
					this->defaultVal = dVal;
					if(n == false)
						this->null = "NO";
					else
						this->null = "";
					if(prime = true)
						this->key = "PRI";
					else
						this->key = "";
				}
		};

		
		int createDataBase(string dataBaseName);
		int createTable(string dataBaseName, string tableName, vector<TableElement> elements);
		int editData(string dataBaseName, string tableName, string ifStatment, string elementNames, string values);
		int insert(string dataBaseName, string tableName, string elemNames, string elemValues);

		bool tableExists(string dataBaseName, string tableName);
		bool elementExists(string dataBaseName, string tableName, string elementName);

		vector<SqlInterface::TableElement> getElements(string dataBaseName);
		SqlInterface::TableElement jsonToTableElement(Json::Value j);
		Json::Value tableElementToJson(TableElement elem);
		Json::Value getData(string dataBaseName, string tableName, string elements, string ifStatment);

		string sqlString(vector<string> words);
		string sqlString(string words[]);

};
