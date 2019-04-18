# NBTLite

NBTLite is a header only library that implement NBT Tree like data structure in C++17.

## Install

 1. Clone or download and extract this repository.
 2. Add or copy the folder `nbtlite` under `project_root/NBTLite/src` to include path
 3. include headers with prefix `nbtlite`
 
## Usage

The library is header only, just include the needed header and start coding.

### Basic usage

~~~cpp
#include <iostream>
#include <nbtlite/CompoundTag.hpp>
#include <nbtlite/ArrayTag.hpp>
#include <nbtlite/CommonTag.hpp> 
 
using namespace std;
 
int main(int argc, char** argv)
{
	// Create a NBT tags tree with CompoundTag.
	auto ptr = nbtlite::CompoundTag::create({
		{ "test1", nbtlite::StringTag::create("hello") },
		{ "test2", nbtlite::StringTag::create("this") },
		{ "test3", nbtlite::StringTag::create("is") },
		{ "test4", nbtlite::StringTag::create("a") },
		{ "test5", nbtlite::StringTag::create({"test"}) },
		{ "test6 num", nbtlite::Int32Tag::create(35) },
		{ "array test", nbtlite::ArrayTag<int>::create({ 34, 54 }) }
	});
	return 0;
}
~~~

### Serialization & deserialization

NBTLite support serializtion and deserialization on all `nbtlite::TagBase` subclasses, the virtual member function
`nbtlite::TagBase::acceptSerializer` did both of the serialization and deserialization process.

The serializers and deserializer are derived from `nbtlite::Serializer`.

#### JSON Serializer

The JSON Serializer is a serializer engine that serialize the NBT data into json format with
[rapidjson library](https://rapidjson.org). The definition will not avaliable if rapidjson library was not found in
include path.

~~~cpp
// headers required for JSON serialization
#include <nbtlite/JSONSerializer.hpp>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
...
rapidjson::Document doc;
doc.SetObject(); // initialize empty doc object.
nbtlite::JSONSerializer engine{ &doc }; // create JSONSerializer engine on rapidjson document.
tagInstance->acceptSerializer("name", engine); // let tag accept a name and an engine. 
rapidjson::StringBuffer buffer;
rapidjson::PrettyWriter<decltype(buffer)> writer{ buffer };
doc.Accept(writer);

cout << buffer.GetString() << endl; // output JSON String or save it to file.
...
~~~

## Documentation

The online version of doxygen generated documentation of NBTLite is avaliable at [here](.)
 
## License

This project is licensed under [The Mozilla Public License 2.0](doxygen_page/liblicense.md).