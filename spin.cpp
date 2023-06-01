#include <iostream>
#include <math.h>
#include <string.h>
using namespace std; 

int main() { 
    // Predefine viewport
    int viewsize; 
    // Defining iterator for period of 2pi, with angular velocity = 0.01 (per frames) 
    float i = 0, spacing = 0.02; 
    // Defining what should be printed for each point.
    // This is defined as the dot product between the surface normal and the light direction. 
    char illum[] = ".,-~:;=!*%#$@";
    // Define the light direction as (0,1,-1)
    float R1 = 4, R2 = 8, K1=30, K2 = 40; 
    // viewsize = (K1*(R1+R2)/(K2+0))*(8/3);
    // cout << viewsize; 
    // K1 = viewsize*K2*3/(8*(R1+R2));
    viewsize = 30; 
    // Initialize the board
    float A = 0, B = 0; 
    int q = 2; 
    while(1){
        string board[viewsize][viewsize];
        for (int j = 0; j < viewsize; j++)
            for (int k = 0; k < viewsize; k++)
                board[j][k] = " ";
        // Pre-computed terms: for every rotation per frames
        // Constructing the donut shape, an1 for cross-sectional circle, an2 for rotating circle in 3D
        float cA = cos(A);
        float sA = sin(A);
        float cB = cos(B);
        float sB = sin(B);
        float ztemp[viewsize][viewsize];
        for (int j = 0; j < viewsize; j++)
            for (int k = 0; k < viewsize; k++)
                ztemp[j][k] = 0;
        // Rotating donut shape in the 3D space, in 2 different plane. 
        // an2 = the smaller circle from the cross-sectional area.
        for (float an1 = 0; an1 < 2*M_PI; an1+= spacing){
            for (float an2 = 0; an2< 2*M_PI; an2+= spacing){
                float can1 = cos(an1), san1 = sin(an1);
                float can2 = cos(an2), san2 = sin(an2);    
                // compute 3D x,y,z:
                float x3d = (R2+R1*can1)*(cB*can2+sA*sB*san2)-R1*cA*sB*san1;
                float y3d = (R2+R1*can1)*(sB*can2-sA*cB*san2)+R1*cA*cB*san1;
                float z3d = (cA)*(R2+R1*can1)*san2+R1*sA*san1; 
                // cout << "z3d " << z3d << endl; 
                // determine final location of the x,y in 2D plane
                int final_x = (K1*x3d)/(K2+z3d);
                int final_y = (K1*y3d)/(K2+z3d);
                // move to the middle of the viewport. 
                final_x += viewsize/2;
                final_y += viewsize/2;
                // cout << final_x << endl << final_y << endl;
                // Compute the lightness;
                float L = can2*can1*sB-cA*can1*san2-sA*san1+cB*(cA*san1-can1*sA*san2);
                // cout << final_x << endl << final_y << endl; 
                // board[final_x][final_y] = illum[(round((L+1)*5))];
                // cout << L << endl ;
                //L ranges from -sqrt(2) to +sqrt(2). 
                // ignore the negative values of L, as it is not pointing towards the direction. 
                int tmp = static_cast<int>(round(L*L*6)); 
                // cout << tmp << endl; 
                // cout << static_cast<int>(round((L+1)*5)) << endl; 
                board[final_x][final_y] = illum[tmp];
                if (L>0){
                // cout << (1/(z3d+K2)>0) << endl ; 
                    if ((1/(z3d+K2)) > ztemp[final_x][final_y]){
                        board[final_x][final_y] = illum[tmp];
                        ztemp[final_x][final_y] = 1/(z3d+K2);
                        // cout << illum[10]; 
                    }
                }
            }
        }
        
        // Projecting the 3D space back to the viewport in 2D; 
        // Print board
        for (int y = 0; y < viewsize; y++){
            for (int x = 0; x < viewsize; x++){
                cout << board[x][y]; 
            }
            cout << endl;
        }

        A += spacing; 
        B += spacing;
    }

    return 0; 
}