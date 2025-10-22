#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "circuit.hpp"

Circuit::Circuit(const char* filename) {
    Component p;
    FILE *fPtr;
    
    /* Try to open the file */
    fPtr = fopen(filename, "r");
    if (!fPtr) { 
        fprintf(stderr, "Could not open file: %s\n", filename); 
        exit(EXIT_FAILURE); 
    }
    
    /* Read the netlist to find out how many components there are */
    while(fscanf(fPtr, "%s %u %u %lf", p.name, &p.n1, &p.n2, &p.value) == 4) {
        nC++;
    }
    
    /* Reserve space for components */
    comp.reserve(nC);
    
    /* Do another pass to read in the components */
    rewind(fPtr); //moves file pointer back to first line
    nC = 0;
    while(fscanf(fPtr, "%s %u %u %lf", p.name, &p.n1, &p.n2, &p.value) == 4) {
        switch(p.name[0]) {
            case 'R': 
                nR++; 
                p.type = ComponentType::RESISTOR; 
                break;
            case 'V': 
                nV++; 
                p.type = ComponentType::VOLTAGE; 
                break;
            case 'I': 
                nI++; 
                p.type = ComponentType::CURRENT; 
                break;
            default: 
                fprintf(stderr, "Unknown component on line %u in file %s.\n", nC + 1, filename); 
                exit(EXIT_FAILURE);
        }
        if (p.n1 > nN) nN = p.n1;
        if (p.n2 > nN) nN = p.n2;
        
        comp.push_back(p);
        nC++;
    }
    
    nN++; /* Node labelling is zero based so add one to get total number of nodes. */
    fclose(fPtr);
}

void Circuit::analyse() const {
    unsigned int n1, n2, i, cV;
    double value, g;
    Matrix A;
    Vector Z, X;
    
    /* Initialise matrices and vectors and zero elements */
    A = create_matrix(nN + nV, nN + nV);
    Z = create_vector(nN + nV);

    /* Build nodal analysis equations */
    for(i=0, cV=0; i<nC; i++) {
        n1 = comp[i].n1;
        n2 = comp[i].n2;
        value = comp[i].value;
        switch(comp[i].type) {
            case ComponentType::RESISTOR: 
                g = 1.0/value;
                A[n1][n2] -= g;
                A[n2][n1] -= g;
                A[n1][n1] += g;
                A[n2][n2] += g;    
                break;
            case ComponentType::VOLTAGE: 
                A[n1][cV + nN] = A[cV + nN][n1] = 1.0;                
                A[n2][cV + nN] = A[cV + nN][n2] = -1.0;
                Z[cV + nN] = -value;
                cV++;
                break;
            case ComponentType::CURRENT: 
                Z[n1] -= value;
                Z[n2] += value;
                break;
        }
    }
    
    /* Node 0 is ground and is treated differently */
    A[0][0] = 1.0; 
    Z[0] = 0.0;
    for(i=1; i<nN + nV; i++) 
        A[0][i] = A[i][0] = 0.0;

    /* Analyse and display results */
    X = solve_linear_system(A, Z);
    printf("----------------------------\n");
    printf(" Voltage sources: %u\n", nV);
    printf(" Current sources: %u\n", nI);
    printf("       Resistors: %u\n", nR);
    printf("           Nodes: %u\n", nN);
    printf("----------------------------\n");
    for(i=0; i<nN; i++)
        printf(" Node %3u = %10.6lf V\n", i, X[i]);
    printf("----------------------------\n");
    if (nV) {
        for(i=0, cV=0; i<nC; i++)
            if (comp[i].type == ComponentType::VOLTAGE)
                printf(" I(%s)    = %10.6lf A\n", comp[i].name, X[nN + cV++]);
        printf("----------------------------\n");
    }
}

void Circuit::print() const {
    printf("Circuit Information:\n");
    printf("----------------------------\n");
    printf(" Voltage sources: %u\n", nV);
    printf(" Current sources: %u\n", nI);
    printf("       Resistors: %u\n", nR);
    printf("      Components: %u\n", nC);
    printf("           Nodes: %u\n", nN);
    printf("----------------------------\n");
    printf("Components:\n");
    for(unsigned int i=0; i<nC; i++) {
        const char* type_str;
        switch(comp[i].type) {
            case ComponentType::RESISTOR: type_str = "Resistor"; break;
            case ComponentType::VOLTAGE: type_str = "Voltage"; break;
            case ComponentType::CURRENT: type_str = "Current"; break;
        }
        printf(" %s: %s, Nodes: %u-%u, Value: %.6lf\n", 
               type_str, comp[i].name, comp[i].n1, comp[i].n2, comp[i].value);
    }
    printf("----------------------------\n");
}

size_t Circuit::n_components() const { 
    return comp.size(); 
}

Vector solve_linear_system(Matrix A, Vector b) {
    /* Note: This function overwrites the contents of A and b. */
    int i, j, k;
    double mult, sum;
    Vector x = create_vector(A.size());

    /* reduce to upper triangular form */
    for (i=0; i<static_cast<int>(A.size())-1; i++)
        for (j=i+1; j<static_cast<int>(A.size()); j++) {   
            mult = -A[j][i]/A[i][i];
            for (k=i; k<static_cast<int>(A[i].size()); k++)
                A[j][k] += mult*A[i][k];
            b[j] += mult*b[i];
        }
    /* back substitute to find Vector x */
    for (i=static_cast<int>(A.size())-1; i>=0; i--) {
        for (j=i+1, sum = 0.0; j<static_cast<int>(A[i].size()); j++)
            sum += A[i][j] * x[j];
        x[i] = (b[i] - sum)/A[i][i];
    }
    return x;
}