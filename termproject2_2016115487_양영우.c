#include <stdio.h>

int words[1000] = {};
int checksum = 0;
	
int calculation_Checksum(message)
int *message;
{
	int i = 0;
	int j;
	int sum = 0;
	int k = 0B00000000000000001111111111111111;
	int word;
	char ask[2];
	int left;
	int right;

	while(1){
		printf("add number:");
		scanf("%d", &word);
		words[i] = word;
		sum += word;
		printf("More words?");
		scanf("%s", &ask);
		if(strcmp(ask, "no") == 0)
			break;
		else{
			i = i+1;
			continue;
		}
	}
	while(1){
		right = sum & k;
		left = sum ^ k;
		left = left>>16;
		printf("right = %d\n left = %d\n", right, left);
		sum = right + left;
		if(sum > k)
			continue;
		else
			break;
	}	
	checksum = ~sum;
	checksum = checksum & k;
	printf("checksum = %d\n", checksum);
}

int check_Checksum(message)
int *message;
{
	int j;
	int k = 0B00000000000000001111111111111111;
	int left, right;
	int newsum = 0;
	int newchecksum = 0;
	
	for(j = 0; j<sizeof(words)/sizeof(int); j++){
		newsum += words[j];
	}
	newsum += checksum;
	newsum += 32;
	while(1){
		right = newsum & k;
		left = newsum ^ k;
		left = left>>16;
		newsum = right + left;
		if(newsum > k)
			continue;
		else
			break;
	}
	newchecksum = ~newsum;
	newchecksum = newchecksum & k;
	if(newchecksum == 0){
		return 1;
	}
	else{
		return 0;
	}
}

int main(void) {
	int x;
	calculation_Checksum();
	
	x = check_Checksum();
	
	if(x == 0){
		printf("after checking checksum, result is not 0 \nerror\n");
	}
	else{
		printf("after checking checksum, result is 0 \nno error\n");
	}
	
    return 0;
}

