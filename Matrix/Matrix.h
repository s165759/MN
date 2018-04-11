//
// Created by maxchil on 3/29/18.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <array>
#include <cassert>
#include <iostream>

namespace Matrix {

    template <typename value_t, size_t N, size_t M>
    class DenseMatrix{

        value_t values[N * M];

        typedef DenseMatrix<value_t, N, M> matrix_t;

    public:

        static const size_t rows = N;
        static const size_t cols = M;

        DenseMatrix(
                std::initializer_list<std::initializer_list<value_t>> init
        ) {
            int a = 0;

            for (auto i = init.begin(); i != init.end() ; ++i) {
                for (auto j = i->begin(); j != i->end() ; ++j) {
                    values[a] = *j;
                    a++;
                }
            }
        }

        DenseMatrix() = default;

        inline value_t& operator()(size_t n, size_t m){
            return values[n * cols + m];
        }


//        Working implementation
//        template<
//                class matrix_t,
//                class matrix_out_t = DenseMatrix<value_t, rows, matrix_t::cols>
//        >
//        matrix_out_t&& operator*(matrix_t& multi) {
//
//            static_assert(cols == matrix_t::rows, "Matrix dimensions mismatch");
//
//            matrix_out_t a;
//
//            for (size_t i = 0; i < rows; ++i) {
//                for (size_t j = 0; j < matrix_t::cols; ++j) {
//                    a(i, j) = 0;
//                    for (size_t k = 0; k < cols; ++k) {
//                        a(i, j) += (*this) (i, k) * multi(k, j);
//                    }
//                }
//            }
//
//            return std::move(a);
//        }

        template <typename T, size_t C>
        DenseMatrix<T, rows, C>&& operator*(DenseMatrix<T, cols, C>& multi) {
            DenseMatrix<T, rows, C> a;

            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < C; ++j) {
                    a(i, j) = 0;
                    for (size_t k = 0; k < cols; ++k) {
                        a(i, j) += (*this) (i, k) * multi(k, j);
                    }
                }
            }

            return std::move(a);
        }

        matrix_t&& operator+(matrix_t& add){
            matrix_t a;

            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < cols; ++j) {
                    a(i, j) = add(i, j) + (*this)(i, j);
                }
            }

            return std::move(a);
        };

        friend std::ostream& operator<< (std::ostream& stream, matrix_t& m){

            stream << "dimensions: (" << rows << " x " << matrix_t::cols << ')' << std::endl;

            for (size_t i = 0; i < matrix_t::rows; ++i) {
                for (size_t j = 0; j < matrix_t::cols; ++j) {
                    stream << m(i, j) << ' ';
                }
                stream << '\n';
            }

            return stream;
        }
    };

}
#endif //MATRIX_MATRIX_H
