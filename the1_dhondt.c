#include <stdio.h>


int main()
{
	int N, M;
	int i, j;
	int vote;
	int a[26], divi[26], count[26];
	char alpha[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	int tempa, tempdiv, tempcount, temp;
	char tempalpha;
	int max_index;
	scanf("%d" "%d", &N, &M);
	
	for(i = 0; i < N; i++)
	{
		scanf("%d", &vote);
		a[i] = vote;
		
	}
	
	for(i = 0; i < N; i++)
	{
		divi[i] = 1;
	}

	
	for(i = 0; i < N; i++)
	{
		count[i] = 0;
	}
	


	
	for(j = 0; j < M; j++)
	{
		for(i = 0; i < N - 1; i++)
		{
			if(((float) a[i] / divi[i]) < ((float) a[i+1] / divi[i+1]))
			{
				max_index = (i+1);
			}
			else if(((float)a[i] / divi[i]) > ((float) a[i+1] / divi[i+1]))
			{
				max_index = i+1;
				tempa = a[i+1];
				a[i+1] = a[i];
				a[i] = tempa;
				tempdiv = divi[i+1];
				divi[i+1] = divi[i];
				divi[i] = tempdiv;
				tempcount = count[i+1];
				count[i+1] = count[i];
				count[i] = tempcount;
				tempalpha = alpha[i+1];
				alpha[i+1] = alpha[i];
				alpha[i] = tempalpha;
			}
			else
			{
				if(a[i] > a[i+1])
				{
					max_index = i+1;
				    tempa = a[i+1];
				    a[i+1] = a[i];
				    a[i] = tempa;
				    tempdiv = divi[i+1];
				    divi[i+1] = divi[i];
				    divi[i] = tempdiv;
				    tempcount = count[i+1];
				    count[i+1] = count[i];
				    count[i] = tempcount;
				    tempalpha = alpha[i+1];
				    alpha[i+1] = alpha[i];
				    alpha[i] = tempalpha;
				}
				else if(a[i] < a[i+1])
				{
					max_index = (i+1);
				}
			}
		}
		count[max_index] += 1;
		divi[max_index] += 1;
	}

	for(i = 0; i < N-1; i++)
	{
		for(j = 0; j < N-1 - i; j++)
		{
			if (count[j] > count[j + 1])
			{
				temp = count[j];
				count[j] = count[j+1];
				count[j+1] = temp;
				tempalpha = alpha[j];	
				alpha[j] = alpha[j+1];
				alpha[j+1] = tempalpha;
			}
			else if (count[j] == count[j+1])
			{
				if (alpha[j] < alpha[j+1])
				{
					temp = count[j];
					count[j] = count[j+1];
					count[j+1] = temp;
					tempalpha = alpha[j];	
					alpha[j] = alpha[j+1];
					alpha[j+1] = tempalpha;
				}	
					
			}
		}
	}
	
	for(i = (N-1); i >= 0; i--)
	{
		if(count[i] != 0)
		{
			printf("%c: %d\n", alpha[i], count[i]);	
		}
		
	}
	

	return 0;
}
