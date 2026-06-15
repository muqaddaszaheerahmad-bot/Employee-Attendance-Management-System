#include<iostream>
using namespace std;
class Employee{
protected:
    string employee_name;
    int employee_ID;
    bool attendance[30];
    int days;
public:
    Employee(){
        employee_name="Unknown";
        employee_ID=0;
        for (int i=0;i<30;i++){
            attendance[i]=false;
        }
        days=0;
    }

    ~Employee(){
        cout<<"Employee Object Destroyed!"<<endl;
    }

    virtual void input(){
        cout<<"Enter Employee name:";
        cin.ignore();
        getline(cin,employee_name);
        cout<<"Enter Employee ID:";
        cin>>employee_ID;
        cout<<"Present today? (1/0): ";
        cin>>attendance[0];
    }

    virtual void DisplayInfo(){
        cout<<"Employee Name:"<<employee_name<<endl;
        cout<<"Employee ID:"<<employee_ID<<endl;
        cout<<"Employee Attendance"<<attendance[0]<<endl;
    }

    int getID(){
        return employee_ID;
    }

    void markAttendance(bool status){
        if (days < 30){
            attendance[days]=status;
            days++;
            cout<<"Attendance recorded!"<<endl;
        } 
		else{
            cout<<"Attendance already full for 30 days!"<<endl;
        }
    }

    void displayAttendance(){
        for (int i=0;i<days;i++){
            cout<<"Day"<<i +1<<":"
                 <<(attendance[i]?"Present":"Absent")<<endl;
        }
    }

    void setAttendance(int day,bool status){
    if (day>=1&&day<=30){
        attendance[day-1]=status;
        cout<<"Attendance updated for Day"<<day<<endl;
    } else {
        cout<<"Invalid day!"<<endl;
    }
}
};

class PermanentEmployee:public Employee{
private:
    string department;

public:
    void input()override{
        Employee::input();
        cout<<"Enter Department:";
        getline(cin,department);
    }

    void DisplayInfo() override{
        cout << "==== Permanent Employee ====" << endl;
        Employee::DisplayInfo();
        cout<<"Department:"<<department<<endl;
    }
};

class ContractEmployee:public Employee{
protected:
    int contractduration;

public:
	ContractEmployee(){
		contractduration=0;
	}
    void input() override{
        Employee::input();
        cout<<"Enter the contract duration(months) of employee:";
        cin>>contractduration;
        cout<<"You entered:"<<contractduration<<endl;
    }

    void DisplayInfo() override{
        cout<<"===== Contract Employee ===="<<endl;
        Employee::DisplayInfo();
        cout<<"Contract Duratrion:"<<contractduration<<"months"<<endl;
    }
};

int main(){
    Employee*emp[100];
    int count=0;
    int choice;
    do {
        cout<<"==== Menu ===="<<endl;
        cout<<"1.Add Employee."<<endl;
        cout<<"2.View all Employees."<<endl;
        cout<<"3.Search Employee."<<endl;
        cout<<"4.Mark Attendance." <<endl;
        cout<<"5.Update Attendance."<< endl;
        cout<<"6.View Employee Record."<<endl;
        cout<<"7.Delete Employee."<<endl;
        cout<<"8.Employees Present."<<endl;
        cout<<"9.Attendance Report."<<endl;
        cout<<"10.Exiting!"<<endl;
        cout<<"Enter choice:";
        cin>>choice;

        switch(choice){

        case 1: 
	{
            int type;
            cout<<"1. Permanent Employee"<<endl;
            cout<<"2. Contract Employee"<<endl;
            cout<<"Enter type:";
            cin >> type;

            if(type == 1){
            emp[count]=new PermanentEmployee();
            emp[count]->input();
            cout << "Permanent Employee added successfully!"<<endl;
            }
            else if (type==2){
            emp[count] = new ContractEmployee();
            emp[count]->input();
            cout<<"Contract Employee added successfully!"<<endl;
            }
            else{
            cout<<"Invalid type!"<<endl;
            break;
            }

            count++;
            break;
            }

        case 2: 
		{
            for(int i = 0; i < count; i++){
                emp[i]->DisplayInfo();
            }
            break;
        }

        case 3: 
		{
            int id;
            cout<<"Enter Employee id to search:";
            cin>>id;

            for(int i=0;i<count;i++) {
                if(emp[i]->getID() == id){
                    emp[i]->DisplayInfo();
                }
            }
            break;
        }

        case 4: 
		{
            int id;
            cout<<"Enter Employee ID to mark attendance:";
            cin>>id;

            bool found=false;

            for(int i = 0; i < count; i++){
                if (emp[i]->getID() == id){
                    emp[i]->markAttendance(true);
                    cout<<"Attendance marked!"<<endl;
                    found=true;
                    break;
                }
            }

            if(!found){
                cout<<"Employee not found!"<<endl;
            }

            break;
        }

        case 5: 
		{
        int id;
        int day;
        int newAtt;

        cout<<"Enter Employee ID:";
        cin >> id;

        cout<<"Enter Day (1-30):";
        cin>>day;

        cout<<"Enter Attendance(1 = Present, 0 = Absent):";
        cin>>newAtt;

        bool found=false;

        for(int i=0;i<count;i++){
        if (emp[i]->getID() == id){
            emp[i]->setAttendance(day,newAtt==1);
            found=true;
            break;
         }
        }

        if (!found){
           cout<<"Employee not found!"<<endl;
        }

        break;
        }
        case 6: 
		{
            int id;
            cout<<"Enter ID of Employee to view:";
            cin>>id;

            for(int i=0;i<count;i++) {
                if (emp[i]->getID()==id) {
                    emp[i]->DisplayInfo();
                }
            }

            break;
        }

        case 7: {
            int id;
            cout<<"Enter ID to delete:";
            cin>>id;

            for(int i = 0; i < count; i++) {
                if (emp[i]->getID()==id) {
                    delete emp[i];
                    emp[i]=emp[count-1];
                    count--;
                    break;
                }
            }

            break;
        }

        case 8:
		 {
            for(int i=0;i<count;i++){
                emp[i]->markAttendance(true);
            }

            cout <<"Attendance marked for all employees."<<endl;
            break;
        }

        case 9: 
		{
            cout<<"====== Attendance Report ======"<<endl;

            for(int i = 0; i < count; i++){
                emp[i]->DisplayInfo();
            }

            break;
        }

        case 10: 
	{
            cout<<"Exiting program"<<endl;
            break;
        }

        default: 
	{
            cout<<"Invalid choice!";
        }
        }

    } 
	while(choice!=10);

    for(int i=0;i<count;i++) {
        delete emp[i];
    }

    return 0;
}
