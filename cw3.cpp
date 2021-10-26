#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <random>
#include <vector>

using namespace std;

random_device rd;  //Will be used to obtain a seed for the random number engine
mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

ostream &operator<<(ostream &o, vector<double> v)
{
    for (auto e : v)
    {
        o << std::fixed << std::setprecision(5) << "\t" << e;
    }
    return o;
}

vector<double> hill_climbing(function<double(vector<double>)> f, function<bool(vector<double>)> f_domain, vector<double> p0, int iterations)
{
    auto p = p0;
    uniform_int_distribution<> distrib(0, p.size() - 1);
    uniform_real_distribution<> distrib_r(-0.1, 0.1);

    if (!f_domain(p))
        throw std::invalid_argument("The p0 point must be in domain!");
    for (int i = 0; i < iterations; i++)
    {
        auto p2 = p;

        p2[distrib(gen)] += distrib_r(gen);
        if (f_domain(p2))
        {
            double y2 = f(p2);
            if (y2 < f(p))
            {
                p = p2;
                cout << p << " " << f(p) << endl;
            }
        }
    }
    return p;
}
vector<double> operator+(vector<double> a, vector<double> b)
{
    for (int i = 0; i < a.size(); i++)
    {
        a[i] += b[i];
    }
    return a;
}

vector<double> simulated_annealing(
    function<double(vector<double>)> f,
    function<bool(vector<double>)> f_domain,
    vector<double> p0,
    int iterations,
    function<vector<double>(vector<double>)> N,
    function<double(int)> T)
{
    auto s_current = p0;
    auto s_global_best = p0;

    uniform_real_distribution<> u_k(0.0, 1.0);

    if (!f_domain(s_current))
        throw std::invalid_argument("The p0 point must be in domain");

    for (int k = 0; k < iterations; k++)
    {
        auto s_next = N(s_current);
        if (f(s_next) < f(s_current))
        {
            s_current = s_next;
        }
        else
        {
            double u = u_k(gen);
            if (u < exp(-abs(f(s_next) - f(s_current)) / T(k)))
            {
                s_current = s_next;
            }
            else
            {
                // nothing...
            }
        }
        if (f(s_current) < f(s_global_best))
        {
            s_global_best = s_current;
        }
        cout << s_current << " " << f(s_current) << endl;
    }
    return s_global_best;
}

int main(int argc, char *argv[])
{
    string choiceAproach = argv[1];
    string choiceFunction = argv[2];
    string numberOfIterationsString = argv[3];
    string point0_0 = argv[4];
    string point0_1 = argv[5];
    int numberOfIterations = atoi(numberOfIterationsString.c_str());
    int startPoint0 = atoi(point0_0.c_str());
    int startPoint1 = atoi(point0_1.c_str());

    if (numberOfIterations > 0)
    {
        auto boothFunction = [](vector<double> v)
        {
            double x = v.at(0), y = v.at(1);
            return (x + 2 * y - 7) * (x + 2 * y - 7) + (2 * x + y - 5) * (2 * x + y - 5);
        };

        auto boothFunction_domain = [](vector<double> v)
        {
            return (abs(v[0]) <= 10) && (abs(v[1]) <= 10);
        };

        auto himmelFunction = [](vector<double> v)
        {
            double x = v.at(0), y = v.at(1);
            return (x * x + y - 11) * (x * x + y - 11) + (x + y * y - 7) * (x + y * y - 7);
        };

        auto himmelFunction_domain = [](vector<double> v)
        {
            return (abs(v[0]) <= 5) && (abs(v[1]) <= 5);
        };

        uniform_real_distribution<> distrib_rb(startPoint0, startPoint1);
        vector<double> booth_p0 = {
            distrib_rb(gen),
            distrib_rb(gen),
        };

        uniform_real_distribution<> distrib_rh(startPoint0, startPoint1);
        vector<double> himmel_p0 = {
            distrib_rh(gen),
            distrib_rh(gen),
        };
        if (choiceAproach.compare("hill") == 0)
        {
            if (choiceFunction.compare("booth") == 0)
            {
                auto result = hill_climbing(boothFunction, boothFunction_domain, booth_p0, numberOfIterations);
                cout << result << " " << boothFunction(result) << endl;
            }
            else if (choiceFunction.compare("himmel") == 0)
            {
                auto result = hill_climbing(himmelFunction, himmelFunction_domain, himmel_p0, numberOfIterations);
                cout << result << " " << himmelFunction(result) << endl;
            }
            else
            {
                cout << "What happend?" << endl;
            }
        }
        else if (choiceAproach.compare("ann") == 0)
        {
            if (choiceFunction.compare("booth") == 0)
            {
                auto result = simulated_annealing(
                    boothFunction, boothFunction_domain, booth_p0, numberOfIterations, [](auto p)
                    {
                        normal_distribution<double> n(0.0, 0.3);
                        for (auto &e : p)
                        {
                            e = e + n(gen);
                        }
                        return p;
                    },
                    [](int k)
                    { return 1000.0 / k; });

                cout << result << " " << boothFunction(result) << endl;
            }
            else if (choiceFunction.compare("himmel") == 0)
            {
                auto result = simulated_annealing(
                    himmelFunction, himmelFunction_domain, himmel_p0, numberOfIterations, [](auto p)
                    {
                        normal_distribution<double> n(0.0, 0.3);
                        for (auto &e : p)
                        {
                            e = e + n(gen);
                        }
                        return p;
                    },
                    [](int k)
                    { return 1000.0 / k; });

                cout << result << " " << boothFunction(result) << endl;
            }
            else
            {
                cout << "What happend?" << endl;
            }
        }
        else
        {
            if (choiceFunction.compare("booth") == 0)
            {
                auto result = hill_climbing(boothFunction, boothFunction_domain, booth_p0, numberOfIterations);
                cout << result << " " << boothFunction(result) << endl;
            }
            else if (choiceFunction.compare("himmel") == 0)
            {

                auto result = hill_climbing(himmelFunction, himmelFunction_domain, himmel_p0, numberOfIterations);
                cout << result << " " << himmelFunction(result) << endl;
            }
            else
            {
                cout << "What happend?" << endl;
            }
            if (choiceFunction.compare("booth") == 0)
            {
                auto result = simulated_annealing(
                    boothFunction, boothFunction_domain, booth_p0, numberOfIterations, [](auto p)
                    {
                        normal_distribution<double> n(0.0, 0.3);
                        for (auto &e : p)
                        {
                            e = e + n(gen);
                        }
                        return p;
                    },
                    [](int k)
                    { return 1000.0 / k; });

                cout << result << " " << boothFunction(result) << endl;
            }
            else if (choiceFunction.compare("himmel") == 0)
            {
                auto result = simulated_annealing(
                    himmelFunction, himmelFunction_domain, himmel_p0, numberOfIterations, [](auto p)
                    {
                        normal_distribution<double> n(0.0, 0.3);
                        for (auto &e : p)
                        {
                            e = e + n(gen);
                        }
                        return p;
                    },
                    [](int k)
                    { return 1000.0 / k; });

                cout << result << " " << boothFunction(result) << endl;
            }
            else
            {
                cout << "What happend?" << endl;
            }
        }
    }
    else
    {
        cout << "Incorrect number of iterations" << endl;
    }

    return 0;
}