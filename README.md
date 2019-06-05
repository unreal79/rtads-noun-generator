"# rtads-noun-generator" -- Генератор подежных форм для RTADS (русифицированной версии TADS -- системы для создания текстовых игр)"

(с) 2003-2006 Андрей Гранкин
Перенос на Visual C++ -- Станислав Старков, 2006 год

![Image alt](https://github.com/unreal79/rtads-noun-generator/raw/master/screenshot.png)

Советы по генерации падежных форм:

В верхнее поле ввода даётся выражение. Если оно более одной буквы, то немедленно начнется обработка. Если вас не устраивает результат, то,  вероятно, Вам необходимо поменять пол или свойство одушевлённости объекта. В ином случае перейдите на соответствующее поле и наберите нужное значение. Как только Вы начнете работу со строкой, справа от неё снимется галочка, которая обозначает, что при изменении именительного падежа (верхняя строка) данная строка не будет меняться. Если необходимо чтобы все падежные формы выглядели одинаково, поставьте галочку напротив первой строки.

Три галочки во втором столбце вызывают добавление дополнительного слова с пометкой для парсера (синтаксического анализатора), указывающей его как соответствующий падеж. Галочка напротив родительного падежа создают пометку родительного падежа  для всех слов, определённых после предлогов "из", "для", "от" и многих других. Это позволит парсеру (синтаксическому анализатору) узнавать определяющие слова после определяемого существительного. Например, чтобы был распознан объект "посох ужаса", нужно ввести его как "посох для ужаса" и включить пометку напротив родительного падежа. Если вам нужен "ключ из золота", то пометку делать не нужно. Т.е. галочка нужна только в случае отсутствия предлога.

Алгоритм рассчитан на предложение из прилагательных и существительных. Вводить можно до 15 слов. Два и более существительных будут обрабатываться по одной схеме - одушевленность/пол. В сомнительных случаях алгоритм принимает первые слова за прилагательные, а последнее - за существительное, например, "злой смешной ковбой" будет обработан правильно, а "ковбой злой" - нет.

У большинства элементов управления имеются всплывающие подсказки.
