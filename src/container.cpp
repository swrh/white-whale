#include <ww/container.hpp>

using namespace ww;

void
container::set_error(operation_error e)
{
    error = e;
}

container::operation_error
container::get_error() const
{
    return error;
}

std::string
container::get_error_string() const
{
    switch (error) {
    case operation_error::success:
        return "Success";
    case operation_error::unknown_error:
        return "Unknown error";
    case operation_error::invalid_key_or_value_type:
        return "Invalid key or value type";
    case operation_error::container_already_exists:
        return "Container already exists";
    case operation_error::container_not_found:
        return "Container not found";
    case operation_error::storage_error:
        std::string error_string("Container error");
        storage_ptr c = last_failing_storage.lock();
        if (c != nullptr)
            error_string += ": " + c->get_error_string();
        return error_string;
    }
    return "";
}

bool
container::add(const std::string &name, const std::string &key, const std::string &value)
{
    map_type::iterator it = storages.find(name);
    if (it == storages.end()) {
        set_error(operation_error::container_not_found);
        return false;
    }

    bool result = it->second->query_add(key, value);
    if (!result) {
        set_error(operation_error::storage_error);
        last_failing_storage = it->second;
        return false;
    }

    set_error(operation_error::success);
    return true;
}

bool
container::get(const std::string &name, const std::string &key, std::string &value)
{
    map_type::iterator it = storages.find(name);
    if (it == storages.end()) {
        set_error(operation_error::container_not_found);
        return false;
    }

    bool result = it->second->query_get(key, value);
    if (!result) {
        set_error(operation_error::storage_error);
        last_failing_storage = it->second;
        return false;
    }

    set_error(operation_error::success);
    return true;
}

bool
container::destruct(const std::string &name)
{
    map_type::iterator it = storages.find(name);
    if (it == storages.end()) {
        set_error(operation_error::container_not_found);
        return false;
    }

    storages.erase(it);
    set_error(operation_error::success);
    return true;
}

// vim:set sw=4 ts=4 et:
