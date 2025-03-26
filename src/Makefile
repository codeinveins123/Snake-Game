# Компилятор
CXX = g++
WINDRES = windres

# Пути к SFML
SFML_INC = C:/SFML-2.6.2/include
SFML_LIB = C:/SFML-2.6.2/lib

# Флаги компиляции
CXXFLAGS = -I"$(SFML_INC)" -DSFML_STATIC -mwindows
LDFLAGS = -L"$(SFML_LIB)" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lfreetype -lgdi32 -lopengl32 -lwinmm

# Исходники и объектные файлы
SRC = main.cpp Game.cpp AssetManager.cpp StateManager.cpp MainMenu.cpp GamePlay.cpp Snake.cpp GameOver.cpp PauseGame.cpp
OBJ = $(SRC:.cpp=.o)

# Файлы ресурсов (иконка)
RES = icon.rc
RES_OBJ = icon.o

# Итоговый файл
TARGET = main.exe

# Сборка всего
all: $(TARGET)

# Компиляция объектных файлов
%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Компиляция ресурсов
$(RES_OBJ): $(RES)
	$(WINDRES) -O coff $< -o $@

# Линковка всего в main.exe
$(TARGET): $(OBJ) $(RES_OBJ)
	$(CXX) $(OBJ) $(RES_OBJ) -o $(TARGET) $(LDFLAGS)

# Очистка объектных файлов
clean:
	del /Q $(OBJ) $(RES_OBJ) $(TARGET)