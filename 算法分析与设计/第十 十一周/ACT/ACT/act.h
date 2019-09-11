#pragma once

#ifndef ACT_H
#define ACT_H

#include"pch.h"

struct Act {
	int begin, end;
};

int greedy(std::vector<Act>& testData);

int trace(std::vector<Act>& testData);

#endif