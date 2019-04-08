//=====================================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//=====================================================================================================================
#pragma once
#include <iostream>
#include <memory>
#include "Serializer.hpp"

namespace nbtlite
{
	/**
	 * @brief Interface of all NBT tags.
	 */
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
