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

#include "Solaire\Data\File.hpp"

namespace Solaire {

    // File
    File::File(const StringConstant<char>& aPath) :
        mPath(aPath)
    {}

    bool File::exists() const throw() {
        return FileImplementation::size(mPath) != 0;
    }

    bool File::create(const AccessMode aMode) throw() {
        return FileImplementation::createFile(mPath, aMode);
    }

    bool File::delete_() throw() {
        return FileImplementation::deleteFile(mPath);
    }

    int32_t File::size() const throw() {
        return FileImplementation::size(mPath);
    }

    CString File::getPath() const throw() {
        return FileImplementation::getParent(mPath);
    }

    CString File::getName() const throw() {
        return FileImplementation::getName(mPath);
    }

    CString File::getExtention() const throw() {
        return FileImplementation::getExtension(mPath);
    }

    bool File::rename(const StringConstant<char>& aName) throw() {
        if(FileImplementation::rename(mPath, aName)){
            mPath = aName;
            return true;
        }else {
            return false;
        }
    }

    bool File::copy(const StringConstant<char>& aName) const throw() {
        return FileImplementation::copy(mPath, aName);
    }

    bool File::move(const StringConstant<char>& aName) throw() {
        if(FileImplementation::move(mPath, aName)){
            mPath = aName;
            return true;
        }else {
            return false;
        }
    }

    File::AccessMode File::getAccessMode() const throw() {
        return static_cast<AccessMode>(FileImplementation::getAttributes(mPath) & (! READ_WRITE));
    }

}
