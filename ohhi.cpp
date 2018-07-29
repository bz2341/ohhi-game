
#include <iostream>
#include <cctype>
#include "utility.h"
#include "ohhi.h"

/**
 * --------------------------------------------------------
 * ---------- UTILITY FUNCTIONS ---------------------------
 * --------------------------------------------------------
 */

int count_unknown_squares(const int board[MAX_SIZE][MAX_SIZE], int size) {
	int num_of_unknown=0;
	for(int row=0;row<size;row++){
		for(int col=0;col<size;col++){
			if(board[row][col]!=RED&&board[row][col]!=BLUE){
				num_of_unknown++;
			}
		}
	}
	
	return num_of_unknown; 
}

/**
 * --------------------------------------------------------
 * --------- VALIDITY CHECKING FUNCTIONS ------------------
 * --------------------------------------------------------
 */


bool row_has_no_threes_of_color(const int board[MAX_SIZE][MAX_SIZE],
                                int size,
                                int row,
                                int color) {
    bool result=true;
    if(!((size<=MAX_SIZE)&&(size>0)&&(size%2==0))){
    	cout<<"the parameter \"size\" is improper.\n";
    	return -1;
	}
    if(!((0<=row)&&(row<size))){
    	cout<<"the parameter \"row\" is improper.\n";
        return -1;   	
	}
    for(int i=0;i<size-2;i++){
    	if((board[row][i]==color)&&(board[row][i+1]==color)&&(board[row][i+2]==color)){
		    result=false;
		}
	}

    return result;
}


bool col_has_no_threes_of_color(const int board[MAX_SIZE][MAX_SIZE],
                                int size,
                                int col,
                                int color) {                               	
    bool result=true;
    if(!((size<=MAX_SIZE)&&(size>0)&&(size%2==0))){
    	cout<<"the parameter \"size\" is improper.\n";
    	return -1;
	}
    if(!((0<=col)&&(col<size))){
    	cout<<"the parameter \"col\" is improper.\n";
        return -1;   	
	}
    for(int j=0;j<size-2;j++){
    	if((board[j][col]==color)&&(board[j+1][col]==color)&&(board[j+2][col]==color)){
		    result=false;
		}
	}

    return result;
}


bool board_has_no_threes(const int board[MAX_SIZE][MAX_SIZE], int size) {
    bool result=true;
    if(!((size<=MAX_SIZE)&&(size>0)&&(size%2==0))){
    	cout<<"the parameter \"size\" is improper.\n";
    	return -1;
	}
    for(int i=0;i<size;i++){
    	if((row_has_no_threes_of_color(board,size,i,RED)==false)
		||(row_has_no_threes_of_color(board,size,i,BLUE)==false)){
    		result=false;
		}
	}
    for(int j=0;j<size;j++){
    	if((col_has_no_threes_of_color(board,size,j,RED)==false)
		||(col_has_no_threes_of_color(board,size,j,BLUE)==false)){
    		result=false;
		}
	}
    
    return result;
}


bool rows_are_different(const int board[MAX_SIZE][MAX_SIZE],
                        int size,
                        int row1,
                        int row2) {
   bool result=false;
   if(!((size<=MAX_SIZE)&&(size>0)&&(size%2==0))){
    	cout<<"the parameter \"size\" is improper.\n";
    	return -1;
	}
	if(!((0<=row1)&&(row1<size))){
		cout<<"the parameter \"row1\" is improper.\n";
    	return -1;
	}
    if(!((0<=row2)&&(row2<size))){
		cout<<"the parameter \"row2\" is improper.\n";
    	return -1;
    }
    for(int j=0;j<size;j++){
    	if(board[row1][j]!=board[row2][j]){
    		result=true;
    		break;
		}else if((board[row1][j]==UNKNOWN)||(board[row2][j]==UNKNOWN)){
		    result=true;
		    break;
	    }else{
	    	result=false;
		}	
	}

    return result;
}


bool cols_are_different(const int board[MAX_SIZE][MAX_SIZE],
                        int size,
                        int col1,
                        int col2) {
   bool result=false;
   if(!((size<=MAX_SIZE)&&(size>0)&&(size%2==0))){
    	cout<<"the parameter \"size\" is improper.\n";
    	return -1;
	}
	if(!((0<=col1)&&(col1<size))){
		cout<<"the parameter \"col1\" is improper.\n";
    	return -1;
	}
    if(!((0<=col2)&&(col2<size))){
		cout<<"the parameter \"col2\" is improper.\n";
    	return -1;
    }
    for(int i=0;i<size;i++){
    	if(board[i][col1]!=board[i][col2]){
    		result=true;
    		break;
		}else if((board[i][col1]==UNKNOWN)||(board[i][col2]==UNKNOWN)){
		    result=true;
		    break;
	    }else{
	    	result=false;
		}	
	}

    return result;
}



