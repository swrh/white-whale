#include <ww/abstract_storage.hpp>

using namespace ww;

abstract_storage::abstract_storage()
{
}

void
abstract_storage::set_error(operation_error e)
{
    error = e;
}

abstract_storage::~abstract_storage()
{
}

abstract_storage::operation_error
abstract_storage::get_error() const
{
    return error;
}

std::string
abstract_storage::get_error_string() const
{
    switch (error) {
    case operation_error::success: return "Success";
    case operation_error::invalid_key_string: return "Invalid key string";
    case operation_error::invalid_value_string: return "Invalid value string";
    case operation_error::could_not_convert_data: return "Could not convert data";
    case operation_error::entry_not_found: return "Entry not found";
    }
    return "";
}


// vim:set sw=4 ts=4 et:
