#include "DataBase.h"
#include "../../DataObjects/Interaction.h"
#include "../../DataObjects/User.h"

class UserDB:private DataBase{
	private:
		User user;

		Json convertToJson();

	public:
		UserDB();
		UserDB(User u);
		bool update();
		Json getWithEmail(string Email);
		Json getAll();
};
