#include <vector>
#include <cmath>

class Graph {//Base sin function plotter from C2
    protected: // Allow child classes to access its attributes
        int width;
        int space;
        float y;    
        long unsigned x;
        const double PI = 3.14159;
        const int FREQUENCY = 5;
        const int SPACING = 10;

    public:
        Graph();
        int plotPoint(float y);
        virtual int plotGraph();
};

class Fourier: public Graph {
    private:
        std::vector<float> a_coeffs; //cos coefficients
        std::vector<float> b_coeffs; //sin coefficients
        std::vector<float> y_points; //array of points to be plotted
        float a0 = 0.0f;
        int num_harmonics;
        float y_total; //point to be plotted
        float angle;
        float y_min = INFINITY; //remove garbage values
        float y_max = -INFINITY;
    
    public:
        void getUserInput();
        int plotGraph() override;


};