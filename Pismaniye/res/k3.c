int main()
{
	int a = 5;
	int b = 140;
	
	a = b;
	
	if(a < 0)
	{
		a = -5;
	}
	else
	{
		b = 0;
	}
	
	a = a + b;
	
	while(a)
	{
		a = a - 1;
	}
	
	//&& ekle
	if (a && b)
	{
		a = b * 10;
	}
}