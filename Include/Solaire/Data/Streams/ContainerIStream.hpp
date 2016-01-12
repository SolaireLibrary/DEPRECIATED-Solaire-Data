#ifndef SOLAIRE_CONTAINER_ISTREAM_HPP
#define SOLAIRE_CONTAINER_ISTREAM_HPP

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
	\file ComtaomerIStream.hpp
	\brief
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\date
	Created			: 20th November 2015
	Last Modified	: 12th January 2016
*/

#include "Solaire/Core/IStream.hpp"
#include "Solaire/Core/Container.hpp"

namespace Solaire {

	SOLAIRE_EXPORT_INTERFACE ContainerIStream : public IStream {
    private:
        StaticContainer<uint8_t>& mContainer;
        int32_t mOffset;
    private:
        void SOLAIRE_EXPORT_CALL read_(void* const aPtr, const uint32_t aBytes) throw() {
            uint8_t* const ptr = static_cast<uint8_t*>(aPtr);
            for(uint32_t i = 0; i < aBytes; ++i) {
                ptr[i] = mContainer[mOffset++];
            }
        }
        // Inherited from IStream

        uint8_t SOLAIRE_EXPORT_CALL readU8() throw() override {
            return mContainer[mOffset++];
        }

        uint16_t SOLAIRE_EXPORT_CALL readU16() throw() override {
            uint16_t value = 0;
            read_(&value, sizeof(uint16_t));
            return value;
        }

        uint32_t SOLAIRE_EXPORT_CALL readU32() throw() override {
            uint32_t value = 0;
            read_(&value, sizeof(uint32_t));
            return value;
        }

        uint64_t SOLAIRE_EXPORT_CALL readU64() throw() override {
            uint64_t value = 0;
            read_(&value, sizeof(uint32_t));
            return value;
        }

        int8_t SOLAIRE_EXPORT_CALL readI8() throw() override {
            int8_t value = 0;
            read_(&value, sizeof(int8_t));
            return value;
        }

        int16_t SOLAIRE_EXPORT_CALL readI16() throw() override {
            int16_t value = 0;
            read_(&value, sizeof(int16_t));
            return value;
        }

        int32_t SOLAIRE_EXPORT_CALL readI32() throw() override {
            int32_t value = 0;
            read_(&value, sizeof(int32_t));
            return value;
        }

        int64_t SOLAIRE_EXPORT_CALL readI64() throw() override {
            int64_t value = 0;
            read_(&value, sizeof(int64_t));
            return value;
        }

        float SOLAIRE_EXPORT_CALL readF() throw() override {
            float value = 0.f;
            read_(&value, sizeof(float));
            return value;
        }

        double SOLAIRE_EXPORT_CALL readD() throw() override {
            double value = 0.0;
            read_(&value, sizeof(double));
            return value;
        }

        char SOLAIRE_EXPORT_CALL readC() throw() override {
            char value = 0;
            read_(&value, sizeof(char));
            return value;
        }

    public:
        ContainerIStream(StaticContainer<uint8_t>& aContainer) :
            mContainer(aContainer),
            mOffset(0)
        {}

        SOLAIRE_EXPORT_CALL ~ContainerIStream() {

        }

        // Inherited from IStream

        void SOLAIRE_EXPORT_CALL read(void* const aAddress, const uint32_t aBytes) throw() override {
            read_(aAddress, aBytes);
        }

        bool SOLAIRE_EXPORT_CALL isOffsetable() const throw() override {
            return true;
        }

        int32_t SOLAIRE_EXPORT_CALL getOffset() const throw() override {
            return mOffset;
        }

        bool SOLAIRE_EXPORT_CALL setOffset(const int32_t aOffset) throw() override {
            if(aOffset >= mContainer.size()) return false;
            mOffset = aOffset;
            return true;
        }

        bool SOLAIRE_EXPORT_CALL end() const throw() override {
            return mOffset >= mContainer.size();
        }

    };

}

#endif
