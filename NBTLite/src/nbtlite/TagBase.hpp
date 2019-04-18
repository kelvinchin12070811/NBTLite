//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include <iostream>
#include <memory>
#include "Serializer.hpp"

/**
 * @defgroup tags NBT Tags
 *
 * A tag is the holder that hold a specific data with its unique name. All tag is derived from
 * nbtlite::TagBase. The tag can be serialized or deserialized with nbtlite::Serializer objects.
 */

namespace nbtlite
{
	/**
	 * @addtogroup tags
	 * @{
	 */
	/**
	 * @brief Interface of all NBT tags.
	 */
	class TagBase
	{
	public:
		TagBase() = default;
		virtual ~TagBase() = 0;

		/**
		 * Accept a serializer for serialization of deserialization.
		 * @param name[in] Name of this tag.
		 * @param engine[in] Engine or serializer instance to proceed.
		 */
		virtual void acceptSerializer(const std::string& name, Serializer& engine) = 0;

		/**
		 * Cast this TagBase instance to it's corresponding child instance.
		 * @tparam T Subclass to cast to.
		 * @retval T* Instance of object as it's child type, nullptr if casting failed.
		 * @warning This member function cast the object's `this` pointer to it's child instance, do not
		 * create smart pointer with it or use `std::dynamic_pointer_cast` on shared_ptr instance instead.
		 */
		template <typename T>
		typename std::enable_if<std::is_base_of<TagBase, T>::value, T*>::type as()
		{
			return dynamic_cast<T*>(this);
		}
	};
	/** @} */
	inline TagBase::~TagBase() = default;
}
