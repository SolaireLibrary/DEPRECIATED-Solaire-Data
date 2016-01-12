#ifndef SOLAIRE_STL_OSTREAM_HPP
#define SOLAIRE_STL_OSTREAM_HPP

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
	\file STLOStream.hpp
	\brief
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\date
	Created			: 12th January 2016
	Last Modified	: 12th January 2016
*/

#include <ostream>
#include "Solaire/Core/OStream.hpp"


namespace Solaire {

	class STLOStream : public OStream {
    private:
        std::ostream& mStream;
    private:
        // Inherited from OStream

        void SOLAIRE_EXPORT_CALL writeU8(const uint8_t aValue) throw() override {
            mStream << aValue;
        }

        void SOLAIRE_EXPORT_CALL writeU16(const uint16_t aValue) throw() override {
            mStream << aValue;
        }

        void SOLAIRE_EXPORT_CALL writeU32(const uint32_t aValue) throw() override {
            mStream << aValue;
        }

        void SOLAIRE_EXPORT_CALL writeU64(const uint64_t aValue) throw() override {
            mStream << aValue;
        }

        void SOLAIRE_EXPORT_CALL writeI8(const int8_t aValue) throw() override {
            mStream << aValue;
        }

        void SOLAIRE_EXPORT_CALL writeI16(const int16_t aValue) throw() override {
            mStream << aValue;
        }

        void SOLAIRE_EXPORT_CALL writeI32(const int32_t aValue) throw() override {
            mStream << aValue;
        }

        void SOLAIRE_EXPORT_CALL writeI64(const int64_t aValue) throw() override {
            mStream << aValue;
        }

        void SOLAIRE_EXPORT_CALL writeF(const float aValue) throw() override {
            mStream << aValue;
        }

        void SOLAIRE_EXPORT_CALL writeD(const double aValue) throw() override {
            mStream << aValue;
        }

        void SOLAIRE_EXPORT_CALL writeC(const char aValue) throw() override {
            mStream << aValue;
        }

    public:
        STLOStream(std::ostream& aStream) :
            mStream(aStream)
        {}

        SOLAIRE_EXPORT_CALL ~STLOStream() {

        }

        // Inherited from OStream

        void SOLAIRE_EXPORT_CALL write(const void* const aPtr, const uint32_t aBytes) throw() override {
            mStream.write(static_cast<const char*>(aPtr), aBytes);
        }

        bool SOLAIRE_EXPORT_CALL isOffsetable() const throw() override {
            //! \todo Check if mStream is offsetable
            return true;
        }

        int32_t SOLAIRE_EXPORT_CALL getOffset() const throw() override {
            return mStream.tellp();
        }

        bool SOLAIRE_EXPORT_CALL setOffset(const int32_t aOffset) throw() override {
            mStream.seekp(aOffset, std::ios::beg);
            return true;
        }

    };

    static STLOStream STD_OUT(std::cout);
    static STLOStream STD_ERR(std::cerr);
    static constexpr char END_LINE = '\n';

}

#endif
