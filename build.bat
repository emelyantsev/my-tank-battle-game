
cd build
cl.exe ..\src\*.cpp /c /IC:\SDK\SFML-2.5.1-windows-vc15-64-bit\SFML-2.5.1\include /EHsc /std:c++17 /DSFML_STATIC /MD
link.exe *.obj main.res sfml-main.lib sfml-graphics-s.lib sfml-window-s.lib sfml-system-s.lib sfml-audio-s.lib openal32.lib flac.lib vorbisenc.lib vorbisfile.lib vorbis.lib ogg.lib opengl32.lib freetype.lib winmm.lib gdi32.lib user32.lib advapi32.lib /LIBPATH:C:\SDK\SFML-2.5.1-windows-vc15-64-bit\SFML-2.5.1\lib /OUT:..\game.exe /SUBSYSTEM:WINDOWS /ENTRY:"mainCRTStartup"
link.exe *.obj sfml-main.lib sfml-graphics-s.lib sfml-window-s.lib sfml-system-s.lib sfml-audio-s.lib openal32.lib flac.lib vorbisenc.lib vorbisfile.lib vorbis.lib ogg.lib opengl32.lib freetype.lib winmm.lib gdi32.lib user32.lib advapi32.lib /LIBPATH:C:\SDK\SFML-2.5.1-windows-vc15-64-bit\SFML-2.5.1\lib /OUT:..\game_console.exe 
cd ..