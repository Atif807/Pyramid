#Pyramid
Pyramid is a hierarchical approach to Evolutionary Computation
that decomposes problems by first tackling simpler versions of them before scaling up to increasingly more difficult versions with smaller populations; it is best visualised as traversing down a pyramid, where the problem being solved gets increasingly more difficult (longer genomes) the further down one goes.

Starting at the top of the Pyramid, the individuals address the simplest complexity level of the problem. The best performing individuals survive to address the next level of complexity by traversing down the Pyramid. At the final level only a small set of the initial population is left to address the complete version of the problem and from them the best individual chosen. 

# openGA
A forked repository from Arash OpenGA. 
<br>

### Original Download from Arash

Download link:

https://github.com/Arash-codedev/openGA/archive/v1.0.5.zip

### Documentation

Documentation is available at:

https://github.com/Arash-codedev/openGA/blob/master/openGA.pdf





### FAQ 

**Why does the crossover function generate a single offspring instead of two?**
This library calls crossover function two times instead of calling it once to create two offspring. This is to reduce the burden from the client programmer.

**What is the shrink scale?**
The mutation jumps should reduce over generations to increase the accuracy of solution. Shrink scale is a generation dependent coefficient to scale the resolution.

**After optimization, how to access the population?**
To have an access to the last generation, you can use an object field called `last_generation`. A particular usage example can be
```
best_solution = ga_obj.last_generation.chromosomes[ga_obj.last_generation.best_chromosome_index];
```
In the current implementation of openGA, only the middle cost of the last generation is stored. The reason is that keeping the entire generations can lead to a huge memory usage and eventually crashing the application after an out of memory error for particular applications which keep huge amount of data.
If you are keen to keep the full information trace of all generations, you can perform it manually via the report function.

**Does multi-threading always improve the performance?**
Multi-threading itself has an overhead. Therefore, it is helpful when the evaluation process is heavy enough. If the evaluation process is so fast, parallel programming is not necessary.

**Instead of a function, can I set a class method as a GA operator or a cost function?**
Yes, C++ supports it. It can be achieved by using C++ standard library. For this purpose, you need to use `std::bind` and `std::placeholders`. For detailed implementation information search for C++ function template bind.
