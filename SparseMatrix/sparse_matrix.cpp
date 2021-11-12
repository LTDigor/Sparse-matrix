#include <iostream>
#include <cmath>
#include "sparse_matrix.h"

namespace spr_mrx
{
    void add_item( item **item_cur, double value, int column_index)//add new element in the end of list
    {

        item* new_item = new item;//create new element of the list
        if(new_item == nullptr)
            exit( MEMORY_ERROR );

        new_item->next = nullptr;
        new_item->value = value;
        new_item->column_index = column_index;

        for( ; ( *item_cur ); item_cur = &( ( *item_cur )->next ) )//go to the last element
        {}

        ( *item_cur ) = new_item;
    }

    void add_row( row **row_cur, int row_index )//add new element in the end of the list
    {
        row* new_row = new row;//create new element of the list
        if(new_row == nullptr)
            exit( MEMORY_ERROR );

        new_row->next = nullptr;
        new_row->head_item = nullptr;
        new_row->row_index = row_index;

        for( ; ( *row_cur ); row_cur = &( ( *row_cur )->next ) )//go to the last element
        {}

        ( *row_cur ) = new_row;
    }


    void print_row( item *item_cur )//print all list elements
    {
        item *head = item_cur;

        for( ; item_cur; item_cur = item_cur->next )//goes through all the elements
            std::cout << item_cur->value << " ";

        if( head )
            std::cout << std::endl;//don't create new line if row is empty
    }

    void print_row_with_zeros( item *item_cur, int column_quantity )//print all list elements
    {
        for(int i = 0; i < column_quantity; i++)
        {
            if(item_cur == nullptr || item_cur->column_index > i)
                std::cout << 0 << " ";
            else
            {
                std::cout << item_cur->value << " ";
                item_cur = item_cur->next;
            }
        }
        std::cout << std::endl;

    }

    void print_matrix( row *row_cur )//print matrix without zeros
    {
        row *head = row_cur;

        for( ; row_cur; row_cur = row_cur->next )//goes through all the elements
        {
            //cout<< "Row index: " << row_cur->row_index << "::";
            print_row(row_cur->head_item);
        }

        if( head )//if matrix is empty print message
            std::cout << std::endl;
        else
            std::cout << "Matrix is empty" << std::endl << std::endl;
    }

    void print_matrix_with_zeros( row *row_cur, int row_quantity, int column_quantity )//print matrix with zeros
    {
        row *head = row_cur;

        for(int i = 0; i < row_quantity; i++)
        {
            if(row_cur == nullptr || row_cur->row_index > i)
            {
                for(int j = 0; j < column_quantity; j++)
                    std::cout << 0 << " ";
                std::cout << std::endl;
            }
            else
            {
                print_row_with_zeros(row_cur->head_item, column_quantity);
                row_cur = row_cur->next;
            }
        }

        if( head )//if matrix is empty print message
            std::cout << std::endl;
        else
            std::cout << "Matrix is empty" << std::endl << std::endl;
    }

    void set_spare_matrix( row** row_cursor, int row_quantity, int column_quantity)
    {
        for(int row_index = 0; row_index < row_quantity; row_index++)
        {
            bool row_has_items = false;
            for(int column_index = 0; column_index < column_quantity; column_index++)
            {
                double value;
                std::cin >> value;

                if( abs(value) < EPS ) //compare with 0
                    continue;

                if(row_has_items == false)
                {
                    add_row( row_cursor, row_index );
                    row_has_items = true;
                }
                add_item( &((*row_cursor)->head_item), value, column_index);
            }
            if( row_has_items == true)
                row_cursor = &( ( *row_cursor )->next );
        }
    }

    void clean_row( item ** head_item )//delete all row elements
    {
        item *tmp;//helper variable to save pointer *head_item value

        for( ; *head_item; )
        {
            tmp = *head_item;
            *head_item = ( *head_item )->next;
            delete tmp;
        }
    }

    void clean_matrix( row ** head_row )//delete all matrix rows
    {
        row *tmp;//helper variable to save pointer *head_item value

        for( ; *head_row; )
        {
            tmp = *head_row;
            clean_row(&((*head_row)->head_item));
            *head_row = ( *head_row )->next;
            delete  tmp;
        }
    }

    int list_length( row * row_cur )//find value of elements in the list
    {
        int counter = 0;
        for( ; row_cur; row_cur = row_cur->next )//goes through all the elements
            counter++;

        return counter;
    }


    void sort_matrix( row ** head_row )
    {
        int list_len = list_length( *head_row );

        if( (*head_row)->head_item->value > 0)//sort desc
        {
            for( int i = 0; i < list_len - 1; i++ )//bubble sort
            {
                row* tmp_head_row = *head_row;//helpful pointer to save head

                for( int j = 0; j < list_len - 1 - i; j++ )
                {
                    if( (*head_row)->head_item->value <  (*head_row)->next->head_item->value )
                    {
                        //swap head_item pointers in the rows
                        item *tmp_head_item = (*head_row)->head_item;
                        (*head_row)->head_item = (*head_row)->next->head_item;
                        (*head_row)->next->head_item = tmp_head_item;

                        //swap row_index pointers in the rows
                        double tmp_row_index = (*head_row)->row_index;
                        (*head_row)->row_index = (*head_row)->next->row_index;
                        (*head_row)->next->row_index = tmp_row_index;
                    }

                    head_row = &((*head_row)->next);
                }

                head_row = &(tmp_head_row->next);
            }
        }
        else//sort asc
        {
            for( int i = 0; i < list_len - 1; i++ )//bubble sort
            {
                row* tmp_head_row = *head_row;//helpful pointer to save head

                for( int j = 0; j < list_len - 1 - i; j++ )
                {
                    if( (*head_row)->head_item->value >  (*head_row)->next->head_item->value )
                    {
                        item *tmp_head_item = (*head_row)->head_item;//helpful pointer to swap
                        (*head_row)->head_item = (*head_row)->next->head_item;
                        (*head_row)->next->head_item = tmp_head_item;
                    }

                    head_row = &((*head_row)->next);
                }

                head_row = &(tmp_head_row->next);
            }

        }

    }

    void copy_martix( row* head_row, row** head_row_copied )//clean matrix head_row_copied and copy matrix head_row to head_row_copied
    {
        clean_matrix(head_row_copied);

        for( ; head_row; head_row = head_row->next )//go through all rows
        {
            add_row( head_row_copied, head_row->row_index );

            for( ; head_row->head_item; head_row->head_item = head_row->head_item->next)//go through all items in the row
            {
                //add item from old matrix to new
                add_item(&((*head_row_copied)->head_item), head_row->head_item->value,
                          head_row->head_item->column_index);
            }

            head_row_copied = &((*head_row_copied)->next);
        }

    }
}
