/*
Парсер битовой маски
На вход подаётся std::string_view, где записаны числа от 1 до 64, разделённые запятыми.

Нужно превратить эту строку в число типа uint64_t, где каждый бит соответствует числу из строки.

Если в строке встречается число k, то в результате должен быть установлен бит с номером k-1 (нумерация битов с нуля).
Если одно и то же число встречается несколько раз — бит всё равно будет установлен только один раз.
Если строка пустая — результат равен 0.
Числа могут быть окружены пробелами.
Если встретилось некорректное число (например, 0, 999 или буквы) — нужно вернуть ошибку через std::optional.
Примеры
Вход	Установленные биты	Результат
"1,3,64"	0, 2 и 63	0b100...101 (1ULL << 0 | 1ULL << 2 | 1ULL << 63)
" 2 , 2 , 5 "	1 и 4	1ULL << 1 | 1ULL << 4
""	Нет	0
Требования к решению
Нельзя использовать std::string для промежуточных копий — только std::string_view.
Нужно самостоятельно написать разбор строки на подстроки по символу ','.
Для преобразования текста в число нельзя использовать std::stoi (оно аллоцирует и работает только со std::string). Нужно написать свой парсер для std::string_view.
Решение должно работать за время O(n), где n — длина входной строки.
ветка
base_cpp/bitmask
каталоги
base_cpp/bitmask, base_cpp/CMakeLists.txt, CMakeLists.txt
версия задания
v1

*/
#include <iostream>
#include <optional>
#include <string_view>
#include <charconv>
#include <cstdint>
#include <string>
#include <algorithm>

std::optional<uint64_t> parse_mask(std::string_view sv){
    uint64_t n{};
    char delim = ',';
    auto start = sv.begin();

    while (start != sv.end()){
        auto end = std::find(start, sv.end(), delim);
        std::size_t offset = static_cast<std::size_t>(start - sv.begin());
        std::size_t len    = static_cast<std::size_t>(end - start);
        std::string_view token(sv.data() + offset, len);

        if (len > 0){
            uint32_t  value{};
            auto [p, ec] = std::from_chars(token.data(), token.data() + token.size(), value);
           
            if (ec == std::errc{} && p == token.data() + token.size() && value > 0 && value < 64){
                n |= 1 << (value - 1);
            } else{
                return (uint64_t)0;
            }
        }
        if (end == sv.end()) break;
        start = end + 1;
    }
    return n;
}

/*
int main(){
    
    std::string s{};
    std::cin >> s;

    auto result = parse_mask(std::string_view(s));
    
    if (result){
        std::cout << *result << '\n';
    } else {
        std::cout << "no result\n";
    }

    return 0;
}
*/