/* 
 * File:   mathTest.cpp
 * Author: miles
 *
 * Created on Jul 5, 2014, 12:05:40 AM
 */

#include <iostream>
#include <glm/glm.hpp>
#include <glm/mat2x2.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "math/mat_utils.h"

namespace hlm = hamLibs::math;

void printMat(const hlm::mat2& mat) {
    std::cout
        << '\t' << mat[0][0] << ' ' << mat[0][1] << '\n'
        << '\t' << mat[1][0] << ' ' << mat[1][1]
        << std::endl;
}

void printMat(const glm::mat2& mat) {
    std::cout
        << '\t' << mat[0][0] << ' ' << mat[0][1] << '\n'
        << '\t' << mat[1][0] << ' ' << mat[1][1]
        << std::endl;
}

void printMat(const hlm::mat3& mat) {
    std::cout
        << '\t' << mat[0][0] << ' ' << mat[0][1] << ' ' << mat[0][2] << '\n'
        << '\t' << mat[1][0] << ' ' << mat[1][1] << ' ' << mat[1][2] << '\n'
        << '\t' << mat[2][0] << ' ' << mat[2][1] << ' ' << mat[2][2]
        << std::endl;
}

void printMat(const glm::mat3& mat) {
    std::cout
        << '\t' << mat[0][0] << ' ' << mat[0][1] << ' ' << mat[0][2] << '\n'
        << '\t' << mat[1][0] << ' ' << mat[1][1] << ' ' << mat[1][2] << '\n'
        << '\t' << mat[2][0] << ' ' << mat[2][1] << ' ' << mat[2][2]
        << std::endl;
}

void printMat(const hlm::mat4& mat) {
    std::cout
        << '\t' << mat[0][0] << ' ' << mat[0][1] << ' ' << mat[0][2] << ' ' << mat[0][3] << '\n'
        << '\t' << mat[1][0] << ' ' << mat[1][1] << ' ' << mat[1][2] << ' ' << mat[1][3] << '\n'
        << '\t' << mat[2][0] << ' ' << mat[2][1] << ' ' << mat[2][2] << ' ' << mat[2][3] << '\n'
        << '\t' << mat[3][0] << ' ' << mat[3][1] << ' ' << mat[3][2] << ' ' << mat[3][3]
        << std::endl;
}

void printMat(const glm::mat4& mat) {
    std::cout
        << '\t' << mat[0][0] << ' ' << mat[0][1] << ' ' << mat[0][2] << ' ' << mat[0][3] << '\n'
        << '\t' << mat[1][0] << ' ' << mat[1][1] << ' ' << mat[1][2] << ' ' << mat[1][3] << '\n'
        << '\t' << mat[2][0] << ' ' << mat[2][1] << ' ' << mat[2][2] << ' ' << mat[2][3] << '\n'
        << '\t' << mat[3][0] << ' ' << mat[3][1] << ' ' << mat[3][2] << ' ' << mat[3][3]
        << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// 2D Matrix tests
///////////////////////////////////////////////////////////////////////////////
void matrix_2d_arithmetic_tests() {
    hlm::mat2 hm2 = {2.f, 3.f, 4.f, 5.f};
    glm::mat2 gm2 = {2.f, 3.f, 4.f, 5.f};
    
    std::cout << "2x2 Matrix addition: Ham\n";
    printMat(hm2+hm2);
    std::cout << "2x2 Matrix addition: GLM\n";
    printMat(gm2+gm2);
    
    std::cout << "2x2 Matrix subtraction: Ham\n";
    printMat(hm2-hm2);
    std::cout << "2x2 Matrix subtraction: GLM\n";
    printMat(gm2-gm2);
    
    std::cout << "2x2 Matrix multiplication: Ham\n";
    printMat(hm2*hm2);
    std::cout << "2x2 Matrix multiplication: GLM\n";
    printMat(gm2*gm2);
}

void matrix_2d_util_tests() {
    hlm::mat2 hm2 = {2.f, 3.f, 4.f, 5.f};
    glm::mat2 gm2 = {2.f, 3.f, 4.f, 5.f};
    
    std::cout << "2x2 Matrix determinant: Ham\n";
    std::cout << hlm::determinant(hm2) << '\n';
    std::cout << "2x2 Matrix determinant: GLM\n";
    std::cout << glm::determinant(gm2) << '\n';
    
    std::cout << "2x2 Matrix inverse: Ham\n";
    printMat(hlm::inverse(hm2));
    std::cout << "2x2 Matrix inverse: GLM\n";
    printMat(glm::inverse(gm2));
    
    std::cout << "2x2 Matrix transpose: Ham\n";
    printMat(hlm::transpose(hm2));
    std::cout << "2x2 Matrix transpose: GLM\n";
    printMat(glm::transpose(gm2));
}

///////////////////////////////////////////////////////////////////////////////
// 3D Matrix tests
///////////////////////////////////////////////////////////////////////////////
void matrix_3d_arithmetic_tests() {
    hlm::mat3 hm3 = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f};
    glm::mat3 gm3 = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f};
    
    std::cout << "3x3 Matrix addition: Ham\n";
    printMat(hm3+hm3);
    std::cout << "3x3 Matrix addition: GLM\n";
    printMat(gm3+gm3);
    
    std::cout << "3x3 Matrix subtraction: Ham\n";
    printMat(hm3-hm3);
    std::cout << "3x3 Matrix subtraction: GLM\n";
    printMat(gm3-gm3);
    
    std::cout << "3x3 Matrix multiplication: Ham\n";
    printMat(hm3*hm3);
    std::cout << "3x3 Matrix multiplication: GLM\n";
    printMat(gm3*gm3);
}

