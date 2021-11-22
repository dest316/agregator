#include <iostream>
#include <string>

class User
{
	string login;
	string password;
	int id;
public:
	int getID()
	{
		return id;
	}
	bool operator==(User& other)
	{
		return (other.id == this->id);
	}
};

struct Time
{
	int hours;
	int minutes;
	Time()
	{
		hours = minutes = 0;
	}
	bool operator< (Time& other)
	{
		if (this->hours < other.hours)
		{
			return true;
		}
		else if (this->hours < other.hours)
		{
			return false;
		}
		else
		{
			if (this->minutes < other.minutes)
			{
				return true;
			}
			else if (this->minutes < other.minutes)
			{
				return false;
			}
			return true;
		}
	}
	bool operator==(Time& other)
	{
		 
			return (other.hours == this->hours && other.minutes == this->minutes);
		
	}
	bool operator> (Time& other)
	{
		return (!(*this < other) && !(*this == other));
	}
	static Time now()
	{
		Time time;
		return time;
	}
};

class WorkTime
{
public:
	
	Time opentime;
	Time closetime;

	
};

class Dish
{
	int price = 0;
	int ingridientCount = 0;
	string type = "<undefined>";
	string* ingridients = new string[ingridientCount];
public:
	bool is_vegeterian()
	{
		for (int i = 0; i < ingridientCount; i++)
		{
			if (ingridients[i] == "meat")
			{
				return true;
			}
		}
		return false;
	}
	Dish() = default;
	bool is_drink()
	{
		if (type == "drink")
		{
			return true;
		}
		return false;
	}
	int getPrice()
	{
		return price;
	}
};

class Menu
{
	int length;
	
	Dish *menu = new Dish[length];
public:
	double getAveragePrice()
	{
		int summ;
		for (size_t i = 0; i < length; i++)
		{
			summ += menu[i].getPrice();
		}
	}
};

class FoodPoint
{
	double ratesumm;
	WorkTime worktime;
	string name;
	Menu menu;
	int ratecount;
	User* ratelist = new User[ratecount];
	double getRate()
	{
		return (double)ratesumm / ratecount;
	}
public:
	void setRate(int mark, User u)
	{
		if (mark < 1 || mark > 5)
		{
			return;
		}
		for (int i = 0; i < ratecount; i++)
		{
			if (u == ratelist[i])
			{
				return;
			}
		}
		ratesumm += mark;
		ratecount++;
	}
	double getAverageChecksumm()
	{
		menu.getAveragePrice();
	}
	bool is_open(Time checktime = Time::now())
	{
		return (checktime > this->worktime.opentime && checktime < this->worktime.closetime);
	}

};


using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	
	return 0;
}
