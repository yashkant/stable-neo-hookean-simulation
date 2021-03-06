#include <dpsi_neo_hookean_dF.h>

//Input:
//  F - the dense 3x3 deformation gradient
//  C,D - material parameters for the Neo-Hookean model
//Output:
//  psi - the 9x1 gradient of the potential energy wrt to the deformation gradient

void dpsi_neo_hookean_dF(Eigen::Vector9d &dw, Eigen::Ref<const Eigen::Matrix3d> F, double C, double D, const std::string& energy_type) {

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

    if (energy_type == "smith_14"){
        // Stable Neo-hookean (Smith and Kim, 2018, Equation 14, https://dl.acm.org/doi/10.1145/3180491)
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
    else if (energy_type == "smith_13"){
        // Stable Neo-hookean (Smith and Kim, 2018, Equation 13, https://dl.acm.org/doi/10.1145/3180491)
        // Without meta-stability
        dw[0] =  -mu*(F2_2*F3_3-F2_3*F3_2)+F1_1*mu-lambda*(F2_2*F3_3-F2_3*F3_2)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0);
        dw[1] =  mu*(F2_1*F3_3-F2_3*F3_1)+F1_2*mu+lambda*(F2_1*F3_3-F2_3*F3_1)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0);
        dw[2] =  -mu*(F2_1*F3_2-F2_2*F3_1)+F1_3*mu-lambda*(F2_1*F3_2-F2_2*F3_1)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0);
        dw[3] =  mu*(F1_2*F3_3-F1_3*F3_2)+F2_1*mu+lambda*(F1_2*F3_3-F1_3*F3_2)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0);
        dw[4] =  -mu*(F1_1*F3_3-F1_3*F3_1)+F2_2*mu-lambda*(F1_1*F3_3-F1_3*F3_1)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0);
        dw[5] =  mu*(F1_1*F3_2-F1_2*F3_1)+F2_3*mu+lambda*(F1_1*F3_2-F1_2*F3_1)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0);
        dw[6] =  -mu*(F1_2*F2_3-F1_3*F2_2)+F3_1*mu-lambda*(F1_2*F2_3-F1_3*F2_2)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0);
        dw[7] =  mu*(F1_1*F2_3-F1_3*F2_1)+F3_2*mu+lambda*(F1_1*F2_3-F1_3*F2_1)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0);
        dw[8] =  -mu*(F1_1*F2_2-F1_2*F2_1)+F3_3*mu-lambda*(F1_1*F2_2-F1_2*F2_1)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0);

    }
    else if (energy_type == "bower"){
        // Neo-hookean strain energy (Bower, 2009)
        dw[0] =  (mu*(F1_1*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,2.0/3.0)*2.0-(F2_2*F3_3-F2_3*F3_2)*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,5.0/3.0)*(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3)*(2.0/3.0)))/2.0-lambda*(F2_2*F3_3-F2_3*F3_2)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0);
        dw[1] =  (mu*(F1_2*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,2.0/3.0)*2.0+(F2_1*F3_3-F2_3*F3_1)*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,5.0/3.0)*(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3)*(2.0/3.0)))/2.0+lambda*(F2_1*F3_3-F2_3*F3_1)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0);
        dw[2] =  (mu*(F1_3*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,2.0/3.0)*2.0-(F2_1*F3_2-F2_2*F3_1)*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,5.0/3.0)*(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3)*(2.0/3.0)))/2.0-lambda*(F2_1*F3_2-F2_2*F3_1)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0);
        dw[3] =  (mu*(F2_1*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,2.0/3.0)*2.0+(F1_2*F3_3-F1_3*F3_2)*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,5.0/3.0)*(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3)*(2.0/3.0)))/2.0+lambda*(F1_2*F3_3-F1_3*F3_2)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0);
        dw[4] =  (mu*(F2_2*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,2.0/3.0)*2.0-(F1_1*F3_3-F1_3*F3_1)*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,5.0/3.0)*(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3)*(2.0/3.0)))/2.0-lambda*(F1_1*F3_3-F1_3*F3_1)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0);
        dw[5] =  (mu*(F2_3*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,2.0/3.0)*2.0+(F1_1*F3_2-F1_2*F3_1)*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,5.0/3.0)*(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3)*(2.0/3.0)))/2.0+lambda*(F1_1*F3_2-F1_2*F3_1)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0);
        dw[6] =  (mu*(F3_1*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,2.0/3.0)*2.0-(F1_2*F2_3-F1_3*F2_2)*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,5.0/3.0)*(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3)*(2.0/3.0)))/2.0-lambda*(F1_2*F2_3-F1_3*F2_2)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0);
        dw[7] =  (mu*(F3_2*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,2.0/3.0)*2.0+(F1_1*F2_3-F1_3*F2_1)*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,5.0/3.0)*(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3)*(2.0/3.0)))/2.0+lambda*(F1_1*F2_3-F1_3*F2_1)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0);
        dw[8] =  (mu*(F3_3*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,2.0/3.0)*2.0-(F1_1*F2_2-F1_2*F2_1)*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,5.0/3.0)*(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3)*(2.0/3.0)))/2.0-lambda*(F1_1*F2_2-F1_2*F2_1)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0);
    }
    else if (energy_type == "wang"){
    // Neo-hookean strain energy (Wang and Yang, 2016)
        dw[0] =  (lambda*(F2_2*F3_3-F2_3*F3_2))/2.0+(mu*(F1_1*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,2.0/3.0)*2.0-(F2_2*F3_3-F2_3*F3_2)*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,5.0/3.0)*(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3)*(2.0/3.0)))/2.0;
        dw[1] =  lambda*(F2_1*F3_3-F2_3*F3_1)*(-1.0/2.0)+(mu*(F1_2*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,2.0/3.0)*2.0+(F2_1*F3_3-F2_3*F3_1)*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,5.0/3.0)*(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3)*(2.0/3.0)))/2.0;
        dw[2] =  (lambda*(F2_1*F3_2-F2_2*F3_1))/2.0+(mu*(F1_3*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,2.0/3.0)*2.0-(F2_1*F3_2-F2_2*F3_1)*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,5.0/3.0)*(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3)*(2.0/3.0)))/2.0;
        dw[3] =  lambda*(F1_2*F3_3-F1_3*F3_2)*(-1.0/2.0)+(mu*(F2_1*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,2.0/3.0)*2.0+(F1_2*F3_3-F1_3*F3_2)*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,5.0/3.0)*(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3)*(2.0/3.0)))/2.0;
        dw[4] =  (lambda*(F1_1*F3_3-F1_3*F3_1))/2.0+(mu*(F2_2*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,2.0/3.0)*2.0-(F1_1*F3_3-F1_3*F3_1)*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,5.0/3.0)*(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3)*(2.0/3.0)))/2.0;
        dw[5] =  lambda*(F1_1*F3_2-F1_2*F3_1)*(-1.0/2.0)+(mu*(F2_3*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,2.0/3.0)*2.0+(F1_1*F3_2-F1_2*F3_1)*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,5.0/3.0)*(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3)*(2.0/3.0)))/2.0;
        dw[6] =  (lambda*(F1_2*F2_3-F1_3*F2_2))/2.0+(mu*(F3_1*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,2.0/3.0)*2.0-(F1_2*F2_3-F1_3*F2_2)*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,5.0/3.0)*(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3)*(2.0/3.0)))/2.0;
        dw[7] =  lambda*(F1_1*F2_3-F1_3*F2_1)*(-1.0/2.0)+(mu*(F3_2*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,2.0/3.0)*2.0+(F1_1*F2_3-F1_3*F2_1)*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,5.0/3.0)*(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3)*(2.0/3.0)))/2.0;
        dw[8] =  (lambda*(F1_1*F2_2-F1_2*F2_1))/2.0+(mu*(F3_3*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,2.0/3.0)*2.0-(F1_1*F2_2-F1_2*F2_1)*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,5.0/3.0)*(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3)*(2.0/3.0)))/2.0;
    }else if (energy_type == "ogden"){
        // Neo-hookean strain energy (Ogden, 1984)
        dw[0] = (mu*(F1_1*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,2.0/3.0)*2.0-(F2_2*F3_3-F2_3*F3_2)*1.0/pow(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1,5.0/3.0)*(F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3)*(2.0/3.0)))/2.0-lambda*(F2_2*F3_3-F2_3*F3_2)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0)-(mu*(F2_2*F3_3-F2_3*F3_2))/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1);
        dw[0] =  F1_1*mu-(mu*(F2_2*F3_3-F2_3*F3_2))/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1)+(lambda*log(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1)*(F2_2*F3_3-F2_3*F3_2))/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1);
        dw[1] =  F1_2*mu+(mu*(F2_1*F3_3-F2_3*F3_1))/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1)-(lambda*log(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1)*(F2_1*F3_3-F2_3*F3_1))/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1);
        dw[2] =  F1_3*mu-(mu*(F2_1*F3_2-F2_2*F3_1))/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1)+(lambda*log(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1)*(F2_1*F3_2-F2_2*F3_1))/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1);
        dw[3] =  F2_1*mu+(mu*(F1_2*F3_3-F1_3*F3_2))/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1)-(lambda*log(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1)*(F1_2*F3_3-F1_3*F3_2))/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1);
        dw[4] =  F2_2*mu-(mu*(F1_1*F3_3-F1_3*F3_1))/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1)+(lambda*log(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1)*(F1_1*F3_3-F1_3*F3_1))/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1);
        dw[5] =  F2_3*mu+(mu*(F1_1*F3_2-F1_2*F3_1))/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1)-(lambda*log(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1)*(F1_1*F3_2-F1_2*F3_1))/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1);
        dw[6] =  F3_1*mu-(mu*(F1_2*F2_3-F1_3*F2_2))/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1)+(lambda*log(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1)*(F1_2*F2_3-F1_3*F2_2))/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1);
        dw[7] =  F3_2*mu+(mu*(F1_1*F2_3-F1_3*F2_1))/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1)-(lambda*log(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1)*(F1_1*F2_3-F1_3*F2_1))/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1);
        dw[8] =  F3_3*mu-(mu*(F1_1*F2_2-F1_2*F2_1))/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1)+(lambda*log(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1)*(F1_1*F2_2-F1_2*F2_1))/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1);
    }
    else{
        exit(0);
    }


}