#include<iostream>
using namespace std;

template <typename T>
T findmax(T a,T b){
	
	if(a>b){
		return a;
	}else{
		return b;
	}
}

template <typename T>
void setNum(T &num1 ,T &num2)
{
	cout<<"enter num1 and num2 : ";
	cin>>num1>>num2;
}

template <typename T>
class Calculator{
	private:
		T num1,num2;
		
	public:
		Calculator(T a, T b){
			num1 = a;
			num2 = b;
		}
		
		
		T addition(){
			return num1 + num2;
		}
		
		T substraction(){
			return num1 - num2;
		}
		
		T multiplication(){
			return num1 * num2;
		}
		
		T division(){
			if(num2 != 0){
				return num1 / num2;
			}
			else{
				cout<<"Division by zero"<<endl;
				return 0;
			}
		}
};

int main(){
	
	char choice;
    cout << "Choose data type (i for int, f for float, d for double): ";
    cin >> choice;

	if(choice == 'i')
	{
		int a,b;
		setNum(a,b);
		
		Calculator <int>c1(a,b);
		cout<<"Maximum number : "<<findmax(a, b)<<endl;
		cout << "Integer operations:" << endl;
	    cout << a << " + " << b << " = " << c1.addition() << endl;
	    cout << a << " - " << b << " = " << c1.substraction() << endl;
	    cout << a << " * " << b << " = " << c1.multiplication() << endl;
	    cout << a << " / " << b << " = " << c1.division() << endl;
		
	}
	else if(choice == 'f')
	{
		float a,b;
		setNum(a,b);
		Calculator <float>c2(a,b);
		cout << "Integer operations:" << endl;
		cout<<"Maximum number : "<<findmax(a, b)<<endl;
	    cout << a << " + " << b << " = " << c2.addition() << endl;
	    cout << a << " - " << b << " = " << c2.substraction() << endl;
	    cout << a << " * " << b << " = " << c2.multiplication() << endl;
	    cout << a << " / " << b << " = " << c2.division() << endl;
	}
	else if(choice == 'd')
	{
		double a,b;
		setNum(a,b);
		Calculator <double>c3(a,b);
		cout << "Integer operations:" << endl;
		cout<<"Maximum number : "<<findmax(a, b)<<endl;
	    cout << a << " + " << b << " = " << c3.addition() << endl;
	    cout << a << " - " << b << " = " << c3.substraction() << endl;
	    cout << a << " * " << b << " = " << c3.multiplication() << endl;
	    cout << a << " / " << b << " = " << c3.division() << endl;

	}
	else{
		cout<<"Invalid choice"<<endl;
	}
	
	return 0;
	
	
}
