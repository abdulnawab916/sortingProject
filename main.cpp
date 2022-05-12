// Program    : Lab #10 - Final Exam
// Author     : Abdul Hanan Nawab
// Date       : Spring 2021
//Description: This program computes an employee's weekly gross pay,
//taxes, and net pay. And outputs the data in a tabular fashion
//displaying the users full name (reading from a file),
//the taxes, net pay, and gross pay, overime hours, regular hours.. etc.
// Also writes to a file the formatted structure of the table,
// with only one header and displays in descending order
// by using a bubble sort algorithm. Thus, it then writes
// all of the information to a file.


#include <iostream> // provides std::cout, std::cin, std::endl
#include <string> //provides string' data type
#include <iomanip> // provides std::setprecision
#include <fstream>
#include <cstdlib>//including the stream for std::ifstream,
                   //and std::ofstream
#define SIZE 20
#define TAX_RATE .28
#define HOUR_BRIDGE 40.0 //hours which if surpassed, then overtime pay...


void input_data(std::istream &stream, std::string &first_name,
                std::string &last_name, double &hours_worked, double &hourly_rate,
                double &deduct);
void input_partial_name(std::string label, std::string &partial_name);
void glue_names(std::string first_name, std::string last_name,
                std::string &full_name);
double calculate_grosspay(double hours_worked, double hourly_rate,
                          double regular_hours,
                        double overtime_hours);
double calculate_taxes(double gross_pay);
double calculate_netpay(double gross_pay, double taxes, double depend_deduct);
void show_results( std::ostream &stream, std::string full_name,
                  double regular_hours,
                  double overtime_hours,
                  double hourly_rate,
                  double gross_pay,
                  double taxes, double depend_deduct, double net_pay, int num_employees);
void show_header(std::ostream &stream);
void show_header_two(std::ostream &stream);
void process_hour(double &hours_worked);
void process_payrate(double &hourly_rate);
double split_hours(double hours_worked, double &regular_hours);
char get_yes_no(std::string question);
double second_input();
void show_header_two_again(std::ostream &stream, std::string full_names[],
                           double gross_pays[], int num_employees);
double calc_sum_gp(double gross_pays[],int num_employees);
double compute_average(double data[], double count);
double find_total(double data[], double count);
double find_min(double data[], double count);
double find_max(double data[], double count);
void sort_numbers(double num_numbers[], double num_elements);


int main()
{
    std::string first_name,
    last_name, full_name, question;
    int num_employees;
    double taxes, hours_worked, net_pay,
    deduct;
    double hourly_rate, regular_hours, overtime_hours, gross_pay;
    std::ifstream infile;
    std::ofstream outfile;
    std::string full_names[SIZE];
    double gross_pays[SIZE];
    std::cout << std::fixed << std::setprecision(2);
    outfile.open("/Users/abdulnawab/Desktop/temp/payroll.txt"); //These will be different according to the operating system.
    infile.open("/Users/abdulnawab/Desktop/temp/empdata.txt");  //Takes in the text file.
    
    if ((!infile.is_open()) || (!outfile.is_open()))
    {
        std::cout<< "Cannot open input file"<<std::endl;
        exit(EXIT_FAILURE);
    }
    num_employees = 0;
    input_data(infile, first_name, last_name ,hours_worked, hourly_rate, deduct);
    show_header(outfile);
    sort_numbers(gross_pays, num_employees);
    sort_numbers(full_names, num_employees);

    while (!infile.eof())
    {
        //PROCESSING, NO INPUT!!
        glue_names(first_name,last_name ,full_name);
        overtime_hours = split_hours(hours_worked, regular_hours);
        gross_pay = calculate_grosspay(hours_worked,hourly_rate,regular_hours,
                                       overtime_hours);
        taxes = calculate_taxes(gross_pay);
        net_pay = calculate_netpay(gross_pay,taxes,deduct);

        //Output for first table
        show_results(outfile, full_name,regular_hours,overtime_hours,
                     hourly_rate, gross_pay,taxes,deduct,net_pay, num_employees);
        //array storage
        full_names[num_employees] = full_name;
        gross_pays[num_employees] = gross_pay;
        num_employees += 1;

        
        //checks for input again
    
        input_data(infile, first_name, last_name ,hours_worked, hourly_rate, deduct);
    }
    show_header_two(outfile);
    sort_numbers(gross_pays, num_employees);

    show_header_two_again(outfile, full_names,  gross_pays,  num_employees);
    infile.close();
    outfile.close();
  
        
}

