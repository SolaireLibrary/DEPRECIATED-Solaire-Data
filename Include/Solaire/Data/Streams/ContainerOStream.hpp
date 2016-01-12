#ifndef SOLAIRE_CONTAINER_OSTREAM_HPP
#define SOLAIRE_CONTAINER_OSTREAM_HPP

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
	\file ContainerOStream.hpp
	\brief
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\date
	Created			: 20th November 2015
	Last Modified	: 12th January 2016
*/

#include "Solaire/Core/OStream.hpp"
#include "Solaire/Core/Container.hpp"


namespace Solaire {

	SOLAIRE_EXPORT_INTERFACE ContainerOStream : public OStream {
    private:
        Stack<uint8_t>& mContainer;
        int32_t mOffset;
    private:
        void write_(const void* const aPtr, const uint32_t aBytes) throw() {
            const uint8_t* const ptr = static_cast<const uint8_t*>(aPtr);
            for(uint32_t i = 0; i < aBytes; ++i) {
                const int32_t offset = mOffset + aBytes;
                if(offset < mContainer.size()) {
                    mContainer[offset] = ptr[i];
                }else {
                    mContainer.pushBack(ptr[i]);
                }
            }
            mOffset += aBytes;
        }

        // Inherited from OStream

        void SOLAIRE_EXPORT_CALL writeU8(const uint8_t aValue) throw() override {
            write_(&aValue, sizeof(uint8_t));
        }

        void SOLAIRE_EXPORT_CALL writeU16(const uint16_t aValue) throw() override {
            write_(&aValue, sizeof(uint16_t));
        }

        void SOLAIRE_EXPORT_CALL writeU32(const uint32_t aValue) throw() override {
            write_(&aValue, sizeof(uint32_t));
        }

        void SOLAIRE_EXPORT_CALL writeU64(const uint64_t aValue) throw() override {
            write_(&aValue, sizeof(uint64_t));
        }

        void SOLAIRE_EXPORT_CALL writeI8(const int8_t aValue) throw() override {
            write_(&aValue, sizeof(int8_t));
        }

        void SOLAIRE_EXPORT_CALL writeI16(const int16_t aValue) throw() override {
            write_(&aValue, sizeof(int16_t));
        }

        void SOLAIRE_EXPORT_CALL writeI32(const int32_t aValue) throw() override {
            write_(&aValue, sizeof(int32_t));
        }

        void SOLAIRE_EXPORT_CALL writeI64(const int64_t aValue) throw() override {
            write_(&aValue, sizeof(int64_t));
        }

        void SOLAIRE_EXPORT_CALL writeF(const float aValue) throw() override {
            write_(&aValue, sizeof(float));
        }

        void SOLAIRE_EXPORT_CALL writeD(const double aValue) throw() override {
            write_(&aValue, sizeof(double));
        }

        void SOLAIRE_EXPORT_CALL writeC(const char aValue) throw() override {
            write_(&aValue, sizeof(char));
        }

    public:
        ContainerOStream(Stack<uint8_t>& aContainer) :
            mContainer(aContainer),
            mOffset(0)
        {}

        SOLAIRE_EXPORT_CALL ~ContainerOStream() {

        }

        // Inherited from OStream

        void SOLAIRE_EXPORT_CALL write(const void* const aPtr, const uint32_t aBytes) throw() override {
            write_(aPtr, aBytes);
        }

        bool SOLAIRE_EXPORT_CALL isOffsetable() const throw() override {
            return true;
        }

        int32_t SOLAIRE_EXPORT_CALL getOffset() const throw() override {
            return mOffset;
        }

        bool SOLAIRE_EXPORT_CALL setOffset(const int32_t aOffset) throw() override {
            for(int32_t i = mContainer.size(); i < aOffset; ++i) {
                mContainer.pushBack(0);
            }
            mOffset = aOffset;
            return true;
        }

    };

}

#endif
