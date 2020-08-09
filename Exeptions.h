
#ifndef GCALC_EXEPTIONS_H
#define GCALC_EXEPTIONS_H
#include <exception>



class Exception : public std::exception {
public:
    const char* what() const noexcept ;

    };

    class ParserExceptions : public Exception {
    public:
        const char* what() const noexcept ;
    };

    class IllegalArgument : public ParserExceptions {
    public:
        const char* what() const noexcept ;
    };

    class ArgumentNotFound : public ParserExceptions {
    public:
        const char* what() const noexcept ;
    };

    class UndefinedCommand : public ParserExceptions {
    public:
        const char* what() const noexcept ;
    };

    class WrongVertexName : public ParserExceptions {
    public:
        const char* what() const noexcept ;
    };

    class WrongGraphName : public ParserExceptions {
    public:
        const char* what() const noexcept ;
    };

    class CantOpenFile : public ParserExceptions {
    public:
        const char* what() const noexcept ;
    };

    class OutOfAmmo : public ParserExceptions {

    };

    class IllegalTarget : public ParserExceptions {

    };




#endif //GCALC_EXEPTIONS_H
