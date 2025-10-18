#include <cmath>
#include <iostream>
#include <vector>
#include <iterator>

class Graph {
    protected: // Allow child classes to access its attributes
        int width;
        int space;
        float y;    
        long unsigned x;
        const double PI = 3.14159;
        const int FREQUENCY = 5;
        const int SPACING = 10;

    public:
        Graph() { //Constructor 
            width = 0;
            space = 0;
            x = 0;
        }
        
        int plotPoint(float y) { //Plots a single point based on y position given
            width = 60;
            space = 0;
            for (int i = 0; i < y *width; i++) {
                space += 1;
            }
            return space;
        }

        virtual int plotGraph() {
            for (x = 0; x<1000; x++) {
                y = (sin(FREQUENCY * x * PI / 180))/2 + 0.5; //Divide by 2 to squish down to 0.5, then + 0.5 to move it to 0-1
                space = plotPoint(y);
                if (x % SPACING == 0) {
                    printf("x = %.10lu y = %.3f|    %*c*\n", x, y, space, "");
                } else {
                    printf("x = %.10lu y = %.3f|--- %*c*\n", x, y, space, ""); //Indicator for every 10 lines
                }
            }
            return 1;
        }
        
};

class Fourier: public Graph {
    private:
        std::vector<float> a_coeffs;
        std::vector<float> b_coeffs;
        std::vector<float> y_points;
        float a0 = 0.0f;
        int num_harmonics;
        float y_total;
        float angle;
        float y_min = INFINITY;
        float y_max = -INFINITY;
    
    public:
        void getUserInput() {
            std::cout << "Enter the DC offset (a0): ";
            std::cin >> a0;

            std::cout << "How many harmonics would you like to enter (up to 6)? ";
            std::cin >> num_harmonics;

            for (int i = 0; i < num_harmonics; ++i) {
                float a, b;
                std::cout << "Enter coeffs for harmonic " << i + 1 << " (an, bn): ";
                std::cin >> a >> b;
                a_coeffs.push_back(a);
                b_coeffs.push_back(b);
            }
            
        }

        int plotGraph() override {
            const float L = 100.0f; 

            for (x = 0; x< 1000; ++x) {
                y_total = 0; //reset y variable
                y_total += a0 / 2 ;
                for (int n = 1; n <= num_harmonics; ++n) { //a_coeffs summation and b
                    float angle = (n * PI * x) / L;
                    y_total += a_coeffs[n-1] * std::cos(angle);
                    y_total += b_coeffs[n-1] * std::sin(angle);
                }
                y_points.push_back(y_total);
                if(y_total < y_min) y_min = y_total;
                if(y_total > y_max) y_max = y_total;

            }

            for (x = 0; x < 1000; ++x) {
                float normalised_y = (y_points[x] - y_min) / (y_max - y_min); //normalise the y values

                space = plotPoint(normalised_y);
                if (x % SPACING == 0) {
                    printf("x = %.10lu y = %.3f|    %*c*\n", x, y_points[x], space, "");
                } else {
                    printf("x = %.10lu y = %.3f|--- %*c*\n", x, y_points[x], space, ""); //Indicator for every 10 lines
                }
            }

            return 1;
        }

};

int main() {
    Fourier graph;
    graph.getUserInput();
    graph.plotGraph();
    return 0;
}
