//=====================================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//=====================================================================================================================
#pragma once
#include <vector>
#include "TagBase.hpp"

namespace nbtlite
{
	template <typename T>
	class ArrayTag : public TagBase, public std::vector<T>
	{
	public:
		ArrayTag() = default;
		ArrayTag(size_t size): std::vector<T>(size) {}

		ArrayTag(const ArrayTag& rhs)
		{
			this->reserve(rhs.size());
			std::copy(rhs.begin(), rhs.end(), std::back_inserter(*this));
		}

		ArrayTag(ArrayTag&& rhs)
		{
			this->reserve(rhs.size());
			std::move(rhs.begin(), rhs.end(), std::back_inserter(*this));
		}
		~ArrayTag() = default;

		ArrayTag& operator=(const ArrayTag& rhs)
		{
			if (!this->empty())
			{
				this->clear();
				this->shrink_to_fit();
			}

			this->reserve(rhs.size());
			std::copy(rhs.begin(), rhs.end(), std::back_inserter(*this));
		}

		ArrayTag& operator=(ArrayTag&& rhs)
		{
			if (!this->empty())
			{
				this->clear();
				this->shrink_to_fit();
			}
			this->reserve(rhs.size());
			std::move(rhs.begin(), rhs.end(), std::back_inserter(*this));
		}

		void acceptSerializer(const std::string& name, Serializer& engine) override
		{
			engine.arrayBegin(name);
			for (auto itr = this->begin(); itr != this->end(); itr++)
				engine.accept(std::to_string(std::distance(this->begin(), itr)), *itr);
			engine.arrayEnd(name);
		}

		static std::unique_ptr<ArrayTag<T>> create()
		{
			return std::make_unique<ArrayTag<T>>();
		}

		static std::unique_ptr<ArrayTag<T>> create(std::initializer_list<T> list)
		{
			auto ptr = create();
			ptr->reserve(list.size());
			std::move(list.begin(), list.end(), std::back_inserter(*ptr));
			return ptr;
		}
	};
}
