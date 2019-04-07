#pragma once
#include <cstddef>
#include <cstdint>
#include <limits>
#include <string>
#include <type_traits>
#include <vector>
#include "TagBase.hpp"

namespace nbtlite
{
	template <typename DataType>
	class TagWrapper : public TagBase
	{
	public:
		TagWrapper()
		{
			static_assert(std::numeric_limits<DataType>::is_specialized,
					"DataType of default specialization must an internal type");
		}
		TagWrapper(DataType data):
			data(std::move(data))
		{}

		static std::unique_ptr<TagWrapper<DataType>> create(DataType value = DataType())
		{
			return std::make_unique<TagWrapper<DataType>>(std::move(value));
		}

		TagWrapper& operator=(DataType data)
		{
			this->data = std::move(data);
			return *this;
		}

		operator DataType&()
		{
			return get();
		}

		operator const DataType&() const
		{
			return get();
		}

		const DataType& get() const
		{
			return data;
		}

		DataType& get()
		{
			return const_cast<DataType&>(const_cast<const TagWrapper*>(this)->get());
		}

		void acceptSerializer(const std::string& name, Serializer& engine) override
		{
			static_assert(std::numeric_limits<DataType>::is_specialized,
					"Non internal type must specialize TagWrapper::acceptSerializer function");
			engine.accept(name, data);
		}
	private:
		DataType data{ 0 };
	};

	template <>
	TagWrapper<std::string>::TagWrapper() = default;

	template <>
	void TagWrapper<std::string>::acceptSerializer(const std::string& name, Serializer& engine)
	{
		engine.accept(name, data);
	}

	// prespecified types
	using BoolTag = TagWrapper<bool>;
	using CharTag = TagWrapper<char>;
	using FloatTag = TagWrapper<float>;
	using DoubleTag = TagWrapper<double>;
	using LongDoubleTag = TagWrapper<long double>;
	using StringTag = TagWrapper<std::string>;
	using UInt8Tag = TagWrapper<uint8_t>;
	using Int8Tag = TagWrapper<int8_t>;
	using UInt16Tag = TagWrapper<uint16_t>;
	using Int16Tag = TagWrapper<int16_t>;
	using UInt32Tag = TagWrapper<uint32_t>;
	using Int32Tag = TagWrapper<int32_t>;
	using UInt64Tag = TagWrapper<uint64_t>;
	using Int64Tag = TagWrapper<int64_t>;
	using ByteTag = TagWrapper<std::byte>;
}
