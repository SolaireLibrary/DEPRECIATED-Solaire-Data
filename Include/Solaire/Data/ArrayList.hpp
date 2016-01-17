#ifndef SOLAIRE_DYNAMIC_ARRAY_HPP
#define SOLAIRE_DYNAMIC_ARRAY_HPP

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
	\file ArrayList.hpp
	\brief
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\date
	Created			: 11th January 2016
	Last Modified	: 11th January 2016
*/

#include <iostream>

#include <cstdint>
#include "Solaire/Core/NewAllocator.hpp"
#include "Solaire/Core/Container.hpp"
#include "Solaire/Data/Iterators/ContiguousIterator.hpp"
#include "Solaire/Data/Iterators/ReverseContiguousIterator.hpp"

namespace Solaire{

    enum : int32_t {
        DEFAULT_ARRAY_LIST_SIZE = 32
    };

    template<class TYPE, class INDEX = uint16_t>
	class ArrayList : public List<TYPE> {
	public:
		typedef TYPE Type;
		typedef const TYPE ConstType;
		typedef Type& Reference;
		typedef ConstType& ConstReference;
		typedef Type&& Move;
		typedef Type* Pointer;
		typedef ConstType* ConstPointer;
		typedef INDEX Index;
		typedef ArrayList<TYPE, INDEX> Self;

        friend class CString;
	private:
        Allocator* mAllocator;
		Index mHead;
		Index mSize;
		Type* mData;
    private:
        bool copyTo(Type* const aArray) const throw() {
            //std::cout << "CopyTo" << std::endl;
            const int32_t size = mHead;
            for(int32_t i = 0; i < size; ++i) {
                new(aArray + i) Type(mData[i]);
            }
            return true;
        }

        bool moveTo(Type* const aArray) throw() {
            //std::cout << "MoveTo" << std::endl;
            const int32_t size = mHead;
            for(int32_t i = 0; i < size; ++i) {
                new(aArray + i) Type(std::move(mData[i]));
                mData[i].~Type();
            }
            return true;
        }

        bool destructAll() throw() {
            //std::cout << "DestructAll" << std::endl;
            const int32_t size = mHead;
            for(int32_t i = 0; i < size; ++i) {
                mData[i].~Type();
            }
            return true;
        }

        bool shiftUp(const int32_t aIndex) throw() {
            //std::cout << "ShiftUp" << std::endl;
            // Create a new object at the end of the list
            pushBack(mData[mHead - 1]);

            // Shift up existing objects
            const int32_t head = mHead - 1;
            for(int32_t i = head; i > aIndex; --i) {
                Type& high = mData[i];
                Type& low = mData[i - 1];
                high = std::move(low);
            }

            return true;
        }

        bool shiftDown(const int32_t aIndex) throw() {
            //std::cout << "ShiftDown" << std::endl;
            const int32_t size = mHead;
            for(int32_t i = aIndex; i < size; ++i) {
                Type& high = mData[i + 1];
                Type& low = mData[i];
                low = std::move(high);
            }
            --mHead;
            mData[mHead].~Type();
            return true;
        }

        bool reallocate(const Index aSize) throw() {
            //std::cout << "Reallocate" << std::endl;
            Type* const ptr = static_cast<Type*>(mAllocator->allocate(sizeof(Type) * aSize));
            if(! moveTo(ptr)) {
                mAllocator->deallocate(ptr);
                return false;
            }
            mAllocator->deallocate(mData);
            mData = ptr;
            mSize = aSize;
            return true;
        }
    protected:
        // Inherited from StaticContainer

        Pointer SOLAIRE_EXPORT_CALL getPtr(int32_t aOffset) throw() override {
            return mData + aOffset;
        }

        SharedAllocation<Iterator<Type>> SOLAIRE_EXPORT_CALL begin_() throw() override {
            //! \todo SharedAllocate
            //return mAllocator->SharedAllocate<ContiguousIterator<Type>>(*mAllocator, mData, 0);
            return SharedAllocation<Iterator<Type>>(
                *mAllocator,
                new(mAllocator->allocate(sizeof(ContiguousIterator<Type>))) ContiguousIterator<Type>(*mAllocator, mData, 0)
            );
        }

        SharedAllocation<Iterator<Type>> SOLAIRE_EXPORT_CALL end_() throw() override {
            //! \todo SharedAllocate
            //return mAllocator->SharedAllocate<ContiguousIterator>(*mAllocator, mData, mHead);
            return SharedAllocation<Iterator<Type>>(
                *mAllocator,
                new(mAllocator->allocate(sizeof(ContiguousIterator<Type>))) ContiguousIterator<Type>(*mAllocator, mData, mHead)
            );
        }

        SharedAllocation<Iterator<Type>> SOLAIRE_EXPORT_CALL rbegin_() throw() override {
            //! \todo SharedAllocate
            return SharedAllocation<Iterator<Type>>(
                *mAllocator,
                new(mAllocator->allocate(sizeof(ReverseContiguousIterator<Type>))) ReverseContiguousIterator<Type>(*mAllocator, mData, mHead - 1)
            );
        }

        SharedAllocation<Iterator<Type>> SOLAIRE_EXPORT_CALL rend_() throw() override {
            //! \todo SharedAllocate
            return SharedAllocation<Iterator<Type>>(
                *mAllocator,
                new(mAllocator->allocate(sizeof(ReverseContiguousIterator<Type>))) ReverseContiguousIterator<Type>(*mAllocator, mData, -1)
            );
        }

