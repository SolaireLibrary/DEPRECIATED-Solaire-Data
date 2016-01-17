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

#include "Solaire/Core/String.hpp"
#include "Solaire/Data/ArrayList.hpp"

namespace Solaire{

	class CString : public String<char> {
	public:
		typedef char Type;
		typedef const char ConstType;
		typedef Type& Reference;
		typedef ConstType& ConstReference;
		typedef Type&& Move;
		typedef Type* Pointer;
		typedef ConstType* ConstPointer;
		typedef uint32_t Index;
		typedef CString Self;
	private:
	    ArrayList<char, uint32_t> mData;
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
            tmp->decrement(1);
            return tmp;
        }

        SharedAllocation<Iterator<Type>> SOLAIRE_EXPORT_CALL rbegin_() throw() override {
            SharedAllocation<Iterator<Type>> tmp = mData.rbegin_();
            tmp->increment(1);
            return tmp;
        }

        SharedAllocation<Iterator<Type>> SOLAIRE_EXPORT_CALL rend_() throw() override {
             return mData.rend_();
        }

    public:
        CString() :
            mData()
        {
            mData.pushBack('\0');
        }

        CString(Allocator& aAllocator) :
            mData(aAllocator)
        {
            mData.pushBack('\0');
        }

        CString(const Self& aOther) :
            mData(aOther.mData)
        {}

        CString(Self&& aOther) :
            mData(std::move(aOther.mData))
        {}

        template<size_t LENGTH>
        CString(const Type(&aString)[LENGTH]) :
            mData(getDefaultAllocator(), LENGTH)
        {
            std::memcpy(mData.getPtr(0), aString, LENGTH);
            mData.mHead = LENGTH;
        }

        template<size_t LENGTH>
        CString(Allocator& aAllocator, const Type(&aString)[LENGTH]) :
            mData(aAllocator, LENGTH)
        {
            std::strcpy(mData.getPtr(0), aString, LENGTH);
            mData.mHead = LENGTH;
        }

        CString(const StringConstant<char>& aOther) :
            mData(getDefaultAllocator(), aOther.size() + 1)
        {
            const int32_t size = aOther.size();
            if(aOther.isContiguous()) {
                std::memcpy(mData.getPtr(0), &aOther[0], size);
            }else {
                for(int32_t i = 0; i < size; ++i) mData[i] = aOther[0];
            }
            mData[size] = '\0';
            mData.mHead = size + 1;
        }

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
            Type& ref = mData[mData.size() - 1] = aValue;
            mData.pushBack('\0');
            return ref;
        }

		Type SOLAIRE_EXPORT_CALL popBack() throw() {
		    return mData.popBack();
		}

		void SOLAIRE_EXPORT_CALL clear() throw() override {
            mData.clear();
            mData.pushBack('\0');
        }

        // Inherited from Deque

		Type& SOLAIRE_EXPORT_CALL pushFront(const Type& aValue) throw() override {
		    return mData.pushFront(aValue);
		}

		Type SOLAIRE_EXPORT_CALL popFront() throw() override {
		    return mData.size() == 1 ? '\0' : mData.popFront();
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
