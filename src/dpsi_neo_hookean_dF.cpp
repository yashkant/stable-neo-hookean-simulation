#include <dpsi_neo_hookean_dF.h>

//Input:
//  F - the dense 3x3 deformation gradient
//  C,D - material parameters for the Neo-Hookean model
//Output:
//  psi - the 9x1 gradient of the potential energy wrt to the deformation gradient

void dpsi_neo_hookean_dF(Eigen::Vector9d &dw, Eigen::Ref<const Eigen::Matrix3d> F, double C, double D) {

    double mu = C * 2;
    double lambda = D * 2;
    dw.setZero(); double F1_1, F1_2, F1_3, F2_1, F2_2, F2_3,F3_1, F3_2, F3_3;
    F1_1 = F(0,0);
    F1_2 = F(0,1);
    F1_3 = F(0,2);
    F2_1 = F(1,0);
    F2_2 = F(1,1);
    F2_3 = F(1,2);
    F3_1 = F(2,0);
    F3_2 = F(2,1);
    F3_3 = F(2,2);

    // Stable neo-hookean
   dw[0] = F1_1*mu-lambda*(F2_2*F3_3-F2_3*F3_2)*((mu*(3.0/4.0))/lambda-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0)-(F1_1*mu)/(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3+1.0);
   dw[1] = F1_2*mu+lambda*(F2_1*F3_3-F2_3*F3_1)*((mu*(3.0/4.0))/lambda-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0)-(F1_2*mu)/(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3+1.0);
   dw[2] = F1_3*mu-lambda*(F2_1*F3_2-F2_2*F3_1)*((mu*(3.0/4.0))/lambda-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0)-(F1_3*mu)/(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3+1.0);
   dw[3] = F2_1*mu+lambda*(F1_2*F3_3-F1_3*F3_2)*((mu*(3.0/4.0))/lambda-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0)-(F2_1*mu)/(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3+1.0);
   dw[4] = F2_2*mu-lambda*(F1_1*F3_3-F1_3*F3_1)*((mu*(3.0/4.0))/lambda-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0)-(F2_2*mu)/(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3+1.0);
   dw[5] = F2_3*mu+lambda*(F1_1*F3_2-F1_2*F3_1)*((mu*(3.0/4.0))/lambda-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0)-(F2_3*mu)/(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3+1.0);
   dw[6] = F3_1*mu-lambda*(F1_2*F2_3-F1_3*F2_2)*((mu*(3.0/4.0))/lambda-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0)-(F3_1*mu)/(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3+1.0);
   dw[7] = F3_2*mu+lambda*(F1_1*F2_3-F1_3*F2_1)*((mu*(3.0/4.0))/lambda-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0)-(F3_2*mu)/(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3+1.0);
   dw[8] = F3_3*mu-lambda*(F1_1*F2_2-F1_2*F2_1)*((mu*(3.0/4.0))/lambda-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0)-(F3_3*mu)/(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3+1.0);


}