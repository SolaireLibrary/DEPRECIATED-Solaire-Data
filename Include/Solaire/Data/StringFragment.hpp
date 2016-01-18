#ifndef SOLAIRE_STRING_FRAGMENT_HPP
#define SOLAIRE_STRING_FRAGMENT_HPP

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

    template<class T>
	class StringFragment : public StringConstant<T> {
	public:
		typedef char Type;
		typedef const char ConstType;
		typedef Type& Reference;
		typedef ConstType& ConstReference;
		typedef Type&& Move;
		typedef Type* Pointer;
		typedef ConstType* ConstPointer;
		typedef uint32_t Index;
		typedef StringFragment<T> Self;
	private:
	    StringConstant<T>* mString;
	    int32_t mBegin;
	    int32_t mEnd;
    protected:
        // Inherited from StaticContainer

        Pointer SOLAIRE_EXPORT_CALL getPtr(int32_t aOffset) throw() override {
            return mString->getPtr(mBegin + aOffset);
        }

        SharedAllocation<Iterator<Type>> SOLAIRE_EXPORT_CALL begin_() throw() override {
            SharedAllocation<Iterator<Type>> it = mString->begin_();
            it->increment(mBegin);
            return it;
        }

        SharedAllocation<Iterator<Type>> SOLAIRE_EXPORT_CALL end_() throw() override {
            SharedAllocation<Iterator<Type>> it = mString->begin_();
            it->increment(mEnd);
            return it;
        }

        SharedAllocation<Iterator<Type>> SOLAIRE_EXPORT_CALL rbegin_() throw() override {
            SharedAllocation<Iterator<Type>> it = mString->rbegin();
            it->increment(mString.size() - mEnd);
            return it;
        }

        SharedAllocation<Iterator<Type>> SOLAIRE_EXPORT_CALL rend_() throw() override {
            SharedAllocation<Iterator<Type>> it = mString->rbegin();
            it->increment(mString.size() - mBegin);
            return it;
        }

    public:
        StringFragment(StringConstant<T>& aString, const int32_t aBegin) :
            mString(&aString),
            mBegin(aBegin),
            mEnd(aString.size())
        {}

        StringFragment(StringConstant<T>& aString, const int32_t aBegin, const int32_t aEnd) :
            mString(&aString),
            mBegin(aBegin),
            mEnd(aEnd)
        {}

        StringFragment(const Self& aOther) :
            mString(aOther.mString),
            mBegin(aOther.mBegin),
            mEnd(aOther.mEnd)
        {}

        StringFragment(Self&& aOther) :
            mString(aOther.mString),
            mBegin(aOther.mBegin),
            mEnd(aOther.mEnd)
        {}

        SOLAIRE_EXPORT_CALL ~StringFragment() {

        }

        Self& operator=(const Self& aOther) {
            mString = aOther.mString;
            mBegin = aOther.mBegin;
            mEnd = aOther.mEnd;
            return *this;
        }

        Self& operator=(Self&& aOther) {
            mString = aOther.mString;
            mBegin = aOther.mBegin;
            mEnd = aOther.mEnd;
            return *this;
        }

        // Inherited from StaticContainer

        bool SOLAIRE_EXPORT_CALL isContiguous() const throw() override {
            return mString->isContiguous();
        }

        int32_t SOLAIRE_EXPORT_CALL size() const throw() override {
            return mEnd - mBegin;
        }

        Allocator& SOLAIRE_EXPORT_CALL getAllocator() const throw() override {
            return mString->getAllocator();
        }

	};
}

#endif
