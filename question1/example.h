

#include <iostream>

using uint = unsigned int;

template <typename T, typename R> class BasicIterator {
protected:
    T* p;
public:
    using ValueType = R;
    using Pointer = T*;
    using Reference = R&;
    BasicIterator(Pointer p) : p(p) {}
    virtual void advance() = 0;
    const Reference operator*() const { return *p; }
    Pointer operator->() const { return p; }
    bool operator==(const BasicIterator& rhs) const { return p == rhs.p; }
    bool operator!=(const BasicIterator& rhs) const { return p != rhs.p; }
    BasicIterator& operator++() { advance(); return *this; }
    BasicIterator operator++(int) { auto copy(*this); ++(*this); return copy; }
};


template <typename T> class Array {
    uint size; T* elements;
public:
    class Iterator : public BasicIterator<T, T> {
        void advance() { ++p; }
    public:
        Iterator(Pointer p) : BasicIterator(p) {}
        Iterator& operator++() { advance(); return *this; }
        Iterator operator++(int) { auto copy(*this); ++(*this); return copy; }
        const Reference operator*() const { return *p; }
        Pointer operator->() { return p; }
        bool operator==(const BasicIterator& rhs) const { return p == rhs.p; }
        bool operator!=(const BasicIterator& rhs) const { return p != rhs.p; }
    };
    Iterator begin() { return Iterator(elements); }
    Iterator end()
    {
        return elements == nullptr ? begin() : Iterator(&elements[size]);
    }
};



void main() {

	using ints = Array<int*>;

	using intIt = ints::Iterator;

    ints myInts;
	
    for (intIt it = myInts.begin(); it != myInts.end(); ++it) {

    }
	

}