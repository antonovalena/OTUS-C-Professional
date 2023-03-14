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
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void print_ip_address(const std::vector<std::string>& ip) {
    for(std::vector<std::string>::const_iterator ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part) {
        if (ip_part != ip.cbegin())
        {
            std::cout << ".";

        }
        std::cout << *ip_part;
    }
}

struct less_ipv4_address {
    inline bool operator() (const std::vector<std::string>& v1, const std::vector<std::string>& v2) {
       for(size_t ind = 0; ind < 4; ++ind) {
            if (std::atoi(v1[ind].c_str()) < std::atoi(v2[ind].c_str())) {
                return true;
            } else if (std::atoi(v1[ind].c_str()) > std::atoi(v2[ind].c_str())) {
                return false;
            }
       }
       return false;  
    }
};

void filter_by_mask(std::vector<std::vector<std::string>>& v, const std::vector<int>& mask) {
    if (mask.size() > 4) {
        std::cout << "Mask of size " << mask.size() << " is too big, cannot filter ipv4 address by it" << std::endl;
        return;
    }

    auto has_mask = [mask](const std::vector<std::string>& ip_address) {
        for (size_t ind = 0; ind < mask.size(); ++ind) {
            if(std::atoi(ip_address[ind].c_str()) != mask[ind]) {
                return false;
            }
        }
        return true;
    };

    for(std::vector<std::vector<std::string> >::reverse_iterator ip = v.rbegin(); ip != v.rend(); ++ip)
        {   
            if (!has_mask(*ip)) {
                continue;
            }
            print_ip_address(*ip);
            std::cout << std::endl;
        }
}

void filer_by_any(std::vector<std::vector<std::string>>& v, const int byte) {
    auto has_byte = [byte](const std::vector<std::string>& ip_address) {
        for (size_t ind = 0; ind < ip_address.size(); ++ind) {
            if (std::atoi(ip_address[ind].c_str()) == byte) {
                return true;
            }
        }
        return false;
    };
    for(std::vector<std::vector<std::string> >::reverse_iterator ip = v.rbegin(); ip != v.rend(); ++ip)
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
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            if (auto next_address = split(v.at(0), '.'); next_address.size() != 4) {
                std::cout << "Wrong format: cant add ip address " << line  << v.size()<< std::endl;
            } else {
                ip_pool.push_back(next_address);
            }
        }

        std::sort(ip_pool.begin(), ip_pool.end(), less_ipv4_address());

        for(std::vector<std::vector<std::string> >::reverse_iterator ip = ip_pool.rbegin(); ip != ip_pool.rend(); ++ip)
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