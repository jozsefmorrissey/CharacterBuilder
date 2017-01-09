#ifndef INTERACTION_H
#define INTERACTION_H

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <string>
#include <jsoncpp/json/json.h>

#include "User.h"

using namespace std;

/** 		db variables are the values currently contained in the database. m variables allow modification
 * 		before update.
 */
class Interaction{
	private:
		int ID;
		string creatorEmail;
		string dbAbout;
		vector<string> dbContributorEmails;
		vector<string> dbExperianceComments;
		vector<string> dbBeforeImages, dbAfterImages, dbProgressImages;

	public:
		Interaction(string link);
		Interaction(int Id);
		Interaction(string cEmail, string about);
		Interaction(Json::Value j);
		
		virtual int addContributor(string email);
		virtual int removeContributor(string email);

		virtual int addComment(UserC user, string comment);
		virtual int removeComment(UserC user);

		virtual vector<string> getBeforeImages();
		virtual vector<string> getAfterImages();
		virtual vector<string> getProgressImages();

		virtual int updateBeforeImage(UserC user, vector<string> imgs);
		virtual int updateAfterImage(UserC user, vector<string> imgs);
		virtual int updateProgressImages(UserC user, vector<string> imgs);
};


class InteractionC{
	private:
		string creatorEmail;
		string mAbout;
		vector<string> mContributorEmails;
		vector<string> mExperianceComments;
		vector<string> mBeforeImages, mAfterImages, mProgressImages;

	public:
		InteractionC(string link);
		InteractionC(int id);
		InteractionC(string cEmail, string about);
		InteractionC(Json::Value j);
		
		virtual int addContributor(string email);
		virtual int removeContributor(string email);

		virtual int addComment(UserC user, string comment);
		virtual int removeComment(UserC user);
		string getComment(UserC user);

		virtual vector<string> getBeforeImages();
		virtual vector<string> getAfterImages();
		virtual vector<string> getProgressImages();

		virtual int updateBeforeImage(UserC user, vector<string> imgs);
		virtual int updateAfterImage(UserC user, vector<string> imgs);
		virtual int updateProgressImages(UserC user, vector<string> imgs);
};





#endif //INTERACTION_H
