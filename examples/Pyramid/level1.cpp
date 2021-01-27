// This library is free and distributed under
// Mozilla Public License Version 2.0.

#include <string>
#include <vector>
#include "openGA.hpp"
#include <fstream>
#include <sstream>
#include "../Pyramid/pyramid.h"
#include "helper.cpp"
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
//using namespace std;


int main(int argc, char *argv[]) {
	//output_file.open("./bin/result_so-rastrigin.txt");


	//int c_l = 4;
	//output_file.open("./bin/"+to_string(c_l)+"result_so-rastrigin.txt");
		//total_level = atoi(argv[2]);
		//std::cout <<"User Entered = "<<total_level<<std::endl;


		//file_n = atoi(argv[7]);
			Pyramid pyramid_obj;
			/*genome_len = p.get_genome_length();
			std::cout<<"default genome length = "<<genome_len<<std::endl;
			genome_len = atoi(argv[3]);
		    std::cout <<"User Entered Genome Length = "<<genome_len<<std::endl;*/

	//std::cout << "default total levels = " << pyramid_obj.get_total_levels() << std::endl;
	//std::cout << "default genome length = " << pyramid_obj.get_genome_length() << std::endl;
	if(argc == 1){
		total_level = pyramid_obj.get_total_levels();
		genome_length = pyramid_obj.get_genome_length();
	}
	if (argc == 2) {
		total_level = atoi(argv[1]);
		pyramid_obj.set_total_levels(total_level);
	}
	if (argc == 3) {
		total_level = atoi(argv[1]);
		genome_length = atoi(argv[2]);
		pyramid_obj.set_total_levels(total_level);
		pyramid_obj.set_genome_length(genome_length);
	}
	//std::cout << "User entered total levels = " << pyramid_obj.get_total_levels() << std::endl;
	//std::cout << "User entered genome length = " << pyramid_obj.get_genome_length() << std::endl;
	/*total_level = p.get_total_levels();
	std::cout << "User Entered = " << total_level << std::endl;
	total_level = p.get_total_levels();
	std::cout << "after user setting (final value) = " << total_level
			<< std::endl;
*/


	EA::Chronometer timer;
	timer.tic();

	GA_Type ga_obj;
	ga_obj.problem_mode = EA::GA_MODE::SOGA;
	ga_obj.multi_threading = false;
	ga_obj.dynamic_threading = false;
	ga_obj.idle_delay_us = 0; // switch between threads quickly
	ga_obj.verbose = false;
	//ga_obj.population = 100;
	//ga_obj.generation_max = 5;
	ga_obj.calculate_SO_total_fitness = calculate_SO_total_fitness;
	ga_obj.init_genes = init_genes;
	ga_obj.eval_solution = eval_solution;
	ga_obj.mutate = mutate;
	ga_obj.crossover = crossover;
	ga_obj.SO_report_generation = SO_report_generation;
	ga_obj.best_stall_max = 20;
	ga_obj.average_stall_max = 20;
	ga_obj.tol_stall_best = 1e-6;
	ga_obj.tol_stall_average = 1e-6;
	ga_obj.elite_count = 10;
	ga_obj.crossover_fraction = 0.8;
	ga_obj.mutation_rate = 0.005;


	for(int current_level=1; current_level<=total_level; current_level++)
		{

		output_file.open("./bin/results.txt");
		create_folders(current_level, total_level);
		//update pop and generation
		ga_obj.population = update_pop(current_level, total_level);
		//std::cout<<"pop = "<< ga_obj.population<<std::endl;
		ga_obj.generation_max = update_gen(total_level);
		//std::cout<<"Gen = "<< ga_obj.generation_max<<std::endl;
		//std::cout<<"Level = "+std::to_string(current_level)+"\n"<<std::endl;
		ga_obj.solve(current_level, total_level);
		//copy file
		output_file.close();
		std::string des = "Pyramid/Results/L"+std::to_string(total_level)+"/L"+std::to_string(current_level)+"_results/result.txt";
		const char *destination = des.c_str();
		copyFile("./bin/results.txt", destination );
		if(current_level < total_level){
		std::string des1 = "Pyramid/Results/L"+std::to_string(total_level)+"/L"+std::to_string(current_level)+"_results/promoted_individuals.txt";
		const char *destination1 = des1.c_str();
		copyFile("promoted_individuals.txt", destination1 );}
		}



	std::cout << "The problem is optimized in " << timer.toc() << " seconds."
			<< std::endl;
	//output_file.close();
	return 0;
}
