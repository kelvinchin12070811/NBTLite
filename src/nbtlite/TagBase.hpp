#pragma once
#include <iostream>
#include <memory>
#include "Serializer.hpp"

namespace nbtlite
{
	class TagBase
	{
	public:
		TagBase() = default;
		virtual ~TagBase() = 0;

		virtual void acceptSerializer(const std::string& name, Serializer& engine) = 0;

		template <typename T>
		typename std::enable_if<std::is_base_of<TagBase, T>::value, T*>::type as()
		{
			return dynamic_cast<T*>(this);
		}
	};

	inline TagBase::~TagBase() = default;
}