bool board_has_no_duplicates(const int board[MAX_SIZE][MAX_SIZE], int size) {
    bool result=true;
    if(!((size<=MAX_SIZE)&&(size>0)&&(size%2==0))){
    	cout<<"the parameter \"size\" is improper.\n";
    	return -1;
	}
    for(int i=0;i<size;i++){
    	for(int j=i+1;j<size;j++){
    		if(rows_are_different(board,size,i,j)==false){
    		    result=false;
    		    break;
		    }
		}
	}
    for(int i=0;i<size;i++){
    	for(int j=i+1;j<size;j++){
    		if(cols_are_different(board,size,i,j)==false){
    		    result=false;
    		    break;
		    }
		}
	}
    
    return result;


}

/**
 * --------------------------------------------------------
 * ---------- SOLVING FUNCTIONS ---------------------------
 * --------------------------------------------------------
 */

void solve_three_in_a_row(int board[MAX_SIZE][MAX_SIZE],
                          int size,
                          int row,
                          bool announce) {
    if(!((size<=MAX_SIZE)&&(size>0)&&(size%2==0))){
    	cout<<"the parameter \"size\" is improper.\n";
    	return;
	}
    if(!((0<=row)&&(row<size))){
    	cout<<"the parameter \"row\" is improper.\n";
        return;   	
	}
	if(!(board_is_valid(board,size))){
		cout<<"the board is invalid.\n";
		return;
	}
    for(int i=0;i<size;i++){
    	if((board[row][i]==UNKNOWN)&&(board[row][i+1]==RED)&&(board[row][i+2]==RED)){
    		mark_square_as(board,size,row,i,BLUE,announce); 
		}else if((board[row][i]==UNKNOWN)&&(board[row][i+1]==BLUE)&&(board[row][i+2]==BLUE)){
			mark_square_as(board,size,row,i,RED,announce);
		}else if((board[row][i]==RED)&&(board[row][i+1]==UNKNOWN)&&(board[row][i+2]==RED)){
			mark_square_as(board,size,row,i+1,BLUE,announce);
		}else if((board[row][i]==BLUE)&&(board[row][i+1]==UNKNOWN)&&(board[row][i+2]==BLUE)){
			mark_square_as(board,size,row,i+1,RED,announce);
		}else if((board[row][i]==RED)&&(board[row][i+1]==RED)&&(board[row][i+2]==UNKNOWN)){
			mark_square_as(board,size,row,i+2,BLUE,announce);
		}else if((board[row][i]==BLUE)&&(board[row][i+1]==BLUE)&&(board[row][i+2]==UNKNOWN)){
			mark_square_as(board,size,row,i+2,RED,announce);
		}
	}

    return;
}


void solve_three_in_a_column(int board[MAX_SIZE][MAX_SIZE],
                          int size,
                          int col,
                          bool announce) {
    if(!((size<=MAX_SIZE)&&(size>0)&&(size%2==0))){
    	cout<<"the parameter \"size\" is improper.\n";
    	return;
	}
    if(!((0<=col)&&(col<size))){
    	cout<<"the parameter \"col\" is improper.\n";
        return;   	
	}
	if(!(board_is_valid(board,size))){
		cout<<"the board is invalid.\n";
		return;
	}
    for(int i=0;i<size;i++){
    	if((board[i][col]==UNKNOWN)&&(board[i+1][col]==RED)&&(board[i+2][col]==RED)){
    		mark_square_as(board,size,i,col,BLUE,announce); 
		}else if((board[i][col]==UNKNOWN)&&(board[i+1][col]==BLUE)&&(board[i+2][col]==BLUE)){
			mark_square_as(board,size,i,col,RED,announce);
		}else if((board[i][col]==RED)&&(board[i+1][col]==UNKNOWN)&&(board[i+2][col]==RED)){
			mark_square_as(board,size,i+1,col,BLUE,announce);
		}else if((board[i][col]==BLUE)&&(board[i+1][col]==UNKNOWN)&&(board[i+2][col]==BLUE)){
			mark_square_as(board,size,i+1,col,RED,announce);
		}else if((board[i][col]==RED)&&(board[i+1][col]==RED)&&(board[i+2][col]==UNKNOWN)){
			mark_square_as(board,size,i+2,col,BLUE,announce);
		}else if((board[i][col]==BLUE)&&(board[i+1][col]==BLUE)&&(board[i+2][col]==UNKNOWN)){
			mark_square_as(board,size,i+2,col,RED,announce);
		}
	}

    return;
} 


