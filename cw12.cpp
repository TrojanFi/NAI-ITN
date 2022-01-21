#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <random>
#include <vector>
using namespace std;
random_device r_device;
mt19937 rand_gen(r_device());

using matrix_t = vector<vector<double>>;
using vector_t = vector<double>;

ostream &operator<<(ostream &o, const matrix_t &m)
{
    for (auto row : m)
    {
        o << "| ";
        for (auto e : row)
        {
            o << e << " ";
        }
        o << "|\n";
    }
    return o;
}
ostream &operator<<(ostream &o, const vector_t &row)
{
    o << "[ ";
    for (auto e : row)
    {
        o << e << " ";
    }
    o << "]\n";
    return o;
}

int neuron1(
    const vector<vector_t> &m,
    const vector<vector_t> &a)
{
    int output = 0;
    auto wejscie = a.at(0);
    auto waga = m.at(0);
    auto bias = m.at(0).at(2);
    cout << "neuron 1 - dana wejsciowa 1 = " << wejscie.at(0) << endl;
    cout << "neuron 1 - dana wejsciowa 2 = " << wejscie.at(1) << endl;
    cout << "neuron 1 - wagi = " << waga.at(0) << " " << waga.at(1) << endl;
    output = wejscie.at(0) * waga.at(0) + wejscie.at(1) * waga.at(1) + bias;
    cout << "wzbudzenie dla neurona 1 = " << output << endl;

    if (output > 0)
        output = 1;
    else
        output = 0;

    cout << "wartosc po obliczeniu funkcji aktywacji dla neurona 1 = " << output << "\n\n";

    return output;
}

int neuron2(
    const vector<vector_t> &m,
    const vector<vector_t> &a)
{
    int output = 0;
    auto wejscie = a.at(1);
    auto waga = m.at(1);
    auto bias = m.at(1).at(2);
    cout << "neuron 2 - dana wejsciowa 1 = " << wejscie.at(0) << endl;
    cout << "neuron 2 - dana wejsciowa 2 = " << wejscie.at(1) << endl;
    cout << "neuron 2 - wagi = " << waga.at(0) << " " << waga.at(1) << endl;
    output = wejscie.at(0) * waga.at(0) + wejscie.at(1) * waga.at(1) + bias;
    cout << "wzbudzenie dla neurona 1 = " << output << endl;

    if (output > 0)
        output = 1;
    else
        output = 0;

    cout << "wartosc po obliczeniu funkcji aktywacji dla neurona 2 = " << output << "\n\n";

    return output;
}

void neuron3(
    const vector<vector_t> &m,
    int x,
    int y)
{
    int output = 0;
    auto waga = m.at(2);
    auto bias = m.at(2).at(2);
    cout << "neuron 3 - dana wejsciowa 1 = " << x << endl;
    cout << "neuron 3 - dana wejsciowa 2 = " << y << endl;
    cout << "neuron 3 - wagi = " << waga.at(0) << " " << waga.at(1) << endl;
    output = x * waga.at(0) + y * waga.at(1) + bias;
    cout << "wzbudzenie dla neurona 3 = " << output << "\n\n";

    if (output > 0)
        output = 1;
    else
        output = -1;

    cout << "wynik = " << output << endl;
}

int main(int argc, char **argv)
{

    if (argc < 4)
    {
        cerr << "Podaj 2 argumenty do funkcji xor" << endl;
        return -1;
    }
    // wagi
    vector<vector_t> m = {
        {1, 1, -1},
        {-1, 1, 1},
        {1, -1, 1}};
    // wejscia dla neuronow
    vector<vector_t> a = {
        {stof(argv[1]), stof(argv[2])},
        {stof(argv[3]), stof(argv[4])}};

    cout << "[waga,waga,bias]" << endl;
    for (auto m_ : m)
        cout << m_;

    for (auto a_ : a)
        cout << "dane wejsciowe: " << a_;

    cout << "------------------\n";
    auto x = neuron1(m, a);
    auto y = neuron2(m, a);
    cout << "neuron 1 i 2 po funkcjach aktywacji -> [" << x << " " << y << "]\n\n"; 
    neuron3(m, x, y);
    return 0;
}