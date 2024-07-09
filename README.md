# Quain_method_on_Cpp

Данная программа помогает оптимизировать СДНФ методом Квайна

## Пример

Изначально вводим уравнение любой длины. Большая латинская буква обозначает $\bar{x_n}$, маленькая $x_n$.

Указывает формат вывода, false просто в терминал таблицей(пример ниже).

Либо в формате tex, важно последним символом указать разделитель колонок

```C++
int main() {
    Quain quain;
    quain.method(std::vector<std::string>{ "ABCD",
                                           "ABCd",
                                           "ABcd",
                                           "AbCD",
                                           "AbCd",
                                           "AbcD",
                                           "Abcd",
                                           "aBCD",
                                           "aBCd",
                                           "aBcD"},
                                           true,
                                           "c");
    return  0;
}
```

### Вывод в терминал

```cmd
Оптимизация для СДНФ
ABCD  0|ABCD+ABCd=ABC  0'|ABC+AbC=AC  0''| AC|
ABCd  1|ABCD+AbCD=ACD  1'|ABC+aBC=BC  1''| Ab|
ABcd  2|ABCD+aBCD=BCD  2'|ACD+ACd=AC  2''| Ad|
AbCD  3|ABCd+ABcd=ABd  3'|BCD+BCd=BC  3''| BC|
AbCd  4|ABCd+AbCd=ACd  4'|ABd+Abd=Ad  4''|aBD|
AbcD  5|ABCd+aBCd=BCd  5'|ACd+Acd=Ad  5''|   |
Abcd  6|ABcd+Abcd=Acd  6'|AbC+Abc=Ab  6''|   |
aBCD  7|AbCD+AbCd=AbC  7'|AbD+Abd=Ab  7''|   |
aBCd  8|AbCD+AbcD=AbD  8'|               |   |
aBcD  9|AbCd+Abcd=Abd  9'|               |   |
       |AbcD+Abcd=Abc 10'|               |   |
       |aBCD+aBCd=aBC 11'|               |   |
       |aBCD+aBcD=aBD 12'|               |   |
y = AC + Ab + Ad + BC + aBD
```

### В формате tex

