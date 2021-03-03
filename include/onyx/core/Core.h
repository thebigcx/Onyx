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

    T& operator*()
    {
        assert(valid());
        return *(m_ptr.lock());
    }

    operator std::shared_ptr<T>()
    {
        return m_ptr.lock();
    }

    operator bool()
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

private:
    std::weak_ptr<T> m_ptr;
};

}