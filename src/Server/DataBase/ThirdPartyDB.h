#include "DataBase.h"
#include "../../DataObjects/ThirdParty.h"

class ThirdPartyDB:private DataBase{
	private:
		ThirdParty thirdParty;

		Json convertToJson(ThirdParty tp);

	public:
		ThirdPartyDB();
		ThirdPartyDB(User u, ThirdParty tp);

		bool update();
		Json getWithId(int id);
		Json getAll();
};
