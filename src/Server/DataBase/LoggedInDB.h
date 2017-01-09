#include "DataBase.h"
#include "../../DataObjects/User.h"

class LoggedInDB:private DataBase{
	private:
		int commPort;
		string email;
		string password;

		bool update(User u);		
		Json convertToJson();


	public:
		LoggedInDB();
		LoggedInDB(User u, int port);
		Json getAll();
};




