#ifndef USER_H
#define USER_H

#include <iostream>
#include <ctime>
#include "stdlib.h"
#include <string>
#include <vector>
#include <jsoncpp/json/json.h>

#include "../Server/DataBase/SqlInterface.h"

using namespace std;

/** 		db variables are the values currently contained in the database. m variables allow modification
 * 		before update.
 */
class User{
	
	private:
		string dbFirstName;
		string dbLastName;
		string dbEmail;
		time_t dbDOB;
		string dbHeading;
		string dbAbout;
		vector<string> dbUserLinks;
		vector<string> dbThirdPartyLinks;
		vector<string> dbInteractionLinks;
		vector<string> dbAccounts;
		string dbProfilePic;

	public:
		User(string link);
		User(Json::Value j);

		virtual int update();

		string getFirstName();
		string getLastName();
		string getFullName();
		string getEmail();
		string getDOB();
		string getHeading();
		string getAbout();
		string getUserLinks();
		string getInteractionLinks();
		string getThirdPartyLinks();
		string getAcounts();
		string getImage();

		virtual string setFirstName();
		virtual string setLastName();
		virtual string setPassword();
		virtual string setEmail();
		virtual string setHeading();
		virtual string setAbout();
		virtual string setUserLinks();
		virtual string setInteractionLinks();
		virtual string setThirdPartyLinks();
		virtual string setAcounts();

		virtual int addAccount();
		virtual int editAccount();
		virtual int removeAccount();

		virtual int setImage();

		virtual int removeUserLink(string link);
		virtual int removeInteractionLink(string link);
		virtual int removeThirdPartyLink(string link);

		vector<SqlInterface> getTableElements();
};


/** User object to be used in the client.
 */
class UserC:public User{
	private:
		bool loggedIn;

		string mFirstName;
		string mLastName;
		string mEmail;
		string mPassword;
		string mHeading;
		string mAbout;
		vector<string> mUserLinks;
		vector<string> mThirdPartyLinks;
		vector<string> mInteractionLinks;
		string mAccountAndPassword[2];
		string mProfilePic;

	public:
		UserC(string link);
		UserC(Json::Value j);
		UserC(string email, string password);

		virtual string setFirstName();
		virtual string setLastName();
		virtual string setPassword();
		virtual string setEmail();
		virtual string setHeading();
		virtual string setAbout();
		virtual string setUserLinks();
		virtual string setInteractionLinks();
		virtual string setThirdPartyLinks();
		virtual string setAcounts();

		virtual int addAccount();
		virtual int editAccount();
		virtual int removeAccount();

		virtual int setImage();

		virtual int removeUserLink(string link);
		virtual int removeInteractionLink(string link);
		virtual int removeThirdPartyLink(string link);

		virtual int update();
};








#endif //USER_H
