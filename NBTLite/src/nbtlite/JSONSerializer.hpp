//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#if __has_include(<rapidjson/document.h>)
#include <stack>
#include <rapidjson/document.h>
#include "Serializer.hpp"

namespace nbtlite
{
	class JSONSerializer : public Serializer
	{
	public:
		inline JSONSerializer(rapidjson::Value* root, rapidjson::Value::AllocatorType* allocator):
			root(root), allocator(allocator)
		{
			if (this->root->IsNull() || !this->root->IsObject())
				throw std::logic_error{ "root must be an object" };
		}

		inline JSONSerializer(rapidjson::Document* doc):
			root(doc), allocator(&doc->GetAllocator())
		{
			if (doc->IsNull() || !doc->IsObject())
				throw std::logic_error{ "Document must be an object" };
		}

		inline void treeBegin(const std::string& name) override
		{
			callStack.push({ name, rapidjson::Value{ rapidjson::kObjectType } });
		}

		inline void treeEnd(const std::string& name) override
		{
			auto data = std::move(callStack.top());
			callStack.pop();
			append(data.first, std::move(data.second));
		}

		inline void arrayBegin(const std::string& name) override
		{
			callStack.push({ name, rapidjson::Value{ rapidjson::kArrayType } });
		}

		inline void arrayEnd(const std::string& name) override
		{
			auto data = std::move(callStack.top());
			callStack.pop();
			append(data.first, std::move(data.second));
		}

		inline void accept(const std::string& name, bool& value) override
		{
			rapidjson::Value v;
			v.SetBool(value);
			append(name, std::move(v));
		}

		inline void accept(const std::string& name, char& value) override
		{
			rapidjson::Value v{ rapidjson::kStringType };
			v.SetString(&value, 1, *allocator);
			append(name, std::move(v));
		}
		inline void accept(const std::string& name, float& value) override
		{
			rapidjson::Value v{ rapidjson::kNumberType };
			v.SetFloat(value);
			append(name, std::move(v));
		}
		inline void accept(const std::string& name, double& value) override
		{
			rapidjson::Value v{ rapidjson::kNumberType };
			v.SetDouble(value);
			append(name, std::move(v));
		}
		inline void accept(const std::string& name, long double& value) override
		{
			std::string t = std::to_string(value);
			rapidjson::Value v{ rapidjson::kStringType };
			v.SetString(t.c_str(), t.length(), *allocator);
			append(name, std::move(v));
		}
		inline void accept(const std::string& name, std::string& value) override
		{
			rapidjson::Value v{ rapidjson::kStringType };
			v.SetString(value.c_str(), value.length(), *allocator);
			append(name, std::move(v));
		}
		inline void accept(const std::string& name, uint8_t& value) override
		{
			rapidjson::Value v{ rapidjson::kNumberType };
			v.SetUint(static_cast<uint32_t>(value));
			append(name, std::move(v));
		}
		inline void accept(const std::string& name, int8_t& value) override
		{
			rapidjson::Value v{ rapidjson::kNumberType };
			v.SetInt(static_cast<int32_t>(value));
			append(name, std::move(v));
		}
		inline void accept(const std::string& name, uint16_t& value) override
		{
			rapidjson::Value v{ rapidjson::kNumberType };
			v.SetUint(static_cast<uint32_t>(value));
			append(name, std::move(v));
		}
		inline void accept(const std::string& name, int16_t& value) override
		{
			rapidjson::Value v{ rapidjson::kNumberType };
			v.SetInt(static_cast<int32_t>(value));
			append(name, std::move(v));
		}
		inline void accept(const std::string& name, uint32_t& value) override
		{
			rapidjson::Value v{ rapidjson::kNumberType };
			v.SetUint(value);
			append(name, std::move(v));
		}
		inline void accept(const std::string& name, int32_t& value) override
		{
			rapidjson::Value v{ rapidjson::kNumberType };
			v.SetInt(value);
			append(name, std::move(v));
		}
		inline void accept(const std::string& name, uint64_t& value) override
		{
			rapidjson::Value v{ rapidjson::kNumberType };
			v.SetUint64(value);
			append(name, std::move(v));
		}
		inline void accept(const std::string& name, int64_t& value) override
		{
			rapidjson::Value v{ rapidjson::kNumberType };
			v.SetInt64(value);
			append(name, std::move(v));
		}
		inline void accept(const std::string& name, std::byte& value) override
		{
			rapidjson::Value v{ rapidjson::kNumberType };
			v.SetUint(std::to_integer<uint32_t>(value));
		}
	private:
		inline void append(const std::string& name, rapidjson::Value value)
		{
			if (callStack.empty())
			{
				root->AddMember(rapidjson::Value{ name.c_str(), *allocator }, value, *allocator);
			}
			else
			{
				if (auto& top = callStack.top(); top.second.GetType() == rapidjson::kArrayType)
				{
					top.second.PushBack(std::move(value), *allocator);
				}
				else
				{
					using namespace rapidjson;
					top.second.AddMember(Value{ name.c_str(), static_cast<unsigned int>(name.length()), *allocator },
						std::move(value), *allocator);
				}
			}
		}
	private:
		std::stack<std::pair<std::string, rapidjson::Value>> callStack;
		rapidjson::Value* root{ nullptr };
		rapidjson::Value::AllocatorType* allocator{ nullptr };
	};
}
#endif
