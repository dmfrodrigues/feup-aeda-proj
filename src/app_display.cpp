#include "app.h"

void App::print_list(const std::vector<const Client*> &v){
    std::cout << std::endl;
    std::cout << " ╭─╴╷   ┬ ╭─╴╷ ╷╶┬╴╭─╴ \n"
              << " │  │   │ ├─╴│╲│ │ ╰─╮ \n"
              << " ╰─╴╰─╴ ┴ ╰─╴╵ ╵ ╵ ╶─╯ \n";
    std::cout << std::endl;
    std::cout << "╒════════════════╤═══════════════════════════════════════╤═══════════════════════════════╤═══════════════════════╤══════════════════╕" << std::endl;
    std::cout << "│ Username [0]   │ Name [1]                              │ Address [2]                   │ Phone number [3]      │ VAT [4]          │" << std::endl;
    std::cout << "╞════════════════╪═══════════════════════════════════════╪═══════════════════════════════╪═══════════════════════╪══════════════════╡" << std::endl;
    for(const Client* p:v){
        std::cout << "│ "
                  << utils::ljust((std::string)p->get_username()                 ,13) << "\t │ "
                  << utils::ljust((std::string)p->get_name()                     ,36) << "\t │ "
                  << utils::ljust((std::string)p->get_address().format("%street"),28) << "\t │ "
                  << utils::ljust((std::string)p->get_phonenumber()              ,20) << "\t │ "
                  << utils::rjust((std::string)p->get_vat()                      ,16) <<   " │"
                  << std::endl;
    }
    std::cout << "╘════════════════╧═══════════════════════════════════════╧═══════════════════════════════╧═══════════════════════╧══════════════════╛" << std::endl;
}

void App::print_list(const std::vector<const Driver*> &v){
    std::cout << std::endl;
    std::cout << " ┌─╮┌─╮ ┬ ╷  ╭─╴┌─╮╭─╴ \n"
              << " │ │├┬╯ │ │ ╱├─╴├┬╯╰─╮ \n"
              << " └─╯╵╰  ┴ │╱ ╰─╴╵╰ ╶─╯ \n";
    std::cout << std::endl;
    std::cout << "╒════════════════╤═══════════════════════════════════════╤═══════════════════════════════╤═══════════════════════╤══════════════════╤═════════════════╕" << std::endl;
    std::cout << "│ Username [0]   │ Name [1]                              │ Address [2]                   │ Phone number [3]      │ VAT [4]          │ Base salary [5] │" << std::endl;
    std::cout << "╞════════════════╪═══════════════════════════════════════╪═══════════════════════════════╪═══════════════════════╪══════════════════╪═════════════════╡" << std::endl;
    for(const Driver* p:v){
        std::cout << "│ "
                  << utils::ljust((std::string)p->get_username()                  ,13) << "\t │ "
                  << utils::ljust((std::string)p->get_name()                      ,36) << "\t │ "
                  << utils::ljust((std::string)p->get_address().format("%street") ,28) << "\t │ "
                  << utils::ljust((std::string)p->get_phonenumber()               ,20) << "\t │ "
                  << utils::rjust((std::string)p->get_vat()                       ,16) <<   " │ "
                  << utils::rjust(utils::ftos("%.2f",(double)p->get_base_salary()),15) <<   " │"
                  << std::endl;
    }
    std::cout << "╘════════════════╧═══════════════════════════════════════╧═══════════════════════════════╧═══════════════════════╧══════════════════╧═════════════════╛" << std::endl;
}

void App::print_list(const std::vector<const Manager*> &v){
    std::cout << std::endl;
    std::cout << " ╭┬╮╭─╮╷ ╷╭─╮╭─╮╭─╴┌─╮╭─╴ \n"
              << " │╵│├─┤│╲│├─┤│ ╮├─╴├┬╯╰─╮ \n"
              << " ╵ ╵╵ ╵╵ ╵╵ ╵╰─╯╰─╴╵╰╴╶─╯ \n";
    std::cout << std::endl;
    std::cout << "╒════════════════╤═══════════════════════════════════════╤═══════════════════════════════╤═══════════════════════╤══════════════════╤═════════════════╕" << std::endl;
    std::cout << "│ Username [0]   │ Name [1]                              │ Address [2]                   │ Phone number [3]      │ VAT [4]          │ Base salary [5] │" << std::endl;
    std::cout << "╞════════════════╪═══════════════════════════════════════╪═══════════════════════════════╪═══════════════════════╪══════════════════╪═════════════════╡" << std::endl;
    for(const Manager* p:v){
        std::cout << "│ "
                  << utils::ljust((std::string)p->get_username()                  ,13) << "\t │ "
                  << utils::ljust((std::string)p->get_name()                      ,36) << "\t │ "
                  << utils::ljust((std::string)p->get_address().format("%street") ,28) << "\t │ "
                  << utils::ljust((std::string)p->get_phonenumber()               ,20) << "\t │ "
                  << utils::rjust((std::string)p->get_vat()                       ,16) <<   " │ "
                  << utils::rjust(utils::ftos("%.2f",(double)p->get_base_salary()),15) <<   " │"
                  << std::endl;
    }
    std::cout << "╘════════════════╧═══════════════════════════════════════╧═══════════════════════════════╧═══════════════════════╧══════════════════╧═════════════════╛" << std::endl;
}

