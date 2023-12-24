//Emil Davlityarov
//e.davlityarov@innopolis.university
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#ifdef WIN32
#define GNUPLOT_NAME "C:\\gnuplot\\bin\\gnuplot -persist"
#else
#define GNUPLOT_NAME "gnuplot -persist"
#endif
using namespace std;
double calculateV(double t, double a1, double a2, double b1, double b2, double v0, double k0){
    if (t == 0){
        return v0 + a2/b2;
    }
    return v0 * cos(sqrt(a1 * a2) * t) - k0 * ((sqrt(a2) * b1)/(b2 * sqrt(a1)) ) * sin(sqrt(a1 * a2) * t) + a2/b2;
}
double calculateK(double t, double a1, double a2, double b1, double b2, double v0, double k0){
    if (t == 0){
        return k0 + a1/b1;
    }
    return v0 * ((sqrt(a1) * b2)/(b1 * sqrt(a2))) * sin (sqrt(a1 * a2) * t) + k0 * cos(sqrt(a1 * a2) * t) + a1/b1;
}
int main() {
#ifdef WIN64
    FILE* pipe1 = _popen(GNUPLOT_NAME, "w");
    FILE* pipe2 = _popen(GNUPLOT_NAME, "w");
#else
    FILE* pipe = popen(GNUPLOT_NAME, "w");
    FILE* pipe2 = popen(GNUPLOT_NAME, "w");
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    double v0, k0, T;
    int N;
    double alpha1, beta1, alpha2, beta2;
    cin >> v0 >> k0 >> alpha1 >> beta1 >> alpha2 >> beta2 >> T >> N;
    double delta = T / N;
    v0 = v0 - alpha2/beta2;
    k0 = k0 - alpha1/beta1;
    double t = 0;
    vector<double > v;
    vector<double > k;
    cout << "t:\n";
    fprintf(pipe1, "set xlabel 'Time'\n");
    fprintf(pipe1, "set ylabel 'Population'\n");
    fprintf(pipe1, "plot[0:150][0:150] '-' with lines title 'Prey', '-' with lines title 'Predator'\n");
    do{
        cout.precision(2);
        cout << fixed << t << " ";
        v.push_back(calculateV(t, alpha1, alpha2, beta1, beta2, v0, k0));
        k.push_back(calculateK(t, alpha1, alpha2, beta1, beta2, v0, k0));
        t += delta;
    } while (t <= T);
    t = 0;
    do{
        fprintf(pipe1, "%f %f\n",t, calculateV(t, alpha1, alpha2, beta1, beta2, v0, k0));
        t += delta;
    } while (t <= T);
    fprintf(pipe1, "e\n");
    t = 0;
    do{
        fprintf(pipe1, "%f %f\n",t, calculateK(t, alpha1, alpha2, beta1, beta2, v0, k0));
        t += delta;
    } while (t <= T);
    fprintf(pipe1, "e\n");
    fflush(pipe1);
    pclose(pipe1);
    fprintf(pipe2, "set xlabel 'Predator'\n");
    fprintf(pipe2, "set ylabel 'Prey'\n");
    fprintf(pipe2, "plot[0:150][0:150] '-' with lines title 'v(k)'\n");
    for (int i = 0; i < v.size(); i++) {
        fprintf(pipe2, "%f %f\n", k[i], v[i]);
    }
    fprintf(pipe2, "e\n");
    fflush(pipe2);
    pclose(pipe2);
    cout << endl << "v:\n";
    for (double i : v){
        cout.precision(2);
        cout << fixed << i << " ";
    }
    cout << endl << "k:\n";
    for (double i : k){
        cout.precision(2);
        cout << fixed << i << " ";
    }
    cout << endl;
    return 0;
}