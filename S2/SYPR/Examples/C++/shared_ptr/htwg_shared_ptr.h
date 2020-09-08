/*
 * htwg_shared_ptr.h
 *
 * Stark vereinfachter shared_ptr.
 *
 * Autor: H.Drachenfels
 * Erstellt am: 15.11.2019
 */
#ifndef HTWG_UNIQUE_PTR_H
#define HTWG_UNIQUE_PTR_H

namespace htwg
{
    template<typename T>
    class shared_ptr final
    {
    private:
        T *p;   // verwalteter Zeiger
        int *n; // Referenzzaehler
    public:
        shared_ptr()
        : p(nullptr), n(nullptr)
        { }

        explicit shared_ptr(T *q)
        : p(q), n(new int{1})
        { }

        ~shared_ptr()
        {
            if (this->n && --*this->n == 0)
            {
                delete this->p;
                delete this->n;
            }
        }

        shared_ptr(const shared_ptr& v)
        : p(v.p), n(v.n)
        {
            if (this->n)
            {
                ++*this->n;
            }
        }

        shared_ptr& operator=(const shared_ptr& v)
        {
            if (this != &v)
            {
                if (this->n && --*this->n == 0)
                {
                    delete this->p;
                    delete this->n;
                }

                this->p = v.p;
                this->n = v.n;

                if (this->n)
                {
                    ++*this->n;
                }
            }
            return *this;
        }

        shared_ptr(shared_ptr&& v)
        : p(v.p), n(v.n)
        {
            v.p = nullptr;
            v.n = nullptr;
        }

        shared_ptr& operator=(shared_ptr&& v)
        {
            if (this != &v)
            {
                if (this->n && --*this->n == 0)
                {
                    delete this->p;
                    delete this->n;
                }

                this->p = v.p;
                this->n = v.n;
                v.p = nullptr;
                v.n = nullptr;
            }
            return *this;
        }

        T* get() const
        {
            return this->p;
        }

        int use_count() const
        {
            return this->n ? *this->n : 0;
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
    bool operator==(const shared_ptr<T>& u, const shared_ptr<T>& v)
    {
        return u.get() == v.get();
    }

    template<typename T>
    bool operator!=(const shared_ptr<T>& u, const shared_ptr<T>& v)
    {
        return u.get() != v.get();
    }
}

#endif

