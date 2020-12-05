# include <stdio.h>
int plus(int a){
	int b = a + 10;
	printf("%d",b);
	
	return 0;
}
int main(){
	int a = 10;

	printf("%d\n",a);
	plus(a);
	return 0;

}
