@echo off

cd ThirdParty

curl https://www.libsdl.org/release/SDL2-devel-2.0.14-VC.zip -o SDL2.zip
curl https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-VC.zip -o SDL2_image.zip

7z x SDL2.zip
7z x SDL2_image.zip
