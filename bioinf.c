#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

int max(int x, int y, int z)  
{
    int i;
    i=x;
    if (y>i)
       i=y;
    if (z>i)
       i=z;
    return i;
}

int max2(int x, int y)  
{
    if (x>y)
       return x;
    else
        return y;
}

    

void make_mat(int ***D, int m, int n) {        //function for making matrix
  int i = 0;
  *D = (int **)malloc(m*sizeof(int*));
  for (i = 0; i < m; i++) {
    (*D)[i] = (int*)malloc(n*sizeof(int));
    }
}


int main (int argc, char *argv[])
{  
   int m, n , match, mismatch, gap,i,j, size=0, size2=0,left=0, top=0, diagonal=0, z=0, k,l;
   char *First,*Second; 
   char *P1,*P2;
   int **D;
   int **Path=NULL;
   
   FILE *input, *output;
   input = fopen("input.txt", "r");            
   if (input == NULL) 
		printf("Unable to open file."); 
   fscanf(input, "%d %d %d %d %d", &m, &n, &match, &mismatch, &gap);
   
   First = (char *)malloc( (m+1)*sizeof(char) );        
   Second = (char *)malloc( (n+1)*sizeof(char) );
   First[m]='\0';
   Second[n]='\0';
   fscanf(input,"%s", First);
   fscanf(input,"%s", Second);
   
   make_mat(&D,m+1,n+1);
   make_mat(&Path,m+1,n+1);
   puts(First);
   puts(Second);
   
   printf("\n");
          
   for (i = 0; i <= m; i++){
   for (j = 0; j <= n; j++)
   {
      
        
        if ((i == 0) || (j == 0))
        {
             D[i][j] = 0;
             Path[i][j]=0;
        }
        else if ((i == m) || (j == n))
           {        
                left = D[i][j - 1];
                top = D[i - 1][j];
                if(First[i-1] == Second[j-1])
                     diagonal= D[i - 1][j - 1] + match;
                else 
                     diagonal = max2(0,D[i - 1][j - 1] + mismatch);
                     
                D[i][j]=max(left, top, diagonal);
                if   (D[i][j]==top)
                        {  Path[i][j]=2; }
                else if(D[i][j]==left)
                        { Path[i][j]=3;}
                else if(D[i][j]==diagonal)
                          Path[i][j]=1;}
           
        else
           {
               left = max2(0, D[i][j - 1] + gap);
               top = max2(0, D[i - 1][j] + gap);
               if(First[i-1] == Second[j-1])
                     diagonal= D[i - 1][j - 1] + match;
               else 
                     diagonal = max2(0,D[i - 1][j - 1] + mismatch);
               D[i][j] = max(diagonal, top, left);
               if (D[i][j]==top)
                    Path[i][j]=2; 
               else if(D[i][j]==left)
                    Path[i][j]=3;
               else if(D[i][j]==diagonal)
                    Path[i][j]=1;
           }    
                
              
        
    //printf("%d   ", D[i][j]);
      
    }
    //printf ("\n");
    }
    
    
    printf("\nRezultat je: %d\n\n", D[m][n]);
    /*for (i = 0; i <= m; i++){
         for (j = 0; j <= n; j++)
             printf("%d ", Path[i][j]);
    printf("\n");}*/
    k=m,l=n;
    do
    {
        if (Path[k][l]==1)
          { z++;
            k--,l--;}
        else if (Path[k][l]==2)
           {  z++;
              k--;} 
        else if (Path[k][l]==3)
           {  z++;
              l--;}  
        else if (Path[k][l]==0 && l==0)
        {
             z++;
             k--;
             }
        else if (Path[k][l]==0 && k==0)
        {
             z++;
             l--;
             }
    }while(k>0 || l>0);
   
   // printf ("\nz= %d\n",z);
    k=z;
    
    P1 = (char *)malloc ((z+1) *sizeof(char)); 
    P2 = (char *)malloc ((z+1) *sizeof(char));
    P1[z]='\0';
    P2[z]='\0';
    
    z--;
    
    i=m;
    j=n;
  
    
    do
    {
        if (Path[m][n]==1)
          { P1[z]=First[m-1];
            P2[z]=Second[n-1];
            m--,n--, z--;
            }
        else if (Path[m][n]==2)
           {  P1[z]=First[m-1];
              P2[z]='-';
              m--,z--;} 
        else if (Path[m][n]==3)
           {  P1[z]='-';
              P2[z]=Second[n-1];
              n--,z--;
              }
        else if (Path[m][n]==0 && n==0)
        {
             P1[z]=First[m-1];
             P2[z]='-';
             z--, m--;
             }
        else if (Path[m][n]==0 && m==0)
        {  
             P2[z]=Second[n-1];
             P1[z]='-';
             z--, n--;
             }
    }while(m>0 || n>0);
    
    printf("%s \n", P1);
    printf("%s \n", P2);
 
    fclose(input);
    output = fopen("output.txt", "w"); 
    if (output == NULL) {
       printf("Datoteka ne postoji\n");
       exit(1);
       }
    fprintf(output,"%s\n",P1);
    fprintf(output,"%s\n",P2);
    fclose(output);  
    getch();
}




