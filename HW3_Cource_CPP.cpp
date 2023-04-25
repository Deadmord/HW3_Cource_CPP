#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
//using namespace std;

//implement max, min, swap template functions for two arguments.

template <typename Ta, typename Tb>
auto min(const Ta& a, const Tb& b)
{
    return a <= b ? a : b;
}

template <typename Ta, typename Tb>
auto max(const Ta& a, const Tb& b)
{
    return a >= b ? a : b;
}

template <typename T>
void my_swap(T& a, T& b)
{
    //T* ap = &a;
    //T* bp = &b;
    //T tmp = *ap;
    //*ap = *bp;
    //*bp = tmp;

    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
void std_swap(T &a, T &b)
{
    std::swap(a, b);
}

// using appropriate function from <algorithm> print if the randomly filled array of integers contains :
// all odd values
// all even values
// at least one odd value
// at least one even value
// calculate the number of odd and even values
// find value in the array(using std::find_if)

//template <typename T>
void init_array(int a[], size_t size, int min, int max)
{
    srand(time(0));
    for (size_t i(0); i != size; i++)
    {
        a[i] = rand()%(max-min+1) + min;
    }
}

void print_array(int a[], size_t size, std::ostream& out)
{
    for (size_t i(0); i != size; i++)
    {
        out << a[i] << " ";
    }

    out << '\n';
}

void check_array(int a[], size_t size, int find_value, std::ostream& out)
{
    bool res[4];
    size_t odd_count, even_count;
    size_t find_value_position;

    res[0] = std::all_of(a, a + size, [](int a) {return (a % 2) == 0; });
    res[1] = std::all_of(a, a + size, [](int a) {return (a % 2) == 1; });
    res[2] = std::any_of(a, a + size, [](int a) {return (a % 2) == 0; });
    res[3] = std::any_of(a, a + size, [](int a) {return (a % 2) == 1; });
    odd_count = std::count_if(a, a + size, [](int a) {return (a % 2) == 0; });
    even_count = std::count_if(a, a + size, [](int a) {return (a % 2) == 1; });
    find_value_position = std::find_if(a, a + size, [find_value](int a) {return a == find_value; }) - a;

    out << "all odd values: \t" << (res[0] ? "true" : "false") << '\n';
    out << "all even values: \t" << (res[1] ? "true" : "false") << '\n';
    out << "at least one odd value: " << (res[2] ? "true" : "false") << '\n';
    out << "at least one even value:" << (res[3] ? "true" : "false") << '\n';
    out << "number of odd values: \t" << odd_count << '\n';
    out << "number of even values: \t" << even_count << '\n';

    out << "find value position: \t";
    find_value_position == size ? (out << "not found" << '\n') : out << find_value_position << '\n';
}

//- implement template 'map' function.the function should convert all values from array using functor
//function prototype :
//template<typename F> void my_map(T* b, T* e, std::function<T(const T&)> f)
//where b - pointer to begin of array, b - pointer to end of array, [a, b)
//f - mapping function
//example 1, 2, 3, 4->should be converted into 1, 4, 9, 16 using square operation
//int a[]{ 1, 2, 3, 4 }; my_map(a, a + 4, [](auto a) {return a * a; });

template<typename T> 
void my_map(T* b, T* e, std::function<T(const T&)> f)
{
    while (b != e)
    {
        *b = f(*b);
        b++;
    }
}

//- implement template 'reduce' function.the function should convert all values from array using the functor
//function prototype :
//template<typename F> void my_reduce(T* b, T* e, std::function<T(T& accum, const T& v)> f, T accum0)
//where b - pointer to begin of array, b - pointer to end of array, [a, b)
//f - reduce function
//example 1, 2, 3, 4->should be converted into 10 using the sum operation
//int a[]{ 1, 2, 3, 4 }; my_reduce(a, a + 4, [](auto acc, auto a) {return acc + a; });

template<typename T> 
void my_reduce(T* b, T* e, std::function<T(T& accum, const T& v)> f, T& accum)
{
    while (b != e)
    {
        accum = f(accum, *b);
        b++;
    }
}

//- sort array of structures with integer, double, and string(const char*) fields by all these fields withoutand with indexes(lecture example).
struct electric_car
{
    const char* name;
    int id;
    int capacity;
    float current_level; // 0 to 1
};
std::ostream& operator << (std::ostream& os, const electric_car& car)
{
    return os << car.id << " \t" << car.name << " \tcurrent charge: " << car.capacity * car.current_level << " kWth";
}

template<class T>
void print_array_vertical(T arr[], size_t size, std::ostream& out)
{
    for (size_t i(0); i != size; i++)
    {
        out << arr[i] << "\n";
    }
    out << "\n";
}

template<class T>
void print_array_vertical_by_idx(int idx[], T arr[], size_t size, std::ostream& out)
{
    for (size_t i(0); i != size; i++)
    {
        out << arr[idx[i]] << "\n";
    }
    out << "\n";
}

template<class T>
void sort_array(T arr[], size_t size, std::function<bool(T, T)> sort) 
{
    std::sort(arr, arr + size, sort);
}

template<class T>
void sort_array_by_idx(int idx[], T arr[], size_t size, std::function<bool(int, int)> sort)
{
    std::sort(idx, idx + size, sort);
}

//-------------------------------main---------------------------------------
int main()
{
    std::cout << "Implement max, min template functions for two arguments.\n";
    int a = 3;
    double b = 2.718;
    auto modifable_res = min(a, b);

    std::cout << a << " < " << b << " = " << min(a, b) << "\t" << typeid(min(a, b)).name() << "\n";
    std::cout << a << " > " << b << " = " << max(a, b) << "\t\t" << typeid(max(a, b)).name() << "\n";
    std::cout << "Inc min = " << ++modifable_res << "\t\t" << typeid(modifable_res).name() << "\n";

    std::cout << "\nImplement swap template functions for two arguments. Few different ways.\n";
    char ar1[] = "swap_array_1";
    char ar2[] = "swap_array_2";
    std_swap(ar1, ar2);
    std::cout << ar1 << " " << ar2 << "\n";

    std::string a2 = "string_1";
    std::string b2 = "str-2";
    my_swap(a2, b2);
    std::cout << a2 << " " << b2 << "\n";

    char* a3 = new char[10] {"hellllo"};
    char* b3 = new char[5] {"wrld"};
    my_swap(a3, b3);
    std::cout << a3 << " " << b3 << "\n";

    float a4 = 42;
    float b4 = 1.618;
    my_swap(a4, b4);
    std::cout << a4 << " " << b4 << "\n";
    //---------------------------------------------------------------------------------------------
    std::cout << "\nUsing appropriate function from <algorithm> print if the randomly filled array of integers contains :\n";
    const size_t arr_size(5);
    int arr[arr_size];
    int find_val = 8;

    init_array(arr, arr_size, 5, 20); // Init array with random numbers from 5 to 20
    print_array(arr, arr_size, std::cout);
    check_array(arr, arr_size, find_val, std::cout);

    //---------------------------------------------------------------------------------------------
    std::cout << "\nImplement template 'map' function. the function should convert all values from array using functor:\n";
    int map_arr[] = { 2, 3, 4, 5};
    print_array(map_arr, 4, std::cout);
    my_map<int>(map_arr, map_arr + 4, [](auto a) {return a * a; });
    print_array(map_arr, 4, std::cout);

    //---------------------------------------------------------------------------------------------
    std::cout << "\nImplement template 'reduce' function.the function should convert all values from array using the functor:\n";
    int reduce_arr[]{ 1, 2, 3, 4 };
    int acc(0);
    print_array(reduce_arr, 4, std::cout);
    my_reduce<int>(reduce_arr, reduce_arr + 4, [](auto acc, auto a) {return acc + a; }, acc);
    std::cout << acc << "\n";

    //---------------------------------------------------------------------------------------------
    std::cout << "\nSort array of structures with integer, double, and string (const char*) fields by all these fields without and with indexes (lecture example).\n";
    int idx[] = { 0, 1, 2, 3, 4, 5 };
    electric_car park[] = {
        {"Model S", 01, 85, 0.75},
        {"Model S", 02, 85, 0.34},
        {"Model S", 03, 85, 0.95},
        {"Model 3", 04, 55, 0.60},
        {"Model 3", 05, 55, 0.25},
        {"Cybertruck", 06, 200, 0.50},
    };
    std::function<bool(electric_car, electric_car)> sortByNameAndCharge = [](electric_car i1, electric_car i2) -> bool
    {
        if (i1.name == i2.name)
            return (i1.capacity * i1.current_level > i2.capacity * i2.current_level);
        else
            return i1.name > i2.name;
    };
    std::function<bool(int, int)> sortByNameAndChargeIdx = [park](int i1, int i2) -> bool
    {
        if (park[i1].name == park[i2].name)
            return (park[i1].capacity * park[i1].current_level > park[i2].capacity * park[i2].current_level);
        else
            return park[i1].name > park[i2].name;
    };

    print_array_vertical_by_idx(idx, park, 6, std::cout);

    std::cout << "\nSort array of structures with indexes, by name and current charge:\n";
    sort_array_by_idx(idx, park, 6, sortByNameAndChargeIdx);
    print_array_vertical_by_idx(idx, park, 6, std::cout);

    std::cout << "\nSort array of structures without indexes, , by name and current charge:\n";
    sort_array(park, 6, sortByNameAndCharge);
    print_array_vertical(park, 6, std::cout);
}