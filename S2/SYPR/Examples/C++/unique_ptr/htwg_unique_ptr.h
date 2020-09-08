/*
 * htwg_unique_ptr.h
 *
 * Stark vereinfachter unique_ptr.
 *
 * Autor: H.Drachenfels
 * Erstellt am: 14.11.2019
 */
#ifndef HTWG_UNIQUE_PTR_H
#define HTWG_UNIQUE_PTR_H

namespace htwg
{
    template<typename T>
    class unique_ptr final
    {
    private:
        T *p;
    public:
        unique_ptr()
        : p(nullptr)
        { }

        explicit unique_ptr(T *q)
        : p(q)
        { }

        ~unique_ptr()
        {
            delete this->p;
        }

        unique_ptr(const unique_ptr& v) = delete;
        unique_ptr& operator=(const unique_ptr& v) = delete;

        unique_ptr(unique_ptr&& v)
        : p(v.p)
        {
            v.p = nullptr;
        }

        unique_ptr& operator=(unique_ptr&& v)
        {
            if (this != &v)
            {
                delete this->p;
                this->p = v.p;
                v.p = nullptr;
            }
            return *this;
        }

        T* get() const
        {
            return this->p;
        }

        operator bool()
        {
            return this->p != nullptr;
        }

        T& operator*() const
        {
            return *this->p;
        }

        T* operator->() const
        {
            return this->p;
        }
    };

    template<typename T>
    bool operator==(const unique_ptr<T>& u, const unique_ptr<T>& v)
    {
        return u.get() == v.get();
    }

    template<typename T>
    bool operator!=(const unique_ptr<T>& u, const unique_ptr<T>& v)
    {
        return u.get() != v.get();
    }
}

#endif

