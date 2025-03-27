# Компилятор
CXX = g++
WINDRES = windres

# Пути к заголовочным файлам и библиотекам
INCLUDES = -I"../include/" -I"C:/SFML-2.6.2/include"
LIBS = -L"C:/SFML-2.6.2/lib" -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s \
       -lfreetype -lgdi32 -lopengl32 -lwinmm -lopenal32 -lflac -lvorbisfile -lvorbis -lvorbisenc -logg -static-libgcc -static-libstdc++ -lpthread -mwindows

# Флаги компиляции
CXXFLAGS = $(INCLUDES) -DSFML_STATIC

# Исходные файлы
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

# Главная цель
all: main.exe

# Компиляция объектных файлов
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Компиляция ресурса (иконки)
icon.o: icon.rc
	$(WINDRES) $< -o $@

# Сборка итогового exe
main.exe: $(OBJ) icon.o
	$(CXX) $(OBJ) icon.o -o $@ $(LIBS)

# Очистка
clean:
	del -f *.o main.exe icon.o