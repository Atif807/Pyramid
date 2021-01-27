/*
 * pyramid.cpp
 *
 *  Created on: 19 Jan 2021
 *      Author: atif
 */
#include "openGA.hpp"
#include "pyramid.h"
#include <iostream>

void checking()
{
   std::cout<< "Successful Call"<<std::endl;

}
typedef EA::Genetic<MySolution,MyMiddleCost> GA_Type;
typedef EA::GenerationType<MySolution,MyMiddleCost> Generation_Type;
GA_Type ga_obj;



/*
StopReason promotional_critera(thisGenerationType last_generation)
{
	                //cout<< "BEfore SORTING"<<endl;
	                //for (int i=0; i<int(last_generation.chromosomes.size()); i++)
	                //cout<< last_generation.chromosomes[i].genes.to_string()<<"\t"<<calculate_SO_total_fitness(last_generation.chromosomes[i]) <<endl;

	                int gen_size = (int) last_generation.chromosomes.size();
	                thisGenerationType gen;
	                for(int i=0; i<gen_size; i++)
	                        gen.chromosomes.push_back(last_generation.chromosomes[last_generation.sorted_indices[i]]);
	                //cout << "------------------------------------------"<<endl;
	                //cout << "After SORTING"<<endl;
	                // for (int i=0; i<int(gen.chromosomes.size()); i++)
	                //cout<< gen.chromosomes[i].genes.to_string()<<"\t"<<calculate_SO_total_fitness(gen.chromosomes[i]) <<endl;
	                      int loop_limit =int( gen_size * top_ind_pct);
	                      //std::cout<<"loop "<<loop_limit<<std::endl;
	                      std::ofstream o_file;
	                      o_file.open("promoted_L1_individuals.txt");
	                      double sum = 0.0;
	                          for (int i=0; i<loop_limit; i++)
	                          {
	                          double fitness = calculate_SO_total_fitness(gen.chromosomes[i]);
	                          o_file <<  gen.chromosomes[i].genes.to_string() << "\t" << fitness <<  "\n";
	                          sum =sum + fitness;
	                          }
	                        o_file.close();
	                        double all_avg = last_generation.average_cost;
	                        double top_ind_aevg = sum/loop_limit;
	                    // std::cout<< "top "<<top_ind_aevg<< std::endl;
	                    // std::cout << "all "<< all_avg <<std::endl;

	                             double better = all_avg*0.2;
	                             //double better = all_avg*5;

	                  if(generation_step<2 && !user_request_stop)
	                        return StopReason::Undefined;

	                if(is_single_objective())
	                {
	                        const thisGenSOAbs &g1=generations_so_abs[int(generations_so_abs.size())-2];
	                        const thisGenSOAbs &g2=generations_so_abs[int(generations_so_abs.size())-1];

	                        if(std::abs(g1.best_total_cost-g2.best_total_cost)<tol_stall_best)
	                                best_stall_count++;
	                        else
	                                best_stall_count=0;
	                        if(std::abs(g1.average_cost-g2.average_cost)<tol_stall_average)
	                                average_stall_count++;
	                        else
	                                average_stall_count=0;
	                }
	                //if(top_ind_aevg < top_ind_avg)
	                                //         return StopReason::UserRequest;
	                                if(top_ind_aevg <= better)
	                                                return StopReason::UserRequest;
	                                if(generation_step>=generation_max)
	                                                return StopReason::MaxGenerations;
	                                if(average_stall_count>=average_stall_max)
	                                      return StopReason::StallAverage;
	                                if(best_stall_count>=best_stall_max)
	                                      return StopReason::StallBest;
	                                                 // above lines are commented by Atif
	                                //if(user_request_stop)
	                                  //      return StopReason::UserRequest;

	                                return StopReason::Undefined;
	                        }

*/










