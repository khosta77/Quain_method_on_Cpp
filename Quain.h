#ifndef QUAIN_H_
#define QUAIN_H_

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
    int get_coincidence_parameters(const std::string &w1, const std::string &w2) const; 

    /* Функция вернет результат склеивания двух логических выражений
     * */
    std::string get_out_logex(const std::string &_l, const std::string &_r);

    /* Функция вернет строку одной колонки
     * */
    Row get_row( const std::string &_l, const size_t &_l_num, const std::string &_r, const size_t &_r_num);

    /*  Функци вернет колонку импликантов
     * */
    Col get_col_implicant(const std::vector<std::string> &y); 

    template<class T>
    void del_elem_in_vector(std::vector<T> &v, const T &elem); 

    /*  Функция очищает предыдущую колонку от повторных значений 
     * */
    std::vector<std::string> clear_pred_vector(); 

    /*  Функция возращает массив y взятых из колонки
     * */
    std::vector<std::string> get_y(const Col &col) const; 

    void get_cols(const std::vector<std::string> &y); 

    void get_y_optimized();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                        Вывод                                                        ////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::string conventer_to_tex(const std::string &str); 
    std::string conventer_to_tex_PDNF(const std::string &str); 
    std::string conventer_to_tex_PCNF(const std::string &str);

    std::string out_abcd(const std::string &str); 
    std::string out_abcd_PCNF(const std::string &str);

    /* Функция определяет колличество строк, которые надо будет выводить
     * */
    size_t get_size_row(const std::vector<std::string> &y, const std::vector<std::string> &y_optimized); 

    void out_1(); 
    void out_2(const std::vector<std::string> &y_result, const std::string &symbol); 

    void print_tex(const std::string &symbol);
    void print();

///////////////////////////////////////////////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
    void clear();

    public:
    Quain() = default;
    ~Quain() {
        clear();
    }
        
    void method(const int &form, const std::vector<std::string> &y_in, const bool &tex = false, const std::string &symbol = "a"); };


#endif  // QUAIN_H_
