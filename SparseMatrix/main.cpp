#include <iostream>
#include <cmath>
#include "sparse_matrix.h"

int main()
{
    spr_mrx::row* matrix = nullptr;
    spr_mrx::row* matrix_sorted = nullptr;
    int row_quantity, column_quantity;

    std::cout << "Enter the number of rows in the matrix: ";
    std::cin >> row_quantity;

    std::cout << "Enter the number of columns in the matrix: ";
    std::cin >> column_quantity;

    std::cout << "Enter matrix:" << std::endl;
    spr_mrx::set_spare_matrix( &matrix, row_quantity, column_quantity);

    std::cout << "Matrix without zeros:" << std::endl;
    spr_mrx::print_matrix(matrix);

    std::cout << "Matrix with zeros:" << std::endl;
    spr_mrx::print_matrix_with_zeros(matrix, row_quantity, column_quantity);

    spr_mrx::copy_martix( matrix, &matrix_sorted );

    std::cout << "New matrix without zeros:" << std::endl;
    spr_mrx::print_matrix(matrix_sorted);

    spr_mrx::sort_matrix(&matrix_sorted);

    std::cout << "New sorted matrix without zeros:" << std::endl;
    spr_mrx::print_matrix(matrix_sorted);

    spr_mrx::clean_matrix(&matrix);
    spr_mrx::clean_matrix(&matrix_sorted);

    return 0;
}
