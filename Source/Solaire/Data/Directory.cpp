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

#include "Solaire\Data\Directory.hpp"

namespace Solaire {

    // Directory

    Directory::Directory(const StringConstant<char>& aPath) :
        mPath(aPath)
    {}

    bool Directory::exists() const throw() {
        //! \todo Implement Directory::exists
        return false;
    }

    bool Directory::create() throw() {
        return FileImplementation::createDirectory(mPath);
    }

    bool Directory::delete_() throw() {
        ArrayList<File> files = getFiles();
        ArrayList<Directory> directories = getDirectories();

        for(File& i : files) if(! i.delete_()) return false;
        for(Directory& i : directories) if(! i.delete_()) return false;

        return FileImplementation::deleteDirectory(mPath);
    }

    ArrayList<File> Directory::getFiles() const throw() {
        ArrayList<STLString> pathList;
        FileImplementation::getFileList(mPath, pathList);
        ArrayList<File> files(DEFAULT_ALLOCATOR, pathList.size());
        for(const STLString& path : pathList) if(FileImplementation::getAttributes(path) & FileImplementation::FLAG_FILE) {
            files.pushBack(File(path));
        }
        return files;
    }

    ArrayList<Directory> Directory::getDirectories() const throw() {
        ArrayList<STLString> pathList;
        FileImplementation::getFileList(mPath, pathList);
        ArrayList<Directory> directories(DEFAULT_ALLOCATOR, pathList.size());
        for(const STLString& path : pathList) if(FileImplementation::getAttributes(path) & FileImplementation::FLAG_DIRECTORY) {
            directories.pushBack(Directory(path));
        }
        return directories;
    }

    CString Directory::getPath() const throw() {
        return mPath;
    }

    bool Directory::rename(const StringConstant<char>& aPath) throw() {
        if(FileImplementation::rename(mPath, aPath)){
            mPath = aPath;
            return true;
        }else {
            return false;
        }
    }

    bool Directory::copy(const StringConstant<char>& aPath) const throw() {
        return FileImplementation::rename(mPath, aPath);
    }

    bool Directory::move(const StringConstant<char>& aPath) throw() {
        if(FileImplementation::move(mPath, aPath)){
            mPath = aPath;
            return true;
        }else {
            return false;
        }
    }


}
