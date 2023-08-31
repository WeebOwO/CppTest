#include <iostream>
#include <vector>
using namespace std;

template <typename T> class Vector {
public:
    Vector() = default;
    ~Vector() {
        delete[] m_data;
    }

    Vector(const Vector& other) {
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_data = new T[m_capacity];
        for(size_t i = 0; i < m_size; ++i) {
            m_data[i] = other.m_data[i];
        }
    }

    Vector& operator=(const Vector& other) {
        if(this != other) {
            delete[] m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_data = new T[m_capacity];
            for(size_t i = 0; i < m_capacity; ++i) {
                m_data[i] = other.m_data[i];
            }
        }
        return *this;
    }

    Vector(Vector&& other) noexcept {
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_data = other.m_data;
        other.m_size = 0;
        other.m_capacity = 0;
        other.m_data = nullptr;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_data = other.m_data;
            other.m_size = 0;
            other.m_capacity = 0;
            other.m_data = nullptr;
        }
        return *this;
    }

    void push_back(const T& val) {
        if (m_size >= m_capacity) {
            size_t newCapacity = m_capacity == 0 ? 1 : 2 * m_capacity;
            T*     newData     = new T[newCapacity];
            for (size_t i = 0; i < m_size; ++i) {
                newData[i] = m_data[i];
            }
            delete[] m_data;
            m_data     = newData;
            m_capacity = newCapacity;
        }
        m_data[m_size++] = val;
    }

    void push_back(T&& val) {
        if (m_size >= m_capacity) {
            size_t newCapacity = m_capacity == 0 ? 1 : 2 * m_capacity;
            T*     newData     = new T[newCapacity];
            for (size_t i = 0; i < m_size; ++i) {
                newData[i] = std::move(m_data[i]);
            }
            delete[] m_data;
            m_data     = newData;
            m_capacity = newCapacity;
        }
        m_data[m_size++] = val;
    }

    void pop_back() {
        if (m_size > 0) { m_size--; }
    }

    size_t size() { return m_size; }

    T& operator[](int index) { return m_data[index]; }

private:
    T*     m_data {nullptr};
    size_t m_size {0};
    size_t m_capacity {0};
};

int main() {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;

    vec.pop_back();

    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;

    return 0;
}
