/*
** EPITECH PROJECT, 2020
** clone_arcade
** File description:
** Exception
*/

#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <iostream>
#include <exception>

class Exception : public std::exception {
    public:
        Exception(const std::string &message);
        ~Exception() throw();
        std::string const &getComponent() const;
        virtual const char *what() const throw();

    protected:
        std::string _message;
    private:
};

#endif /* !EXCEPTION_HPP_ */
