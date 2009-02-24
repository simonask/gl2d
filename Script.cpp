#include "Script.h"
#include "Log.h"
#include "v8.h"

using v8::Context;
using v8::Persistent;
using v8::Handle;
using v8::Value;
using v8::HandleScope;
using v8::ObjectTemplate;
using v8::FunctionTemplate;
using v8::Arguments;
using v8::Undefined;
using v8::String;

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
using namespace std;

static Handle<Context> context;

namespace js {
	static Handle<Value> load(const Arguments& args)
	{
		const char* file = *String::Utf8Value(args[0]);
		Script::load(file);
		return Undefined();
	}
	
	static Handle<Value> log(const Arguments& args)
	{
		stringstream ss;
		for (int i = 0; i < args.Length(); ++i) {
			ss << *String::Utf8Value(args[i]);
		}
		Log::log(ss.str().c_str());
		return Undefined();
	}
}

void Script::initializeGlobalTemplate(Handle<ObjectTemplate>& global)
{
	global->Set(String::New("load"), FunctionTemplate::New(js::load));
	global->Set(String::New("log"), FunctionTemplate::New(js::log));
}

void Script::setContext(Persistent<Context>& context_ref)
{
	context = context_ref;
}

void Script::load(const char* file)
{
	ifstream fs(file);
	if (!fs.is_open())
	{
		cerr << "ERROR: File not found: " << file << endl;
		throw runtime_error("FILE NOT FOUND!");
	}
	stringstream source_str;
	string line;
	while (fs.is_open() && !fs.eof())
	{
		getline(fs, line);
		if (line[0] != '#')
			source_str << line << endl;
	}
	fs.close();

	Handle<String> source = String::New(source_str.str().c_str());
	Handle<v8::Script> script = v8::Script::Compile(source);
	script->Run();
}
