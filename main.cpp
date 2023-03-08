#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>

#define PDNF 1  // Perfect Disjunctive Normal Form()
#define PCNF 2  // Perfect Conjunctive Normal Form()

class Quain {
    /* \struct Impl - импликант, выражение в строке */
    struct Impl {
        std::string _l_logex;    // Сокращенно от logical expression
        size_t      _l_num;      // Номер логического выражения
        std::string _r_logex;
        size_t      _r_num;

        Impl() = default;
        Impl(const Impl& _tmp) : _l_logex(_tmp._l_logex), _l_num(_tmp._l_num), _r_logex(_tmp._r_logex),
            _r_num(_tmp._r_num) {}
        Impl(const std::string &l, const size_t &l_num, const std::string &r, const size_t &r_num) :
            _l_logex(l), _l_num(l_num), _r_logex(r), _r_num(r_num) {}
        ~Impl() {
            clear();
        }

        bool empty() const {
            return ((_l_logex.empty() || _r_logex.empty()) ? 1 : 0);
        }

        void clear() {
            _l_logex.clear();
            _r_logex.clear();
        }
    };

    typedef std::pair<Impl, std::string> Row;  // Cтрока одной колонки
    typedef std::vector<Row> Col;              // Одна колонка

    std::vector<Col> cols;                 // Колонки
    std::vector<std::string> y;            // Введенное y
    std::vector<std::string> y_optimized;  // y оптимизированное

    int _form;

    /* Функция проверяет совпадающие параметры(символы) 
     * Если все символы равны, но разные по значению \return true
     * Если все символы равны, все значения равны ---   // предполагается что одинаковых входных выражений
     *                                                   \ быть не должно
     * Иначе \return false
     * */
    int get_coincidence_parameters(const std::string &w1, const std::string &w2) const {
        int coincidence_parameters = 0;
        for (size_t k = 0; k < w1.size(); ++k)  // вопрос, стоит ли тут писать {}?
            if (w1[k] == w2[k])
                ++coincidence_parameters;
            else
                if (std::tolower(w1[k]) != std::tolower(w2[k]))
                    return 0;
        return coincidence_parameters;
    }

#if 0
// Хотел функцию красивой сделать, но что то не вышло. Ладно в общем это задел для будущих версий если улучшать буду
    bool get_coincidence_parameters(const std::string &w1, const std::string &w2) const {
        if (w1.size() != w2.size() || w1 == w2)  // Проверка на одинаковый размер слов
            throw;

        for (size_t k = 0; k < w1.size(); ++k) {
            if (w1[k] != w2[k]) {
                if (std::tolower(w1[k]) != std::tolower(w2[k])) {
                    return false;
                }
            }
        }
        return true;
    }
#endif

    /* Функция вернет результат склеивания двух логических выражений
     * */
    std::string get_out_logex(const std::string &_l, const std::string &_r) {
        if (_l.size() != _r.size() || _l == _r)
            throw;

        std::string _buf_logex;
        for (size_t i = 0; i < _l.size(); ++i) {
            if (_l[i] == _r[i]) {
                _buf_logex += _l[i];
            }
        }
        return _buf_logex; 
    }

    /* Функция вернет строку одной колонки
     * */
    Row get_row( const std::string &_l, const size_t &_l_num, const std::string &_r, const size_t &_r_num) {
        std::string _buf_logex = get_out_logex( _l, _r);
        Impl impl( _l, _l_num, _r, _r_num);
        return Row(impl, _buf_logex);
    }

    /*  Функци вернет колонку импликантов
     * */
    Col get_col_implicant(const std::vector<std::string> &y) {
        Col col;
        for (size_t i = 0; i < y.size() - 1; ++i) {
            for (size_t j = (i + 1); j < y.size(); ++j) {
                if (get_coincidence_parameters( y[i], y[j]) == (y[i].size() - 1)) { //Проверка на схожие символы, но разные значения в logex
                    col.push_back(get_row(y[i], i, y[j], j)); 
                }
            }
        }
        return col;
    }

    template<class T>
    void del_elem_in_vector(std::vector<T> &v, const T &elem) {
        for(auto iter = v.begin(); iter != v.end(); ++iter)
            if(*iter == elem) {
                v.erase(iter);
                break;
            }
    }

    /*  Функция очищает предыдущую колонку от повторных значений 
     * */
    std::vector<std::string> clear_pred_vector() {
        std::vector<std::string> y_buffer = get_y(
            cols.at((cols.size() - ((cols.size() >= 2) ? 2 : 1))));  // импликант после преолбразования, первая колонка, 3 символа
        for (size_t i = 0; i < cols.back().size(); ++i) {
            del_elem_in_vector( y_buffer, cols.back()[i].first._l_logex);
            del_elem_in_vector( y_buffer, cols.back()[i].first._r_logex);
        }
        return y_buffer;
    }