//Module that recieves input data from user and calls
//other modules to get first/last names & to concatenate
//them as a full name.
//Then it gets the inputted hours worked, and hourly rate.
void input_data(std::istream &stream, std::string &first_name, std::string &last_name,
                double &hours_worked,
                double &hourly_rate, double &deduct)
{
    stream >> first_name >> last_name;
    stream >> hours_worked >> hourly_rate >> deduct;
}



//module that concatenates the first/last name
void glue_names(std::string first_name, std::string last_name,
               std::string &full_name)
{
    full_name = last_name + ", " + first_name;
    
}

 //A function that calculates the gross pay
double calculate_grosspay(double hours_worked, double hourly_rate,
                        double regular_hours,
                        double overtime_hours)
{
    double gross_pay;
    gross_pay =
    (regular_hours * hourly_rate) + (overtime_hours * (hourly_rate * 1.5));
    return gross_pay;
}

//Function that calcualtes the taxes that need to be paid.
double calculate_taxes(double gross_pay)
{
    double taxes;
    taxes = TAX_RATE * gross_pay;
    return taxes;
}
//Function that calculates the net pay.
double calculate_netpay(double gross_pay, double taxes, double deduct)
{
    double net_pay;
    net_pay = gross_pay - taxes - deduct;
    return net_pay;
}

//module that displays a table header in professionally orientated spacing.
//Depending on whether it is an output to the file
//or an output to the screen.
void show_header(std::ostream &stream)
{
    stream << std::fixed << std::setprecision(2);
    stream << ""
    <<std::endl;
    stream
    <<"Name                  Reg    Ovt    Hourly  Gross                    Net"
    <<std::endl;
    stream
    <<"                      Hours  Hours  Rate    Pay      Taxes   Deduct  Pay"
    <<std::endl;
    stream
    <<"====================  =====  =====  ======  =======  ======  ======  ======="
    <<std::endl;


}


//module for displaying the second portion to the file.
//ask if this is allowed.
void show_header_two(std::ostream &stream)
{
            {
                stream << std::fixed << std::setprecision(2);
                stream <<std::endl;
                stream <<"=============================" <<std::endl;
                stream <<"  Employee Payroll Summary   " <<std::endl;
                stream <<"=============================" <<std::endl;
                stream <<"Name                  Gross   " <<std::endl;
                stream <<"                      Pay   "   <<std::endl;
                stream <<"====================  ======= " << std::endl;
            }

    }
//Displays the header for the total/average/etc gross pay amounts
//Displays by calling the function.
void show_header_two_again(std::ostream &stream, std::string full_names[],
                           double gross_pays[], int num_employees)
{

    int i;
    for (i = 0; i < num_employees; i++)
    {
    stream <<std::left<<std::setw(20) << <<"  "
        <<std::right<<std::setw(7)
        <<  gross_pays[i] <<std::endl;
    }

    stream
           <<std::endl;
    stream <<std::left<<std::setw(20)
            <<"Total Gross Pay"
            <<"  "
            <<std::right<<std::setw(7)
    <<
            << find_total(gross_pays, num_employees)<<std::endl;
    stream <<std::left<<std::setw(20)
    <<"Average Gross Pay"
    <<"  "
    <<std::right<<std::setw(7)
     << compute_average(gross_pays, num_employees)<<std::endl;
    stream <<std::left<<std::setw(20)
    <<"Minimum Gross Pay"
    <<"  "
    <<std::right<<std::setw(7)
    << find_min(gross_pays, num_employees)<<std::endl;
    stream <<std::left<<std::setw(20)
    <<"Maximum Gross Pay"
    << "  "
    <<std::right<<std::setw(7)
    <<find_max(gross_pays, num_employees) << std::endl;

    
}

