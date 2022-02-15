/*
 * pyramid.cpp
 *
 *  Created on: 26 Jan 2021
 *      Author: atif
 *    this file actually called the function defined in Pyramid header
 */
#include <iostream>
#include <vector>
#include "pyramid.h"
using namespace std;

int Pyramid::get_hyper_mutation(){
		return hyper_mutation;
	}
	void Pyramid::set_hyper_mutation(int hyper_mutation)
	{
		this->hyper_mutation = hyper_mutation;
	}

	int Pyramid::get_total_levels(){
		return total_levels;
	}
	void Pyramid::set_total_levels(int total_levels)
	{
	  this->total_levels = total_levels;
	}

	int Pyramid::get_genome_length(){
			return genome_length;
		}
		void Pyramid::set_genome_length(int genome_length)
		{
		  this->genome_length = genome_length;
		}



