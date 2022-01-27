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
    cout << "bias = " << bias << endl;
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
    cout << "bias = " << bias << endl;
    cout << "wzbudzenie dla neurona 1 = " << output << endl;

    if (output > 0)
        output = 1;
    else
        output = 0;

    cout << "wartosc po obliczeniu funkcji aktywacji dla neurona 2 = " << output << "\n\n";

    return output;
}

void final(
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

int oblicz(const vector<vector_t> &m,
           int x,
           int y, int neuronNumber)
{
    int output = 0;
    auto waga = m.at(neuronNumber - 1);
    auto bias = m.at(neuronNumber - 1).at(2);
    cout << "neuron " << neuronNumber << " - dana wejsciowa 1 = " << x << endl;
    cout << "neuron " << neuronNumber << " - dana wejsciowa 2 = " << y << endl;
    cout << "neuron " << neuronNumber << " - wagi = " << waga.at(0) << " " << waga.at(1) << endl;
    output = x * waga.at(0) + y * waga.at(1) + bias;
    cout << "bias = " << bias << endl;
    cout << "wzbudzenie dla neurona " << neuronNumber << " = " << output << "\n";

    return output;
}

int neuron(
    const vector<vector_t> &m,
    int x,
    int y, int neuronNumber)
{
    int output = 0;
    output = oblicz(m, x, y, neuronNumber);

    if (output > 0)
        output = 1;
    else
        output = 0;

    cout << "wartosc po obliczeniu funkcji aktywacji dla neurona " << neuronNumber << " = " << output << "\n\n";
    return output;
}

void net(
    int a, int b, int c, int d, int e, int f, int g, int h, int i)
{

    cout << a << "---   ---" << c << "---" << endl;
    cout << "   |   |     ]" << endl;
    cout << "   |---|     " << e << "----" << endl;
    cout << "   |   |     ]   |" << endl;
    cout << b << "---   ---" << d << "---   |" << endl;
    cout << "                 |---" << i << endl;
    cout << f << "-------------   |" << endl;
    cout << "             ]   |" << endl;
    cout << "             " << h << "----" << endl;
    cout << "             ]" << endl;
    cout << g << "-------------" << endl;
}

int main(int argc, char **argv)
{

    if (argc < 6)
    {
        cerr << "Podaj 4 argumenty do funkcji" << endl;
        return -1;
    }
    // wagi
    vector<vector_t> m = {
        {1, 1, -1},  // n1
        {-1, 1, 1},  // n2
        {1, -1, 1},  // final
        {-1, 1, -1}, // n4
        {-1, 1, 1},  // n5
        {1, 1, -1},  // n6
        {-1, 1, -1}, // n7
        {1, 1, -1},  // n8
        {-1, 1, 1},  // n9
    };
    // wejscia dla neuronow
    vector<vector_t> a = {
        {stof(argv[1]), stof(argv[2])},
        {stof(argv[3]), stof(argv[4])},
        {stof(argv[5]), stof(argv[6])},
    };

    cout << "[waga,waga,bias]" << endl;
    for (auto m_ : m)
        cout << m_;

    for (auto a_ : a)
        cout << "dane wejsciowe: " << a_;

    cout << "------------------\n";

    cout << "siec 1" << endl;
    net(1, 2, 4, 5, 6, 7, 8, 9, 3);
    final(
        m,
        neuron(
            m,
            neuron(m, neuron1(m, a), neuron2(m, a), 4), neuron(m, neuron1(m, a), neuron2(m, a), 5),
            6),
        neuron(
            m,
            neuron(m, a.at(2).at(0), a.at(2).at(1), 7),
            neuron(m, a.at(2).at(0), a.at(2).at(1), 8),
            9));

    cout << "siec 2" << endl;
    net(9, 2, 6, 7, 5, 1, 4, 8, 3);
    final(
        m,
        neuron(
            m,
            neuron(m, neuron(m, a.at(2).at(0), a.at(2).at(1), 9), neuron2(m, a), 6), neuron(m, neuron(m, a.at(2).at(0), a.at(2).at(1), 9), neuron2(m, a), 7),
            5),
        neuron(
            m,
            neuron1(m, a),
            neuron(m, a.at(2).at(0), a.at(2).at(1), 4),
            8));

    cout << "siec 3" << endl;
    net(4, 5, 6, 7, 9, 1, 2, 8, 3);
    final(
        m,
        neuron(
            m,
            neuron(m,
                   neuron(m, a.at(2).at(0), a.at(2).at(1), 4), neuron(m, a.at(2).at(0), a.at(2).at(1), 5),
                   6),
            neuron(m,
                   neuron(m, a.at(2).at(0), a.at(2).at(1), 4), neuron(m, a.at(2).at(0), a.at(2).at(1), 5),
                   7),
            9),
        neuron(
            m,
            neuron1(m, a),
            neuron2(m, a),
            8));
    return 0;
}
