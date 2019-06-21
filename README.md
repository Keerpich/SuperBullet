# SuperBullet

##Prerequisites
CMake v3.1.2 or greater
Python 3.X

##Setup
1. Run `python -m pip install conan`. This installs conan which we will use as a package manager
2. Run `conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan`. This will add Bincrafters as a possible remote
3. Create a folder where the CMake output will be and set the current path in that folder (e.g. `mkdir SuperBullet` and `cd SuperBullet`)
4. Run `conan install .. -s build_type=Debug --build sfml &&  conan install .. -s build_type=Release --build sfml`. This adds SFML to your machine via conan

##Windows and VS specific steps
5. Run `cmake .. -G "Visual Studio 15 Win64"`. This generates the solution and projects
6. Set *main* as Start-up project