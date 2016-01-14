#ifndef SOLAIRE_LINKED_LIST_HPP
#define SOLAIRE_LINKED_LIST_HPP

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
	\file LinkedList.hpp
	\brief
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\date
	Created			: 14th January 2016
	Last Modified	: 14th January 2016
*/

#include <cstdint>
#include "Solaire/Core/Container.hpp"

namespace Solaire{

    template<class T>
    struct LinkedNode {
        SharedAllocation<LinkedNode<T>> Previous;
        SharedAllocation<LinkedNode<T>> Next;
        T Value;

        LinkedNode(const T& aValue) :
            Previous(),
            Next(),
            Value(aValue)
        {}
    };

    template<class TYPE>
	class LinkedList : public List<TYPE> {
	public:
		typedef TYPE Type;
		typedef const TYPE ConstType;
		typedef Type& Reference;
		typedef ConstType& ConstReference;
		typedef Type&& Move;
		typedef Type* Pointer;
		typedef ConstType* ConstPointer;
		typedef LinkedList<TYPE> Self;
	private:
        SharedAllocation<LinkedNode<TYPE>> mFront;
        SharedAllocation<LinkedNode<TYPE>> mBack;
        Allocator* mAllocator;
        int32_t mSize;
    private:
        SharedAllocation<LinkedNode<TYPE>> getNode(int32_t aOffset) throw() {
            SharedAllocation<LinkedNode<TYPE>> n = mFront;
            while(aOffset != 0) {
                if(n == nullptr) break;
                n = n->Next;
                --aOffset;
            }
            return n;
        }
    protected:
        // Inherited from StaticContainer

        Pointer SOLAIRE_EXPORT_CALL getPtr(int32_t aOffset) throw() override {
            return &getNode(aOffset)->Value;
        }

        SharedAllocation<Iterator<Type>> SOLAIRE_EXPORT_CALL begin_() throw() override {
            //! \todo Implement begin_
        }

        SharedAllocation<Iterator<Type>> SOLAIRE_EXPORT_CALL end_() throw() override {
            //! \todo Implement end_
        }

        SharedAllocation<Iterator<Type>> SOLAIRE_EXPORT_CALL rbegin_() throw() override {
            //! \todo Implement rbegin_
        }

        SharedAllocation<Iterator<Type>> SOLAIRE_EXPORT_CALL rend_() throw() override {
            //! \todo Implement rend_
        }

    public:
        LinkedList() :
            mFront(),
            mBack(),
            mAllocator(&DEFAULT_ALLOCATOR),
            mSize(0)
        {}

        LinkedList(Allocator& aAllocator) :
            mFront(),
            mBack(),
            mAllocator(&aAllocator),
            mSize(0)
        {}

        LinkedList(const Self& aOther) :
            mFront(),
            mBack(),
            mAllocator(aOther.mAllocator),
            mSize(0)
        {
            SharedAllocation<LinkedNode<TYPE>> n = aOther.Front;
            for(int32_t i = 1; i < mSize; ++i) {
                pushBack(n->Value);
                n = n->Next;
            }
        }

        LinkedList(Self&& aOther) :
            mFront(aOther.mFront),
            mBack(aOther.mBack),
            mAllocator(aOther.mAllocator),
            mSize(aOther.mSize)
        {
            aOther.mFront = SharedAllocation<LinkedNode<TYPE>>();
            aOther.mBack = SharedAllocation<LinkedNode<TYPE>>();
            aOther.mSize = 0;
        }

        SOLAIRE_EXPORT_CALL ~LinkedList() {
            clear();
        }

        Self& operator=(const Self& aOther) {
            mFront = SharedAllocation<LinkedNode<TYPE>>();
            mBack = SharedAllocation<LinkedNode<TYPE>>();
            mSize = 0;
            SharedAllocation<LinkedNode<TYPE>> n = aOther.Front;
            for(int32_t i = 1; i < mSize; ++i) {
                pushBack(n->Value);
                n = n->Next;
            }
            return *this;
        }

        Self& operator=(Self&& aOther) {
            mFront.swap(aOther.mFront);
            mBack.swap(aOther.mBack);
            std::swap(mSize, aOther.mSize);
            std::swap(mAllocator, mAllocator);
            return *this;
        }

        // Inherited from StaticContainer

