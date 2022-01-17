#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

struct Neighbor
{
  string Name;
  int Distance;
  int Fare;
};

class	City
{
public:
	string	Name;
	string AccumulatedPath;
	int	AccumulatedDistance;
	int AccumulatedFare;
	int EuclidianDistance;
	int EstimatedPrice;

	vector<Neighbor> Neighbors;
	vector<Neighbor>::iterator	NeighborNumber;

	City();
	City(string, int, int);

	void	AddNeighbor	(string, int, int);
};


City::City()
{
	Name="";
	NeighborNumber=Neighbors.begin();
	AccumulatedDistance=0;
	AccumulatedFare=0;
	AccumulatedPath="";
	EuclidianDistance=0;
	EstimatedPrice=0;
}


City::City(string CityName, int EDistance, int EPrice)
{
	Name=CityName;
	NeighborNumber=Neighbors.begin();
	AccumulatedFare=0;
	AccumulatedDistance=0;
	AccumulatedPath=CityName;
	EuclidianDistance=EDistance;
	EstimatedPrice=EPrice;
}

void	City::AddNeighbor(string NeighborName, int NeighborDistance, int CostFare)
{
	Neighbor TempNeighbor;
	TempNeighbor.Name=NeighborName;
	TempNeighbor.Distance=NeighborDistance;
	TempNeighbor.Fare=CostFare;
	Neighbors.push_back(TempNeighbor);
	NeighborNumber=Neighbors.begin();
}
vector<City> Cities;


void BuildMap();
bool Search(string StartName, string EndName);
//City PriorityQueueCost(int *MinDistance);



int main()
{
    BuildMap();
    Search("Los Angeles", "New York");
    return 0;
}

