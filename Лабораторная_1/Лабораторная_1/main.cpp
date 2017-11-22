
// Бибилиотеки windows.h и windowsx.h позволяют  использовать в своей программе
// функционал, предоставляемый операционной системой Windows
#include <windows.h>
#include <windowsx.h>
// Библиотека для ввода-вывода
#include <fstream>
// Библиотека нужна для создания строковых переменных
#include <string>


// Структура круга
struct Circle {
	int centerX, centerY; // Центр круга
	int radius; // Радиус круга

	int r = 0, g = 255, b = 0; // Цвет окружности
	int rFill = 0, gFill = 255, bFill = 0; // Цвет внутри фигуры
	
	// Конструктор структуры - нужен, чтобы легко и просто создавать структуру
	// Не тратя каждый раз по одной строке на centerX, centerY, radius
	Circle(int centerX, int centerY, int radius) {
		this->centerX = centerX;
		this->centerY = centerY;
		this->radius = radius;
	};
};


// Проверка на корректность данных
// А именно на нулевой радиус и принадлежность окну
//
// Входные данные: Указатель на стркутуру RECT, eказатель на структуру круга
// Указатели константные, т.к. мы не меняем их содержимое
// P.S. Структура RECT определяет координаты прямоугольника. В нашем случае - контекста отображения
//
// Выходные данные: true - если данные корректны, иначе false
boolean isCorrect(const RECT* rt, const Circle* circle) {
	// Проверка на 'нулевой радиус'
	if (circle->radius <= 0) {
		printf_s("Ошибка, у круга отрицательный радиус\n");
		return false;
	}
	// Проверка на принадлежность окну
	// Если верх или лево круга 'вылазят' за контекст отображения
	if ((circle->centerX - circle->radius) < 0 || (circle->centerY - circle->radius) < 0 ||
		// Если низ или право 'вылазят' за контекст отображения
		(circle->centerX + circle->radius > rt->right) || (circle->centerY + circle->radius) > rt->bottom) {
		printf_s("Ошибка, круг вылазит за контект отображения\n");
		return false;
	}
	// Если все проверки пройдены - возвращаем true
	return true;
}


// Рисование незакрашенного круга, т.е. кисть будет иметь значение RGB(0,0,0)
// 
// Входные данные: HDC - дескриптор, т.е. целое число, идентификатор контекста отображения
// Константные указатели на стркутуры RECT и Circle
void drawUnpaintedCircle(HDC hdc, const RECT* rt, const Circle* circle) {
	// Если данные у круга неккоректны - выходим из функции
	if (!isCorrect(rt, circle)) return;
	// Создаем перо и кисть
	HPEN pen = SelectPen(hdc, CreatePen(PS_SOLID, 1, RGB(circle->r, circle->g, circle->b)));
	HBRUSH brush = SelectBrush(hdc, CreateSolidBrush(RGB(0, 0, 0))); // Фон у нас RGB(0,0,0) т.к. незакрушенная фигура
	// Вызываем функцию для рисования круга
	// Входные данные - hdc, две противоположные точки у эллипса
	Ellipse(hdc, circle->centerX - circle->radius, circle->centerY - circle->radius,
		    circle->centerX + circle->radius, circle->centerY + circle->radius);
	// удаляем кисть и перо, чтобы освободить память
	DeletePen(pen);
	DeleteBrush(brush);
}


// Рисование закрашенного круга
// Функция аналогична предыдущей, за исключением цвета кисти
void drawPaintedCircle(HDC hdc, const RECT* rt, const Circle* circle) {
	// Если данные у круга неккоректны - выходим из функции
	if (!isCorrect(rt, circle)) return;
	// Создаем перо и кисть
	HPEN pen = SelectPen(hdc, CreatePen(PS_SOLID, 1, RGB(circle->r, circle->g, circle->b)));
	HBRUSH brush = SelectBrush(hdc, CreateSolidBrush(RGB(circle->rFill, circle->gFill, circle->bFill)));
	// Рисуем эллипс (в нашем случае круг)
	Ellipse(hdc, circle->centerX - circle->radius, circle->centerY - circle->radius,
		circle->centerX + circle->radius, circle->centerY + circle->radius);
	// удаляем кисть и перо, чтобы освободить память
	DeletePen(pen);
	DeleteBrush(brush);
}