        bool SOLAIRE_EXPORT_CALL isContiguous() const throw() override {
            return false;
        }

        int32_t SOLAIRE_EXPORT_CALL size() const throw() override {
            return mSize;
        }

        Allocator& SOLAIRE_EXPORT_CALL getAllocator() const throw() override {
            return *mAllocator;
        }

        // Inherited from Stack

		Type& SOLAIRE_EXPORT_CALL pushBack(const Type& aValue) throw() override {
		    SharedAllocation<LinkedNode<TYPE>> n = mAllocator->sharedAllocate<LinkedNode<TYPE>>(aValue);
            if(mBack == nullptr) {
                mFront = n;
                mBack = n;
            }else{
                SharedAllocation<LinkedNode<TYPE>> b = mBack;
                mBack = n;
                b->Next = n;
                n->Previous = b;
            }
            ++mSize;
            return n->Value;
        }

		Type SOLAIRE_EXPORT_CALL popBack() throw() {
            SharedAllocation<LinkedNode<TYPE>> n = mBack;
            if(mSize == 1) {
                mFront = SharedAllocation<LinkedNode<TYPE>>();
                mBack = SharedAllocation<LinkedNode<TYPE>>();
                mSize = 0;
            }else {
                mBack = n->Previous;
                mBack->Next = SharedAllocation<LinkedNode<TYPE>>();
                --mSize;
            }
            return n->Value;
		}

		void SOLAIRE_EXPORT_CALL clear() throw() override {
            mFront = SharedAllocation<LinkedNode<TYPE>>();
            mBack = SharedAllocation<LinkedNode<TYPE>>();
            mSize = 0;
        }

        // Inherited from Deque

		Type& SOLAIRE_EXPORT_CALL pushFront(const Type& aValue) throw() override {
		    SharedAllocation<LinkedNode<TYPE>> n = mAllocator->sharedAllocate<LinkedNode<TYPE>>(aValue);
            if(mFront == nullptr) {
                mFront = n;
                mBack = n;
            }else{
                SharedAllocation<LinkedNode<TYPE>> f = mFront;
                mFront = n;
                f->Previous = n;
                n->Next = f;
            }
            ++mSize;
            return n->Value;
		}

		Type SOLAIRE_EXPORT_CALL popFront() throw() override {
            SharedAllocation<LinkedNode<TYPE>> n = mFront;
            if(mSize == 1) {
                mFront = SharedAllocation<LinkedNode<TYPE>>();
                mBack = SharedAllocation<LinkedNode<TYPE>>();
                mSize = 0;
            }else {
                mFront = n->Next;
                mFront->Previous = SharedAllocation<LinkedNode<TYPE>>();
                --mSize;
            }
            return n->Value;
		}

		// Inherited from List

		Type& SOLAIRE_EXPORT_CALL insertBefore(const int32_t aPos, const Type& aValue) throw() override {
		    SharedAllocation<LinkedNode<TYPE>> before = getNode(aPos)->Previous;
		    if(before == nullptr) return aValue;
		    SharedAllocation<LinkedNode<TYPE>> after = before->Next;
		    SharedAllocation<LinkedNode<TYPE>> n = mAllocator->sharedAllocate<LinkedNode<TYPE>>(aValue);

		    n->Previous = before;
		    n->Next = after;
		    before->Next = n;
		    if(after != nullptr) after->Previous = n;

		    if(before == mFront) mFront = n;
		    if(after == mBack) mBack = n;

		    ++mSize;

            return n->Value;
		}

		Type& SOLAIRE_EXPORT_CALL insertAfter(const int32_t aPos, const Type& aValue) throw() override {
		    return insertBefore(aPos + 1, aValue);
		}

		bool SOLAIRE_EXPORT_CALL erase(const int32_t aPos) throw() override {
		    SharedAllocation<LinkedNode<TYPE>> n = getNode(aPos);
		    if(n == nullptr) return false;
		    SharedAllocation<LinkedNode<TYPE>> before = n->Previous;
		    SharedAllocation<LinkedNode<TYPE>> after = n->Next;

		    if(before != nullptr) before->Next = after;
		    if(after != nullptr) after->Previous = before;

		    if(mFront == n) mFront = after;
		    if(mBack == n) mBack = before;

            --mSize;

		    return true;
		}

	};
}

#endif
