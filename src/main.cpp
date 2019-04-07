#include <iostream>
#include <tuple>
#include <typeinfo>
#include "nbtlite/CompoundTag.hpp"
#include "nbtlite/ArrayTag.hpp"
#include "nbtlite/CommonTag.hpp"
#include "nbtlite/JSONSerializer.hpp"
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

using namespace std;

int main()
{
	cout << "Hello World" << endl;
	auto ptr = nbtlite::CompoundTag::create({
		{ "test1", nbtlite::StringTag::create("hello") },
		{ "test2", nbtlite::StringTag::create("this") },
		{ "test3", nbtlite::StringTag::create("is") },
		{ "test4", nbtlite::StringTag::create("a") },
		{ "test5", nbtlite::StringTag::create({"test"}) },
		{ "test6 num", nbtlite::Int32Tag::create(35) },
		{ "array test", nbtlite::ArrayTag<int>::create({ 34, 54 }) }
	});

	rapidjson::Document doc;
	doc.SetObject();
	nbtlite::JSONSerializer engine{ &doc };
	ptr->acceptSerializer("root", engine);
	rapidjson::StringBuffer buffer;
	rapidjson::PrettyWriter<decltype(buffer)> writer{ buffer };
	doc.Accept(writer);

	cout << buffer.GetString() << endl;

	return 0;
}