//Module that shows the results corresponding with the table.
//With the designated alingment as well (left for names, right for numbers)
void show_results(std::ostream &stream, std::string full_name, double regular_hours,
                  double overtime_hours,
                  double hourly_rate,
                  double gross_pay,
                  double taxes, double deduct, double net_pay, int num_employees)
{

    stream << std::fixed << std::setprecision(2);
    stream
    <<std::left<<std::setw(20)<< full_name<< "  "
    <<std::right<<std::setw(5)<< regular_hours << "  "
    <<std::right<<std::setw(5)<< overtime_hours<< "  "
    <<std::right<<std::setw(6)<< hourly_rate << "  "
    <<std::right<<std::setw(7)<< gross_pay<< "  "
    <<std::right<<std::setw(6)<< taxes << "  "
    <<std::right<<std::setw(6)<< deduct << "  "
    <<std::right<<std::setw(7)<< net_pay << "  ";
    stream <<std::endl;

}
// Function that splits hours from the given hours and outputs
// overtime and regular variables.
double split_hours(double hours_worked, double &regular_hours)
{
    double overtime_hours;
    if (hours_worked >= HOUR_BRIDGE)
    {
        regular_hours = HOUR_BRIDGE;
        overtime_hours = hours_worked - HOUR_BRIDGE;
    }
    else
    {
        regular_hours = hours_worked;
        overtime_hours = 0.00;
    }
    return overtime_hours;
}
//Function that calculates the sum of a given array.
double calc_sum_gp(double gross_pays[], int num_employees)

{
    double gross_pay_sum;
    gross_pay_sum = 0;
    int i;
    for(i = 0; i < num_employees; i++)
    {
        gross_pay_sum = gross_pay_sum + gross_pays[i];
    }
    return gross_pay_sum;
}
//Function that adds all gross pay
double find_total(double data[], double count)
{
    int i;
    double sum;
    sum = 0.0;
    for (i=0; i < count; i++)
    {
        sum += data[i];
        
    }
    return sum;
}
//Function that calculates the average cALL WHEN NEED AVERAGE AND SUM!
double compute_average(double data[], double count)
{
    
    int i;
    double average = 0.0;
    for (i=0; i < count; i++)
    {
        average = find_total(data, count)/count;

    }
    return average;
}
//Function finds min of gross pay
double find_min(double data[], double count)
{
    int i;
    int minimum;
    minimum = data[0];
    for (i=1; i < count; i++)
    {
        if (data[i] < minimum){
            minimum = data[i];
        }
    }
    return minimum;
}
//Function that finds max of gross pay
double find_max(double data[], double count)
{
    int i;
    int maximum;
    maximum = data[0];
    for (i = 1; i < count; i++)
    {
        if(data[i] > maximum){
            maximum = data[i];
        }
    }
    return maximum;
}

//Optimized bubble sort algorithm that displays in descending order.
//Could be more efficient, has runtime O(n^2). Nested for-loops.
void sort_numbers(double num_numbers[], double num_elements)
{
    bool swaps;
    int pass;
    int i;
    int temp_number;
    
    
    swaps = true;
    for (pass = 1; (pass < num_elements) && swaps; pass++){
        swaps = false;
        for (i=0; i < num_elements-pass; i++){
            if(num_numbers[i] < num_numbers[i+1]){
                swaps= true;
            temp_number = num_numbers[i];
            num_numbers[i]= num_numbers[i+1];
            num_numbers[i+1] = temp_number;
        }
    }

    }
}
