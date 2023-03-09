#include "./Quain.h"


/* Функция проверяет совпадающие параметры(символы) 
 * Если все символы равны, но разные по значению \return true
 * Если все символы равны, все значения равны ---   // предполагается что одинаковых входных выражений
 *                                                   \ быть не должно
 * Иначе \return false
 * */
int Quain::get_coincidence_parameters(const std::string &w1, const std::string &w2) const {
	if (w1.size() != w2.size() || w1 == w2) {   // Проверка на одинаковый размер слов
		std::cout << "Выражение " << w1 << " конфликтует с " << w1 << " !!!" << std::endl;  
		throw;
	}

    int coincidence_parameters = 0;
    for (size_t k = 0; k < w1.size(); ++k)  // вопрос, стоит ли тут писать {}?
		if (w1[k] == w2[k])
            ++coincidence_parameters;
        else
			if (std::tolower(w1[k]) != std::tolower(w2[k]))
                return 0;
    return coincidence_parameters;
}

/* Функция вернет результат склеивания двух логических выражений
 * */
std::string Quain::get_out_logex(const std::string &_l, const std::string &_r) {
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
Quain::Row Quain::get_row( const std::string &_l, const size_t &_l_num, const std::string &_r, const size_t &_r_num) {
    std::string _buf_logex = get_out_logex( _l, _r);
    Impl impl( _l, _l_num, _r, _r_num);
	return Row(impl, _buf_logex);
}

/*  Функци вернет колонку импликантов
 * */
Quain::Col Quain::get_col_implicant(const std::vector<std::string> &y) {
    Col col;
    for (size_t i = 0; i < y.size() - 1; ++i) {
        for (size_t j = (i + 1); j < y.size(); ++j) {
			//Проверка на схожие символы, но разные значения в logex
            if (get_coincidence_parameters( y[i], y[j]) == (y[i].size() - 1)) {
                col.push_back(get_row(y[i], i, y[j], j)); 
            }
        }
    }
    return col;
}

template<class T>
void Quain::del_elem_in_vector(std::vector<T> &v, const T &elem) {
    for(auto iter = v.begin(); iter != v.end(); ++iter)
        if(*iter == elem) {
            v.erase(iter);
            break;
        }
}

/*  Функция очищает предыдущую колонку от повторных значений 
 * */
std::vector<std::string> Quain::clear_pred_vector() {
	// Импликант после преобразования
    std::vector<std::string> y_buffer = get_y(cols.at((cols.size() - ((cols.size() >= 2) ? 2 : 1))));
    for (size_t i = 0; i < cols.back().size(); ++i) {
        del_elem_in_vector( y_buffer, cols.back()[i].first._l_logex);
		del_elem_in_vector( y_buffer, cols.back()[i].first._r_logex);
    }
    return y_buffer;
}

/*  Функция возращает массив y взятых из колонки
 * */
std::vector<std::string> Quain::get_y(const Col &col) const {
    std::vector<std::string> y_buf;
    for (size_t i = 0; i < col.size(); ++i) {
		y_buf.push_back(col[i].second);
    }
    return y_buf;
}

void Quain::get_cols(const std::vector<std::string> &y) {
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

void Quain::get_y_optimized() {
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
std::string Quain::conventer_to_tex(const std::string &str) {
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

std::string Quain::conventer_to_tex_PDNF(const std::string &str) {
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

std::string Quain::conventer_to_tex_PCNF(const std::string &str) {
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

std::string Quain::out_abcd(const std::string &str) {
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

std::string Quain::out_abcd_PCNF(const std::string &str) {
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
size_t Quain::get_size_row(const std::vector<std::string> &y, const std::vector<std::string> &y_optimized) {
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

void Quain::out_1() {
    std::cout << "	\\begin{center}\n" 
	          << "     \\begin{tabular}{ |c|";
	for (size_t i = 0; i < cols.size(); ++i) 
        std::cout << "c|";
	std::cout << "c| }"
		      << "         \\hline\n";
}

void Quain::out_2( const std::vector<std::string> &y_result, const std::string &symbol) {
    std::cout << " 	\\hline\n"
	          << "   \\end{tabular}\n"
			  << "\\end{center}\n";
    std::cout << "$y_" << symbol << " =$ " << conventer_to_tex(y_result[0]); 
    for (size_t i = 1; i < y_result.size(); ++i) {
        std::cout << " + " << conventer_to_tex(y_result[i]); 
	}
    std::cout << std::endl;
}

void Quain::print_tex(const std::string &symbol) {
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
                std::cout << "+";
                std::cout << imp.first._r_num;
				for (size_t k = 0; k < j; ++k)
                    std::cout << "'";
                std::cout << "="; 
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
 
void Quain::print() {
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

void Quain::clear() {
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

void Quain::method(const int &form, const std::vector<std::string> &y_in, const bool &tex, const std::string &symbol) { 
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


