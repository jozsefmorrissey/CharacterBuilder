#ifndef THIRD_PARTY_H
#define THIRD_PARTY_H

#include <iostream>
#include <ctime>
#include <string>
#include <jsoncpp/json/json.h>

#include "User.h"

using namespace std;

class ThirdParty{

	private:
		int ID;
		time_t lastUpdate;
		string userEmail;
		string userAcctName;
		string updateUrl;
		string updateCmd;
		string Info;

		int setLastUpdate();

	public:
		ThirdParty(string link);
		ThirdParty(Json::Value j);
		ThirdParty(User u, string acctName, string password, string url, string cmd);
		ThirdParty(User u, string password, string url, string cmd); // uses user email as acct name.

		int setUpdateUrl(string url);
		int setUpdateCmd(string cmd);
};


class ThirdPartyC: private ThirdParty{

	private:
		int ID;
		bool pub;
		time_t lastUpdate;
		string userEmail;
		string userAcctName;
		string updateUrl;
		string updateCmd;
		string Info;

		int setLastUpdate();

	public:
		ThirdPartyC(string link);
		ThirdPartyC(Json::Value j);
		ThirdPartyC(User u, int Id);
		ThirdPartyC(User u, string acctName, string password, string url, string cmd);
		ThirdPartyC(User u, string password, string url, string cmd); // uses user email as acct name.

		int update();
		int getId();
		bool isPublic();
		string getUserEmail();
		string getInfo();
		time_t getLastUpdate();
};







#endif //THIRD_PARTY_H