void BuildMap()
{
    City TempCity;

//Los Angeles Data
	TempCity.Name="Los Angeles";
	TempCity.EuclidianDistance=2475;
	TempCity.EstimatedPrice=499;
	TempCity.Neighbors.clear();
	TempCity.AddNeighbor("San Francisco", 338, 199);
	TempCity.AddNeighbor("Seattle",954,159);
	TempCity.AddNeighbor("Dallas",1235,239);
	Cities.push_back(TempCity);


//San Francisco Data
    TempCity.Name="San Francisco";
    TempCity.EuclidianDistance=2586;
	TempCity.EstimatedPrice=529;
    TempCity.Neighbors.clear();
    TempCity.AddNeighbor("Los Angeles",338,199);
	TempCity.AddNeighbor("Denver",967,219);
	TempCity.AddNeighbor("DC",2442,439);
    Cities.push_back(TempCity);

//Seattle Data
    TempCity.Name="Seattle";
    TempCity.EuclidianDistance=2421;
	TempCity.EstimatedPrice=529;
    TempCity.Neighbors.clear();
    TempCity.AddNeighbor("Los Angeles",954,159);
	TempCity.AddNeighbor("Miami",2724,529);
	TempCity.AddNeighbor("Chicago",1721,399);
    Cities.push_back(TempCity);

//Salt Lake City Data
    TempCity.Name="Salt Lake City";
    TempCity.EuclidianDistance=1989;
	TempCity.EstimatedPrice=459;
    TempCity.Neighbors.clear();
    TempCity.AddNeighbor("Denver",391,129);
    Cities.push_back(TempCity);

//Denver Data
    TempCity.Name="Denver";
    TempCity.EuclidianDistance=1626;
	TempCity.EstimatedPrice=359;
    TempCity.Neighbors.clear();
    TempCity.AddNeighbor("Salt Lake City",391,129);
	TempCity.AddNeighbor("San Francisco", 967, 219);
	TempCity.AddNeighbor("Dallas",641,199);
	TempCity.AddNeighbor("Chicago",888,199);
	Cities.push_back(TempCity);

//Dallas Data
    TempCity.Name="Dallas";
    TempCity.EuclidianDistance=1391;
	TempCity.EstimatedPrice=319;
    TempCity.Neighbors.clear();
    TempCity.AddNeighbor("Los Angeles",1235,239);
	TempCity.AddNeighbor("New Orleans", 448, 199);
	TempCity.AddNeighbor("Atlanta",732,249);
	TempCity.AddNeighbor("Denver",641,199);
    Cities.push_back(TempCity);

//Omaha Data
    TempCity.Name="Omaha";
    TempCity.EuclidianDistance=1154;
	TempCity.EstimatedPrice=329;
    TempCity.Neighbors.clear();
    TempCity.AddNeighbor("Chicago",416,349);
    Cities.push_back(TempCity);

//St. Louis Data
    TempCity.Name="St. Louis";
    TempCity.EuclidianDistance=892;
	TempCity.EstimatedPrice=279;
    TempCity.Neighbors.clear();
    TempCity.AddNeighbor("Chicago",338,199);
    Cities.push_back(TempCity);

//Chicago Data
    TempCity.Name="Chicago";
    TempCity.EuclidianDistance=740;
	TempCity.EstimatedPrice=199;
    TempCity.Neighbors.clear();
    TempCity.AddNeighbor("Seattle",1721,399);
	TempCity.AddNeighbor("St. Louis", 258, 159);
	TempCity.AddNeighbor("Omaha",416,349);
	TempCity.AddNeighbor("Denver",888,199);
	TempCity.AddNeighbor("DC",612,199);
	TempCity.AddNeighbor("New York",740,199);
    Cities.push_back(TempCity);

//New Orleans Data
    TempCity.Name="New Orleans";
    TempCity.EuclidianDistance=1182;
	TempCity.EstimatedPrice=319;
    TempCity.Neighbors.clear();
    TempCity.AddNeighbor("Dallas",448,199);
    Cities.push_back(TempCity);

//Atlanta Data
    TempCity.Name="Atlanta";
    TempCity.EuclidianDistance=760;
	TempCity.EstimatedPrice=259;
    TempCity.Neighbors.clear();
	TempCity.AddNeighbor("DC",547,209);
	TempCity.AddNeighbor("Dallas",732,249);
    Cities.push_back(TempCity);

//Miami Data
    TempCity.Name="Miami";
    TempCity.EuclidianDistance=1090;
	TempCity.EstimatedPrice=499;
    TempCity.Neighbors.clear();
	TempCity.AddNeighbor("Seattle",2724,529);
	TempCity.AddNeighbor("New York",1090,199);
    Cities.push_back(TempCity);

//DC Data
    TempCity.Name="DC";
    TempCity.EuclidianDistance=213;
	TempCity.EstimatedPrice=89;
    TempCity.Neighbors.clear();
	TempCity.AddNeighbor("Chicago",612,199);
	TempCity.AddNeighbor("Atlanta",547,209);
	TempCity.AddNeighbor("San Francisco",2442,439);
    Cities.push_back(TempCity);

//New York Data
    TempCity.Name="New York";
    TempCity.EuclidianDistance=0;
	TempCity.EstimatedPrice=0;
    TempCity.Neighbors.clear();
    TempCity.AddNeighbor("Chicago",740,199);
	TempCity.AddNeighbor("Miami",1090,199);
    Cities.push_back(TempCity);
}

bool	GetChildCity(Neighbor Parent, City* ChildCity)
{
	City			TempCity;
	vector<City>::iterator	CityNumber;

	for(CityNumber=Cities.begin();CityNumber<Cities.end();CityNumber++)
	{
		TempCity=*CityNumber;
		if(TempCity.Name==Parent.Name)
		{
			*ChildCity=TempCity;
			return true;
		}
	}
	return false;
}



//Search function

