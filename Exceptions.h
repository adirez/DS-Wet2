//
// Created by adire on 31-Dec-17.
//

#ifndef WET2_EXCEPTIONS_H
#define WET2_EXCEPTIONS_H

#include <exception>
#include <stdexcept>


class SplayException : public std::exception{};

class EmptyTree : public SplayException{};
class KeyAlreadyExists : public SplayException{};
class KeyNotFound : public SplayException{};
class InvalidParameter : public SplayException{};
class MemoryProblem : public SplayException{};

#endif //WET2_EXCEPTIONS_H
