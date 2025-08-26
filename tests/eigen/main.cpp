#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/Eigenvalues>
#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace Eigen;

void print_separator(const std::string& title) {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << title << "\n";
    std::cout << std::string(50, '=') << "\n";
}

void demo_basic_matrix_operations() {
    print_separator("基础矩阵操作");
    
    // 创建矩阵
    Matrix3d m1;  // 3x3 double矩阵
    m1 << 1, 2, 3,
          4, 5, 6,
          7, 8, 9;
    
    Matrix3d m2;
    m2 << 2, 0, 1,
          1, 3, 2,
          0, 1, 4;
    
    std::cout << "矩阵 A:\n" << m1 << "\n\n";
    std::cout << "矩阵 B:\n" << m2 << "\n\n";
    
    // 基本运算
    std::cout << "A + B:\n" << m1 + m2 << "\n\n";
    std::cout << "A - B:\n" << m1 - m2 << "\n\n";
    std::cout << "A * B:\n" << m1 * m2 << "\n\n";
    
    // 标量乘法
    std::cout << "2 * A:\n" << 2 * m1 << "\n\n";
    
    // 转置
    std::cout << "A的转置:\n" << m1.transpose() << "\n\n";
    
    // 行列式
    std::cout << "A的行列式: " << m1.determinant() << "\n\n";
    
    // 迹
    std::cout << "A的迹: " << m1.trace() << "\n\n";
}

void demo_vector_operations() {
    print_separator("向量操作");
    
    // 创建向量
    Vector3d v1(1, 2, 3);
    Vector3d v2(4, 5, 6);
    
    std::cout << "向量 v1: " << v1.transpose() << "\n";
    std::cout << "向量 v2: " << v2.transpose() << "\n\n";
    
    // 向量运算
    std::cout << "v1 + v2: " << (v1 + v2).transpose() << "\n";
    std::cout << "v1 - v2: " << (v1 - v2).transpose() << "\n\n";
    
    // 点积
    double dot_product = v1.dot(v2);
    std::cout << "点积 v1·v2: " << dot_product << "\n\n";
    
    // 叉积 (仅适用于3D向量)
    Vector3d cross_product = v1.cross(v2);
    std::cout << "叉积 v1×v2: " << cross_product.transpose() << "\n\n";
    
    // 向量长度
    std::cout << "v1的长度: " << v1.norm() << "\n";
    std::cout << "v2的长度: " << v2.norm() << "\n\n";
    
    // 单位向量
    Vector3d v1_normalized = v1.normalized();
    std::cout << "v1单位向量: " << v1_normalized.transpose() << "\n";
    std::cout << "单位向量长度: " << v1_normalized.norm() << "\n\n";
    
    // 向量夹角
    double angle_rad = std::acos(v1.dot(v2) / (v1.norm() * v2.norm()));
    double angle_deg = angle_rad * 180.0 / M_PI;
    std::cout << "v1和v2夹角: " << angle_deg << "°\n\n";
}

void demo_matrix_decomposition() {
    print_separator("矩阵分解");
    
    Matrix4d A;
    A << 4,  2, -1,  3,
         2,  6,  0,  1,
        -1,  0,  8, -2,
         3,  1, -2,  5;
    
    std::cout << "原矩阵 A:\n" << A << "\n\n";
    
    // LU分解
    PartialPivLU<Matrix4d> lu_decomp(A);
    std::cout << "LU分解:\n";
    Matrix4d L = Matrix4d(lu_decomp.matrixLU().triangularView<StrictlyLower>()) + Matrix4d::Identity();
    Matrix4d U = Matrix4d(lu_decomp.matrixLU().triangularView<Upper>());
    std::cout << "L矩阵:\n" << L << "\n\n";
    std::cout << "U矩阵:\n" << U << "\n\n";
    
    // QR分解
    HouseholderQR<Matrix4d> qr_decomp(A);
    Matrix4d Q = qr_decomp.householderQ();
    Matrix4d R = Matrix4d(qr_decomp.matrixQR().triangularView<Upper>());
    
    std::cout << "QR分解:\n";
    std::cout << "Q矩阵:\n" << Q << "\n\n";
    std::cout << "R矩阵:\n" << R << "\n\n";
    
    // 验证QR分解
    Matrix4d QR_product = Q * R;
    std::cout << "Q * R (应该等于A):\n" << QR_product << "\n\n";
    std::cout << "QR分解误差: " << (A - QR_product).norm() << "\n\n";
    
    // Cholesky分解 (仅适用于正定矩阵)
    Matrix3d symmetric_positive_definite;
    symmetric_positive_definite << 4, 2, 1,
                                   2, 5, 3,
                                   1, 3, 6;
    
    LLT<Matrix3d> chol_decomp(symmetric_positive_definite);
    if (chol_decomp.info() == Success) {
        Matrix3d L = chol_decomp.matrixL();
        std::cout << "对称正定矩阵:\n" << symmetric_positive_definite << "\n\n";
        std::cout << "Cholesky分解 L:\n" << L << "\n\n";
        std::cout << "验证 L*L^T:\n" << L * L.transpose() << "\n\n";
    }
}