    /*  Функция возращает массив y взятых из колонки
     * */
    std::vector<std::string> get_y(const Col &col) const {
        std::vector<std::string> y_buf;
        for (size_t i = 0; i < col.size(); ++i) {
            y_buf.push_back(col[i].second);
        }
        return y_buf;
    }

    void get_cols(const std::vector<std::string> &y) {
        cols.push_back(get_col_implicant(y));
        for (;;) {  // Это надо переделать, выглядит УЖАСНО
            if (!cols.back().empty()) {
                if (cols.back().front().second.size() != 2) {
                    cols.push_back(get_col_implicant(get_y(cols.back()))); 
                } else { 
                    break;
                }
            } else {
                cols.pop_back();
                break;
            }
        }
    }

    void get_y_optimized() {
        if (cols.empty()) {
            y_optimized = y;
            return;
        }

        // Убрали повторяющиеся элементы, после второго склеивания
        auto y_last_buffer = get_y(cols.back());
        std::set<std::string> y_set_buf( y_last_buffer.begin(), y_last_buffer.end());
    
        // Убираем сокращенные элементы из первой колонки
        std::vector<std::string> y_buffer = clear_pred_vector(); 

        // на этом этапе получаем финальную колонку где просто просуммировать надо
        for (size_t i = 0; i < y_buffer.size(); ++i)
            y_set_buf.insert(y_buffer[i]);

        std::copy(y_set_buf.begin(), y_set_buf.end(), std::back_inserter(y_optimized));
    } 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                  Вывод
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::string conventer_to_tex(const std::string &str) {
        switch (_form) {
            case PDNF:
                return conventer_to_tex_PDNF(str);
            case PCNF:
                return conventer_to_tex_PCNF(str);
            default:
                std::cout << "что то не так с переменной _form в классе Quain: " << _form << std::endl;
                throw;
        }
    }

    std::string conventer_to_tex_PDNF(const std::string &str) {
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

    std::string conventer_to_tex_PCNF(const std::string &str) {
        std::string msg = "$(";
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
            if (i < (str.size() - 1)) {
                msg += "\\vee ";
            }
        }
        msg += ")$";
        return msg;
    }

    std::string out_abcd(const std::string &str) {
        switch (_form) {
            case PDNF:
                return str;
            case PCNF:
                return out_abcd_PCNF(str);
            default:
                std::cout << "что то не так с переменной _form в классе Quain: " << _form << std::endl;
                throw;
        }
    }

    std::string out_abcd_PCNF(const std::string &str) {
        std::string msg = "(";
        for (size_t i = 0; i < str.size(); ++i) {
            msg += str[i];
            if (i < (str.size() - 1)) {
                msg += " + ";
            }
        }
        msg += ")";
        return msg;
    }

    /* Функция определяет колличество строк, которые надо будет выводить
     * */
    size_t get_size_row(const std::vector<std::string> &y, const std::vector<std::string> &y_optimized) {
        // Определим максимальное колличество строк
        std::vector<size_t> size_v;
        size_v.push_back(y.size()); 
        for (size_t i = 0; i < cols.size(); ++i) {
            size_v.push_back(cols[i].size());
        }
        size_v.push_back(y_optimized.size());
        size_t size_row = *std::max_element( size_v.begin(), size_v.end()); 
        size_v.clear();
        return size_row;
    }

    void out_1() {
        std::cout << "	\\begin{center}\n" 
		          << "     \\begin{tabular}{ |c|";
        for (size_t i = 0; i < cols.size(); ++i) 
            std::cout << "c|";
        std::cout << "c| }"
			      << "         \\hline\n";
    }

    void out_2( const std::vector<std::string> &y_result, const std::string &symbol) {
        std::cout << " 	\\hline\n"
		          << "   \\end{tabular}\n"
	              << "\\end{center}\n";
        std::cout << "$y_" << symbol << " =$ " << conventer_to_tex(y_result[0]); 
        for (size_t i = 1; i < y_result.size(); ++i) {
            std::cout << " + " << conventer_to_tex(y_result[i]); 
        }
        std::cout << std::endl;

    }

