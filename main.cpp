#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>

class Quain {
    typedef std::pair<std::pair<std::string, std::string>, std::string> Implicant;
//    typedef std::pair<std::vector<Implicant>, std::vector<std::string>> Column_impl;

    int get_coincidence_parameters(const std::string &w1, const std::string &w2) {
        int coincidence_parameters = 0;
        for (size_t k = 0; k < w1.size(); ++k)  // вопрос, стоит ли тут писать {}?
            if (w1[k] == w2[k])
                ++coincidence_parameters;
            else
                if (std::tolower(w1[k]) != std::tolower(w2[k]))
                    return 0;
        return coincidence_parameters;
    }

    void push_element(std::vector<Implicant> &impls, std::vector<std::string> &next_y, const std::string &w1,
                                                                                   const std::string &w2) {
        std::string buf;
        for (size_t k = 0; k < w1.size(); ++k) {
            if (w1[k] == w2[k]) {
                buf += w1[k];
            }
        }
        impls.push_back(Implicant(std::pair<std::string, std::string>(w1, w2), buf));
        next_y.push_back(buf);    
    }

    std::pair<std::vector<Implicant>, std::vector<std::string>> get_Implicant(const std::vector<std::string> &y) {
        std::vector<Implicant> impls;
        std::vector<std::string> next_y;
        for (size_t i = 0; i < y.size() - 1; ++i) {
            for (size_t j = (i + 1); j < y.size(); ++j) {
                if (y[i].size() != y[j].size())  // если на входе размеры выражений не равны выдать ошибку
                    throw;

                if (get_coincidence_parameters( y[i], y[j]) == (y[i].size() - 1))
                    push_element( impls, next_y, y[i], y[j]);
            }
        }
        return std::pair<std::vector<Implicant>, std::vector<std::string>>(impls, next_y);
    }

    template<class T>
    void del_elem_in_vector(std::vector<T> &v, const T &elem) {
        for(auto iter = v.begin(); iter != v.end(); ++iter)
            if(*iter == elem) {
                v.erase(iter);
                break;
            }
    }

    std::string conventer_to_tex(const std::string &str) {
        std::string msg = "$";
        for (size_t i = 0; i < str.size(); ++i) {
            switch (int(std::tolower(str[i]))) {
                case 97:
                    msg += ((str[i] == 'a') ? "x_0 " : "\\bar{x_0} ");
                    break;
                case 98:
                    msg += ((str[i] == 'b') ? "x_1 " : "\\bar{x_1} ");
                    break;
                case 99:
                    msg += ((str[i] == 'c') ? "x_2 " : "\\bar{x_2} ");
                    break;
                case 100:
                    msg += ((str[i] == 'd') ? "x_3 " : "\\bar{x_3} ");
                    break;
            };
        }   
        msg += "$";
        return msg;
    }

    void print_tex(const std::vector<std::string> &y, const std::vector<std::pair<std::vector<Implicant>, 
        std::vector<std::string>>> &cols, const std::vector<std::string> &y_optimized, const std::string &symbol) {
        // Определим максимальное колличество строк
        std::vector<size_t> size_v;
        size_v.push_back(y.size()); 
        for (size_t i = 0; i < cols.size(); ++i) {
            size_v.push_back(cols[i].second.size());
        }
        size_v.push_back(y_optimized.size());
        size_t size_row = *std::max_element( size_v.begin(), size_v.end()); 
        size_v.clear();

        std::cout << "	\\begin{center}\n" 
		          << "     \\begin{tabular}{ |c|";
        for (size_t i = 0; i < cols.size(); ++i) 
            std::cout << "c|";
        std::cout << "c| }"
			      << "         \\hline\n";
        for (size_t i = 0; i < size_row; ++i) {
            try {
                std::cout << conventer_to_tex(y.at(i)) << " " << std::setw(2) << i << "&";
            } catch (...) {
                std::cout << " &"; 
            }

            for (size_t j = 0; j < cols.size(); ++j) {
                try {
                    auto imp = cols[j].first.at(i);
                    std::cout << conventer_to_tex(imp.first.first) << " + "
                              << conventer_to_tex(imp.first.second) << " = " 
                              << conventer_to_tex(imp.second) << " " << std::setw(2) << i;
                    for (size_t k = 0; k < (j + 1); ++k)
                        std::cout << "'";
                    std::cout << " &";
                } catch(...) {
                    std::cout << " &";
                }
            }
            try {
                std::cout << conventer_to_tex(y_optimized.at(i)) << "\\\\" << std::endl; 
            } catch (...) {
                std::cout << "   \\\\" << std::endl;
            }
        } 

        std::cout << " 	\\hline\n"
		          << "   \\end{tabular}\n"
	              << "\\end{center}\n";
        std::cout << "$y_" << symbol << " =$ " << conventer_to_tex(y_optimized[0]); 
        for (size_t i = 1; i < y_optimized.size(); ++i) {
            std::cout << " + " << conventer_to_tex(y_optimized[i]); 
        }
        std::cout << std::endl;
    }
 

