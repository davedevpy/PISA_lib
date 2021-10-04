/*========================================================================
  PISA  (www.tik.ee.ethz.ch/pisa/)
 
  ========================================================================
  Computer Engineering (TIK)
  ETH Zurich
 
  ========================================================================
  PISALIB 
  
  Functions the user must implement
  
  C file.
  
  file: variator_user.c
  author: Fabian Landis, flandis@ee.ethz.ch

  revision by: Stefan Bleuler, bleuler@tik.ee.ethz.ch
  last change: $date$
  
  ========================================================================
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>

#include "variator.h"
#include "variator_user.h"



/*----------------------| global variables |---------------------------*/

/* declared extern in variator_user.h and used in other files as well */

char paramfile[FILE_NAME_LENGTH]; /* file with local parameters */

char *log_file = "variator_error.log";
/**** Change the definition of 'log_file' if you want another name! Or
      set to NULL if you want to write error messages to stderr. */


/*-------------------------| individual |-------------------------------*/

void free_individual(individual *ind) 
/* Frees the memory for one indiviual.

   post: memory for ind is freed
*/
{
     /**** Here comes your code for freeing the memory allocated for
           the members of the 'individual_t' struct. */

     free(ind);
}

double get_objective_value(int identity, int i)
/* Gets objective value of an individual.

   pre: 0 <= i <= dimension - 1 (dimension is the number of objectives)

   post: Return value == the objective value number 'i' in individual '*ind'.
         If no individual with ID 'identity' return value == -1. 
*/   
{
     double objective_value = -1.0;

     assert(0 <= i && i < dimension); /* asserting the pre-condition */
     
     /**** Here comes your code for getting the objective values from
           the 'individual_t' struct. */
  
     return (objective_value);
}

/*-------------------------| statemachine functions |-------------------*/

int state0() 
/* Do what needs to be done in state 0.

   pre: The global variable 'paramfile' contains the name of the
        parameter file specified on the commandline.
        The global variable 'alpha' contains the number of indiviuals
        you need to generate for the initial population.
                
   post: Optionally read parameter specific for the module.
         Optionally do some initialization.
         Initial population created.
         Information about initial population written to the ini file
         using write_ini().
         Return value == 0 if successful,
                      == 1 if unspecified errors happened,
                      == 2 if file reading failed.
*/
{
    
     int result; /* stores return values of called functions */
     int *initial_population; /* storing the IDs of the individuals */
     initial_population = (int *) malloc(alpha * sizeof(int)); 
     if (initial_population == NULL)
     {
          log_to_file(log_file, __FILE__, __LINE__, "variator out of memory");
          return (1);
     }
     
     /**** Here you could call a function to read the local parameter
           values from the 'paramfile'. */

     /**** Here comes your code for creating the initial population.
           Add each individual to the global population using add_individual
           and put all identities in the 'initial_population' array. */


     result = write_ini(initial_population);
     if (result != 0)
     { 
          log_to_file(log_file, __FILE__, __LINE__,
                      "couldn't write ini");
          free(initial_population);
          return (1);
     }

     free(initial_population);
     return (0);
}



int state2()
/* Do what needs to be done in state 2.

   pre: The global variable 'mu' contains the number of indiviuals
        you need to read using 'read_sel()'.
        The global variable 'lambda' contains the number of individuals
        you need to create by variation of the individuals specified the
        'sel' file.
        
   post: Optionally call read_arc() in order to delete old uncessary
         individuals from the global population.
         read_sel() called
         'lambda' children generated from the 'mu' parents
         Children added to the global population using add_individual().
         Information about children written to the 'var' file using
         write_var().
         Return value == 0 if successful,
                      == 1 if unspecified errors happened,
                      == 2 if file reading failed.
*/
{
     int *parent_identities, *offspring_identities; /* array of identities */
     int result; /* stores return values of called functions */

     parent_identities = (int *) malloc(mu * sizeof(int)); 
     if (parent_identities == NULL)
     {
          log_to_file(log_file, __FILE__, __LINE__, "variator out of memory");
          return (1);
     }

     offspring_identities = (int *) malloc(lambda * sizeof(int)); 
     if (offspring_identities == NULL)
     {
          log_to_file(log_file, __FILE__, __LINE__, "variator out of memory");
          return (1);
     }
     
     result = read_sel(parent_identities);
     if (result != 0) /* if some file reading error occurs, return 2 */
          return (2);

     result = read_arc(); 
     if (result != 0) /* if some file reading error occurs, return 2 */
          return (2);

     /**** Here comes your code for creating lambda new individuals by
           variating the parents in 'parent_identities'.
           add all inidividuals to the global population using
           add_individual() and write their IDs in offspring_identities. */

     result = write_var(offspring_identities);
     if (result != 0)
     { 
          log_to_file(log_file, __FILE__, __LINE__,
                      "couldn't write var");
          free(offspring_identities);
          free(parent_identities);
          return (1);
     }

     free(offspring_identities);
     free(parent_identities);
     return (0);
}
 

int state4() 
/* Do what needs to be done in state 4.

   pre: State 4 means the variator has to terminate.

   post: Free all memory.
         Return value == 0 if successful,
                      == 1 if unspecified errors happened,
                      == 2 if file reading failed.
*/
{
     /**** Here comes your code if you need to do anything before
           terminating. E.g. call some kind of output function, which
           informs about the results of the optimization run. */
     
     return (0);
}


int state7()
/* Do what needs to be done in state 7.

   pre: State 7 means that the selector has just terminated.

   post: You probably don't need to do anything, just return 0.
         Return value == 0 if successful,
                      == 1 if unspecified errors happened,
                      == 2 if file reading failed.
*/
{
     return(0);  
}


int state8()
/* Do what needs to be done in state 8.

   pre: State 8 means that the variator needs to reset and get ready to
        start again in state 0.

   post: Get ready to start again in state 0. 
         Return value == 0 if successful,
                      == 1 if unspecified errors happened,
                      == 2 if file reading failed.
*/
{
     /**** Here comes your code if you need to do anything before
           resetting. */
     
     return (0);
}


int state11()
/* Do what needs to be done in state 11.

   pre: State 11 means that the selector has just reset and is ready
        to start again in state 1.

   post: You probably don't need to do anything, just return 0.
         Return value == 0 if successful,
                      == 1 if unspecified errors happened,
                      == 2 if file reading failed.
*/
{
     return (0);  
}


int is_finished()
/* Tests if ending criterion of your algorithm applies.

   post: return value == 1 if optimization should stop
         return value == 0 if optimization should continue
*/
{    
     /**** Here comes your code for checking the termination criteria. */
}
