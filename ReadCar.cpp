#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct carType
{
  enum {MAX_CHAR_LEN=100};
  char CarName[MAX_CHAR_LEN];
  double MPG;
  int Cylinders;
  double Displacement;
  double Horsepower;
  double Weight;
  double Acceleration;
  int Model;
  char Origin[MAX_CHAR_LEN];
  bool ValidEntry;
  carType();
};
carType::carType()
{
  for (int i = 0; i < MAX_CHAR_LEN; i++)
  {
    CarName[i] = ' ';
  }
  MPG = 0;
  Cylinders = 0;
  Displacement = 0;
  Horsepower = 0;
  Weight = 0;
  Acceleration = 0;
  Model = 0;
  for (int i = 0; i < MAX_CHAR_LEN; i++)
  {
    Origin[i] = ' ';
  }
  ValidEntry = false;
}
carType readCar(ifstream &infile)
{
  carType car;
  infile.get(car.CarName, carType::MAX_CHAR_LEN, ';');
  infile.ignore(100,';');
  infile >> car.MPG;
  infile.ignore(100,';');
  infile >> car.Cylinders;
  infile.ignore(100,';');
  infile >> car.Displacement;
  infile.ignore(100,';');
  infile >> car.Horsepower;
  infile.ignore(100,';');
  infile >> car.Weight;
  infile.ignore(100,';');
  infile >> car.Acceleration;
  infile.ignore(100,';');
  infile >> car.Model;
  infile.ignore(100,';');
  infile.get(car.Origin, carType::MAX_CHAR_LEN);
  car.ValidEntry = !infile.eof();
  infile.ignore(100,'\n');
  return car;
}
const int MAX_CAR = 500;
int readInt(const char prompt[]){
    int temp = 0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid Data!" << endl;
        cout << prompt;
        cin >> temp;
    }
    return temp;
}
int readDouble(const char prompt[]){
    double temp = 0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid Data!" << endl;
        cout << prompt;
        cin >> temp;
    }
    return temp;
}
int readCars(carType cars[])
{
  ifstream carfile("cars.txt");
  int numCars = 0;
  while(carfile.peek() != EOF && numCars < MAX_CAR)
  {
    cars[numCars] = readCar(carfile);
    numCars++;
  }
  return numCars;
}
void printCar(carType car[], int num)
{
  for(int i = 0; i < num; i++)
  {
  if(car[i].ValidEntry)
  {
  cout << i << ". " << car[i].CarName << " "
       << car[i].MPG << " "
       << car[i].Cylinders << " "
       << car[i].Displacement << " "
       << car[i].Horsepower << " "
       << car[i].Weight << " "
       << car[i].Acceleration << " "
       << car[i].Model << " "
       << car[i].Origin << endl;
  }
  }
}
carType addCar(carType car[])
{ int empty = 0;
  for (int i = 0; i < MAX_CAR; i++)
  {
    if(!car[i].ValidEntry)
    {
      empty = i;
      break;
    }
  }
  if(empty == 0) 
  {
    cout << "Full!" << endl;
  }
  
  cout << "Please enter name of car: ";
  cin.ignore(100,'\n');
  cin.getline(car[empty].CarName, carType::MAX_CHAR_LEN);
  car[empty].MPG = readDouble("Please enter MPG: ");
  car[empty].Cylinders = readInt("Please enter Cylinders: ");
  car[empty].Displacement = readDouble("Please enter Displacement: ");
  car[empty].Horsepower = readDouble("Please enter Horsepower: ");
  car[empty].Weight = readDouble("Please enter Weight: ");
  car[empty].Acceleration = readInt("Please enter Acceleration: ");
  car[empty].Model = readInt("Please enter Model: ");
  cout << "Please enter Origin of car: ";
  cin.ignore(100, '\n');
  cin.getline(car[empty].Origin, carType::MAX_CHAR_LEN);
  car[empty].ValidEntry = true;
    
  return car[empty];
}
void searchOrigin(carType car[], int num)
{
  char origin[100];
  cout << "Please enter origin of car: ";
  cin.ignore(100, '\n');
  cin.getline(origin, 100);
  cout << origin << endl;
  for (int i = 0; i < num; i++)
  {
    if(strcmp(car[i].Origin, origin)==0)
    {
      cout << i << ". " << car[i].CarName << " "
       << car[i].MPG << " "
       << car[i].Cylinders << " "
       << car[i].Displacement << " "
       << car[i].Horsepower << " "
       << car[i].Weight << " "
       << car[i].Acceleration << " "
       << car[i].Model << " "
       << car[i].Origin << endl;
    }
  }
}
void displayMenu()
{
  cout << "What would you like to do?" << endl << endl;
  cout << "1. Display Info of all cars" << endl;
  cout << "2. Enter Info for new car" << endl;
  cout << "3. Remove car" << endl;
  cout << "4. Search car from certain Origin" << endl;
  cout << "5. Quit" << endl;
}
void removeCar(carType car[], int num)
{
  int remove = 0;
  remove = readInt("Please enter the index you wish to remove: ");
  cout << remove << endl;
  while (remove <= 0 || remove > num )
  {
    cout << "Outside of index try again" << endl;
    cin >> remove;
  }
  car[remove].ValidEntry = false;
  cout << "Remove successful!" << endl;
}
int main()
{
  carType vroom[MAX_CAR];
  int num = readCars(vroom); 
  int select = 0;

  cout << num << endl;

  while (select != 5)
  {
    displayMenu();
    cout << "Enter here: ";
    cin >> select;

    while (select < 0 || select > 5)
    {
      cout <<"Please choose an option between 1-5: ";
      cin >> select;

    }

    if (select == 1)
    {
        printCar(vroom, num);
    }
    if (select == 2)
  {
    addCar(vroom);
    num++;
  }
    if (select == 3)
    {
      removeCar(vroom, num);
      num--;
    }
    if (select == 4)
    {
      searchOrigin(vroom, num);
    }
  }
  cout << "Thanks for using my program" << endl;

  return 0;
}