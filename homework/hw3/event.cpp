class Event
{
private: 
	std::string m_name; 

public: 
	Event(std::string name);
	virtual ~Event(); 

	std::string name() const; //getter function for name 
	virtual bool isSport() const;
	virtual std::string need() const =0;
};
Event::Event(std::string name) : m_name(name) {}

Event::~Event(){}

bool Event::isSport() const
{
	return true; 
}

std::string Event::name() const
{
	return m_name; 
}

////////////////////////////
////////////////////////////
//    basketballgame
////////////////////////////
////////////////////////////

class BasketballGame: public Event 
{

public:
	BasketballGame(std::string basketballGame); //constructor 
	virtual ~BasketballGame(); 
	virtual std::string need() const;

};

BasketballGame::BasketballGame(std::string basketballGame): Event(basketballGame)
{
}

BasketballGame::~BasketballGame()
{
	std::cout << "Destroying the " << name() << " basketball game" << std::endl;
}

std::string BasketballGame::need() const
{
	return "hoops"; 
}

////////////////////////////
////////////////////////////
//    HockeyGame
////////////////////////////
////////////////////////////

class HockeyGame : public Event
{

public: 
	HockeyGame(std::string hockeyGame); //constructor 
	virtual ~HockeyGame(); //destructor 
	virtual std::string need() const;
};

HockeyGame::HockeyGame(std::string hockeyGame) : Event(hockeyGame)
{
}

HockeyGame::~HockeyGame()
{
	std::cout << "Destroying the " << name() << " hockey game" << std::endl;
}

std::string HockeyGame::need() const
{
	return "ice";
}

////////////////////////////
////////////////////////////
//    Concert
////////////////////////////
////////////////////////////

class Concert : public Event
{
private:
	std::string m_singerName;
	std::string m_genre;
public:
	Concert(std::string singer, std::string genre); //constructor 
	virtual ~Concert(); //destructor 
	virtual bool isSport() const;
	virtual std::string need() const;
};

Concert::Concert(std::string singer, std::string genre) : Event(singer), m_singerName(singer), m_genre(genre)
{
}

Concert::~Concert() 
{
	std::cout << "Destroying the " << m_singerName << " " << m_genre << " concert" << std::endl;
}

bool Concert::isSport() const 
{
	return false; 
}

std::string Concert::need() const
{
	return "a stage"; 
}


