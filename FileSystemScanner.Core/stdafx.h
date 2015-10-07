/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN // Исключите редко используемые компоненты из заголовков Windows

#include <string>
#include <memory>

#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/unordered_set.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