    void print(const std::vector<std::string> &y, const std::vector<std::pair<std::vector<Implicant>, 
        std::vector<std::string>>> &cols, const std::vector<std::string> &y_optimized) {
        // Определим максимальное колличество строк
        std::vector<size_t> size_v;
        size_v.push_back(y.size()); 
        for (size_t i = 0; i < cols.size(); ++i) {
            size_v.push_back(cols[i].second.size());
        }
        size_v.push_back(y_optimized.size());
        size_t size_row = *std::max_element( size_v.begin(), size_v.end()); 
        size_v.clear();

        for (size_t i = 0; i < size_row; ++i) {
            try {
                std::cout << y.at(i) << " " << std::setw(2) << i << "|";
            } catch (...) {
                std::cout << std::setfill(' ') << std::setw((y[0].size() + 1 + 2 + 1)) << "|"; 
            }

            for (size_t j = 0; j < cols.size(); ++j) {
                try {
                    auto imp = cols[j].first.at(i);
                    std::cout << imp.first.first << "+" << imp.first.second << "=" << imp.second << " " << std::setw(2) << i;
                    for (size_t k = 0; k < (j + 1); ++k)
                        std::cout << "'";
                    std::cout << "|";
                } catch(...) {
                    auto imp_c = cols[j].first[0];
                    std::cout << std::setfill (' ') << std::setw((2 * imp_c.first.first.size() + imp_c.second.size() + 3 + 2 + (2 *j + 1))) << "|";
                }
            }
            try {
                std::cout << std::setw(3) << y_optimized.at(i) << "|" << std::endl; 
            } catch (...) {
                std::cout << "   |" << std::endl;
            }
        } 

        std::cout << "y = " << y_optimized[0]; 
        for (size_t i = 1; i < y_optimized.size(); ++i) {
            std::cout << " + " << y_optimized[i]; 
        }
        std::cout << std::endl;
    }
    
    public:
    Quain() = default;
    ~Quain() = default;
        
    void method(const std::vector<std::string> &y, const bool &tex = false, const std::string &symbol = "a") {
        std::vector<std::pair<std::vector<Implicant>, std::vector<std::string>>> cols;
        cols.push_back(get_Implicant(y));

        for (;;) {  // Это надо переделать, выглядит УЖАСНО
            if (!cols.back().second.empty())
                if (cols.back().second.front().size() != 2)
                    cols.push_back(get_Implicant(cols.back().second)); 
                else 
                    break;
            else {
                cols.pop_back();
                break;
            }
        }

        // Убрали повторяющиеся элементы, после второго склеивания
        std::set<std::string> y_set_buf(cols.back().second.begin(), cols.back().second.end());
    
        // Убираем сокращенные элементы из первой колонки
        auto y_buffer = cols.at((cols.size() - ((cols.size() >= 2) ? 2 : 1))).second;  // импликант после преолбразования, первая колонка, 3 символа
        for (size_t i = 0; i < cols.back().first.size(); ++i) {
            del_elem_in_vector( y_buffer, cols.back().first[i].first.second);
            del_elem_in_vector( y_buffer, cols.back().first[i].first.first);
        }

        // на этом этапе получаем финальную колонку где просто просуммировать надо
        for (size_t i = 0; i < y_buffer.size(); ++i)
            y_set_buf.insert(y_buffer[i]);

        std::vector<std::string> y_optimized;  // y финальный ответ, оптимизированное выражение
        std::copy(y_set_buf.begin(), y_set_buf.end(), std::back_inserter(y_optimized));

        if (!tex) {
            std::cout << "Оптимизация для СДНФ" << std::endl;
            print(y, cols, y_optimized);  // Красивый выход
        } else {
            print_tex(y, cols, y_optimized, symbol);
        }
    }
};

void get_quain_method() {
    Quain quain;
//    quain.method(std::vector<std::string>{ "ABCD", "ABcD", "ABcd", "AbCd", "AbcD", "Abcd", "aBCD", "aBCd", "aBcD"}, true, "a");
//    quain.method(std::vector<std::string>{ "ABCD", "ABCd", "ABcD", "ABcd", "AbCD", "Abcd", "aBCD", "aBCd", "aBcD"}, true, "b");
    quain.method(std::vector<std::string>{ "ABCD", "ABCd", "ABcd", "AbCD", "AbCd", "AbcD", "Abcd", "aBCD", "aBCd", "aBcD"}, true, "c");
//    quain.method(std::vector<std::string>{ "ABCD", "ABcD", "ABcd", "AbCd", "AbcD", "aBCD", "aBCd"}, true, "d");
//    quain.method(std::vector<std::string>{ "ABCD", "ABcD", "AbcD", "aBCD", "aBcD"}, true, "e");
//    quain.method(std::vector<std::string>{ "ABCD", "AbCD", "AbCd", "AbcD", "aBCD", "aBCd", "aBcD"}, true, "f");
//    quain.method(std::vector<std::string>{ "ABcD", "ABcd", "AbCD", "AbCd", "AbcD", "aBCD", "aBCd"}, true, "g");
}

int main() {
    get_quain_method();
    return  0;
}
