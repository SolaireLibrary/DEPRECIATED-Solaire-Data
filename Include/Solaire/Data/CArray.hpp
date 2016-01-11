#ifndef SOLAIRE_DATA_CARRAY_HPP
#define SOLAIRE_DATA_CARRAY_HPP

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
	\file CArray.hpp
	\brief
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\date
	Created			: 10th January 2016
	Last Modified	: 10th January 2016
*/

#include "Solaire/Core/Container.hpp"
#include "Solaire/Data/Iterators/ContiguousIterator.hpp"

namespace Solaire {

	template<class T>
    class CArray : public StaticContainer<T> {
    private:
        Allocator* mAllocator;
        T* mData;
        int32_t mSize;
    private:
        CArray(CArray<T>&&);
        CArray(const CArray<T>&);
        CArray& operator=(CArray<T>&&);
        CArray& operator=(const CArray<T>&);
    protected:
        // Inherited from Container

        T* SOLAIRE_EXPORT_CALL GetPtr(int32_t aOffset) throw() {
            return mData + aOffset;
        }

        SharedAllocation<Iterator<T>> SOLAIRE_EXPORT_CALL begin_() throw() {
            return mAllocator->sharedAllocate<ContiguousIterator<T>>(*mAllocator, mData, 0);
        }

        SharedAllocation<Iterator<T>> SOLAIRE_EXPORT_CALL end_() throw() {
            return mAllocator->sharedAllocate<ContiguousIterator<T>>(*mAllocator, mData, mSize);
        }

        SharedAllocation<Iterator<T>> SOLAIRE_EXPORT_CALL rbegin_() throw() {
            //! \todo Implement reverse iterator
            return mAllocator->sharedAllocate<ContiguousIterator<T>>(*mAllocator, mData, 0);
        }

        SharedAllocation<Iterator<T>> SOLAIRE_EXPORT_CALL rend_() throw() {
            //! \todo Implement reverse iterator
            return mAllocator->sharedAllocate<ContiguousIterator<T>>(*mAllocator, mData, mSize);
        }

    public:
        CArray(Allocator& aAllocator, const int32_t aSize) throw() :
            mAllocator(&aAllocator),
            mData(reinterpret_cast<T*>(aAllocator.allocate(sizeof(T) * aSize))),
            mSize(aSize)
        {
            for(int32_t i = 0; i < mSize; ++i) {
                new(mData + i) T();
            }
        }

        SOLAIRE_EXPORT_CALL ~CArray() throw() {
            for(int32_t i = 0; i < mSize; ++i) {
                mData[i].~T();
            }
            mAllocator->deallocate(mData);
        }

        // Inherited from Container

        bool SOLAIRE_EXPORT_CALL isContiguous() const throw() {
            return true;
        }

        int32_t SOLAIRE_EXPORT_CALL size() const throw() {
            return mSize;
        }

        Allocator& SOLAIRE_EXPORT_CALL getAllocator() const throw() {
            return *mAllocator;
        }

    };
}

#endif
