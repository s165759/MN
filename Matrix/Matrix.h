//
// Created by maxchil on 3/29/18.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <vector>

template <typename T>
class AbstractMatrix {

protected:
    std::vector<int> dimensions;

public:
    virtual AbstractMatrix(std::initializer_list<int> dim) : dimensions(dim){};
    virtual ~AbstractMatrix() = default;

public:
    virtual AbstractMatrix& operator*= (AbstractMatrix& rhs) = 0;
    virtual AbstractMatrix& operator+= (AbstractMatrix& rhs) = 0;
    virtual AbstractMatrix operator+  (AbstractMatrix lhs, AbstractMatrix& rhs) = 0;
    virtual AbstractMatrix operator* (AbstractMatrix lhs, AbstractMatrix& rhs) = 0;
    virtual AbstractMatrix& operator-= (AbstractMatrix& rhs) = 0;
    virtual AbstractMatrix operator- (AbstractMatrix lhs, AbstractMatrix& rhs) = 0;
    virtual AbstractMatrix& operator/= (AbstractMatrix& rhs) = 0;
    virtual AbstractMatrix operator/ (AbstractMatrix lhs, AbstractMatrix& rhs) = 0;

    template <typename U>
    virtual AbstractMatrix& operator*= (U u) = 0;

    template <typename U>
    virtual AbstractMatrix operator* (AbstractMatrix lhs, U& rhs) = 0;

    template <typename U>
    virtual AbstractMatrix& operator/= (U& rhs) = 0;

    template <typename U>
    virtual AbstractMatrix operator/ (AbstractMatrix lhs, U& rhs) = 0;


    virtual T &operator()(std::initializer_list<int> l) = 0;
};

template <typename T>
class Matrix : public AbstractMatrix<T>{

    T *values;

public:

    Matrix::Matrix(const std::initializer_list<int> &dim) : AbstractMatrix(dim) {
        int no_elements = 0;

        for (auto& e : dim) {
            no_elements += e;
        }

        values = new T[no_elements];
    }

    AbstractMatrix<T> &operator*=(AbstractMatrix &rhs) override {

    }

    AbstractMatrix<T> &operator+=(AbstractMatrix &rhs) override {
        return <#initializer#>;
    }

    AbstractMatrix<T> operator+(AbstractMatrix lhs, AbstractMatrix &rhs) override {
        return nullptr;
    }

    AbstractMatrix<T> operator*(AbstractMatrix lhs, AbstractMatrix &rhs) override {
        return nullptr;
    }

    AbstractMatrix<T> &operator-=(AbstractMatrix &rhs) override {
        return <#initializer#>;
    }

    AbstractMatrix<T> operator-(AbstractMatrix lhs, AbstractMatrix &rhs) override {
        return nullptr;
    }

    AbstractMatrix<T> &operator/=(AbstractMatrix &rhs) override {
        return <#initializer#>;
    }

    AbstractMatrix<T> operator/(AbstractMatrix lhs, AbstractMatrix &rhs) override {
        return nullptr;
    }

    template <typename U>
    AbstractMatrix<T> &operator*=(U u) override {

        for (int i = 0; i < sizeof(values) / sizeof(T); ++i) {
            values[i] *= u;
        }

        return *this;
    }

    template <typename U>
    AbstractMatrix<T> operator*(AbstractMatrix lhs, U &rhs) override {
        return lhs *= rhs;
    }

    template <typename U>
    AbstractMatrix<T> &operator/=(U &rhs) override {
        for (int i = 0; i < sizeof(values) / sizeof(T); ++i) {
            values[i] /= rhs;
        }

        return *this;
    }

    template <typename U>
    AbstractMatrix<T> operator/(AbstractMatrix lhs, U &rhs) override {
        return lhs /= rhs;
    }

    T &operator()(std::initializer_list<int> l) override {
        static_assert(l.size() == dimensions.size());

        int indeks = 0;
        auto dimIter = dimensions.end();

        for(auto iter = l.end(); iter != l.begin(); iter--){
            indeks *= *dimIter;
            indeks += *iter;
            dimIter--;
        }

        return values[indeks];

    }

};


#endif //MATRIX_MATRIX_H
