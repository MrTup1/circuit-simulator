#include <cmath>
#include <iostream>

class Graph {
    private:
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

        int plotGraph() {
            for (x; x<1000; x++) {
                y = (sin(FREQUENCY * x * PI / 180))/2 + 0.5; //Divide by 2 to squish down to 0.5, then + 0.5 to move it to 0-1
                space = plotPoint(y);
                if (x % SPACING) {
                    printf("x = %.10lu y = %.3f|    %*c*\n", x, y, space, "");
                } else {
                    printf("x = %.10lu y = %.3f|--- %*c*\n", x, y, space, ""); //Indicator for every 10 lines
                }
            }
            return 1;
        }
        
};



int main() {
    Graph graph;
    graph.plotGraph();
    return 0;
}
