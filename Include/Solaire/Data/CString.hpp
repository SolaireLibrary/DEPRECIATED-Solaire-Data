#ifndef SOLAIRE_CSTRING_HPP
#define SOLAIRE_CSTRING_HPP

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
	\file CString.hpp
	\brief
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\date
	Created			: 12th January 2016
	Last Modified	: 12th January 2016
*/

#include "Solaire/Data/ArrayList.hpp"

namespace Solaire{

    template<class TYPE, const TYPE TERMINATOR = '\0', class INDEX = uint16_t>
	class CString : public List<TYPE> {
	public:
		typedef TYPE Type;
		typedef const TYPE ConstType;
		typedef Type& Reference;
		typedef ConstType& ConstReference;
		typedef Type&& Move;
		typedef Type* Pointer;
		typedef ConstType* ConstPointer;
		typedef INDEX Index;
		typedef CString<TYPE, TERMINATOR, INDEX> Self;
	private:
	    ArrayList<TYPE, INDEX> mData;
    protected:
        // Inherited from StaticContainer

        Pointer SOLAIRE_EXPORT_CALL getPtr(int32_t aOffset) throw() override {
            return mData.getPtr(aOffset);
        }

        SharedAllocation<Iterator<Type>> SOLAIRE_EXPORT_CALL begin_() throw() override {
            return mData.begin_();
        }

        SharedAllocation<Iterator<Type>> SOLAIRE_EXPORT_CALL end_() throw() override {
            SharedAllocation<Iterator<Type>> tmp = mData.begin_();
            --tmp;
            return tmp;
        }

        SharedAllocation<Iterator<Type>> SOLAIRE_EXPORT_CALL rbegin_() throw() override {
            SharedAllocation<Iterator<Type>> tmp = mData.rbegin_();
            ++tmp;
            return tmp;
        }

        SharedAllocation<Iterator<Type>> SOLAIRE_EXPORT_CALL rend_() throw() override {
             return mData.rend_();
        }

    public:
        CString(Allocator& aAllocator) :
            mData(aAllocator)
        {}

        CString(const Self& aOther) :
            mData(aOther)
        {}

        CString(Self&& aOther) :
            mData(std::move(aOther.mData))
        {}

        SOLAIRE_EXPORT_CALL ~CString() {

        }

        Self& operator=(const Self& aOther) {
            mData = aOther.mData;
            return *this;
        }

        Self& operator=(Self&& aOther) {
            mData = std::move(aOther.mData);
            return *this;
        }

        // Inherited from StaticContainer

        bool SOLAIRE_EXPORT_CALL isContiguous() const throw() override {
            return true;
        }

        int32_t SOLAIRE_EXPORT_CALL size() const throw() override {
            return mData.size() - 1;
        }

        Allocator& SOLAIRE_EXPORT_CALL getAllocator() const throw() override {
            return mData.getAllocator();
        }

        // Inherited from Stack

		Type& SOLAIRE_EXPORT_CALL pushBack(const Type& aValue) throw() override {
            Type& ref = pushBack.back() = aValue;
            mData.pushBack(TERMINATOR);
            return ref;
        }

		Type SOLAIRE_EXPORT_CALL popBack() throw() {
		    return mData.popBack();
		}

		void SOLAIRE_EXPORT_CALL clear() throw() override {
            mData.clear();
            mData.pushBack(TERMINATOR);
        }

        // Inherited from Deque

		Type& SOLAIRE_EXPORT_CALL pushFront(const Type& aValue) throw() override {
		    return mData.pushFront(aValue);
		}

		Type SOLAIRE_EXPORT_CALL popFront() throw() override {
		    return mData.size() == 1 ? TERMINATOR : mData.popFront();
		}

		// Inherited from List

		Type& SOLAIRE_EXPORT_CALL insertBefore(const int32_t aPos, const Type& aValue) throw() override {
		    //! \todo Protect terminator
            return mData.insertBefore(aPos, aValue);
		}

		Type& SOLAIRE_EXPORT_CALL insertAfter(const int32_t aPos, const Type& aValue) throw() override {
		    //! \todo Protect terminator
            return mData.insertAfter(aPos, aValue);
		}

		bool SOLAIRE_EXPORT_CALL erase(const int32_t aPos) throw() override {
		    //! \todo Protect terminator
            return mData.erase(aPos);
		}

	};
}

#endif
