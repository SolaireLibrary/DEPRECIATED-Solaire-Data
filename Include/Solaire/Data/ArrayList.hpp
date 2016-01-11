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

#include <cstdint>
#include "Solaire/Core/Container.hpp"
#include "Solaire/Data/Iterators/ContiguousIterator.hpp"

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
	private:
        Allocator* mAllocator;
		Index mHead;
		Index mSize;
		Type* mData;
    private:
        bool CopyTo(Type* const aArray) const throw() {
            //std::cout << "CopyTo" << std::endl;
            const int32_t size = mHead;
            for(int32_t i = 0; i < size; ++i) {
                new(aArray + i) Type(mData[i]);
            }
            return true;
        }

        bool MoveTo(Type* const aArray) throw() {
            //std::cout << "MoveTo" << std::endl;
            const int32_t size = mHead;
            for(int32_t i = 0; i < size; ++i) {
                new(aArray + i) Type(std::move(mData[i]));
                mData[i].~Type();
            }
            return true;
        }

        bool DestructAll() throw() {
            //std::cout << "DestructAll" << std::endl;
            const int32_t size = mHead;
            for(int32_t i = 0; i < size; ++i) {
                mData[i].~Type();
            }
            return true;
        }

        bool ShiftUp(const int32_t aIndex) throw() {
            //std::cout << "ShiftUp" << std::endl;
            // Create a new object at the end of the list
            PushBack(mData[mHead - 1]);

            // Shift up existing objects
            const int32_t head = mHead - 1;
            for(int32_t i = head; i > aIndex; --i) {
                Type& high = mData[i];
                Type& low = mData[i - 1];
                high = std::move(low);
            }

            return true;
        }

        bool ShiftDown(const int32_t aIndex) throw() {
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

        bool Reallocate(const Index aSize) throw() {
            //std::cout << "Reallocate" << std::endl;
            Type* const ptr = static_cast<Type*>(mAllocator->Allocate(sizeof(Type) * aSize));
            if(! MoveTo(ptr)) {
                mAllocator->Deallocate(ptr);
                return false;
            }
            mAllocator->Deallocate(mData);
            mData = ptr;
            mSize = aSize;
            return true;
        }
    protected:
        // Inherited from StaticContainer

        Pointer SOLAIRE_EXPORT_CALL GetPtr(int32_t aOffset) throw() override {
            return mData + aOffset;
        }

        SharedAllocation<Iterator<Type>> SOLAIRE_EXPORT_CALL Begin() throw() override {
            //! \todo Implement iterator
            //return mAllocator->SharedAllocate<ContiguousIterator>(*mAllocator, mData, 0);
            return SharedAllocation<Iterator<Type>>();
        }

        SharedAllocation<Iterator<Type>> SOLAIRE_EXPORT_CALL End() throw() override {
            //! \todo Implement iterator
            //return mAllocator->SharedAllocate<ContiguousIterator>(*mAllocator, mData, mHead);
            return SharedAllocation<Iterator<Type>>();
        }

        SharedAllocation<Iterator<Type>> SOLAIRE_EXPORT_CALL Rbegin() throw() override {
            //! \todo Implement reverse iterator
            return SharedAllocation<Iterator<Type>>();
        }

        SharedAllocation<Iterator<Type>> SOLAIRE_EXPORT_CALL Rend() throw() override {
            //! \todo Implement reverse iterator
            return SharedAllocation<Iterator<Type>>();
        }

    public:
        ArrayList(Allocator& aAllocator) :
            mAllocator(&aAllocator),
            mHead(0),
            mSize(DEFAULT_ARRAY_LIST_SIZE),
            mData(static_cast<Type*>(aAllocator.Allocate(sizeof(Type) * DEFAULT_ARRAY_LIST_SIZE)))
        {}

        ArrayList(Allocator& aAllocator, const Index aSize) :
            mAllocator(&aAllocator),
            mHead(0),
            mSize(aSize),
            mData(static_cast<Type*>(aAllocator.Allocate(sizeof(Type) * aSize)))
        {}

        ArrayList(const Self& aOther) :
            mAllocator(aOther.mAllocator),
            mHead(aOther.mHead),
            mSize(aOther.mSize),
            mData(static_cast<Type*>(aOther.mAllocator->Allocate(sizeof(Type) * aOther.mSize)))
        {
            aOther.CopyTo(mData);
        }

        ArrayList(Self&& aOther) :
            mAllocator(aOther.mAllocator),
            mHead(aOther.mHead),
            mSize(aOther.mSize),
            mData(aOther.mData)
        {
            aOther.mData = nullptr;
        }

        SOLAIRE_EXPORT_CALL ~ArrayList() {
            if(mData != nullptr) {
                Clear();
                mAllocator->Deallocate(mData);
                mData = nullptr;
            }
        }

        Self& operator=(const Self& aOther) {
            if(mSize < aOther.mHead) {
                Reallocate(aOther.mHead);
            }

            DestructAll();
            aOther.CopyTo(mData);
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

        bool SOLAIRE_EXPORT_CALL IsContiguous() const throw() override {
            return true;
        }

        int32_t SOLAIRE_EXPORT_CALL Size() const throw() override {
            return static_cast<int32_t>(mHead);
        }

        Allocator& SOLAIRE_EXPORT_CALL GetAllocator() const throw() override {
            return *mAllocator;
        }

        // Inherited from Stack

		Type& SOLAIRE_EXPORT_CALL PushBack(const Type& aValue) throw() override {
            if(mHead == mSize) {
                Reallocate(mSize * 2);
		    }
		    Type* const ptr = mData + mHead;
		    ++mHead;
		    new(ptr) Type(aValue);
            return *ptr;
        }

		Type SOLAIRE_EXPORT_CALL PopBack() throw() {
		    --mHead;
		    Type& back = mData[mHead];
		    Type tmp = std::move(back);
		    back.~Type();
		    return tmp;
		}

		void SOLAIRE_EXPORT_CALL Clear() throw() override {
            DestructAll();
            mHead = 0;
        }

        // Inherited from Deque
		Type& SOLAIRE_EXPORT_CALL PushFront(const Type& aValue) throw() override {
		    if(mHead == 0) return PushBack(aValue);

            ShiftUp(0);
            new(mData) Type(aValue);
            return *mData;
		}

		Type SOLAIRE_EXPORT_CALL PopFront() throw() override {
		    Type& front = *mData;
            Type tmp = front;
            front.~Type();
            ShiftDown(0);
            return tmp;
		}

		// Inherited from List

		Type& SOLAIRE_EXPORT_CALL InsertBefore(const int32_t aPos, const Type& aValue) throw() override {
            ShiftUp(aPos);
            Type* const ptr = mData + aPos;
            new(ptr) Type(aValue);
            return *ptr;
		}

		Type& SOLAIRE_EXPORT_CALL InsertAfter(const int32_t aPos, const Type& aValue) throw() override {
            return InsertBefore(aPos + 1, aValue);
		}

		bool SOLAIRE_EXPORT_CALL Erase(const int32_t aPos) throw() override {
            return ShiftDown(aPos);
		}

	};
}

#endif
