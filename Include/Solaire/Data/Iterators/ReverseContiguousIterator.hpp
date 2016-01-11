#ifndef SOLAIRE_DATA_REVERSE_CONTIGUOUS_ITERATOR_HPP
#define SOLAIRE_DATA_REVERSE_CONTIGUOUS_ITERATOR_HPP

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
	\file ReverseContiguousIterator.hpp
	\brief
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\date
	Created			: 10th January 2016
	Last Modified	: 10th January 2016
*/

#include "Solaire/Core/Iterator.hpp"

namespace Solaire {

	template<class T>
    class ReverseContiguousIterator : public Iterator<T> {
    private:
        Allocator* mAllocator;
        T* mBase;
        int16_t mOffset;
    public:
        ReverseContiguousIterator(Allocator& aAllocator, T* const aBase, const int32_t aOffset) throw() :
            mAllocator(&aAllocator),
            mBase(aBase),
            mOffset(aOffset)
        {}

        SOLAIRE_EXPORT_CALL ~ReverseContiguousIterator() throw() {

        }

        // Inherited from Iterator

        Iterator<T>& SOLAIRE_EXPORT_CALL increment(int32_t aOffset) throw() {
            mOffset -= aOffset;
            return *this;
        }

        Iterator<T>& SOLAIRE_EXPORT_CALL decrement(int32_t aOffset) throw() {
            mOffset += aOffset;
            return *this;
        }

        SharedAllocation<Iterator<T>> SOLAIRE_EXPORT_CALL copy() const throw() {
            //! \todo SharedAllocate
            return SharedAllocation<Iterator<T>>(
                *mAllocator,
                new(mAllocator->allocate(sizeof(ReverseContiguousIterator<T>))) ReverseContiguousIterator<T>(*mAllocator, mBase, mOffset)
            );
        }

        int32_t SOLAIRE_EXPORT_CALL getOffset() const throw() {
            return mOffset;
        }

        T* SOLAIRE_EXPORT_CALL getPtr() throw() {
            return mBase + mOffset;
        }

    };
}

#endif
