//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include <map>
#include <string>
#include <type_traits>
#include "TagBase.hpp"

namespace nbtlite
{
	/**
	 * @addtogroup tags
	 * @{
	 */
	/**
	 * @brief The data structre that map tags to a uniqe name.
	 *
	 * BasicCompoundTag is the tag that store NBT tags by mapping it to a uniqe name. The implementation of
	 * map is based on the @p MapType, if @p MapType is std::map it will store the tags in data
	 * tree (typically red-black tree), if @p MapType is std::unordered_map it will store the tags in
	 * hash table.
	 *
	 * @tparam MapType Map that used to store the tags tree.
	 *
	 * @sa nbtlite::CompoundTag
	 */
	template <typename MapType>
	class BasicCompoundTag : public TagBase, public MapType
	{
	public:
		/**
		 * Constructor of Generic CompoundTag, static_assert will triggered if MapType have no key and value
		 * pair of std::string & std::shared_ptr<nbtlite::TagBase>.
		 */
		BasicCompoundTag()
		{
			static_assert(std::is_same<typename MapType::key_type, std::string>::value &&
					std::is_same<typename MapType::mapped_type, std::shared_ptr<TagBase>>::value,
					"The map key and value pair must be std::string and std::shared_ptr<nbtlite::TagBase>");
		}

		/**
		 * Insert a tag.
		 * @param key Unique name of the tag.
		 * @param tag Tag to insert.
		 * return true if success, false if failed (contain tag with same name).
		 */
		bool insert(const std::string& key, std::shared_ptr<TagBase> tag)
		{
			return MapType::insert({ key, std::move(tag) }).second;
		}

		void acceptSerializer(const std::string& name, Serializer& engine) override
		{
			engine.treeBegin(name);
			for (auto&& itr : *this)
				itr.second->acceptSerializer(itr.first, engine);
			engine.treeEnd(name);
		}

		/** Create new BasicCompoundTag. */
		static std::unique_ptr<BasicCompoundTag<MapType>> create()
		{
			return std::make_unique<BasicCompoundTag<MapType>>();
		}

		/**
		 * Create new BasicCompoundTag with default values.
		 * @param tags Tags to insert to compound tag.
		 */
		static std::unique_ptr<BasicCompoundTag<MapType>> create(std::initializer_list<std::pair<
			std::string,
			std::shared_ptr<TagBase>>
		>tags)
		{
			auto ptr = create();
			for (auto&& itr : tags)
				ptr->insert(std::move(itr.first), std::move(itr.second));
			return ptr;
		}
	};

	/**
	 * Alias of BasicCompoundTag that used std::map as it's container.
	 */
	using CompoundTag = BasicCompoundTag<std::map<std::string, std::shared_ptr<nbtlite::TagBase>>>;
	/** @} */
}
