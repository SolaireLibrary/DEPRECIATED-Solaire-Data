#ifndef SOLAIRE_LIST_MAP_HPP
#define SOLAIRE_LIST_MAP_HPP

//Copyright 2015 Adam Smith
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

// Contact :
// Email             : solairelibrary@mail.com
// GitHub repository : https://github.com/SolaireLibrary/SolaireCPP

/*!
	\file ListMap.hpp
	\brief
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\version 1.0
	\date
	Created			: 16th January 2016
	Last Modified	: 16th January 2016
*/

#include "Solaire\Core\Container.hpp"
#include "Solaire\Data\ArrayList.hpp"

namespace Solaire {

    template<class K, class T>
	class ListMap : public Map<K,T> {
    private:
        ArrayList<typename Map<K,T>::Entry> mEntries;
    private:
		int32_t findIndex(const K& aKey) const throw() {
            return mEntries.findFirstIf([&](const typename Map<K,T>::Entry& aEntry)->bool{
                return aEntry.first == aKey;
            });
        }
	public:
	    ListMap() :
	        mEntries()
        {}

	    ListMap(Allocator& aAllocator) :
	        mEntries(aAllocator)
        {}

	    ListMap(const Map<K,T>& aOther) :
	        mEntries(aOther.getAllocator())
        {
            const SharedAllocation<StaticContainer<typename Map<K,T>::Entry>> entries = aOther.getEntries();
            const auto end = entries->end();
            for(auto i = entries->begin(); i != end; ++i) emplace(i->first, i->second);
        }

		SOLAIRE_EXPORT_CALL ~ListMap() throw() {

		}

        // Inherited from Map

		T& SOLAIRE_EXPORT_CALL emplace(const K& aKey, const T& aValue) throw() override {
            const int32_t pos = findIndex(aKey);
            if(pos != mEntries.size()) return mEntries[pos].second = aValue;
            return mEntries.pushBack(typename Map<K,T>::Entry(aKey, aValue)).second;
        }

		const T& SOLAIRE_EXPORT_CALL get(const K& aKey) const throw() override {
            const int32_t pos = findIndex(aKey);
            return mEntries[pos].second;
        }

		T& SOLAIRE_EXPORT_CALL get(const K& aKey) throw() override {
            const int32_t pos = findIndex(aKey);
            return mEntries[pos].second;
        }

		bool SOLAIRE_EXPORT_CALL contains(const K& aKey) const throw() override {
            return mEntries.size() != findIndex(aKey);
        }

		bool SOLAIRE_EXPORT_CALL erase(const K& aKey) throw() override {
		    const int32_t pos = findIndex(aKey);
            return pos == mEntries.size() ? false : mEntries.erase(pos);
        }

		void SOLAIRE_EXPORT_CALL clear() throw() override {
            mEntries.clear();
        }

        int32_t SOLAIRE_EXPORT_CALL size() const throw() override {
            return mEntries.size();
        }

        Allocator& SOLAIRE_EXPORT_CALL getAllocator() const throw() override {
            return mEntries.getAllocator();
        }

        SharedAllocation<StaticContainer<typename Map<K,T>::Entry>> getEntries() const throw() override {
            return SharedAllocation<StaticContainer<typename Map<K,T>::Entry>>();
            //typedef ArrayList<typename Map<K,T>::Entry> ContainterType;
            //return getAllocator().sharedAllocate<ContainterType>(mEntries);
        }

	};

}

#endif
