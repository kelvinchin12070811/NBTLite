//=====================================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//=====================================================================================================================
#pragma once
#include <map>
#include <string>
#include <type_traits>
#include "TagBase.hpp"

namespace nbtlite
{
	template <typename MapType>
	class BasicCompoundTag : public TagBase, public MapType
	{
	public:
		BasicCompoundTag()
		{
			static_assert(std::is_same<typename MapType::key_type, std::string>::value &&
					std::is_same<typename MapType::mapped_type, std::shared_ptr<TagBase>>::value,
					"The map key and value pair must be std::string and std::shared_ptr<nbtlite::TagBase>");
		}

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

		static std::unique_ptr<BasicCompoundTag<MapType>> create()
		{
			return std::make_unique<BasicCompoundTag<MapType>>();
		}

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

	using CompoundTag = BasicCompoundTag<std::map<std::string, std::shared_ptr<nbtlite::TagBase>>>;
}
