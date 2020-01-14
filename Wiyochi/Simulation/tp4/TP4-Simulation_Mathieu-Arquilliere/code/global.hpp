/**
 * @file global.hpp
 * @author Mathieu Arquilliere (mathieu.arquilliere@etu.uca.fr)
 * @brief Fichier d'include global pour que tous les fichiers ait accès aux includes et au distributions
 * @version 0.1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <iostream>
#include <random>
#include <cstring>
#include <list>
#include <algorithm>
#include <cmath>
#include <string>

extern std::mt19937 generator;
extern std::uniform_real_distribution<>    dis_real_0_1;
extern std::uniform_int_distribution<>     dis_int_3_6;
extern std::uniform_int_distribution<>     dis_int_0_11;
extern std::uniform_int_distribution<>     dis_int_5_8;
extern std::normal_distribution<>          dis_normal_6_1;

#endif