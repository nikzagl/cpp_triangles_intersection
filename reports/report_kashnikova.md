# Отчет
## Кашникова Анна (Апрель-Май)
### Summary
Мной был разработан модуль графического интерфейса:
- добавлено информационное окно для пользователя;
- имеется отрисовка графических элементов - треугольников;
- созданы кнопки для пользовательского ввода координат;
- добавлена отрисовка пересечения треугольников;
Остальную разработку кода(рефакторинг, отрисовка выпуклых многоугольников) взяли на себя Матвей Клочихин и Никита Заглумонин.
### Lowlights
- Графический модуль зависит от математического модуля, из-за напрямую вызываемых в нём функций для нахождения точек пересечения треугольников;
### Plans
- Исправить зависимость графического модуля от математического;
### Details
Графический модуль был написан на основе библиотеки Dear Imgui, имеющая зависимости от библиотеки GLFW и API OpenGL. Разработан класс UserInterface, экземпляры, которого представляют собой графический интерфейс и содержат информацию о треугольниках. Класс имеет функцию Update, в которой описаны основные видимые пользователем элементы. От основного класса UserInterface, были отделены функции, занимающиеся непосредственно установкой и отрисовкой окна, и помещены в класс Window.