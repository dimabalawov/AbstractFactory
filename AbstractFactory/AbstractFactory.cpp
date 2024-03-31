#include <iostream>
using namespace std;

class Herbivore abstract {
protected:
	unsigned int weight;
	bool isAlive;
public:
	Herbivore(unsigned int weight)
	{
		this->weight = weight;
		isAlive = 1;
	}

	void EatGrass() {
		if (!isAlive)
			return;
		weight += 10;
	}

	int GetWeigth()const {
		return weight;
	}

	bool IsAlive()const {
		return isAlive;
	}

	void SetLife(bool life) {
		this->isAlive = life;
	}

	virtual string GetName() = 0;
};

class Wildebeest :public Herbivore
{
public:
	Wildebeest() :Herbivore(230) {};
	string GetName()
	{
		return "Wildebeest";
	}
};

class Bison : public Herbivore
{
public:
	Bison() :Herbivore(600) {};
	string GetName() 
	{
		return "Bison";
	}
};

class Elk : public Herbivore
{
public:
	Elk() :Herbivore(250) {};
	string GetName()
	{
		return "Elk";
	}
};


class Carnivore abstract {
protected:
	unsigned int power;
public:
	Carnivore(unsigned int power)
	{
		this->power = power;
	}
	unsigned int GetPower()const
	{
		return power;
	}

	void Eat(Herbivore*& herbivore) {
		if (this->power >= herbivore->GetWeigth())
		{
			this->power += 10;
			herbivore->SetLife(false);

			cout << herbivore->GetName() << " has got eaten by " << this->GetName()<< endl;

		}
		else
			this->power -= 10;
	};
	virtual string GetName() = 0;

};

class Lion : public Carnivore
{
public:
	Lion() :Carnivore(550) {};
	string GetName()
	{
		return "Lion";
	}
};

class Wolf : public Carnivore {
public:
	Wolf() : Carnivore(270) {};
	string GetName()
	{
		return "Wolf";
	}
};

class Tiger : public Carnivore
{
public:
	Tiger() :Carnivore(400) {};
	string GetName()
	{
		return "Tiger";
	}
};

class Continent abstract
{ 
public:

	virtual void GetName() = 0;
	virtual Carnivore* CreateCarnivore() = 0;
	virtual Herbivore* CreateHerbivore() = 0;
};

class Africa :public Continent {
	void GetName()override {
		cout << "Africa" << endl;
	}
	Carnivore* CreateCarnivore()
	{
		return new Lion();
	}
	Herbivore* CreateHerbivore()
	{
		return new Wildebeest();
	}
};

class America : public Continent {
	void GetName()
	{
		cout << "America" << endl;
	}
	Carnivore* CreateCarnivore()
	{
		return new Wolf();
	}
	Herbivore* CreateHerbivore()
	{
		return new Bison();
	}
};

class Eurasia : public Continent {
	void GetName() override {
		cout << "Eurasia" << endl;
	}
	Carnivore* CreateCarnivore()
	{
		return new Tiger();
	}
	Herbivore* CreateHerbivore() 
	{
		return new Elk();
	}
};

class Client
{
private:
	Carnivore* carnivore;
	Herbivore* herbivore;
public:
	Client(Continent* continent)
	{
		carnivore = continent->CreateCarnivore();
		herbivore = continent->CreateHerbivore();
	}
	void Start()
	{
		FeedHerbivores();
		HuntHerbivores();
		cout <<carnivore->GetName() << "'s power is " << carnivore->GetPower() << endl;
		cout << herbivore->GetName() << " is ";
		herbivore->IsAlive() ? cout << "alive" : cout << "dead";
		cout << endl;
		cout << endl;
	}

	string GetCarnivoreName()
	{
		return carnivore->GetName();
	}

	string GetHerbivoreName()
	{
		return herbivore->GetName();
	}
	void FeedHerbivores()
	{
		herbivore->EatGrass();
	}
	void HuntHerbivores()
	{
		carnivore->Eat(herbivore);
	}
};


int main() {
	Continent* continent = new America();
	Client* client = new Client(continent);
	client->Start();
	delete continent;
	delete client;

	continent = new Eurasia();
	client = new Client(continent);
	client->Start();
	delete continent;
	delete client;

	continent = new Africa();
	client = new Client(continent);
	client->Start();
	delete continent;
	delete client;
}
