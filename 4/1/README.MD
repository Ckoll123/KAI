# Задача 2. Устранение дублирования

### Описание
Дана программа:

``` c++
#include <iostream>

int main(){

    int value = 5, power = 2, result = 1;

    for (int i = 0; i < power; i++){
        result *= result;
    }

    std::cout << value << " в степени " << power << " = " << result << std::endl;
  
    value = 3;
    power = 3;
    result = 1;

    for (int i = 0; i < power; i++){
        result *= result;
    }

    std::cout << value << " в степени " << power << " = " << result << std::endl;
  
    value = 4;
    power = 4;
    result = 1;

    for (int i = 0; i < power; i++){
        result *= result;
    }

    std::cout << value << " в степени " << power << " = " << result << std::endl;

    return 0;
}
```

Определите, что она делает, и найдите дублирующийся код. Создайте функцию, которая будет устранять дублирование, и вместо повторяющегося кода вызывайте её. Результат работы программы не должен измениться.

### Пример работы программы
```
5 в степени 2 = 25
3 в степени 3 = 27
4 в степени 4 = 256
```
