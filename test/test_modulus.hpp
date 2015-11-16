#ifndef BOOST_TEST_MODULUS_HPP
#define BOOST_TEST_MODULUS_HPP

//  Copyright (c) 2015 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <exception>
#include <cxxabi.h>

#include "../include/safe_integer.hpp"

template<class T1, class T2>
bool test_modulus(
    T1 v1,
    T2 v2,
    const char *av1,
    const char *av2,
    char expected_result
){
    std::cout
        << "testing  "
        << av1 << " % " << av2
        << std::endl;
    {
        safe_t<T1> t1 = v1;
        safe_t<decltype(v1 % v2)> result;

        try{
            result = t1 % v2;

            static_assert(
                boost::numeric::is_safe<decltype(t1 + v2)>::value,
                "Expression failed to return safe type"
            );
            
            if(expected_result != '.'){
                std::cout
                    << "failed to detect error in modulus "
                    << std::hex << result << "(" << std::dec << result << ")"
                    << " ! = "<< av1 << " % " << av2
                    << std::endl;
                try{
                    t1 % v2;
                }
                catch(std::exception){}
                return false;
            }
        }
        catch(std::exception){
            if(expected_result != 'x'){
                std::cout
                    << "erroneously detected error in modulus "
                    << std::hex << result << "(" << std::dec << result << ")"
                    << " == "<< av1 << " % " << av2
                    << std::endl;
                try{
                    t1 % v2;
                }
                catch(std::exception){}
                return false;
            }
        }
    }
    {
        safe_t<T2> t2 = v2;
        safe_t<decltype(v1 % v2)> result;

        try{
            result = v1 % t2;

            static_assert(
                boost::numeric::is_safe<decltype(v1 % t2)>::value,
                "Expression failed to return safe type"
            );
            
            if(expected_result != '.'){
                std::cout
                    << "failed to detect error in modulus "
                    << std::hex << result << "(" << std::dec << result << ")"
                    << " ! = "<< av1 << " % " << av2
                    << std::endl;
                try{
                    v1 % t2;
                }
                catch(std::exception){}
                return false;
            }
        }
        catch(std::exception){
            if(expected_result != 'x'){
                std::cout
                    << "erroneously detected error in modulus "
                    << std::hex << result << "(" << std::dec << result << ")"
                    << " == "<< av1 << " % " << av2
                    << std::endl;
                try{
                    v1 % t2;
                }
                catch(std::exception){}
                return false;
            }
        }
    }
    {
        safe_t<T1> t1 = v1;
        safe_t<T2> t2 = v2;

        safe_t<decltype(v1 % v2)> result;

        try{
            result = t1 % t2;

            if(expected_result != '.'){
                std::cout
                    << "failed to detect error in modulus "
                    << std::hex << result << "(" << std::dec << result << ")"
                    << " ! = "<< av1 << " % " << av2
                    << std::endl;
                try{
                    result = t1 % t2;
                }
                catch(std::exception){}
                return false;
            }
        }
        catch(std::exception){
            if(expected_result != 'x'){
                std::cout
                    << "erroneously detected error in modulus "
                    << std::hex << result << "(" << std::dec << result << ")"
                    << " == "<< av1 << " % " << av2
                    << std::endl;
                try{
                    t1 % t2;
                }
                catch(std::exception){}
                return false;
            }
        }
    }
    return true;
}

#endif // BOOST_TEST_MODULUS
