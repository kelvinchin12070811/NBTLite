#pragma once
#include <cstddef>

namespace nbtlite
{
	class Serializer
	{
	public:
		virtual ~Serializer() = 0;

		virtual void treeBegin(const std::string& name) = 0;
		virtual void treeEnd(const std::string& name) = 0;
		virtual void arrayBegin(const std::string& name) = 0;
		virtual void arrayEnd(const std::string& name) = 0;

		virtual void accept(const std::string& name, bool& value) = 0;
		virtual void accept(const std::string& name, char& value) = 0;
		virtual void accept(const std::string& name, float& value) = 0;
		virtual void accept(const std::string& name, double& value) = 0;
		virtual void accept(const std::string& name, long double& value) = 0;
		virtual void accept(const std::string& name, std::string& value) = 0;
		virtual void accept(const std::string& name, uint8_t& value) = 0;
		virtual void accept(const std::string& name, int8_t& value) = 0;
		virtual void accept(const std::string& name, uint16_t& value) = 0;
		virtual void accept(const std::string& name, int16_t& value) = 0;
		virtual void accept(const std::string& name, uint32_t& value) = 0;
		virtual void accept(const std::string& name, int32_t& value) = 0;
		virtual void accept(const std::string& name, uint64_t& value) = 0;
		virtual void accept(const std::string& name, int64_t& value) = 0;
		virtual void accept(const std::string& name, std::byte& value) = 0;
	};

	inline Serializer::~Serializer() = default;
}
