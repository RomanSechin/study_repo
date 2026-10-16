#include <iostream>
#include <string_view>
#include <optional>
#include <charconv>
#include <cstdint>

std::optional<uint64_t> parse_bitmask(std::string_view sv){
    uint64_t result = (uint64_t)0;

    auto start  = sv.data();
    auto finish = sv.data() + sv.size();
    
    uint64_t number{};    

    while (start < finish){
        while((start != finish) && (*start == ' ' || *start == ',')){ ++start;}
        if (start >= finish) break;
        auto res = std::from_chars(start, finish, number);
        if (res.ec != std::errc()) {
            return uint64_t(0);
        }
        start = res.ptr; 
        if (number > 64 || number == 0) {
            return uint64_t(0);
        }
        else{
            result |= ( UINT64_C(1) << (number - 1));
        }
    }
    return result;
}

int main(){
    std::string_view sv{" 2 , 2 , 3 "};
    auto result = parse_bitmask(sv);
    if (result)
        std::cout << *result << "\n";
    return 0;
}