void demo_eigenvalues_eigenvectors() {
    print_separator("特征值和特征向量");
    
    Matrix3d A;
    A << 3, -2,  0,
        -2,  3,  0,
         0,  0,  5;
    
    std::cout << "对称矩阵 A:\n" << A << "\n\n";
    
    // 计算特征值和特征向量
    SelfAdjointEigenSolver<Matrix3d> eigensolver(A);
    if (eigensolver.info() != Success) {
        std::cout << "特征值计算失败!\n";
        return;
    }
    
    Vector3d eigenvalues = eigensolver.eigenvalues();
    Matrix3d eigenvectors = eigensolver.eigenvectors();
    
    std::cout << "特征值:\n" << eigenvalues << "\n\n";
    std::cout << "特征向量矩阵:\n" << eigenvectors << "\n\n";
    
    // 验证特征值和特征向量
    for (int i = 0; i < 3; ++i) {
        Vector3d eigenvec = eigenvectors.col(i);
        double eigenval = eigenvalues(i);
        
        Vector3d Av = A * eigenvec;
        Vector3d lambda_v = eigenval * eigenvec;
        
        std::cout << "特征值 " << i+1 << ": " << eigenval << "\n";
        std::cout << "A * v" << i+1 << ": " << Av.transpose() << "\n";
        std::cout << "λ" << i+1 << " * v" << i+1 << ": " << lambda_v.transpose() << "\n";
        std::cout << "误差: " << (Av - lambda_v).norm() << "\n\n";
    }
    
    // 一般矩阵的特征值
    Matrix3d general_matrix;
    general_matrix << 1, 2, 3,
                      0, 4, 5,
                      0, 0, 6;
    
    std::cout << "一般矩阵:\n" << general_matrix << "\n\n";
    
    EigenSolver<Matrix3d> general_solver(general_matrix);
    std::cout << "一般矩阵的特征值:\n" << general_solver.eigenvalues() << "\n\n";
}

void demo_linear_systems() {
    print_separator("线性方程组求解");
    
    Matrix3d A;
    A << 2, 1, -1,
        -3, -1, 2,
        -2, 1, 2;
    
    Vector3d b(8, -11, -3);
    
    std::cout << "线性方程组 Ax = b:\n";
    std::cout << "A =\n" << A << "\n\n";
    std::cout << "b = " << b.transpose() << "\n\n";
    
    // 方法1: 直接求逆 (不推荐用于大型矩阵)
    Vector3d x1 = A.inverse() * b;
    std::cout << "方法1 (矩阵求逆): x = " << x1.transpose() << "\n";
    
    // 方法2: LU分解
    Vector3d x2 = A.lu().solve(b);
    std::cout << "方法2 (LU分解): x = " << x2.transpose() << "\n";
    
    // 方法3: QR分解
    Vector3d x3 = A.householderQr().solve(b);
    std::cout << "方法3 (QR分解): x = " << x3.transpose() << "\n";
    
    // 方法4: SVD分解 (最稳定)
    Vector3d x4 = A.bdcSvd(ComputeFullU | ComputeFullV).solve(b);
    std::cout << "方法4 (SVD分解): x = " << x4.transpose() << "\n\n";
    
    // 验证解
    Vector3d residual = A * x4 - b;
    std::cout << "残差: " << residual.transpose() << "\n";
    std::cout << "残差范数: " << residual.norm() << "\n\n";
    
    // 最小二乘解 (超定系统)
    MatrixXd A_over(4, 3);
    VectorXd b_over(4);
    
    A_over << 1, 2, 1,
              2, 1, 3,
              1, 1, 2,
              3, 2, 1;
    
    b_over << 4, 7, 5, 8;
    
    std::cout << "超定系统 (最小二乘):\n";
    std::cout << "A =\n" << A_over << "\n\n";
    std::cout << "b = " << b_over.transpose() << "\n\n";
    
    VectorXd x_ls = A_over.bdcSvd(ComputeFullU | ComputeFullV).solve(b_over);
    std::cout << "最小二乘解: x = " << x_ls.transpose() << "\n";
    
    VectorXd residual_ls = A_over * x_ls - b_over;
    std::cout << "最小二乘残差范数: " << residual_ls.norm() << "\n\n";
}

