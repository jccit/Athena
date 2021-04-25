@echo off

REM Download SDL2
cd ThirdParty

curl https://www.libsdl.org/release/SDL2-devel-2.0.14-VC.zip -o SDL2.zip
curl https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-VC.zip -o SDL2_image.zip

7z x SDL2.zip
7z x SDL2_image.zip

cd ..

set rootDir=%cd%
set sdlPath=%rootDir%\ThirdParty\SDL2-2.0.14
set sdlImgPath=%rootDir%\ThirdParty\SDL2_image-2.0.5

REM Start the build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DSDL2_PATH=%sdlPath% -DSDL2_IMAGE_PATH=%sdlImgPath% ..
devenv Sources\Athena2D\Athena.vcxproj /build "Release"

REM Archive the build
set out=build
cd bin\Release
mkdir %out%
move Athena.exe %out%
move sqstdlib.dll %out%
move squirrel.dll %out%

REM Copy deps
copy %sdlPath%\lib\x64\SDL2.dll %out%
copy %sdlImgPath%\lib\x64\SDL2_image.dll %out%
copy %sdlImgPath%\lib\x64\libpng16-16.dll %out%
copy %sdlImgPath%\lib\x64\zlib1.dll %out%
xcopy %rootDir%\Content %out% /e /i /h

7z a Athena-Win-x64.zip %out%