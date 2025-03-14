//
// Copyright (C) 2013 Mateusz Loskot <mateusz@loskot.net>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)
//

#ifndef SOCI_QUERY_TRANSFORMATION_H_INCLUDED
#define SOCI_QUERY_TRANSFORMATION_H_INCLUDED

#include "soci/soci-platform.h"
#include <string>

namespace soci
{

namespace details
{

// Query transformation is a mechanism that enables user to apply
// any string-to-string transformation to SQL statement just
// before it is executed.
// Transformation procedure is specified by user,
// be it a function or an arbitrary type as long as it
// defines operator() with the appropriate signature:
// unary function takes any type converible-to std::string
// and returns std::string.

class query_transformation_function
{
public:
    virtual ~query_transformation_function() {}
    virtual std::string operator()(std::string const&) const = 0;
};

template <typename T>
class query_transformation : public query_transformation_function
{
public:
    query_transformation(T callback)
        : callback_(callback)
    {}

    std::string operator()(std::string const& query) const override
    {
        return callback_(query);
    }

private:
    T callback_;
};

} // namespace details

} // namespace soci

#endif // SOCI_QUERY_TRANSFORMATION_H_INCLUDED