```cmd
	\begin{center}
     \begin{tabular}{ |c|c|c|c| }         \hline
$\bar{x_0} \bar{x_1} \bar{x_2} \bar{x_3} $  0&$\bar{x_0} \bar{x_1} \bar{x_2} \bar{x_3} $ + $\bar{x_0} \bar{x_1} \bar{x_2} x_3 $ = $\bar{x_0} \bar{x_1} \bar{x_2} $  0' &$\bar{x_0} \bar{x_1} \bar{x_2} $ + $\bar{x_0} x_1 \bar{x_2} $ = $\bar{x_0} \bar{x_2} $  0'' &$\bar{x_0} \bar{x_2} $\\
$\bar{x_0} \bar{x_1} \bar{x_2} x_3 $  1&$\bar{x_0} \bar{x_1} \bar{x_2} \bar{x_3} $ + $\bar{x_0} x_1 \bar{x_2} \bar{x_3} $ = $\bar{x_0} \bar{x_2} \bar{x_3} $  1' &$\bar{x_0} \bar{x_1} \bar{x_2} $ + $x_0 \bar{x_1} \bar{x_2} $ = $\bar{x_1} \bar{x_2} $  1'' &$\bar{x_0} x_1 $\\
$\bar{x_0} \bar{x_1} x_2 x_3 $  2&$\bar{x_0} \bar{x_1} \bar{x_2} \bar{x_3} $ + $x_0 \bar{x_1} \bar{x_2} \bar{x_3} $ = $\bar{x_1} \bar{x_2} \bar{x_3} $  2' &$\bar{x_0} \bar{x_2} \bar{x_3} $ + $\bar{x_0} \bar{x_2} x_3 $ = $\bar{x_0} \bar{x_2} $  2'' &$\bar{x_0} x_3 $\\
$\bar{x_0} x_1 \bar{x_2} \bar{x_3} $  3&$\bar{x_0} \bar{x_1} \bar{x_2} x_3 $ + $\bar{x_0} \bar{x_1} x_2 x_3 $ = $\bar{x_0} \bar{x_1} x_3 $  3' &$\bar{x_1} \bar{x_2} \bar{x_3} $ + $\bar{x_1} \bar{x_2} x_3 $ = $\bar{x_1} \bar{x_2} $  3'' &$\bar{x_1} \bar{x_2} $\\
$\bar{x_0} x_1 \bar{x_2} x_3 $  4&$\bar{x_0} \bar{x_1} \bar{x_2} x_3 $ + $\bar{x_0} x_1 \bar{x_2} x_3 $ = $\bar{x_0} \bar{x_2} x_3 $  4' &$\bar{x_0} \bar{x_1} x_3 $ + $\bar{x_0} x_1 x_3 $ = $\bar{x_0} x_3 $  4'' &$x_0 \bar{x_1} \bar{x_3} $\\
$\bar{x_0} x_1 x_2 \bar{x_3} $  5&$\bar{x_0} \bar{x_1} \bar{x_2} x_3 $ + $x_0 \bar{x_1} \bar{x_2} x_3 $ = $\bar{x_1} \bar{x_2} x_3 $  5' &$\bar{x_0} \bar{x_2} x_3 $ + $\bar{x_0} x_2 x_3 $ = $\bar{x_0} x_3 $  5'' &   \\
$\bar{x_0} x_1 x_2 x_3 $  6&$\bar{x_0} \bar{x_1} x_2 x_3 $ + $\bar{x_0} x_1 x_2 x_3 $ = $\bar{x_0} x_2 x_3 $  6' &$\bar{x_0} x_1 \bar{x_2} $ + $\bar{x_0} x_1 x_2 $ = $\bar{x_0} x_1 $  6'' &   \\
$x_0 \bar{x_1} \bar{x_2} \bar{x_3} $  7&$\bar{x_0} x_1 \bar{x_2} \bar{x_3} $ + $\bar{x_0} x_1 \bar{x_2} x_3 $ = $\bar{x_0} x_1 \bar{x_2} $  7' &$\bar{x_0} x_1 \bar{x_3} $ + $\bar{x_0} x_1 x_3 $ = $\bar{x_0} x_1 $  7'' &   \\
$x_0 \bar{x_1} \bar{x_2} x_3 $  8&$\bar{x_0} x_1 \bar{x_2} \bar{x_3} $ + $\bar{x_0} x_1 x_2 \bar{x_3} $ = $\bar{x_0} x_1 \bar{x_3} $  8' & &   \\
$x_0 \bar{x_1} x_2 \bar{x_3} $  9&$\bar{x_0} x_1 \bar{x_2} x_3 $ + $\bar{x_0} x_1 x_2 x_3 $ = $\bar{x_0} x_1 x_3 $  9' & &   \\
 &$\bar{x_0} x_1 x_2 \bar{x_3} $ + $\bar{x_0} x_1 x_2 x_3 $ = $\bar{x_0} x_1 x_2 $ 10' & &   \\
 &$x_0 \bar{x_1} \bar{x_2} \bar{x_3} $ + $x_0 \bar{x_1} \bar{x_2} x_3 $ = $x_0 \bar{x_1} \bar{x_2} $ 11' & &   \\
 &$x_0 \bar{x_1} \bar{x_2} \bar{x_3} $ + $x_0 \bar{x_1} x_2 \bar{x_3} $ = $x_0 \bar{x_1} \bar{x_3} $ 12' & &   \\
 	\hline
   \end{tabular}
\end{center}
$y_c =$ $\bar{x_0} \bar{x_2} $ + $\bar{x_0} x_1 $ + $\bar{x_0} x_3 $ + $\bar{x_1} \bar{x_2} $ + $x_0 \bar{x_1} \bar{x_3} $
```
