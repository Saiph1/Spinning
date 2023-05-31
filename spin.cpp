#include <iostream>
#include <math.h>
#include <string.h>
using namespace std; 

int main() { 
    // Predefine viewport
    const int viewheight = 20, viewwidth = 50; 
    // Defining iterator for period of 2pi, with angular velocity = 0.01 (per frames) 
    float i = 0, spacing = 0.01; 
    // Defining what should be printed for each point.
    // This is defined as the dot product between the surface normal and the light direction. 
    char illum[] = ".,-~:=!*#$@";
    // Defining container for x,y,z in 3D space. 
    float x3d = 0, y3d=0, z3d=0; 
    // Define the light direction as (0,1,-1)
    const float R1 = 2, R2 = 8, K1 = 100, K2 = 50; 

    // Initialize the board
    string board[viewwidth][viewheight];
    for (int j = 0; j < viewwidth; j++)
        for (int k = 0; k < viewheight; k++)
            board[j][k] = " ";

    while(1){
        // Pre-computed terms: for every rotation per frames
        // Constructing the donut shape, an1 for cross-sectional circle, an2 for rotating circle in 3D
        float A = 0, B = 0; 
        float cA = cos(A);
        float sA = sin(A);
        float cB = cos(B);
        float sB = sin(B);

        // Rotating donut shape in the 3D space, in 2 different plane. 
        // an2 = the smaller circle from the cross-sectional area.
        for (float an1 = 0; an1 < 2*M_PI; an1+= spacing){
            for (float an2 = 0; an2< 2*M_PI; an2+= spacing){
                float can1 = cos(an1), san1 = sin(an1);
                float can2 = cos(an2), san2 = sin(an2);    
                // compute 3D x,y,z:
                float x3d = (R2+R1*can2)*(cB*can1+sA*sB*san1)-R1*cA*sB*san2;
                float y3d = (R2+R1*can2)*(sB*can1-sA*cB*san1)+R1*cA*cB*san2;
                float z3d = (cA)*(R2+R1*can2)*san1+R1*sA*san2; 

                // determine final location of the x,y in 2D plane
                int final_x = (K1*x3d)/(K2+z3d);
                int final_y = (K1*y3d)/(K2+z3d);
                // move to the middle of the viewport. 
                final_x += viewwidth/2;
                final_y += viewheight/2;
                // cout << final_x << endl << final_y << endl;
                // Compute the lightness;
                float L = can1*can2*sB-cA*can2*san1-sA*san2+cB*(cA*san2-can2*sA*san1);
                // cout << final_x << endl << final_y << endl; 
                // board[final_x][final_y] = illum[(round((L+1)*5))];
                // cout << L << endl ;
                int tmp = static_cast<int>(round((L+1)*5));
                // cout << static_cast<int>(round((L+1)*5)) << endl; 
                if (tmp< 0)
                    board[final_x][final_y] = illum[0];
                else if (tmp > 10)
                    board[final_x][final_y] = illum[10];
                else 
                    board[final_x][final_y] = illum[tmp];
                // cout << illum[10]; 
            }
        }
        

        // Projecting the 3D space back to the viewport in 2D; 

        // Print board
        for (int y = 0; y < viewheight; y++){
            for (int x = 0; x < viewwidth; x++){
                cout << board[x][y]; 
            }
            cout << endl;
        }
        A += spacing; 
        B += spacing;
    }

    return 0; 
}
// int main() {
//     float A = 0, B = 0;
//     float i, j;
//     int k;
//     float z[1760];
//     char b[1760];
//     printf("\033[?25l");
//     printf("\x1b[2J");
//     for(;;) {
//         memset(b,32,1760);
//         memset(z,0,7040);
//         for(j=0; j < 6.28; j += 0.07) {
//             for(i=0; i < 6.28; i += 0.02) {
//                 float c = sin(i);
//                 float d = cos(j);
//                 float e = sin(A);
//                 float f = sin(j);
//                 float g = cos(A);
//                 float h = d + 2;
//                 float D = 1 / (c * h * e + f * g + 5);
//                 float l = cos(i);
//                 float m = cos(B);
//                 float n = sin(B);
//                 float t = c * h * g - f * e;
//                 int x = 40 + 30 * D * (l * h * m - t * n);
//                 int y= 12 + 15 * D * (l * h * n + t * m);
//                 int o = x + 80 * y;
//                 int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
//                 if(22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
//                     z[o] = D;
//                     b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
//                 }
//             }
//         }
//         printf("\033[?25l");
//         printf("\x1b[H");
//         for(k = 0; k < 1761; k++) {
//             putchar(k % 80 ? b[k] : 10);
//             A += 0.00004;
//             B += 0.00002;
//         }
//         //usleep(30000);
//     }
//     return 0;
// }