void App::display(const Client *p){
    std::cout << "╒══════════════════╤═════════════════════════════════════════════════════════════════════════════════════╕\n"
              << "│ [0] Username     │ " << utils::ljust((std::string)p->get_username()                        ,82) << "\t │\n"
              << "│ [1] Name         │ " << utils::ljust((std::string)p->get_name()                            ,82) << "\t │\n"
              << "│ [2] Address      │ " << utils::ljust(p->get_address().format("%street (%postal %city)")    ,82) << "\t │\n"
              << "│ [3] Phone number │ " << utils::ljust((std::string)p->get_phonenumber()                     ,82) << "\t │\n"
              << "│ [4] VAT          │ " << utils::ljust((std::string)p->get_vat()                             ,82) << "\t │\n"
              << "╘══════════════════╧═════════════════════════════════════════════════════════════════════════════════════╛" << std::endl;
}

void App::display(const Driver *p){
    std::cout << "╒══════════════════╤═════════════════════════════════════════════════════════════════════════════════════╕\n"
              << "│ [0] Username     │ " << utils::ljust((std::string)p->get_username()                        ,82) << "\t │\n"
              << "│ [1] Name         │ " << utils::ljust((std::string)p->get_name()                            ,82) << "\t │\n"
              << "│ [2] Address      │ " << utils::ljust(p->get_address().format("%street (%postal %city)")    ,82) << "\t │\n"
              << "│ [3] Phone number │ " << utils::ljust((std::string)p->get_phonenumber()                     ,82) << "\t │\n"
              << "│ [4] VAT          │ " << utils::ljust((std::string)p->get_vat()                             ,82) << "\t │\n"
              << "│ [5] Base salary  │ " << utils::ljust(utils::ftos("%.2f",(double)p->get_base_salary())      ,82) << "\t │\n"
              << "╘══════════════════╧═════════════════════════════════════════════════════════════════════════════════════╛" << std::endl;
}

void App::display(const Manager *p){
    std::cout << "╒══════════════════╤═════════════════════════════════════════════════════════════════════════════════════╕\n"
              << "│ [0] Username     │ " << utils::ljust((std::string)p->get_username()                        ,82) << "\t │\n"
              << "│ [1] Name         │ " << utils::ljust((std::string)p->get_name()                            ,82) << "\t │\n"
              << "│ [2] Address      │ " << utils::ljust(p->get_address().format("%street (%postal %city)")    ,82) << "\t │\n"
              << "│ [3] Phone number │ " << utils::ljust((std::string)p->get_phonenumber()                     ,82) << "\t │\n"
              << "│ [4] VAT          │ " << utils::ljust((std::string)p->get_vat()                             ,82) << "\t │\n"
              << "│ [5] Base salary  │ " << utils::ljust(utils::ftos("%.2f",(double)p->get_base_salary())      ,82) << "\t │\n"
              << "╘══════════════════╧═════════════════════════════════════════════════════════════════════════════════════╛" << std::endl;
}

void App::display(const Truck *p){
    std::cout << "╒══════════════════╤═════════════════════════════════════════════════════════════════════════════════════╕\n"
              << "│ [0] Number plate │ " << utils::ljust((std::string)p->get_numberplate()                     ,82) << "\t │\n"
              << "│ [2] Date         │ " << utils::ljust(p->get_plateregisterdate().format("%m/%Y")            ,82) << "\t │\n"
              << "│ [2] Fuel         │ " << utils::ljust(Truck::fuel_string(p->get_fuel())                     ,82) << "\t │\n"
              << "│ [3] Range        │ " << utils::ljust(utils::ftos("%.1f", (float)p->get_range())            ,82) << "\t │\n"
              << "│ [4] Category     │ " << utils::ljust((std::string)p->get_category()                        ,82) << "\t │\n"
              //<< "│ [5] Base salary  │ " << utils::ljust(utils::ftos("%.2f",(double)p->get_base_salary())      ,82) << "\t │\n"
              << "╘══════════════════╧═════════════════════════════════════════════════════════════════════════════════════╛" << std::endl;
}