    public:
        ArrayList() :
            mAllocator(&getDefaultAllocator()),
            mHead(0),
            mSize(DEFAULT_ARRAY_LIST_SIZE),
            mData(static_cast<Type*>(getDefaultAllocator().allocate(sizeof(Type) * DEFAULT_ARRAY_LIST_SIZE)))
        {

                std::cout << std::endl << ((uint64_t) mAllocator) << " == " << ((uint64_t)&getDefaultAllocator()) <<
                    " = " << (mAllocator == &getDefaultAllocator() ? "true" : "false") << std::endl;
        }

        ArrayList(Allocator& aAllocator) :
            mAllocator(&aAllocator),
            mHead(0),
            mSize(DEFAULT_ARRAY_LIST_SIZE),
            mData(static_cast<Type*>(aAllocator.allocate(sizeof(Type) * DEFAULT_ARRAY_LIST_SIZE)))
        {}

        ArrayList(Allocator& aAllocator, const Index aSize) :
            mAllocator(&aAllocator),
            mHead(0),
            mSize(aSize),
            mData(static_cast<Type*>(aAllocator.allocate(sizeof(Type) * aSize)))
        {}

        ArrayList(const Self& aOther) :
            mAllocator(aOther.mAllocator),
            mHead(aOther.mHead),
            mSize(aOther.mSize),
            mData(static_cast<Type*>(aOther.mAllocator->allocate(sizeof(Type) * aOther.mSize)))
        {
            aOther.copyTo(mData);
        }

        ArrayList(Self&& aOther) :
            mAllocator(aOther.mAllocator),
            mHead(aOther.mHead),
            mSize(aOther.mSize),
            mData(aOther.mData)
        {
            aOther.mData = nullptr;
        }

        ArrayList(const StaticContainer<const Type>& aOther) :
            mAllocator(&aOther.getAllocator()),
            mHead(0),
            mSize(DEFAULT_ARRAY_LIST_SIZE),
            mData(static_cast<Type*>(aOther.getAllocator().allocate(sizeof(Type) *DEFAULT_ARRAY_LIST_SIZE)))
        {
            const auto end = aOther.end();
            for(auto i = aOther.begin(); i != end; ++i) pushBack(*i);
        }

        SOLAIRE_EXPORT_CALL ~ArrayList() {

                std::cout << std::endl << ((uint64_t) mAllocator) << " == " << ((uint64_t) &getDefaultAllocator()) <<
                    " = " << (mAllocator == &getDefaultAllocator() ? "true" : "false") << std::endl;
            if(mData != nullptr) {
                clear();
                mAllocator->deallocate(mData);
                mData = nullptr;
            }
        }

        Self& operator=(const Self& aOther) {
            if(mSize < aOther.mHead) {
                reallocate(aOther.mHead);
            }

            destructAll();
            aOther.copyTo(mData);
            mHead = aOther.mHead;

            return *this;
        }

        Self& operator=(Self&& aOther) {
            std::swap(mAllocator, aOther.mAllocator);
            std::swap(mHead, aOther.mHead);
            std::swap(mSize, aOther.mSize);
            std::swap(mData, aOther.mData);
            return *this;
        }

        // Inherited from StaticContainer

        bool SOLAIRE_EXPORT_CALL isContiguous() const throw() override {
            return true;
        }

        int32_t SOLAIRE_EXPORT_CALL size() const throw() override {
            return static_cast<int32_t>(mHead);
        }

        Allocator& SOLAIRE_EXPORT_CALL getAllocator() const throw() override {
            return *mAllocator;
        }

        // Inherited from Stack

		Type& SOLAIRE_EXPORT_CALL pushBack(const Type& aValue) throw() override {
            if(mHead == mSize) {
                reallocate(mSize * 2);
		    }
		    Type* const ptr = mData + mHead;
		    ++mHead;
		    new(ptr) Type(aValue);
            return *ptr;
        }

		Type SOLAIRE_EXPORT_CALL popBack() throw() {
		    --mHead;
		    Type& back = mData[mHead];
		    Type tmp = std::move(back);
		    back.~Type();
		    return tmp;
		}

		void SOLAIRE_EXPORT_CALL clear() throw() override {
            destructAll();
            mHead = 0;
        }

        // Inherited from Deque
		Type& SOLAIRE_EXPORT_CALL pushFront(const Type& aValue) throw() override {
		    if(mHead == 0) return pushBack(aValue);

            shiftUp(0);
            new(mData) Type(aValue);
            return *mData;
		}

		Type SOLAIRE_EXPORT_CALL popFront() throw() override {
		    Type& front = *mData;
            Type tmp = front;
            front.~Type();
            shiftDown(0);
            return tmp;
		}

		// Inherited from List

		Type& SOLAIRE_EXPORT_CALL insertBefore(const int32_t aPos, const Type& aValue) throw() override {
            shiftUp(aPos);
            Type* const ptr = mData + aPos;
            new(ptr) Type(aValue);
            return *ptr;
		}

		Type& SOLAIRE_EXPORT_CALL insertAfter(const int32_t aPos, const Type& aValue) throw() override {
            return insertBefore(aPos + 1, aValue);
		}

		bool SOLAIRE_EXPORT_CALL erase(const int32_t aPos) throw() override {
            return shiftDown(aPos);
		}

	};
}

#endif
