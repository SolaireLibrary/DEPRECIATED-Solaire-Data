#ifndef SOLAIRE_DATA_DIRECTORY_HPP
#define SOLAIRE_DATA_DIRECTORY_HPP

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
	\file Directory.hpp
	\brief
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\version 1.0
	\date
	Created			: 15th November 2016
	Last Modified	: 15th January 2016
*/

#include "Solaire\Data\File.hpp"

namespace Solaire {

    class Directory {
    private:
        CString mPath;
    public:
        Directory(const StringConstant<char>&);

        bool exists() const throw();
        bool create() throw();
        bool delete_() throw();
        ArrayList<File> getFiles() const throw();
        ArrayList<Directory> getDirectories() const throw();
        CString getPath() const throw();
        bool rename(const StringConstant<char>&) throw();
        bool copy(const StringConstant<char>&) const throw();
        bool move(const StringConstant<char>&) throw();
    };

}

#endif
