#include<stdlib.h>
#include<pthread.h>
#include <stdio.h>
#define Item(X, I, J, NCOL)      X[((J) + (I) * (NCOL))]

/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */
struct arr {
    int *a;
    int *b;
    int *c;
    int row;
    int M;
    int col;
    int n;
    int sum;
};
void matmult(int* A, int* B, int* C, int l, int m, int n)
{
    for(int i=0; i<l; i++)
        for(int j=0; j<n; j++)
        {
            int sum = 0;
            for(int k=0; k<m; k++)
                sum += Item(A, i, k, m) * Item(B, k, j, n);
            Item(C, i, j, n) = sum;
        }
}


void * mul_el(void *arg){
    //pasing the prametars from the struct to the variables
    struct arr* matrix=(struct arr*) arg;
    int* A=matrix->a;
    int* B=matrix->b;
    int* C=matrix->c;
    int row_st=matrix->row;
    int m_m=matrix->M;
    int col_st=matrix->col;
    int n=matrix->n;
    int sum=0;
    // calculating the element of the array 
    for(int i=0;i<m_m;i++){
            sum += Item(A, row_st, i, m_m) * Item(B, i, col_st,n);
            
            }
    matrix->sum=sum;
    // assigning the calculated element to the array 
    Item(C, row_st, col_st,n ) = sum;
    pthread_exit(0);
}
/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */
void matmult_v1(int* A, int* B, int* C, int l, int m, int n)
{
    pthread_t t_id[l][n];
    struct arr args[l][n];
    for(int i=0; i<l; i++){
        for(int j=0; j<n; j++)
        {pthread_attr_t attr;
		pthread_attr_init(&attr);
        //passing the arguments the to the struct to passing it while creating the thread
        args[i][j].a=A;    
        args[i][j].b=B;
        args[i][j].c=C;
        args[i][j].row=i;
         args[i][j].col=j;
          args[i][j].M=m;
           args[i][j].n=n;
           // creating the thread  for each element
		pthread_create(&t_id[i][j], &attr, mul_el, &args[i][j]);   
	}
            }
     for(int i=0; i<l; i++){
        for(int j=0; j<n; j++)
        {	// waiting for the thread to terminate 
            pthread_join(t_id[i][j], NULL);
       
	    }
                           }
    // for(int i=0; i<l; i++){
    //     // for(int j=0; j<n; j++)
    //     // {	
    //     // printf("the sum of %d \n",args[i][j].sum);
	//     // }
    //                        }
      
}

void * mul_rw(void *arg){
    //pasing the prametars from the struct to the variables
    struct arr* matrix=(struct arr*) arg;
    int* A=matrix->a;
    int* B=matrix->b;
    int* C=matrix->c;
    int row_st=matrix->row;
    int m_m=matrix->M;
//    int col_st=matrix->col;
    int n=matrix->n;
    int sum=0;
    for(int i=0;i<n;i++){
        sum=0;
        for(int j=0;j<m_m;j++){
              sum += Item(A, row_st, j, m_m) * Item(B, j, i,n);
        }
         matrix->sum=sum;
         //setting the result to the matrix 
        Item(C, row_st, i,n ) = sum; 
            
         }
    
    pthread_exit(0);
}

/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */
void matmult_v2(int* A, int* B, int* C, int l, int m, int n)
{
 pthread_t t_id[l];
    struct arr args[l];
    for(int i=0; i<l; i++){
        pthread_attr_t attr;
		pthread_attr_init(&attr);
        // assigning the paramters to the struct to pass it to the thread
        args[i].a=A;
        args[i].b=B;
        args[i].c=C;
        args[i].row=i;
        //  args[i].col=j;
          args[i].M=m;
           args[i].n=n;
           // create thread to each row
		pthread_create(&t_id[i], &attr, mul_rw, &args[i]);
	}
            
   
        for(int j=0; j<l; j++)
        
        {	
            // waiting for the thread to terminate
            pthread_join(t_id[j], NULL);
       
	    }
                          
   
        // for(int j=0; j<l; j++)
        // {	
        // printf("the sum of %d \n",args[j].sum);
	    // }
                           
}
