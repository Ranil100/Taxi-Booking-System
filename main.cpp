#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
using namespace std;
class Taxi;
class Booking;
class TaxiBookingSystem;

class Taxi
{
    public:
    static int id;
    int taxiId;
    char currentPoint;
    int totalEarnings;
    int availableTime;
    Taxi()
    {
        currentPoint = 'A';
        totalEarnings = 0;
        taxiId = ++id;
        availableTime = 0;
    }
};
int Taxi :: id = 0;
class Booking
{
    public:
    int bookingId;
    int customerId;
    int taxiId;
    char fromPoint;
    char toPoint;
    int pickupTime;
    int dropTime;
    int amount;

    Booking(int bookingId, int customerId, int taxiId, char fromPoint, char toPoint, int pickupTime, int dropTime, int amount)
    {
        this->bookingId = bookingId;
        this->customerId = customerId;
        this->taxiId = taxiId + 1;
        this->fromPoint = fromPoint;
        this->toPoint = toPoint;
        this->pickupTime = pickupTime;
        this->dropTime = dropTime;
        this->amount = amount;
    }
};
class TaxiBookingSystem
{
    vector <Taxi> taxis;
    vector <Booking> bookings;
    int bookingId;
    public:
    TaxiBookingSystem()
    {
        for(int i = 0; i < 6; i++)
        {
            Taxi t;
            taxis.push_back(t);
        }
        bookingId = 0;
    }
    void bookTaxi()
    {
        int customerId;
        char fromPoint;
        char toPoint;
        int pickupTime;
        while(true)
        {
            cout<<"Enter Customer ID:";
            cin>>customerId;
            if(cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Error: Input is not an integer. Please try again.\n";
            }
            else
            {
                break;
            }
        }
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout<<"Enter From Point (A to F):";
        cin>>fromPoint;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout<<"Enter To Point (A to F):";
        cin>>toPoint;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        while(true)
        {
            cout<<"Enter Pickup Time:";
            cin>>pickupTime;
            if(cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Error: Input is not an integer. Please try again.\n";
            }
            else
            {
                break;
            }
        }
        int taxi = checkAvailability(fromPoint, pickupTime);
        if(taxi == -1)
        {
            cout<<"No Taxis Available\n";
            return;
        }
        vector<int> temp = calculateFareAndTime(fromPoint, toPoint); 
        int fare = temp[0];
        int dropTime = temp[1] + pickupTime;
        Booking book(++bookingId, customerId, taxi, fromPoint, toPoint, pickupTime, dropTime, fare);
        bookings.push_back(book);
        taxis[taxi].currentPoint = toPoint;
        taxis[taxi].totalEarnings += fare;
        taxis[taxi].availableTime = dropTime;
        cout<<"\nTaxi "<<taxi+1<<" is alloted\n";
    }
    vector<int> calculateFareAndTime(char fromPoint, char toPoint)
    {
        int fare = 100;
        int distance = calculateDistance(fromPoint, toPoint);
        int time = distance;
        distance = distance * 15;
        fare = fare + (distance - 5)*10;
        return {fare, time};
    }
    int checkAvailability(char fromPoint, int pickupTime)
    {
        int minDistance = INT_MAX;
        int nearestTaxi = -1;
        for(int i = 0; i < 6; i++)
        {
            if((taxis[i].availableTime <= pickupTime) && pickupTime >= (taxis[i].availableTime + calculateDistance(fromPoint,taxis[i].currentPoint)))
            {   
                int distance = calculateDistance(fromPoint, taxis[i].currentPoint);
                if(distance < minDistance)
                {
                    minDistance = distance;
                    nearestTaxi = i;
                }
                else if(distance == minDistance)
                {
                    if(taxis[i].totalEarnings < taxis[nearestTaxi].totalEarnings)
                    {
                        nearestTaxi = i;
                    }
                }
            }
        }
        return nearestTaxi;
        
    }
    int calculateDistance(char fromPoint, char currentPoint)
    {
        int distance = abs((int)fromPoint - (int)currentPoint);
        return distance;
    }
    void viewTaxiDetails()
    {
        cout<<"\n------------------------------------------------------------------------------------\n";
        cout<<endl<<setw(20)<<"Taxi ID"<<setw(20)<<"Total Earnings"<<setw(20)<<"Current Point"<<setw(20)<<"Available Time\n";
        for(int i = 0; i < taxis.size(); i++)
        {
            cout<<"------------------------------------------------------------------------------------\n";
            cout<<setw(20)<<taxis[i].taxiId;
            cout<<setw(20)<<taxis[i].totalEarnings;
            cout<<setw(20)<<taxis[i].currentPoint;
            cout<<setw(20)<<taxis[i].availableTime;
            cout<<endl;
        }
    }
    void viewBookings()
    {
        cout<<"\n------------------------------------------------------------------------------------------------------------------------\n";
        cout<<endl<<setw(14)<<"Booking ID"<<setw(14)<<"Customer ID"<<setw(14)<<"Taxi ID"<<setw(14)<<"From Point"<<setw(14)<<"To Point"<<setw(14)<<"Pickup Time"<<setw(14)<<"Drop Time"<<setw(14)<<"Fare\n";
        for(int i = 0; i < bookings.size(); i++)
        {
            cout<<"------------------------------------------------------------------------------------------------------------------------\n";
            cout<<setw(14)<<bookings[i].bookingId;
            cout<<setw(14)<<bookings[i].customerId;
            cout<<setw(14)<<bookings[i].taxiId;
            cout<<setw(14)<<bookings[i].fromPoint;
            cout<<setw(14)<<bookings[i].toPoint;
            cout<<setw(14)<<bookings[i].pickupTime;
            cout<<setw(14)<<bookings[i].dropTime;
            cout<<setw(14)<<bookings[i].amount;
            cout<<endl;
        }
    }
    void run()
    {
        while(true)
        {
            cout<<"\n\t\t<----------------Taxi Booking System------------------>\n";
            int choice;
            while(true)
            {
                cout<<"\n1. Book a taxi";
                cout<<"\n2. View Bookings";
                cout<<"\n3. View Taxi Details";
                cout<<"\n4. Exit the Application\n";
                cout<<"\nEnter the choice:";
                cin>>choice;
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << "Error: Input is not an integer. Please try again.\n";
                }
                else
                {
                    break;
                }
            }
            switch(choice)
            {
                case 1:
                    bookTaxi();
                    break;
                case 2:
                    viewBookings();
                    break;
                case 3:
                    viewTaxiDetails();
                    break;
                case 4:
                    exit(0);
                default:
                    run();
            }
        }
    }
};
int main()
{
    TaxiBookingSystem obj;
    obj.run();
}