    void print_tex(const std::string &symbol) {
        size_t size_row = get_size_row( y, y_optimized); 
        out_1();
        for (size_t i = 0; i < size_row; ++i) {
            try {
                std::cout << conventer_to_tex(y.at(i)) << " " << std::setw(2) << i << "&";
            } catch (...) {
                std::cout << " &"; 
            }

            for (size_t j = 0; j < cols.size(); ++j) {
                try {
                    auto imp = cols[j].at(i);
                    std::cout << imp.first._l_num;
                    for (size_t k = 0; k < j; ++k)
                        std::cout << "'";
                    std::cout << " + ";
                    std::cout << imp.first._r_num;
                    for (size_t k = 0; k < j; ++k)
                        std::cout << "'";
                    std::cout << " = "; 
                    std::cout << conventer_to_tex(imp.second) << " " << std::setw(2) << i;
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
        out_2( y_optimized, symbol);
    }
 
    void print() {
        size_t size_row = get_size_row( y, y_optimized);
        for (size_t i = 0; i < size_row; ++i) {
            try {
                std::cout << out_abcd(y.at(i)) << " " << std::setw(2) << i << "|";
            } catch (...) {
                std::cout << std::setfill(' ') << std::setw((out_abcd(y[0]).size() + 1 + 2 + 1)) << "|"; 
            }
            for (size_t j = 0; j < cols.size(); ++j) {
                try {
                    auto imp = cols[j].at(i);
                    std::cout << std::setw(2) << imp.first._l_num;
                    for (size_t k = 0; k < j; ++k)
                        std::cout << "'";
                    std::cout << " + " << std::setw(2) << imp.first._r_num;
                    for (size_t k = 0; k < j; ++k)
                        std::cout << "'";
                    std::cout << " = " << out_abcd(imp.second) << " " << std::setw(2) << i;
                    for (size_t k = 0; k < (j + 1); ++k)
                        std::cout << "'";
                    std::cout << " |";
                } catch(...) {
                    std::cout << std::setfill(' ') 
                              << std::setw((16 + 3 * j + out_abcd(cols[j][0].second).size())) << " |";
                }
            }
            try {
                std::cout << out_abcd(y_optimized.at(i)) << std::endl; 
            } catch (...) {
                std::cout << std::endl;
            }
        } 
        std::cout << "y = " << out_abcd(y_optimized[0]); 
        for (size_t i = 1; i < y_optimized.size(); ++i) {
            std::cout << " + " << out_abcd(y_optimized[i]); 
        }
        std::cout << std::endl;
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
    void clear() {
        for (size_t i = 0; i < cols.size(); ++i) {
            for (size_t j = 0; j < cols[i].size(); ++j) {
                cols[i][j].first.clear();
                cols[i][j].second.clear();
            }
            cols[i].clear();
        }
        cols.clear();
        y.clear();
        y_optimized.clear();
    }

    public:
    Quain() = default;
    ~Quain() {
        clear();
    }
        
    void method(const int &form, const std::vector<std::string> &y_in, const bool &tex = false, const std::string &symbol = "a") {
        _form = form;
        y = y_in;
        // Получаем все колонки, возможно ситуация при которой колонок не будет вовсе
        get_cols(y);

        // Получаем оптимизированный y
        get_y_optimized();

        if (!tex) {  // вынести
            print();
        } else {
            print_tex(symbol);
        }
        clear();
    }
};

void get_quain_method() {
    Quain quain;
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "ABcD", "ABcd", "AbCd", "AbcD", "Abcd", "aBCD", "aBCd", "aBcD"});
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "ABCd", "ABcD", "ABcd", "AbCD", "Abcd", "aBCD", "aBCd", "aBcD"});
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "ABCd", "ABcd", "AbCD", "AbCd", "AbcD", "Abcd", "aBCD", "aBCd", "aBcD"});
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "ABcD", "ABcd", "AbCd", "AbcD", "aBCD", "aBCd"});
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "ABcD", "AbcD", "aBCD", "aBcD"});
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "AbCD", "AbCd", "AbcD", "aBCD", "aBCd", "aBcD"});
    quain.method( PDNF, std::vector<std::string>{ "ABcD", "ABcd", "AbCD", "AbCd", "AbcD", "aBCD", "aBCd"});
#if 0
    quain.method(std::vector<std::string>{ "ABCD", "ABcD", "ABcd", "AbCd", "AbcD", "Abcd", "aBCD", "aBCd", "aBcD"}, true, "a");
    quain.method(std::vector<std::string>{ "ABCD", "ABCd", "ABcD", "ABcd", "AbCD", "Abcd", "aBCD", "aBCd", "aBcD"}, true, "b");
    quain.method(std::vector<std::string>{ "ABCD", "ABCd", "ABcd", "AbCD", "AbCd", "AbcD", "Abcd", "aBCD", "aBCd", "aBcD"}, true, "c");
    quain.method(std::vector<std::string>{ "ABCD", "ABcD", "ABcd", "AbCd", "AbcD", "aBCD", "aBCd"}, true, "d");
    quain.method(std::vector<std::string>{ "ABCD", "ABcD", "AbcD", "aBCD", "aBcD"}, true, "e");
    quain.method(std::vector<std::string>{ "ABCD", "AbCD", "AbCd", "AbcD", "aBCD", "aBCd", "aBcD"}, true, "f");
    quain.method(std::vector<std::string>{ "ABcD", "ABcd", "AbCD", "AbCd", "AbcD", "aBCD", "aBCd"}, true, "g");
#endif
}

int main() {
    get_quain_method();
    return  0;
}
