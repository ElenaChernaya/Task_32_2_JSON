#include <iostream>
#include "nlohmann/json.hpp"
#include <vector>
#include <map>
#include <fstream>


//Структура с данными о фильме

struct MovieAdd {
    std::string genre = "Horror";
    std::map<std::string, std::map<std::string, std::vector<std::string>>> list = {
            {"Dead end", {
                    {"autors", {{"Jean-Baptiste Andrea"}, {"Fabrice Canepa"}}},
                    {"directors", {{"Jean-Baptiste Andrea"}, {"Fabrice Canepa"}}},
                    {"producers", {{"Sonya Shillito"}, {"Gabriella Stollenwerk"}, {"Cecile Telerman"}}},
                    {"actors", {{"Alexandra Holden"},
                                      {"Ray Wise"},
                                      {"Lin Shay"},
                                      {"Mick Kane"},
                                      {"Amber Smith"},
                                      {"Billy Asher"},
                                      {"Karen S. Gregan"},
                                      {"Sharon Madden"},
                                      {"Steve Valentine"},
                                      {"Jimmy F. Skaggs"}}},
                    },
            },

            {"Mirrors", {
                    {"autors", {{"Alexandre Azha"}, {"Gregory Levasseur"}, {"Kim Seong-ho"}}},
                    {"directors", {"Alexandre Azha"}},
                    {"producers", {{"Gregory Levasseur"}, {"Alexandra Milchan"}, {"Mark Sternberg"}}},
                    {"actors", {{"Kie fer Sutherland"},
                                      {"Paula Patton"},
                                      {"Cameron Boyce"},
                                      {"Erica Gluck"},
                                      {"Amy Smart"},
                                      {"Mary Beth Peil"},
                                      {"John Shrapnel"},
                                      {"Jason Fleming"},
                                      {"Tim Ahern"},
                                      {"Julian Glover"}}}
                    }

            },

            {"Paranormal Activity", {
                    {"autors", {"Oren Peli"}},
                    {"directors", {"Oren Peli"}},
                    {"producers", {{"Jason Blum"}, {"Oren Peli"}, {"Rick Osako"}}},
                    {"actors", {{"Cathy Featherston"},
                                      {"Mika Slot"},
                                      {"Mark Fredericks"},
                                      {"Amber Armstrong"},
                                      {"Ashley Palmer"},
                                      {"Crystal Cartwright"},
                                      {"Spencer Marks"},
                                      {"Randy McDowell"},
                                      {"Tim Piper"}}}
                    }

            }
    };
};


//Структура для считывания данных из файла
struct MovieRead
{
    std::map<std::string, std::map<std::string, std::vector<std::string>>> list;
    std::string genre;
    std::string studio_name;
    int date_of_creation;
};


//функция для записи и сохранения данных о фильме в файл, в формате json
void Add()
{
    MovieAdd movie;
    nlohmann::json dict;
    std::ofstream file("movies.json");
    for (auto it = movie.list.begin(); it != movie.list.end(); ++it)
    {
        for (auto jt = movie.list[it->first].begin(); jt != movie.list[it->first].end(); ++jt)
        {
            for(int v = 0; v < jt->second.size(); ++v)
            {
                dict[it->first][jt->first].push_back(jt->second[v]);
                dict[it->first]["genre"] = movie.genre;
                dict["Dead end"]["studio name"] = "France";
                dict["Mirrors"]["studio name"] = "USA";
                dict["Paranormal Activity"]["studio name"] = "USA";
                dict["Dead end"]["date of creation"] = 2003;
                dict["Mirrors"]["date of creation"] = 2008;
                dict["Paranormal Activity"]["date of creation"] = 2007;
            }
        }
    }

    file << dict;
    file.close();
}


//функция для считывания из файла в структуру
void Search()
{
    MovieRead movie;
    std::ifstream file("movies.json");
    nlohmann::json dict;
    file >> dict;

    //.dump(4) - пропуск количества пробелов для отступа
      std::cout << dict.dump(4) << std::endl;
    //std::cout << std::setw(4) << dict << std::endl; //тоже самое, что и .dump(4)



    std::string name = "Mary Beth Peil"; //ищем кино в котором снималась данная актриса

    for (auto it = dict.begin(); it != dict.end(); ++it)
    {
        //преобразовываем ключ actors в значение, которое присваиваем переменной actors
        nlohmann::json actors = it.value()["actors"];

        auto c_name = to_string(actors); //преобразовываем массив строк в строку
        if (c_name.find(name) != std::string::npos) //делаем проход до конца строки
        {
            //если такое имя есть в строке - выводим ключ, по которому оно лежит. Т.е. - название фильма
            std::cout << name << " starred in the movie \"" << it.key() << "\"" << std::endl;
        }
    }


   //поиск по названию фильма и вывод в консоль отдельных его параметров
    movie.genre = dict["Mirrors"]["genre"];
    movie.studio_name = dict["Dead end"]["studio name"];
    movie.date_of_creation = dict["Paranormal Activity"]["date of creation"];

    std::cout << "\"Mirrors genre\" - " << movie.genre << "\n" << "\"Dead end\" studio name - " << movie.studio_name
              << "\n" << "\"Paranormal Activity\" date of creation - " << movie.date_of_creation << std::endl;

    file.close();
}


int main() {
   Add();
   Search();
   return 0;
}
