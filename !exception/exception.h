// ННГУ, ИИТММ, Курс "Основы программирования"
//
// Copyright (c) Сысоев А.В.
// 
// 29.03.2023
//
// exception.h - Класс для работы с исключениями

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <cstring>

namespace file_fuction_line_exception
{
  using std::copy;

  enum TExceptionSizes
  {
    es_file_default_size = 20,
    es_func_default_size = 20,
    es_desc_default_size = 100
  };

  template <size_t file_size, size_t func_size, size_t desc_size>
  class TException
  {
  private:
    char   file[file_size + 1];
    char   function[func_size + 1];
    size_t line;
    char   description[desc_size + 1];
  public:
    TException(const char* _file, const char* _function, int _line,
      const char* _description) noexcept
    {
      size_t sz;
      const char* slash = std::strrchr(_file, '\\');
      _file = slash + 1;
      sz = std::strlen(_file);
      sz = (sz <= file_size) ? sz : file_size;
      copy(_file, _file + sz, file);
      file[sz] = '\0';

      sz = std::strlen(_function);
      sz = (sz <= func_size) ? sz : func_size;
      copy(_function, _function + sz, function);
      function[sz] = '\0';

      line = _line;

      sz = std::strlen(_description);
      sz = (sz <= desc_size) ? sz : desc_size;
      copy(_description, _description + sz, description);
      description[sz] = '\0';
    }
    ~TException() = default;
    const char* GetFile() const noexcept
    {
      return file;
    }
    size_t GetLine() const noexcept
    {
      return line;
    }
    const char* GetFunction() const noexcept
    {
      return function;
    }
    const char* GetDescription() const noexcept
    {
      return description;
    }
  };
}

namespace ffle = file_fuction_line_exception;

#define TFFLE_EXCEPTION ffle::TException<ffle::es_file_default_size,\
 ffle::es_func_default_size, ffle::es_desc_default_size>

#define FFLE_EXCEPTION_OBJ(desc) ffle::TException<ffle::es_file_default_size,\
 ffle::es_func_default_size, ffle::es_desc_default_size>(__FILE__, __FUNCTION__, __LINE__, desc)

#endif // __EXCEPTION_H__
