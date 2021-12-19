#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>

using namespace std;

class AbstractUser
{
private:
	string login;
	string password;
	int id;
protected:
	virtual int getID() = 0;

};

class User: public AbstractUser
{
private:
	string login;
	string password;
	int id;
public:
	
	int getID() override
	{
		return id;
	}
	bool operator==(User& other)
	{
		return (other.id == this->id);
	}
	User()
	{
		srand(time(NULL));
		cout << "Введите логин и пароль: " << endl;
		cin >> login >> password;
		id = rand() % 1000000;
	}
	void setID(int new_id)
	{
		this->id = new_id;
	}
	void setID()
	{
		this->id = rand() % 1000000;
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
	string type = "";
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
	string getType()
	{
		return type;
	}
	void set_all(int price, int ingridient_count, string type)
	{
		this->price = price;
		this->ingridientCount = ingridientCount;
		this->type = type;
	}
};

class Menu
{
	vector<Dish> menu;
public:
	double getAveragePrice()
	{
		int summ = 0;
		for (size_t i = 0; i < menu.size(); i++)
		{
			summ += menu[i].getPrice();
		}
	}

	
	void add_new_dish(Dish dsh)
	{
		menu.resize(menu.size() + 1);
		menu.push_back(dsh);
	}
	void add_new_dish()
	{
		Dish dsh;
		int price, ingridient_count;
		string type;
		cout << "Введите цену, количество ингридиентов, и тип нового блюда... ";
		try
		{
			cin >> price >> ingridient_count >> type;
		}
		catch (const std::exception&)
		{
			cout << "Input error!" << endl;
			return;
		}
		dsh.set_all(price, ingridient_count, type);
		
		menu.push_back(dsh);
	}
	void print_menu()
	{
		for (size_t i = 0; i < menu.size(); i++)
		{
			cout << menu[i].getType() << '\t' << menu[i].getPrice() << endl;
		}
	}
};



class FoodPoint
{
	friend class Host;
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
	template <class Number>
	void setRate(Number mark, User u)
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
	Menu get_menu()
	{
		return this->menu;
	}
	void print_menu()
	{
		this->menu.print_menu();
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
class Host : public AbstractUser
{
private:
	FoodPoint fp;
	int id;
public:

	
	int getID() override
	{
		return this->id;
	}
	bool performance_assessment_fp()
	{
		return (fp.getRate() > 3.5);
	}
	void set_fp(FoodPoint newfp)
	{
		this->fp = newfp;
	}
	void set_fp()
	{
		this->fp = FoodPoint();
	}
	Host()
	{
		this->id = rand() % 1000000;
		set_fp();
	}
};



int main()
{
	
	setlocale(LC_ALL, "ru");
	User localuser;
	Host localhost;
	FoodPoint pryanik;

	pryanik.setRate(4.0, localuser);
	pryanik.setRate(2.0, localuser);

	localhost.set_fp(pryanik);
	if (!localhost.performance_assessment_fp()) {
		cout << "Низкое качество обслуживания" << endl;
	}
	else
	{
		cout << "Хорошее качество обслуживания" << endl;
	}
	cout << "ID localuser: " << localuser.getID() << "\tID localhost: " << localhost.getID() << endl;
	Dish dsh;
	dsh.set_all(150, 4, "fish");
	pryanik.get_menu().add_new_dish(dsh);
	pryanik.print_menu();
	

	return 0;
}
