#include<iostream>
#include<map>
#include<vector>
#include<numeric>
#include<string>
#include<algorithm>
using namespace std;

double calculateAverage(const vector<int>& marks) {
    if (marks.empty()) 
		return 0;
    return accumulate(marks.begin(), marks.end(), 0.0) / marks.size();
}

int main(){
	map<string , vector <int> > studentRecord;
	int choice;
	
	do{
		cout<<"1.Add student record\n 2.Display student record\n 3.Show topper\n 4.Exit\n";
		cout<<"---------------------------------\n";
		cout<<"Enter your choice: ";
		cin >> choice;
		
		switch(choice){
			case 1:{
				string name;
				vector<int> marks(3);
				cout<<"Enter student name: ";
				cin >> name;
				cout << "Enter marks of 3 subjects: ";
				for(int i=0; i < 3; i++){
					cin >> marks[i];
				}
				studentRecord[name] =  marks;
				cout<<"-------------------------------\n";
				break;
				
			}
			
			case 2:{
				cout <<"\nStudent records: "<<endl;
				for (map<string, vector <int> >::iterator it = studentRecord.begin(); it != studentRecord.end(); ++it) {
    				const string& name = it->first;
    				const vector<int>& marks = it->second;
    				double avg = calculateAverage(marks);

    				cout << "Student: " << name << ", Marks: ";
    
    				for (vector<int>::const_iterator vit = marks.begin(); vit != marks.end(); ++vit) {
       	 				cout << *vit << " ";
    				}
    
    				cout << ", Average: " << avg << endl<<endl;
				}
				cout<<"-------------------------------\n";
				break;
			}
			
			
    		case 3: {
    			if (studentRecord.empty()) {
        			cout << "Record unavailable." << endl<<endl;
        			break;
    			}

    			string topperName;
    			double highestAvg = 0.0;

    			for (map<string, vector <int> >::iterator it = studentRecord.begin(); it != studentRecord.end(); ++it) {
        			double avg = calculateAverage(it->second);
        			if (avg > highestAvg) {
            			highestAvg = avg;
            			topperName = it->first;
        			}
    			}

    			cout << "Topper: " << topperName << " with average " << highestAvg << endl<<endl;
    			cout<<"-------------------------------\n";
    			break;
			}

			
			case 4:{
				cout<<"Exiting.....!"<<endl;
				break;
			}
			
			default :
				cout << "Invalid choice.."<<endl;
		}
		
	}while(choice != 4);
	
	return 0;
}
