#include <iostream>
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "scalar_product.h"

TEST(scalar_product, can_product_vectors_with_100_range)
{
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::vector<int> vec1;
	std::vector<int> vec2;
	vec1 = creatRandomVector(100);
	vec2 = creatRandomVector(100);

	int res1 = getParallelScalarProduct(vec1, vec2);
	int res2 = getSequentialScalarProduct(vec1, vec2);
	if (rank == 0)
		ASSERT_EQ(res1, res2);
}

TEST(scalar_product, can_throw_if_product_vectors_with_different_ranges)
{
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::vector<int> vec1 = creatRandomVector(100);
	std::vector<int> vec2 = creatRandomVector(120);
	ASSERT_ANY_THROW(getParallelScalarProduct(vec1, vec2));
}

TEST(scalar_product, can_product_vectors_with_odd_range)
{
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::vector<int> vec1;
	std::vector<int> vec2;
	vec1 = creatRandomVector(125);
	vec2 = creatRandomVector(125);

	int res1 = getParallelScalarProduct(vec1, vec2);
	int res2 = getSequentialScalarProduct(vec1, vec2);
	if (rank == 0)
		ASSERT_EQ(res1, res2);
}

TEST(scalar_product, can_product_vectors_with_big_range)
{
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::vector<int> vec1;
	std::vector<int> vec2;
	vec1 = creatRandomVector(100000);
	vec2 = creatRandomVector(100000);

	int res1 = getParallelScalarProduct(vec1, vec2);
	int res2 = getSequentialScalarProduct(vec1, vec2);
	if (rank == 0)
		ASSERT_EQ(res1, res2);
}

TEST(scalar_product, can_product_vectors_with_very_big_range)
{
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::vector<int> vec1;
	std::vector<int> vec2;
	vec1 = creatRandomVector(1000000);
	vec2 = creatRandomVector(1000000);

	int res1 = getParallelScalarProduct(vec1, vec2);
	int res2 = getSequentialScalarProduct(vec1, vec2);
	if (rank == 0)
		ASSERT_EQ(res1, res2);
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	int status, rank, size;
	status = MPI_Init(&argc, &argv);
	testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment());
	testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();

	listeners.Release(listeners.default_result_printer());
	listeners.Release(listeners.default_xml_generator());

	listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
	return RUN_ALL_TESTS();
	status = MPI_Finalize();
}