bool Search(string StartName, string EndName)
{
  City StartCity;
  City CurrentCity;
  City ChildCity;
  City ExploredCity;
  City FrontierCity;
  City BestCity;
  City LowestNodeNumber;


  int SomeMax=5000;
  int AccumulatedFare=0;
  int AccumulatedDistance=0;
  int AirFare=0;
  int Nodes=0;
  int BestFare=0;
  int BestDistance;
  int GoalDistance=0;
  int GoalFare=0;


  Neighbor CurrentNeighbor;
  Neighbor BestNeighbor;

  vector<City>::iterator CityNumber;
  vector<Neighbor>::iterator NeighborNumber;


  deque<City> Frontier;
  deque<City> Explored;

  deque<City>::iterator BestNode;
  deque<City>::iterator FrontierCityNumber;
  deque<City>::iterator ExploredCityNumber;

  bool StartCityFound=false;
  bool GoalFound=false;
  bool AlreadyExplored;
  bool AlreadyInFrontier;
  bool NewChildFound;
  bool PathFound;

  string GoalPath;

  if(StartName==EndName) return true;

  if(StartName == "" || EndName == "") return false;

//USE LOS ANGELES AS THE START - LOOK THROUGH ALL CITIES STRUCTURE TO FIND SAME NAME

  for(CityNumber=Cities.begin();CityNumber<Cities.end();CityNumber++)
  {
    CurrentCity=*CityNumber;
    if(CurrentCity.Name==StartName)
    {
      StartCity=CurrentCity;
      StartCityFound=true;
      StartCity.AccumulatedPath=StartName;
    }
  }

  if(StartCityFound==false) return false;

  Frontier.push_front(StartCity);

//MAIN SEARCH
//cout<<"Greedy Search (Distance)"<<endl;   // Greedy Search (Distance) Label
//cout<<"Greedy Search (Fare)"<<endl;   // Greedy Search (Fare) label
//cout<<"A* Search (Distance)" <<endl; //A* search label (Distance) label
cout<<"A* Search (Fare)" <<endl; //A* search label (Fare) label


//while(!Frontier.empty() && (GoalDistance>BestDistance || GoalFound==false))   // for A* distance - checks to see if there are possibly shorter paths
while(!Frontier.empty() && (GoalFare>BestFare || GoalFound==false))   // for A* fare - checks to see if there are possibly shorter paths
//  while(!Frontier.empty() && GoalFound==false)  // for greedy searches
  {
//    CurrentCity=Frontier.front();    // for greedy searches


    FrontierCityNumber=Frontier.begin();
	CurrentCity=*FrontierCityNumber;
	BestFare=CurrentCity.AccumulatedFare+CurrentCity.EstimatedPrice;
	BestDistance=CurrentCity.AccumulatedDistance + CurrentCity.EuclidianDistance;
	BestNode=FrontierCityNumber;
	FrontierCityNumber++;
	while(FrontierCityNumber<Frontier.end())
	{
		CurrentCity=*FrontierCityNumber;
//		if(BestDistance>CurrentCity.AccumulatedDistance + CurrentCity.EuclidianDistance)  //for A* Distance search
        if(BestFare>CurrentCity.AccumulatedFare + CurrentCity.EstimatedPrice)  //for A* Fare search
		{
		    BestFare=CurrentCity.AccumulatedFare+CurrentCity.EstimatedPrice;
			BestDistance=CurrentCity.AccumulatedDistance +
            CurrentCity.EuclidianDistance;
			BestNode=FrontierCityNumber;
		}
		FrontierCityNumber++;
	}
	Nodes++;
	CurrentCity=*BestNode;
	cout<<CurrentCity.Name<<", ";
	Frontier.erase(BestNode);

//	if(GoalDistance>BestDistance || GoalFound==false) // for A* distance
	if(GoalFare>BestFare || GoalFound==false) // For A* fare
	{
			for(CurrentCity.NeighborNumber=CurrentCity.Neighbors.begin();
				CurrentCity.NeighborNumber<CurrentCity.Neighbors.end();
				CurrentCity.NeighborNumber++)
			{
				CurrentNeighbor=*CurrentCity.NeighborNumber;
				if(GetChildCity(CurrentNeighbor, &ChildCity)==false)
				{
					cout<<"Child City not found - Terminating\n";
					return false;
				}

				ChildCity.AccumulatedPath=CurrentCity.AccumulatedPath +
					", " + ChildCity.Name;
                ChildCity.AccumulatedFare=CurrentCity.AccumulatedFare+CurrentNeighbor.Fare;
				ChildCity.AccumulatedDistance=CurrentCity.AccumulatedDistance +
					CurrentNeighbor.Distance;
//					cout<<"Current Expanded Path: "<<ChildCity.AccumulatedPath<<
//					" Distance: "<<ChildCity.AccumulatedDistance<<endl;

				if(ChildCity.Name==EndName)
				{
				    Nodes++;
					GoalDistance=ChildCity.AccumulatedDistance;
					GoalFare=ChildCity.AccumulatedFare;
					GoalPath=ChildCity.AccumulatedPath;
					cout<<ChildCity.Name<<endl<<"Number of Nodes Expanded: "<<Nodes<<endl;
					cout<<"Traveling Distance: " << GoalDistance << " miles"<< endl;
					cout<<"Air Fare: "<< GoalFare <<" Dollars"<<endl;
					GoalFound=true;
				}
				Frontier.push_back(ChildCity);
			}
		}
  }
}

