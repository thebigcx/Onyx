#pragma once

#include <memory>
#include <cassert>

namespace Onyx
{

template<typename T>
class WeakPtr
{
public:
    WeakPtr(const std::shared_ptr<T>& ptr)
        : m_ptr(ptr) {}
    
    WeakPtr(const nullptr_t& null)
        : m_ptr(std::shared_ptr<T>(null)) {}

    std::shared_ptr<T> operator->() const
    {
        assert(valid());
        return m_ptr.lock();
    }

    T& operator*() const
    {
        assert(valid());
        return *(m_ptr.lock());
    }

    std::shared_ptr<T> lock() const
    {
        return m_ptr.lock();
    }

    operator std::shared_ptr<T>() const
    {
        return m_ptr.lock();
    }

    operator bool() const
    {
        return valid();
    }

    bool valid() const
    {
        return !m_ptr.expired();
    }

    T* get() const
    {
        return m_ptr.lock().get();
    }

    std::weak_ptr<T> getPtr() const
    {
        return m_ptr;
    }

private:
    std::weak_ptr<T> m_ptr;
};

}