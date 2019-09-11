#pragma once
#ifndef TOOLS_H
#define TOOLS_H
#include "act.h"
#include "pch.h"

std::vector<Act> getTestData(int N);

double test(std::string testFunction, std::vector<Act>& testData);

void draw(std::vector<double>& time_t, std::vector<double>& time_g);

#endif