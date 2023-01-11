//#define _USE_MATH_DEFINES
//#include<cmath>
//#include<iostream>
//using namespace std;
//
//
//
//void fwFunction(double t1, double t2, double t3, double t4, double t5, double t6) {
//    t1 = t1 * (M_PI / 180);
//    t2 = t2 * (M_PI / 180);
//    t3 = t3 * (M_PI / 180);
//    t4 = t4 * (M_PI / 180);
//    t5 = t5 * (M_PI / 180);
//    t6 = t6 * (M_PI / 180);
//
//    double d[7] = { 645,    0,         0,       0,         -1220,      0,          -215 };
//    double a[7] = { 0,      330,       1150,    115,       0,          0,          0 };
//    double al[7] = { M_PI,   M_PI / 2,  0,       M_PI / 2,  -M_PI / 2,  M_PI / 2,   M_PI };
//    double th[7] = { 0,      0,         0,      -M_PI / 2,  0,          0,          M_PI };
//
//    double T_0[4][4] = {
//        {cos(th[0]),       -sin(th[0]) * cos(al[0]),        sin(th[0]) * sin(al[0]),          a[0] * cos(th[0]) },
//        {sin(th[0]),        cos(th[0]) * cos(al[0]),       -cos(th[0]) * sin(al[0]),          a[0] * sin(th[0]) },
//        {0,                 sin(al[0]),                     cos(al[0]),                       d[0]},
//        {0,                 0,                              0,                                1 }
//    };
//
//    double T_1[4][4] = {
//        {cos(t1 + th[1]),   -sin(t1 + th[1]) * cos(al[1]),    sin(t1 + th[1]) * sin(al[1]),    a[1] * cos(t1 + th[1]) },
//        {sin(t1 + th[1]),    cos(t1 + th[1]) * cos(al[1]),   -cos(t1 + th[1]) * sin(al[1]),    a[1] * sin(t1 + th[1]) },
//        {0,                  sin(al[1]),                      cos(al[1]),                      d[1]},
//        {0,                  0,                               0,                               1 }
//    };
//
//    double T_2[4][4] = {
//        {cos(t2 + th[2]),  -sin(t2 + th[2]) * cos(al[2]),    sin(t2 + th[2]) * sin(al[2]),    a[2] * cos(t2 + th[2]) },
//        {sin(t2 + th[2]),   cos(t2 + th[2]) * cos(al[2]),   -cos(t2 + th[2]) * sin(al[2]),    a[2] * sin(t2 + th[2]) },
//        {0,                 sin(al[2]),                      cos(al[2]),                      d[2]},
//        {0,                  0,                               0,                               1 }
//    };
//    //al[3]= M_PI/2, th[3]=-M_PI/2;
//    double T_3[4][4] = {
//        {cos(t3 + th[3]),  -sin(t3 + th[3]) * cos(al[3]),    sin(t3 + th[3]) * sin(al[3]),    a[3] * cos(t3 + th[3])},
//        {sin(t3 + th[3]),   cos(t3 + th[3]) * cos(al[3]),   -cos(t3 + th[3]) * sin(al[3]),    a[3] * sin(t3 + th[3]) },
//        {0,                 sin(al[3]),                      cos(al[3]),                      d[3]},
//        {0,                  0,                               0,                               1 }
//    };
//    //al[4]= -M_PI/2, th[4]=0;
//    double T_4[4][4] = {
//        {cos(t4 + th[4]),  -sin(t4 + th[4]) * cos(al[4]),    sin(t4 + th[4]) * sin(al[4]),    a[4] * cos(t4 + th[4])},
//        {sin(t4 + th[4]),   cos(t4 + th[4]) * cos(al[4]),   -cos(t4 + th[4]) * sin(al[4]),    a[4] * sin(t4 + th[4])},
//        {0,                 sin(al[4]),                      cos(al[4]),                      d[4]},
//        {0,                  0,                               0,                               1 }
//    };
//    //al[5]= M_PI/2, th[5]=0;
//    double T_5[4][4] = {
//        {cos(t5 + th[5]),  -sin(t5 + th[5]) * cos(al[5]),    sin(t5 + th[5]) * sin(al[5]),    a[5] * cos(t5 + th[5])},
//        {sin(t5 + th[5]),   cos(t5 + th[5]) * cos(al[5]),   -cos(t5 + th[5]) * sin(al[5]),    a[5] * sin(t5 + th[5]) },
//        {0,                 sin(al[5]),                      cos(al[5]),                      d[5]},
//        {0,                  0,                               0,                               1 }
//    };
//    //al[6]= M_PI, th[6]= M_PI;
//    double T_6[4][4] = {
//        {cos(t6 + th[6]),  -sin(t6 + th[6]) * cos(al[6]),    sin(t6 + th[6]) * sin(al[6]),    a[6] * cos(t6 + th[6])},
//        {sin(t6 + th[6]),   cos(t6 + th[6]) * cos(al[6]),   -cos(t6 + th[6]) * sin(al[6]),    a[6] * sin(t6 + th[6]) },
//        {0,                 sin(al[6]),                      cos(al[6]),                      d[6]},
//        {0,                  0,                               0,                               1 }
//    };
//
//    double T[4][4], T01[4][4], T2[4][4], T3[4][4], T4[4][4], T5[4][4], T6[4][4];
//
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 4; j++) {
//            T[i][j] = 0, T01[i][j] = 0, T2[i][j] = 0, T3[i][j] = 0, T4[i][j] = 0, T5[i][j] = 0, T6[i][j] = 0;
//        }
//    }
//
//
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 4; j++) {
//            for (int k = 0; k < 4; k++) {
//                T01[i][j] += T_0[i][k] * T_1[k][j];
//            }
//        }
//    }
//
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 4; j++) {
//            for (int k = 0; k < 4; k++) {
//                T2[i][j] += T01[i][k] * T_2[k][j];
//            }
//        }
//    }
//
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 4; j++) {
//            for (int k = 0; k < 4; k++) {
//                T3[i][j] += T2[i][k] * T_3[k][j];
//            }
//        }
//    }
//
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 4; j++) {
//            for (int k = 0; k < 4; k++) {
//                T4[i][j] += T3[i][k] * T_4[k][j];
//            }
//        }
//    }
//
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 4; j++) {
//            for (int k = 0; k < 4; k++) {
//                T5[i][j] += T4[i][k] * T_5[k][j];
//            }
//        }
//    }
//
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 4; j++) {
//            for (int k = 0; k < 4; k++) {
//                T6[i][j] += T5[i][k] * T_6[k][j];
//            }
//        }
//    }
//    cout << "-------T6------\n";
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 4; j++) {
//            cout << T6[i][j] << " ";
//        }
//        cout << "\n";
//    }
//}