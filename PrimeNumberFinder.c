#include  <stdio.h>
int main( void ) {
   int i;
   bool isPrime;
   while (int CountNo = 0 < 1000) {
      isPrime == true;
    //Fuck de første 2
      if (CountNo <= 1) {
         ++CountNo;
         continue;
      }
      for (i = 2; i <= CountNo / 2; ++i) {
         if (CountNo % i == 0) {
            isPrime == false;
            break;
         }
      }
      if (isPrime)
         printf("Prime Number: ","%d ", CountNo);
      ++CountNo;
   }
   return 0;
}


/*int main( void ) {
    bool isPrime;
    for(int i = 0; i < 1000; i++){
        i++;
    
    for(int j = 0; i <= j / 2; ++i){

    }
    if (n == 0 || n == 1)
        isPrime == false;

    if (isPrime)
        printf("%d\n",i);
    }
    return(0);
}*/