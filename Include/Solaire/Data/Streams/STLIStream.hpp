#ifndef SOLAIRE_STL_ISTREAM_HPP
#define SOLAIRE_STL_ISTREAM_HPP

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
	\file STLIStream.hpp
	\brief
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\date
	Created			: 12th January 2016
	Last Modified	: 12th January 2016
*/

#include <istream>
#include "Solaire/Core/IStream.hpp"

namespace Solaire {

	class STLIStream : public IStream {
    private:
        std::istream& mStream;
    private:
        // Inherited from IStream

        uint8_t SOLAIRE_EXPORT_CALL readU8() throw() override {
            uint8_t value;
            mStream >> value;
            return value;
        }

        uint16_t SOLAIRE_EXPORT_CALL readU16() throw() override {
            uint16_t value;
            mStream >> value;
            return value;
        }

        uint32_t SOLAIRE_EXPORT_CALL readU32() throw() override {
            uint32_t value;
            mStream >> value;
            return value;
        }

        uint64_t SOLAIRE_EXPORT_CALL readU64() throw() override {
            uint64_t value;
            mStream >> value;
            return value;
        }

        int8_t SOLAIRE_EXPORT_CALL readI8() throw() override {
            int8_t value;
            mStream >> value;
            return value;
        }

        int16_t SOLAIRE_EXPORT_CALL readI16() throw() override {
            int16_t value;
            mStream >> value;
            return value;
        }

        int32_t SOLAIRE_EXPORT_CALL readI32() throw() override {
            int32_t value;
            mStream >> value;
            return value;
        }

        int64_t SOLAIRE_EXPORT_CALL readI64() throw() override {
            int64_t value;
            mStream >> value;
            return value;
        }

        float SOLAIRE_EXPORT_CALL readF() throw() override {
            float value;
            mStream >> value;
            return value;
        }

        double SOLAIRE_EXPORT_CALL readD() throw() override {
            double value;
            mStream >> value;
            return value;
        }

        char SOLAIRE_EXPORT_CALL readC() throw() override {
            char value;
            mStream >> value;
            return value;
        }

    public:
        STLIStream(std::istream& aStream) :
            mStream(aStream)
        {}

        SOLAIRE_EXPORT_CALL ~STLIStream() {

        }

        // Inherited from IStream

        void SOLAIRE_EXPORT_CALL read(void* const aAddress, const uint32_t aBytes) throw() override {
            mStream.read(static_cast<char*>(aAddress), aBytes);
        }

        bool SOLAIRE_EXPORT_CALL isOffsetable() const throw() override {
            //! \todo Check if mStream is offsetable
            return true;
        }

        int32_t SOLAIRE_EXPORT_CALL getOffset() const throw() override {
            return mStream.tellg();
        }

        bool SOLAIRE_EXPORT_CALL setOffset(const int32_t aOffset) throw() override {
            mStream.seekg(aOffset, std::ios::beg);
            return true;
        }

        bool SOLAIRE_EXPORT_CALL end() const throw() override {
            return mStream.eof();
        }

    };

}

#endif
