//
// Created by Stoorx on 08.05.2019.
//

#pragma once

#include <exception>

class IncorrectArgsException :
        std::exception {
  public:
    virtual ~IncorrectArgsException() override = default;
};