void demo_sparse_matrices() {
    print_separator("稀疏矩阵");
    
    // 创建稀疏矩阵
    SparseMatrix<double> sparse_mat(4, 4);
    
    // 使用三元组列表构建稀疏矩阵
    std::vector<Triplet<double>> triplets;
    triplets.push_back(Triplet<double>(0, 0, 4.0));
    triplets.push_back(Triplet<double>(0, 2, 2.0));
    triplets.push_back(Triplet<double>(1, 1, 5.0));
    triplets.push_back(Triplet<double>(2, 0, 1.0));
    triplets.push_back(Triplet<double>(2, 2, 3.0));
    triplets.push_back(Triplet<double>(3, 3, 6.0));
    
    sparse_mat.setFromTriplets(triplets.begin(), triplets.end());
    
    std::cout << "稀疏矩阵:\n" << Matrix<double, 4, 4>(sparse_mat) << "\n\n";
    std::cout << "非零元素数: " << sparse_mat.nonZeros() << "\n";
    std::cout << "稀疏度: " << (1.0 - (double)sparse_mat.nonZeros() / (sparse_mat.rows() * sparse_mat.cols())) * 100 << "%\n\n";
    
    // 稀疏矩阵运算
    SparseVector<double> sparse_vec(4);
    sparse_vec.insert(0) = 1.0;
    sparse_vec.insert(2) = 2.0;
    sparse_vec.insert(3) = 3.0;
    
    std::cout << "稀疏向量: " << VectorXd(sparse_vec).transpose() << "\n";
    
    VectorXd result = sparse_mat * sparse_vec;
    std::cout << "稀疏矩阵 * 稀疏向量: " << result.transpose() << "\n\n";
    
    // 稀疏线性系统求解
    SparseLU<SparseMatrix<double>> solver;
    solver.compute(sparse_mat);
    
    if (solver.info() == Success) {
        VectorXd b_sparse(4);
        b_sparse << 1, 2, 3, 4;
        
        VectorXd x_sparse = solver.solve(b_sparse);
        std::cout << "稀疏线性系统解: " << x_sparse.transpose() << "\n\n";
    }
}

void demo_matrix_functions() {
    print_separator("矩阵函数和高级操作");
    
    Matrix3d A;
    A << 1, 0.5, 0.2,
         0.5, 2, 0.3,
         0.2, 0.3, 3;
    
    std::cout << "对称正定矩阵 A:\n" << A << "\n\n";
    
    // 矩阵的逆
    Matrix3d inv_A = A.inverse();
    std::cout << "A的逆矩阵:\n" << inv_A << "\n\n";
    std::cout << "验证 A * A^(-1):\n" << A * inv_A << "\n\n";
    
    // 矩阵的平方
    Matrix3d A_squared = A * A;
    std::cout << "A的平方:\n" << A_squared << "\n\n";
    
    // 矩阵的条件数
    JacobiSVD<Matrix3d> svd(A, ComputeFullU | ComputeFullV);
    VectorXd singular_values = svd.singularValues();
    double condition_number = singular_values(0) / singular_values(singular_values.size()-1);
    
    std::cout << "奇异值: " << singular_values.transpose() << "\n";
    std::cout << "条件数: " << condition_number << "\n\n";
    
    // 矩阵范数
    std::cout << "矩阵范数:\n";
    std::cout << "  Frobenius范数: " << A.norm() << "\n";
    std::cout << "  1-范数: " << A.lpNorm<1>() << "\n";
    std::cout << "  无穷范数: " << A.lpNorm<Infinity>() << "\n\n";
}

