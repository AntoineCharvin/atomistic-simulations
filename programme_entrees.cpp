#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

void creation_fichier(int N, const vector<float>& X, const vector<float>& Y, const vector<float>& Z, const vector<float>& V_X, const vector<float>& V_Y, const vector<float>& V_Z)
{
    ofstream fichier("parametres.txt");

    fichier << std::setiosflags(std::ios::scientific) << std::setprecision(2);

    for(int i = 0; i < N; i++)
    {
        fichier << X[i] <<" ";
        fichier << Y[i] <<" ";
        fichier << Z[i] <<" ";
        fichier << V_X[i] <<" ";
        fichier << V_Y[i] <<" ";
        fichier << V_Z[i] <<" \n";
    }
}

int main()
{
    int N;
    int type_distrib;

    cout << "Veuillez entrer le nombre de particules : ";
    cin >> N;

    vector<float> X(N, 0);
    vector<float> Y(N, 0);
    vector<float> Z(N, 0);
    vector<float> V_X(N, 0);
    vector<float> V_Y(N, 0);
    vector<float> V_Z(N, 0);

    int rows, cols, depth;

    cout << "Entrez le nombre de lignes du quadrillage : ";
    cin >> rows;

    cout << "Entrez le nombre de colonnes du quadrillage : ";
    cin >> cols;

    cout << "Entrez le nombre de profondeur du quadrillage : ";
    cin >> depth;

    float spacing_x = pow(2., 1. / 6.);
    float spacing_y = pow(2., 1. / 6.);
    float spacing_z = pow(2., 1. / 6.);

    float grid_width = (cols - 1) * spacing_x;
    float grid_height = (rows - 1) * spacing_y;
    float grid_depth = (depth - 1) * spacing_z;

    int particle_count = 0;

    for (int k = 0; k < depth; k++) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                X[particle_count] = (j * spacing_x) - (grid_width / 2.0);
                Y[particle_count] = (i * spacing_y) - (grid_height / 2.0);
                Z[particle_count] = (k * spacing_z) - (grid_depth / 2.0);
                particle_count++;
            }
        }
    }

    // Génération des vitesses aléatoires pour toutes les particules
    float moyenne = 0;
    float ecart_type = 1;

    cout << "\nDistribution aléatoire de Maxwell-Boltzmann de la vitesse : \n-----------------------------------------------------------\n";
    cout << "Entrez la moyenne : ";
    cin >> moyenne;
    cout << "Entrez l'ecart-type : ";
    cin >> ecart_type;

    // Initialise le générateur de nombres aléatoires avec une graine (dépend du temps actuel)
    std::mt19937 generator(time(0));

    // Crée une distribution gaussienne pour les vitesses V_X, V_Y et V_Z
    std::normal_distribution<float> distribution(moyenne, ecart_type);

    // Remplit V_X[], V_Y[] et V_Z[] avec des valeurs aléatoires suivant une distribution de Maxwell-Boltzmann
    for (int i = 0; i < N; i++)
    {
        V_X[i] = distribution(generator);
        V_Y[i] = distribution(generator);
        V_Z[i] = distribution(generator);
    }

    creation_fichier(N, X, Y, Z, V_X, V_Y, V_Z);

    return 0;
}
