// ФАЙЛ 1
// 75 75 50 0 255 0

// ФАЙЛ 2
// 125 125 75 0 255 0

// ФАЙЛ 3
// 75 75 50
// 60 60 28
// 0 255 0

//	Бибилиотеки windows.h и windowsx.h позволяют  использовать в своей программе
//	функционал, предоставляемый операционной системой Windows
#include <windows.h>
#include <windowsx.h>
//	Библиотека для ввода-вывода - Input/Output Stream 
#include <iostream>


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
		printf_s("Ошибка, у круга отрицательный радиус");
		return false;
	}
	// Проверка на принадлежность окну
	// Если верх или лево круга 'вылазят' за контекст отображения
	if ((circle->centerX - circle->radius) < 0 || (circle->centerY - circle->radius) < 0 ||
		// Если низ или право 'вылазят' за контекст отображения
		(circle->centerX + circle->radius > rt->right) || (circle->centerY + circle->radius) > rt->bottom) {
		printf_s("Ошибка, круг вылазит за контект отображения");
		return false;
	}
	// Если все проверки пройдены - возвращаем true
	return true;
}


// Рисование незакрашенного круга, т.е. кисть будет иметь значение RGB(0,0,0)
// 
// Входные данные: HDC - дескриптор, т.е. целое число, идентификатор контекста отображения
// Константные указатели на стркутуры RECT и Circle
void drowUnpaintedCircle(HDC hdc, const RECT* rt, const Circle* circle) {
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
void drowPaintedCircle(HDC hdc, const RECT* rt, const Circle* circle) {
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
void drowTwoCircle(HDC hdc, const RECT* rt, const Circle* big, const Circle* little) {
	if (!isCorrect(rt, big)) return;
	if (!isCorrect(rt, little)) return;

	if (!isInclude(big, little)) return;
	drowPaintedCircle(hdc, rt, big);
	drowUnpaintedCircle(hdc, rt, little);
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


	// Вот тут начало области, куда нужно вставлять рабочий код 
	Circle* figure1 = new Circle(200, 200, 100); // Созадем круг
	drowPaintedCircle(hdc, &rt, figure1); // Рисуем круг
	// Вот тут конец области, куда нужно вставлять рабочий код

	
	system("pause"); // Пауза программы
	// освобождаем контекст отображения
	ReleaseDC(hwnd, hdc);
}