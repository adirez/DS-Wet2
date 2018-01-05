//
// Created by adire on 31-Dec-17.
//

#ifndef WET2_EXCEPTIONS_H
#define WET2_EXCEPTIONS_H

#include <exception>
#include <stdexcept>

class ColosseumException : public std::exception{};

class EmptyTree : public ColosseumException{};
class KeyAlreadyExists : public ColosseumException{};
class KeyNotFound : public ColosseumException{};
class InvalidParameter : public ColosseumException{};
class Failure : public ColosseumException{};

#endif //WET2_EXCEPTIONS_H