//////////EVERYTHING AFTER THIS IS FOR GREEDY SEARCHES//
//    cout<<CurrentCity.Name<< ", ";
//    Explored.push_front(CurrentCity);
//
////////// CONVERTING NEIGHBORS STRUCTURES INTO CITY STRUCTURES
//
//
//    for(NeighborNumber=CurrentCity.Neighbors.begin(); NeighborNumber<CurrentCity.Neighbors.end();NeighborNumber++)
//    {
//        CurrentNeighbor=*NeighborNumber;
//        if(GetChildCity(CurrentNeighbor, &ChildCity)==false)
//        {
//        cout<<"Dead end at " << CurrentCity.Name<<endl;;
//        return false;
//        }
//        ChildCity.AccumulatedDistance=CurrentCity.AccumulatedDistance + CurrentNeighbor.Distance;
//        if(ChildCity.Name==EndName)
//        {
//        GoalFound=true;
//      CurrentCity=ChildCity;
//        }
//
//
////////// SEE IF CHILD HAS BEEN EXPLORED
//
//
//      AlreadyExplored=false;
//      ExploredCityNumber=Explored.begin();
//
//      while(AlreadyExplored==false && ExploredCityNumber<Explored.end())
//      {
//        ExploredCity=*ExploredCityNumber;
//        if(ExploredCity.Name==ChildCity.Name) AlreadyExplored=true;
//        ExploredCityNumber++;
//      }
//
//
////////// SEE IF CHILD IS IN FRONTIER
//
//
//      if(AlreadyExplored==false)
//      {
//        AlreadyInFrontier=false;
//        FrontierCityNumber=Frontier.begin();
//        while(AlreadyInFrontier==false && FrontierCityNumber<Frontier.end())
//        {
//          FrontierCity=*FrontierCityNumber;
//          if(FrontierCity.Name==ChildCity.Name) AlreadyInFrontier=true;
//          FrontierCityNumber++;
//        }
//      }
//
//
////////// ADD THIS CITY TO THE PATH
//
//
//      if(AlreadyExplored==false && AlreadyInFrontier==false)
//      {
//
//////////FOR GREEDY SEARCH
//        if (ChildCity.EuclidianDistance<SomeMax) //for greedy search DISTANCE
////        if (ChildCity.EstimatedPrice<SomeMax) //for greedy search FARE
//        {
////        SomeMax=ChildCity.EstimatedPrice; //for greedy search FARE
//        SomeMax=ChildCity.EuclidianDistance; //for greedy search DISTANCE
//        BestCity=ChildCity;
//        BestNeighbor=*NeighborNumber;
//        }
//      }
//    }
//
//    AccumulatedDistance=AccumulatedDistance+BestNeighbor.Distance;
//    AirFare=AirFare+BestNeighbor.Fare;
//    Frontier.push_front(BestCity);
//    Nodes++;
//    SomeMax=5000;
//}
//  Nodes++;
//cout<<CurrentCity.Name<<endl<<"Number of Nodes Expanded: "<<Nodes<<endl;
//cout<<"Traveling Distance: "<<AccumulatedDistance<<" miles" <<endl;
//cout<<"Air Fare: "<<AirFare<<" Dollars"<<endl;
//  return GoalFound;
//}