void matrix_3d_util_tests() {
    hlm::mat3 hm3 = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f};
    glm::mat3 gm3 = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f};
    
    std::cout << "3x3 Matrix determinant: Ham\n";
    std::cout << hlm::determinant(hm3) << '\n';
    std::cout << "3x3 Matrix determinant: GLM\n";
    std::cout << glm::determinant(gm3) << '\n';
    
    std::cout << "3x3 Matrix inverse: Ham\n";
    printMat(hlm::inverse(hm3));
    std::cout << "3x3 Matrix inverse: GLM\n";
    printMat(glm::inverse(gm3));
    
    std::cout << "3x3 Matrix transpose: Ham\n";
    printMat(hlm::transpose(hm3));
    std::cout << "3x3 Matrix transpose: GLM\n";
    printMat(glm::transpose(gm3));
}

///////////////////////////////////////////////////////////////////////////////
// 4D Matrix tests
///////////////////////////////////////////////////////////////////////////////
void matrix_4d_arithmetic_tests() {
    hlm::mat4 hm4 = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f};
    glm::mat4 gm4 = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f};
    
    std::cout << "4x4 Matrix addition: Ham\n";
    printMat(hm4+hm4);
    std::cout << "4x4 Matrix addition: GLM\n";
    printMat(gm4+gm4);
    
    std::cout << "4x4 Matrix subtraction: Ham\n";
    printMat(hm4-hm4);
    std::cout << "4x4 Matrix subtraction: GLM\n";
    printMat(gm4-gm4);
    
    std::cout << "4x4 Matrix multiplication: Ham\n";
    printMat(hm4*hm4);
    std::cout << "4x4 Matrix multiplication: GLM\n";
    printMat(gm4*gm4);
}

void matrix_4d_util_tests() {
    hlm::mat4 hm4 = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f};
    glm::mat4 gm4 = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f};
    
    std::cout << "4x4 Matrix determinant: Ham\n";
    std::cout << hlm::determinant(hm4) << '\n';
    std::cout << "4x4 Matrix determinant: GLM\n";
    std::cout << glm::determinant(gm4) << '\n';
    
    std::cout << "4x4 Matrix inverse: Ham\n";
    printMat(hlm::inverse(hm4));
    std::cout << "4x4 Matrix inverse: GLM\n";
    printMat(glm::inverse(gm4));
    
    std::cout << "4x4 Matrix transpose: Ham\n";
    printMat(hlm::transpose(hm4));
    std::cout << "4x4 Matrix transpose: GLM\n";
    printMat(glm::transpose(gm4));
    
    std::cout << "4x4 Matrix translation: Ham\n";
    printMat(hlm::translate(hm4, hlm::vec3{1.f, 2.f, 3.f}));
    std::cout << "4x4 Matrix translation: GLM\n";
    printMat(glm::translate(gm4, glm::vec3{1.f, 2.f, 3.f}));
}

///////////////////////////////////////////////////////////////////////////////
// Main
///////////////////////////////////////////////////////////////////////////////
int main() {
    matrix_2d_arithmetic_tests();
    matrix_2d_util_tests();
    
    matrix_3d_arithmetic_tests();
    matrix_3d_util_tests();
    
    matrix_4d_arithmetic_tests();
    matrix_4d_util_tests();
    
    return 0;
}