// Проверка на принадлежность круга little кругу big
// Как понятно из названия - big должен включать little
//
// Выходные данные: true - включает, false - нет
boolean isInclude(const Circle* big, const Circle* little) {
	// Если радиус маленького круга равен или больше, чем радиус большого - то точно не включает
	if (little->radius >= big->radius) return false;

	// distance - расстояние между центрами двух кругов
	double distance = sqrt((little->centerX - big->centerX) * (little->centerX - big->centerX) +
		                   (little->centerY - big->centerY) * (little->centerY - big->centerY));
	// Тут лучше нарисовать - я не знаю как описать эту проверку
	if (big->radius < (little->radius + distance)) return false;
	// Если проверки все пройдены - возвращаем true
	return true;
}


// Рисование двух кругов, круг little принадлежит кругу big
//		1. Проверяем на корректность данных двух кругов
//		2. Проверяем принадлежит ли круг little кругу big
//		3. Рисуем закрашенный круг big
//		4. Рисуем незакрашенный круг little
void drawTwoCircle(HDC hdc, const RECT* rt, const Circle* big, const Circle* little) {
	if (!isCorrect(rt, big)) return;
	if (!isCorrect(rt, little)) return;

	if (!isInclude(big, little)) return;
	drawPaintedCircle(hdc, rt, big);
	drawUnpaintedCircle(hdc, rt, little);
}

// Создание круга по данным из файла filename
// Выходные данные - название файла
//
// Выходные данные - указатель на круг или null, если файл не найден
Circle* loadCircle(const std::string &fileName) {
	// Чтение файла
	std::ifstream input(fileName);
	// Если файл не открыт (не найден) - возвразаем NULL
	if (!input.is_open()) return NULL;
	// Создаем круг
	Circle* circle = new Circle(0, 0, 0);
	// Чтение девяти переменных в круг
	input >> circle->centerX >> circle->centerY >> circle->radius;
	input >> circle->r >> circle->g >> circle->b;
	input >> circle->rFill >> circle->gFill >> circle->bFill;
	
	return circle;
}


// Сохранение круга в файл filename
// Выходные данные - название файла и константный указатель на круг
void saveCircle(const std::string &fileName, const Circle* circle) {
	std::ofstream output(fileName); // Создаем файл
	// Сохраняем все данные
	// На первой строке - центр и радиус, на второй - цвет окружности, на третьей - цвет заливки
	output << circle->centerX << " " << circle->centerY << " " << circle->radius << "\n";
	output << circle->r << " " << circle->g << " " << circle->b << "\n";
	output << circle->rFill << " " << circle->gFill << " " << circle->bFill;
}


void main() {
	// Установка русского языка в консоли
	setlocale(LC_ALL, "Russian");
	// получаем идентификатор окна
	HWND hwnd = GetConsoleWindow();
	// получаем контекст отображения
	HDC hdc = GetDC(hwnd);
	RECT rt;
	// получаем размер окна
	GetClientRect(hwnd, &rt);


	// Вот тут начало области, куда нужно вставлять рабочий код //
	//////////////////////////////////////////////////////////////
	//

	// Создаем 2 круга для тестов
	Circle* big = new Circle(200, 200, 100);
	Circle* little = new Circle(225, 225, 50);

	// Тест 1: Рисование закрашенного круга
	drawPaintedCircle(hdc, &rt, big);
	system("pause"); // Ожидание нажатия любой кнопки
	system("cls"); // Отчистить экран

	// Тест 2: Рисование незакрашенного круга
	drawUnpaintedCircle(hdc, &rt, big);
	system("pause");
	system("cls");

	// Тест 3: Рисование круга в круге
	if (isInclude(big, little))
		drawTwoCircle(hdc, &rt, big, little);
	system("pause");
	system("cls");

	// Тест 4: Ошибка из-за нулевого радиуса
	big->radius = 0;
	drawPaintedCircle(hdc, &rt, big);
	system("pause");
	system("cls");

	// Тест 5: Ошибка из-за выход за границы контекста отображения
	little->centerX = -100;
	drawPaintedCircle(hdc, &rt, little);
	system("pause");
	system("cls");

	//
	/////////////////////////////////////////////////////////////
	// Вот тут конец области, куда нужно вставлять рабочий код //

	
	system("pause"); // Пауза программы
	// освобождаем контекст отображения
	ReleaseDC(hwnd, hdc);
}