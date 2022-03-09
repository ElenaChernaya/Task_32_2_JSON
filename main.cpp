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
                    {"actors", {{"Kiefer Sutherland"},
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
                dict["Dead end"]["studio_name"] = "France";
                dict["Mirrors"]["studio_name"] = "USA";
                dict["Paranormal Activity"]["studio_name"] = "USA";
                dict["Dead end"]["date_of_creation"] = 2003;
                dict["Mirrors"]["date_of_creation"] = 2008;
                dict["Paranormal Activity"]["date_of_creation"] = 2007;
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



    movie.genre = dict["Mirrors"]["genre"];
    movie.studio_name = dict["Dead end"]["studio_name"];
    movie.date_of_creation = dict["Paranormal Activity"]["date_of_creation"];

    std::cout << "\"Mirrors genre\" - " << movie.genre << "\n" << "\"Dead end studio_name\" - " << movie.studio_name
              << "\n" << "\"Paranormal Activity\" date_of_creation - " << movie.date_of_creation << std::endl;

    file.close();
}


int main() {
   Add();
   Search();
   return 0;
}
