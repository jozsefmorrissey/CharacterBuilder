#include "Interaction.h"


//--------------------------  Public  --------------------------//


/**		TODO: comment on function use
 *		
 *		@id - 
 *		@return - TODO: comment on return value
 */
InteractionC::InteractionC(Cint id){
	//TODO: Implement
}


/**		TODO: comment on function use
 *		
 *		@cEmail - 
 *		@about - 
 *		@return - TODO: comment on return value
 */
InteractionC::InteractionC(string cEmail, string about){
	//TODO: Implement
}


/**		TODO: comment on function use
 *		
 *		@j - 
 *		@return - TODO: comment on return value
 */
InteractionC::InteractionC(Json::Value j){
	//TODO: Implement
}


/**		TODO: comment on function use
 *		
 *		@email - 
 *		@return - TODO: comment on return value
 */
int InteractionC::addContributor(string email){
	//TODO: Implement
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@email - 
 *		@return - TODO: comment on return value
 */
int InteractionC::removeContributor(string email){
	//TODO: Implement
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@user - 
 *		@comment - 
 *		@return - TODO: comment on return value
 */
int InteractionC::addComment(UserC user, string comment){
	//TODO: Implement
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@user - 
 *		@return - TODO: comment on return value
 */
int InteractionC::removeComment(UserC user){
	//TODO: Implement
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@user - 
 *		@return - TODO: comment on return value
 */
string InteractionC::getComment(UserC user){
	//TODO: Implement
	return NULL;
}


/**		TODO: comment on function use
 *		
 *		@return - TODO: comment on return value
 */
vector<string> InteractionC::getBeforeImages(){
	//TODO: Implement
	return NULL;
}


/**		TODO: comment on function use
 *		
 *		@return - TODO: comment on return value
 */
vector<string> InteractionC::getAfterImages(){
	//TODO: Implement
	return NULL;
}


/**		TODO: comment on function use
 *		
 *		@return - TODO: comment on return value
 */
vector<string> InteractionC::getProgressImages(){
	//TODO: Implement
	return NULL;
}


/**		TODO: comment on function use
 *		
 *		@user - 
 *		@imgs - 
 *		@return - TODO: comment on return value
 */
int InteractionC::updateBeforeImage(UserC user, vector<string> imgs){
	//TODO: Implement
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@user - 
 *		@imgs - 
 *		@return - TODO: comment on return value
 */
int InteractionC::updateAfterImage(UserC user, vector<string> imgs){
	//TODO: Implement
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@user - 
 *		@imgs - 
 *		@return - TODO: comment on return value
 */
int InteractionC::updateProgressImages(UserC user, vector<string> imgs){
	//TODO: Implement
	return 0;
}

