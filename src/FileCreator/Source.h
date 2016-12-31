#include "Declaration.h"

class Source : public Declaration{

protected:
	string commentBody;
	string functionBody;
	
	virtual void Initialize();
	virtual int parse(string func);	
	bool getCommentSection(string * func);
	bool getFunctionBody(string * func);
	bool removeClassName(string * func);

public:

	Source();
	Source(string dec);
	~Source();
	
	virtual void print();
	virtual string getComment();
	virtual string getFunctionBody();

	bool compare(Declaration dec);
};