void demo_geometry_transformations() {
    print_separator("几何变换");
    
    // 2D变换
    std::cout << "2D几何变换:\n\n";
    
    Vector2d point(3, 4);
    std::cout << "原始点: (" << point.x() << ", " << point.y() << ")\n\n";
    
    // 旋转矩阵
    double angle = M_PI / 4;  // 45度
    Matrix2d rotation;
    rotation << std::cos(angle), -std::sin(angle),
                std::sin(angle),  std::cos(angle);
    
    Vector2d rotated_point = rotation * point;
    std::cout << "旋转45°后: (" << rotated_point.x() << ", " << rotated_point.y() << ")\n\n";
    
    // 缩放矩阵
    Matrix2d scaling;
    scaling << 2, 0,
               0, 0.5;
    
    Vector2d scaled_point = scaling * point;
    std::cout << "缩放(2x, 0.5y)后: (" << scaled_point.x() << ", " << scaled_point.y() << ")\n\n";
    
    // 复合变换
    Vector2d transformed = scaling * rotation * point;
    std::cout << "复合变换(先旋转后缩放): (" << transformed.x() << ", " << transformed.y() << ")\n\n";
    
    // 3D变换 - 使用齐次坐标
    Matrix4d transform_3d = Matrix4d::Identity();
    
    // 平移
    transform_3d(0, 3) = 5;
    transform_3d(1, 3) = -2;
    transform_3d(2, 3) = 3;
    
    // 旋转(绕z轴)
    double angle_3d = M_PI / 6;  // 30度
    transform_3d(0, 0) = std::cos(angle_3d);
    transform_3d(0, 1) = -std::sin(angle_3d);
    transform_3d(1, 0) = std::sin(angle_3d);
    transform_3d(1, 1) = std::cos(angle_3d);
    
    std::cout << "3D变换矩阵:\n" << transform_3d << "\n\n";
    
    Vector4d point_3d(1, 2, 3, 1);  // 齐次坐标
    Vector4d transformed_3d = transform_3d * point_3d;
    
    std::cout << "原始3D点: (" << point_3d(0) << ", " << point_3d(1) << ", " << point_3d(2) << ")\n";
    std::cout << "变换后: (" << transformed_3d(0) << ", " << transformed_3d(1) << ", " << transformed_3d(2) << ")\n\n";
}

void demo_performance_optimization() {
    print_separator("性能优化示例");
    
    const int size = 1000;
    
    // 生成随机矩阵
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-10.0, 10.0);
    
    MatrixXd A = MatrixXd::NullaryExpr(size, size, [&]() { return dis(gen); });
    MatrixXd B = MatrixXd::NullaryExpr(size, size, [&]() { return dis(gen); });
    
    std::cout << "测试 " << size << "x" << size << " 矩阵运算性能:\n\n";
    
    // 矩阵乘法
    auto start = std::chrono::high_resolution_clock::now();
    MatrixXd C = A * B;
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "矩阵乘法时间: " << duration.count() << " ms\n";
    
    // LU分解
    start = std::chrono::high_resolution_clock::now();
    PartialPivLU<MatrixXd> lu(A);
    end = std::chrono::high_resolution_clock::now();
    
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "LU分解时间: " << duration.count() << " ms\n";
    
    // SVD分解
    start = std::chrono::high_resolution_clock::now();
    JacobiSVD<MatrixXd> svd(A, ComputeFullU | ComputeFullV);
    end = std::chrono::high_resolution_clock::now();
    
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "SVD分解时间: " << duration.count() << " ms\n\n";
    
    std::cout << "性能提示:\n";
    std::cout << "• 使用固定大小矩阵 (Matrix3d) 比动态大小 (MatrixXd) 更快\n";
    std::cout << "• 使用 noalias() 避免不必要的临时对象\n";
    std::cout << "• 编译时开启 -O3 优化和 -DNDEBUG\n";
    std::cout << "• 对于大型矩阵，考虑使用多线程版本的BLAS库\n";
}

int main() {
    std::cout << "🧮 Eigen 现代C++线性代数库演示\n";
    std::cout << "==================================\n";
    
    // 设置输出精度
    std::cout << std::fixed << std::setprecision(4);
    
    try {
        demo_basic_matrix_operations();
        demo_vector_operations();
        demo_matrix_decomposition();
        demo_eigenvalues_eigenvectors();
        demo_linear_systems();
        demo_sparse_matrices();
        demo_matrix_functions();
        demo_geometry_transformations();
        demo_performance_optimization();
        
        std::cout << "\n✅ Eigen 演示完成!\n";
        std::cout << "\n📚 主要特性:\n";
        std::cout << "  • 高性能的线性代数运算\n";
        std::cout << "  • 表达式模板技术，零开销抽象\n";
        std::cout << "  • 支持稠密和稀疏矩阵\n";
        std::cout << "  • 丰富的矩阵分解算法\n";
        std::cout << "  • SIMD向量化优化\n";
        std::cout << "  • 编译时大小检查\n";
        std::cout << "  • 与标准C++容器兼容\n";
        std::cout << "  • 头文件库，易于集成\n";
        
    } catch (const std::exception& e) {
        std::cerr << "❌ 错误: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}