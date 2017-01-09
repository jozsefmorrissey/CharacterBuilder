#include "DataBase.h"
#include "../../DataObjects/User.h"

class InteractionDB:private DataBase{
	private:
		Interaction interaction;
		Json convertToJson();


	public:
		InteractionDB();
		InteractionDB(Interaction i, UserDB uDB); 

		bool update();
		Json getWithId(int id);
		Json getAll();
};
