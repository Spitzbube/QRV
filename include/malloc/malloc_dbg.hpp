#ifdef _STD_USING
using std::malloc;
using std::calloc;
using std::free;
using std::realloc;
#endif

#ifndef CHECKED_PTR_T
#define CHECKED_PTR_T
typedef struct Dhead Dhead;

template < class T > class CheckedPtr {
  protected:
    T * bp;
    T *cp;
    size_t siz;
  public:
    CheckedPtr(void) {
        bp = NULL;
        cp = NULL;
        siz = -1;
    }
    CheckedPtr(const CheckedPtr < T > &p) {
        bp = p.bp;
        cp = p.cp;
        siz = p.siz;
    }
    CheckedPtr(T * p);
    CheckedPtr < T > &operator=(T * p);
    CheckedPtr < T > &operator++() {
        cp++;
        return *this;
    }
    CheckedPtr < T > &operator--() {
        cp--;
        return *this;
    }
    CheckedPtr < T > operator++(int) {
        CheckedPtr < T > temp(*this);
        cp++;
        return temp;
    }
    CheckedPtr < T > operator--(int) {
        CheckedPtr < T > temp(*this);
        cp--;
        return temp;
    }
    CheckedPtr < T > &operator+=(const CheckedPtr < T > &p) {
        cp += p.cp;
    }
    CheckedPtr < T > &operator-=(const CheckedPtr < T > &p) {
        cp -= p.cp;
    }
    bool operator==(const T * p) {
        return (cp == p);
    }
    bool operator==(const CheckedPtr < T > p) {
        return (cp == p.cp);
    }
    T & operator*();
    T & operator[](int i);
    T *operator->();
    operator  void *() {
        return cp;
    }
};

template < class T > CheckedPtr < T >::CheckedPtr(T * p)
{
    char *mptr;
    if ((mptr = _mptr((char *) p)) != NULL) {
        bp = (T *) mptr;
        cp = p;
        siz = _musize((char *) bp);
    } else {
        cp = p;
        siz = -1;
    }
}

template < class T > CheckedPtr < T > &CheckedPtr < T >::operator =(T * p)
{
    void *mptr;
    if ((mptr = _mptr((char *) p)) != NULL) {
        bp = (T *) mptr;
        cp = p;
        siz = _musize((char *) bp);
    } else {
        bp = p;
        cp = p;
        siz = -1;
    }
    return *this;
}

extern void *libmalloc_caller_fn(void);

template < class T > T & CheckedPtr < T >::operator*()
{
    if (cp == NULL) {
        void *line = (void *) libmalloc_caller_fn();
        malloc_warning("CheckedPtr<T>::operator*()", NULL, (int) line, NULL);
    }
    if (siz > 1) {
        if (cp < bp || cp >= (T *) ((char *) bp + siz)) {
            void *line = (void *) libmalloc_caller_fn();
            malloc_warning("CheckedPtr<T>::operator*()", NULL, (int) line,
                           (void *) ((Dhead *) bp - 1));
        }
    }
    return *cp;
}

template < class T > T * CheckedPtr < T >::operator->()
{
    if (cp == NULL) {
        void *line = (void *) libmalloc_caller_fn();
        malloc_warning("CheckedPtr<T>::operator->()", NULL, (int) line, NULL);
    }
    if (siz > 1) {
        if (cp < bp || cp >= (T *) ((char *) bp + siz)) {
            void *line = (void *) libmalloc_caller_fn();
            malloc_warning("CheckedPtr<T>::operator->()", NULL, (int) line,
                           (void *) ((Dhead *) bp - 1));
        }
    }
    return cp;
}

template < class T > T & CheckedPtr < T >::operator[](int i) {
    T * np = cp + i;
    if (cp == NULL) {
        void *line = (void *) libmalloc_caller_fn();
        malloc_warning("CheckedPtr<T>::operator[]()", NULL, (int) line, NULL);
    }
    if (siz > 1) {
        if (np < bp || np >= (T *) ((char *) bp + siz)) {
            void *line = (void *) libmalloc_caller_fn();
            malloc_warning("CheckedPtr<T>::operator[]()", NULL, (int) line,
                           (void *) ((Dhead *) bp - 1));
        }
    }
    return cp[i];
}
#endif                          /* CHECKED_PTR_T */