void solve_balance_row(int board[MAX_SIZE][MAX_SIZE],
                       int size,
                       int row,
                       bool announce) {
    if(!((size<=MAX_SIZE)&&(size>0)&&(size%2==0))){
    	cout<<"the parameter \"size\" is improper.\n";
    	return;
	}
    if(!((0<=row)&&(row<size))){
    	cout<<"the parameter \"row\" is improper.\n";
        return;   	
	}
	if(!(board_is_valid(board,size))){
		cout<<"the board is invalid.\n";
		return;
	}
	int num_of_RED=0;
	int num_of_BLUE=0;
	for(int i=0;i<size;i++){
		if(board[row][i]==RED){num_of_RED++;}
		if(board[row][i]==BLUE){num_of_BLUE++;}
	}
	if(num_of_RED==size/2){
		for(int j=0;j<size;j++){
			if(board[row][j]==UNKNOWN){
				mark_square_as(board,size,row,j,BLUE,announce);
			}	
		}
	}
	if(num_of_BLUE==size/2){
		for(int j=0;j<size;j++){
		    if(board[row][j]==UNKNOWN){
				mark_square_as(board,size,row,j,RED,announce);
			}	
		}
	}

    return;
}



void solve_balance_column(int board[MAX_SIZE][MAX_SIZE],
                          int size,
                          int col,
                          bool announce) {
    if(!((size<=MAX_SIZE)&&(size>0)&&(size%2==0))){
    	cout<<"the parameter \"size\" is improper.\n";
    	return;
	}
    if(!((0<=col)&&(col<size))){
    	cout<<"the parameter \"col\" is improper.\n";
        return;   	
	}
	if(!(board_is_valid(board,size))){
		cout<<"the board is invalid.\n";
		return;
	}
	int num_of_RED=0;
	int num_of_BLUE=0;
	for(int i=0;i<size;i++){
		if(board[i][col]==RED){num_of_RED++;}
		if(board[i][col]==BLUE){num_of_BLUE++;}
	}
	if(num_of_RED==size/2){
		for(int j=0;j<size;j++){
			if(board[j][col]==UNKNOWN){
				mark_square_as(board,size,j,col,BLUE,announce);
			}	
		}
	}
	if(num_of_BLUE==size/2){
		for(int j=0;j<size;j++){
		    if(board[j][col]==UNKNOWN){
				mark_square_as(board,size,j,col,RED,announce);
			}	
		}
	}                          	
	
    return;
}



/**
 * --------------------------------------------------------
 * ---------- GAMEPLAY FUNCTIONS --------------------------
 * --------------------------------------------------------
 */

bool board_is_solved(const int board[MAX_SIZE][MAX_SIZE], int size) {
    bool result=true;
    if(!((size<=MAX_SIZE)&&(size>0)&&(size%2==0))){
    	cout<<"the parameter \"size\" is improper.\n";
    	return -1;
	}
    if(count_unknown_squares(board,size)!=0){
    	result=false;
	}else if(board_is_valid(board,size)==false){
		result=false;	
    }
	
    return result;
}


bool check_valid_input(int size, int row_input, char col_input,
                       char color_char, int &row, int &col) {
    bool result=true;                   	
    if((row_input>=1)&&(row_input<=size)&&
	(((col_input>='A')&&(col_input<='A'+size-1))||((col_input>='a')&&(col_input<='a'+size-1)))
	&&((color_char==RED_LETTER)||(color_char==BLUE_LETTER)||(color_char==UNKNOWN_LETTER)||(color_char==RED_LETTER+32)||(color_char==BLUE_LETTER+32))){
        row=row_input-1;
        if(col_input<91){
        	col=col_input-65;
		}else if(col_input>96){
			col=col_input-97;
		}
	}else{
		result=false;
		cout<<"Sorry, that's not a valid input.\n";
	}
	
	                  	
    return result;
}


bool check_valid_move(const int original_board[MAX_SIZE][MAX_SIZE],
                      const int current_board[MAX_SIZE][MAX_SIZE],
                      int size, int row, int col, int color) {
    bool result=true;                                     
   if(!((size<=MAX_SIZE)&&(size>0)&&(size%2==0))){
    	cout<<"the parameter \"size\" is improper.\n";
    	return -1;
	}
	if(!((0<=row)&&(row<size))){
		cout<<"the parameter \"row\" is improper.\n";
    	return -1;
	}
    if(!((0<=col)&&(col<size))){
		cout<<"the parameter \"col\" is improper.\n";
    	return -1;
    }
    if(original_board[row][col]!=UNKNOWN){
    	result=false;
    	cout<<"Sorry, original squares cannot be changed.\n";
	}else if(board_is_valid(current_board,size)==false){
		result=false;
		cout<<"Sorry, that move violates a rule.\n";
	}
    
    
    return result;
}



void solve_lookahead_row(int board[MAX_SIZE][MAX_SIZE],
                         int size,
                         int row,
                         bool announce) {
    // write your code here

    return;
}

void solve_lookahead_column(int board[MAX_SIZE][MAX_SIZE],
                            int size,
                            int col,
                            bool announce) {
    // write your code here
    return;
}
