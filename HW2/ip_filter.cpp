#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
template<typename T>
std::vector<T> split(const std::string &str, char d)
{
    std::vector<T> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);

    while(stop != std::string::npos)
    {
        if constexpr (std::is_integral<T>::value) {
            r.push_back(std::atoi(str.substr(start, stop - start).c_str()));
        } else {
            r.push_back(str.substr(start, stop - start));
        }

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    if constexpr (std::is_integral<T>::value) {
        r.push_back(std::atoi(str.substr(start).c_str()));
    } else {
        r.push_back(str.substr(start));
    }

    return r;
}

void print_ip_address(const std::vector<int>& ip) {
    for(auto ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part) {
        if (ip_part != ip.cbegin())
        {
            std::cout << ".";

        }
        std::cout << *ip_part;
    }
}

struct less_ipv4_address {
    inline bool operator() (const std::vector<int>& v1, const std::vector<int>& v2) {
       for(size_t ind = 0; ind < 4; ++ind) {
            if (v1[ind] < v2[ind]) {
                return true;
            } else if (v1[ind] > v2[ind]) {
                return false;
            }
       }
       return false;  
    }
};

void filter_by_mask(std::vector<std::vector<int>>& v, const std::vector<int>& mask) {
    if (mask.size() > 4) {
        std::cout << "Mask of size " << mask.size() << " is too big, cannot filter ipv4 address by it" << std::endl;
        return;
    }

    auto has_mask = [mask](const std::vector<int>& ip_address) {
        for (size_t ind = 0; ind < mask.size(); ++ind) {
            if(ip_address[ind] != mask[ind]) {
                return false;
            }
        }
        return true;
    };

    for(auto ip = v.rbegin(); ip != v.rend(); ++ip)
        {   
            if (!has_mask(*ip)) {
                continue;
            }
            print_ip_address(*ip);
            std::cout << std::endl;
        }
}

void filer_by_any(std::vector<std::vector<int>>& v, const int byte) {
    auto has_byte = [byte](const std::vector<int>& ip_address) {
        return std::find(ip_address.begin(), ip_address.end(), byte) != ip_address.end();
    };
    for(auto ip = v.rbegin(); ip != v.rend(); ++ip)
        {   
            if (!has_byte(*ip)) {
                continue;
            }
            print_ip_address(*ip);
            std::cout << std::endl;
        }
}

int main(int , char **)
{
    try
    {
        std::vector<std::vector<int> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split<std::string>(line, '\t');
            if (auto next_address = split<int>(v.at(0), '.'); next_address.size() != 4) {
                std::cout << "Wrong format: cant add ip address " << line  << v.size()<< std::endl;
            } else {
                ip_pool.push_back(next_address);
            }
        }

        std::sort(ip_pool.begin(), ip_pool.end(), less_ipv4_address());

        for(auto ip = ip_pool.rbegin(); ip != ip_pool.rend(); ++ip)
        {
            print_ip_address(*ip);
            std::cout << std::endl;
        }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        filter_by_mask(ip_pool, {1});

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        filter_by_mask(ip_pool, {46, 70});

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76


        filer_by_any(ip_pool, 46);

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}