#ifndef SOLAIRE_DATA_CONTIGUOUS_ARRAY_HPP
#define SOLAIRE_DATA_CONTIGUOUS_ARRAY_HPP

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
	\file ContiguousContainer.hpp.hpp
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
    class ContiguousContainer : public StaticContainer<T> {
    private:
        Allocator* mAllocator;
        T* mData;
        int32_t mSize;
    private:
        ContiguousContainer(ContiguousContainer<T>&&);
        ContiguousContainer(const ContiguousContainer<T>&);
        ContiguousContainer& operator=(ContiguousContainer<T>&&);
        ContiguousContainer& operator=(const ContiguousContainer<T>&);
    protected:
        // Inherited from Container

        T* SOLAIRE_EXPORT_CALL GetPtr(int32_t aOffset) throw() {
            return mData + aOffset;
        }

        SharedAllocation<Iterator<T>> SOLAIRE_EXPORT_CALL Begin() throw() {
            return mAllocator->SharedAllocate<ContiguousIterator<T>>(*mAllocator, mData, 0);
        }

        SharedAllocation<Iterator<T>> SOLAIRE_EXPORT_CALL End() throw() {
            return mAllocator->SharedAllocate<ContiguousIterator<T>>(*mAllocator, mData, mSize);
        }

        SharedAllocation<Iterator<T>> SOLAIRE_EXPORT_CALL Rbegin() throw() {
            //! \todo Implement reverse iterator
            return mAllocator->SharedAllocate<ContiguousIterator<T>>(*mAllocator, mData, 0);
        }

        SharedAllocation<Iterator<T>> SOLAIRE_EXPORT_CALL Rend() throw() {
            //! \todo Implement reverse iterator
            return mAllocator->SharedAllocate<ContiguousIterator<T>>(*mAllocator, mData, mSize);
        }

    public:
        ContiguousContainer(Allocator& aAllocator, T* aData, const int32_t aSize) throw() :
            mAllocator(&aAllocator),
            mData(aData),
            mSize(aSize)
        {}

        SOLAIRE_EXPORT_CALL ~ContiguousContainer() throw() {
        }

        // Inherited from Container

        bool SOLAIRE_EXPORT_CALL IsContiguous() const throw() {
            return true;
        }

        int32_t SOLAIRE_EXPORT_CALL Size() const throw() {
            return mSize;
        }

        Allocator& SOLAIRE_EXPORT_CALL GetAllocator() const throw() {
            return *mAllocator;
        }

    };
}

#endif
