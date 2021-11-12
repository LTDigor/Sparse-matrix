#ifndef SPR_MRX_H
#define SPR_MRX_H

namespace spr_mrx
{
    const double EPS = 0.0000000001;
    const int MEMORY_ERROR = -1;

    struct item{
        double value;
        int row_index;
        int column_index;
        item* next = nullptr;
    };

    struct row{
        int row_index;
        row* next = nullptr;
        item* head_item = nullptr;
    };

    void add_item( item **item_cur, double value, int column_index);//add new element in the end of list
    void add_row( row **row_cur, int row_index );//add new element in the end of the list
    void print_row( item *item_cur );//print all list elements
    void print_row_with_zeros( item *item_cur, int column_quantity );//print all list elements
    void print_matrix( row *row_cur );//print matrix without zeros
    void print_matrix_with_zeros( row *row_cur, int row_quantity, int column_quantity );//print matrix with zeros
    void set_spare_matrix( row** row_cursor, int row_quantity, int column_quantity);//create new spare matrix
    void clean_row( item ** head_item );//delete all row elements
    void clean_matrix( row ** head_row );//delete all matrix rows
    int list_length( row * row_cur );//find value of elements in the list
    void sort_matrix( row ** head_row );
    void copy_martix( row* head_row, row** head_row_copied );//clean matrix head_row_copied and copy matrix head_row to head_row_copied
}

#endif
