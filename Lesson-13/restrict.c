#include <stdio.h>

enum day
{
	MONDAY = 1,
	TUESDAY, 
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY
};

char get_last_char(char str[])
{
	char c;
	int i = 0;

	while (str[i])
	{
		c = str[i];
		i++;	
	}

	return c;
}

int is_restricted(int tail_num, enum day today)
{
	int ret = 0;
	// tail_num : 0, 1, --- 9
	// 0, 5 
	// 1, 6
	// ...

	switch (tail_num)
	{
		case 0:
		case 5:
		#if 0	
			if (today == MONDAY)
				ret = 1;
			else
				ret = 0;
		#endif
			ret = (today == MONDAY) ? 1 : 0;
			break;

		case 1:
		case 6:
			ret = (today == TUESDAY) ? 1 : 0;
			break;
		case 2:
		case 7:
			ret = (today == WEDNESDAY) ? 1 : 0;
			break;
		case 3:
		case 8:
			ret = (today == THURSDAY) ? 1 : 0;
			break;
		case 4:
		case 9:
			ret = (today == FRIDAY) ? 1 : 0;
			break;
		default:
			ret = 0;
			break;
	}

	return ret;
}

enum day get_week_day(int year, int month, int day)
{
	// 2013-1-1 : week day 2 (Tuesday)
	int origin_day = 2;	// 2013-1-1 : week day 2
	int m[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};	
	int alldays = 0;
	int i = 0;

	for (i = 1; i < month; i++)
	{
		// i = 1 -> m[0]
		alldays += m[i-1];
	}	

	printf("alldays = %d\n", alldays);
	alldays += day - 1;
	printf("alldays = %d\n", alldays);
	printf("alldays = %d\n", (alldays + origin_day) % 7);

	switch ((alldays + origin_day) % 7)
	{
		case 0:
			return SUNDAY;
		case 1:
			return MONDAY;
		case 2:
			return TUESDAY;
		case 3:	
			return WEDNESDAY;
		case 4:
			return THURSDAY;
		case 5:
			return FRIDAY;
		case 6:
			return SATURDAY;
	}	

	return MONDAY;
}

int main(void)
{
	char car_num_str[8] = "A23456";
	int tail_num = 0;	// "A23456" -> 6
	enum day today;	// 1-7
	char last_char;
	int ret;
	
	printf("Please input your car number:\n");
	scanf("%s", car_num_str);	

	printf("car num is %s\n", car_num_str);
	
	/* get the last char of car number string */
	last_char = get_last_char(car_num_str);
	printf("last char is %c\n", last_char);

	tail_num = last_char - '0';
	//today = MONDAY;
	//today = FRIDAY;
	today = get_week_day(2013, 12, 31);
	printf("today is day %d\n", today);

	ret = is_restricted(tail_num, today);
	if (ret == 1)
		printf("restricted!\n");
	else
		printf("NOT restricted!\n");
		

	return 0;
}
