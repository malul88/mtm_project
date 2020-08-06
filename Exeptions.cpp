
#include "Exeptions.h"

const char *Exception::what() const noexcept {
    return "Error : Exception";
}

const char *ParserExceptions::what() const noexcept {
    return "Error : Parser Exception";}

const char *IllegalArgument::what() const noexcept {
    return "Error : Illegal Argument";
}

const char *ArgumentNotFound::what() const noexcept {
    return "Error : Argument Not Found";
}

const char *UndefinedCommand::what() const noexcept {
    return "Error : Undefined Command";
}

const char *WrongVertexName::what() const noexcept {
    return "Error : Wrong Vertex Name";
}

const char *WrongGraphName::what() const noexcept {
    return "Error : Wrong Graph Name";
}
