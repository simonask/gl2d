#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include "v8.h"

class Script
{
private:
	Script() {}
	virtual ~Script() {}
public:
	
	static void load(const char* file);
	static void initializeGlobalTemplate(v8::Handle<v8::ObjectTemplate>& global_template);
	static void setContext(v8::Persistent<v8::Context>& context);
};

#endif /* _SCRIPT_H_ */
