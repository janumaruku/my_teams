/*
** EPITECH PROJECT, 2026
** tests
** File description:
** DLLoader
*/

#ifndef ARCADE_DLLOADER_HPP
    #define ARCADE_DLLOADER_HPP

    #include "ModuleCommons.hpp"
    #include <string>
    #include <dlfcn.h>
    #include <memory>

    #define ENTRYPOINT "module_entry_point"
    #define TYPEGETTER "module_query_type"

using dlHandler = void *;

class DLLoaderException : public std::exception {
public:
    DLLoaderException(const std::string &what): _what(what) {}
    const char *what() const noexcept override
    {
        return this->_what.c_str();
    }
private:
    const std::string _what;
};

template <typename T>
class DLLoader {
public:
    using entryPoint = T *(*)();

    ~DLLoader();
    explicit DLLoader(const std::string dlname);
    DLLoader(const DLLoader &a) = delete;
    DLLoader& operator=(const DLLoader&a) = delete;
    DLLoader(DLLoader &&) noexcept;
    DLLoader(std::unique_ptr<DLLoader> &&) noexcept;
    DLLoader& operator=(DLLoader &&) = delete;

    T *getInstance();
    ModuleType getInstanceType() const;
    std::string getName() const;
    void *extract(const std::string &fn_name);

private:
    T *_instance = nullptr;
    ModuleType _type;
    void *_entryPoint;
    dlHandler _dlhandler;
    std::string _name;
};

template <typename T>
void *DLLoader<T>::extract(const std::string &name)
{
    if (!this->_dlhandler)
        throw DLLoaderException("Invalid handler");
    if (dlerror() != nullptr)
        throw DLLoaderException("Previous error");
    void *function = dlsym(this->_dlhandler, name.c_str());

    if (!function || dlerror() != nullptr)
        throw DLLoaderException("Couldn't extract function from instance:" + name);
    return function;
}

template <typename T>
DLLoader<T>::DLLoader(const std::string dlname) : _name(dlname)
{
    dlHandler handler = dlopen(dlname.c_str(), RTLD_LAZY);

    if (!handler)
        throw DLLoaderException(dlerror());

    this->_dlhandler = handler;
    this->_entryPoint = this->extract(ENTRYPOINT);
    this->_type =
        reinterpret_cast<ModuleTypeQuery>(this->extract(TYPEGETTER))();
}

template <typename T>
T *DLLoader<T>::getInstance()
{
    if (this->_instance != nullptr)
        return this->_instance;
    if (this->_entryPoint == nullptr)
        throw DLLoaderException("No entrypoint");
    this->_instance = reinterpret_cast<entryPoint>(this->_entryPoint)();
    return this->_instance;
}

template <typename T>
ModuleType DLLoader<T>::getInstanceType() const
{
    return this->_type;
}

template <typename T>
std::string DLLoader<T>::getName() const
{
    return this->_name;
}

template <typename T>
DLLoader<T>::~DLLoader()
{
    if (this->_dlhandler)
        dlclose(this->_dlhandler);
}

template <typename T>
DLLoader<T>::DLLoader(DLLoader &&other) noexcept
    : _instance(other._instance),
      _type(other._type),
      _entryPoint(other._entryPoint),
      _dlhandler(other._dlhandler),
      _name(other._name)
{
    other._instance   = nullptr;
    other._entryPoint = nullptr;
    other._dlhandler  = nullptr;
}
#endif // !DLLOADER_HPP
