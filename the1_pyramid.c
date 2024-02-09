#include <stdio.h>

double calculate_pressure_on_block(int row, int column, double block_weight);


void print_pyramid(int N, double block_weight, int row, int column) {

    if (row == N) {
        return;
    }
	
	else{
	    double p = calculate_pressure_on_block(row, column, block_weight);
        printf("(%d,%d) %.8f\n", row, column, p);
	}
    if (column == row) {
        print_pyramid(N, block_weight, row + 1, 0);
    } 
    else {
        print_pyramid(N, block_weight, row, column + 1);
    }
}


double calculate_pressure_on_block(int row, int column, double block_weight) {

    
    if (row == 0) {
        return 0.0;
    }
	
    if(column == 0){
        double p_right = calculate_pressure_on_block(row - 1, column, block_weight);
    	double p = block_weight * 0.5  + 0.15 * p_right;
		return p;
	}
	
	
	else if(column == row){
	    double p_left = calculate_pressure_on_block(row - 1, column - 1, block_weight);
		double p = block_weight * 0.5 + 0.15 * p_left;
		return p;
	}
	
	else{
	    double p_left = calculate_pressure_on_block(row - 1, column - 1, block_weight);
        double p_right = calculate_pressure_on_block(row - 1, column, block_weight);
		double p = block_weight + 0.15 * (p_left + p_right);
		return p;
	}

}

int main() {
    int N, W;
    scanf("%d %d", &N, &W);

    print_pyramid(N, W, 0, 0);

    return 0;
}
