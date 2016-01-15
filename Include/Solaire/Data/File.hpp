#ifndef SOLAIRE_DATA_FILE_HPP
#define SOLAIRE_DATA_FILE_HPP

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
	\file File.hpp
	\brief
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\version 1.0
	\date
	Created			: 15th November 2016
	Last Modified	: 15th January 2016
*/

#include "Solaire\Core\File.hpp"
#include "Solaire\Data\CString.hpp"
#include "Solaire\Data\ArrayList.hpp"

namespace Solaire {

    class File {
    public:
        enum AccessMode : uint8_t {
            READ = FileImplementation::FLAG_READ,
            WRITE = FileImplementation::FLAG_WRITE,
            READ_WRITE = READ | WRITE
        };
    private:
        CString mPath;
    public:
        File(const StringConstant<char>&);

        bool exists() const throw();
        bool create(const AccessMode) throw();
        bool delete_() throw();
        int32_t size() const throw();
        CString getPath() const throw();
        CString getName() const throw();
        CString getExtention() const throw();
        bool rename(const StringConstant<char>&) throw();
        bool copy(const StringConstant<char>&) const throw();
        bool move(const StringConstant<char>&) throw();
        AccessMode getAccessMode() const throw();
    };

}

#endif
