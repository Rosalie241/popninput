CC := i686-w64-mingw32-gcc

popninput.dll:
	$(CC) -static popninput.c popninput.def -o popninput.dll -shared

clean:
	rm -f popninput.dll
