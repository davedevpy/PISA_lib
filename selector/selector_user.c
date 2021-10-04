/*========================================================================
  PISA  (www.tik.ee.ethz.ch/pisa/)
 
  ========================================================================
  Computer Engineering (TIK)
  ETH Zurich
 
  ========================================================================
  PISALIB 
  
  Implementation file.

  The functions in this file provide a framework for the functions you
  need to implement. These functions will be called by other parts of
  PISALib
  
  file: selector_user.c
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

#include "selector.h"
#include "selector_user.h"


/*----------------------| global variables |---------------------------*/

/* declared extern in selector_user.h and used in other files as well */

char paramfile[FILE_NAME_LENGTH]; /* file with local parameters */

char *log_file = "selector_error.log";
/**** Change the definition of 'log_file' if you want another name! Or
      set to NULL if you want to write error messages to stderr. */


/*-------------------------| individual |-------------------------------*/
int set_objective_value(individual *ind, int index, double obj_value)
/* Sets the objective_value of an individual.
   
   post: It is checked if index is in the correct range. If it is the
         objective value for the objective number i in individual ind
         is set to obj_value.
         Return value is 0 if successful and 1 otherwise.
*/        
{
     if(ind == NULL || index < 0 || index >= dimension)
          return (1);
     else
     {
          /**** Here comes your code for setting the objective values in
                the 'individual_t' struct. */

          return (0);
     }
  
}


individual *create_individual()
/* Allocates memory for a new individual and initializes values.

   post: returns a pointer to the allocated memory
         returns NULL if allocation failed
*/
{
     individual *return_ind;

     return_ind = (individual *) malloc(sizeof(individual));
     if (return_ind == NULL)
     {
          log_to_file(log_file, __FILE__, __LINE__, "selector out of memory");
          return(NULL);
     }

     /**** Here comes your code for allocating memory for the members of
           the 'individual_t' struct */
     
     return (return_ind);
}


void free_individual(individual* ind)
/* Frees the memory for one indiviual.

   post: memory for ind is freed
*/
{
      /**** Here comes your code for freeing the memory allocated for
            the members of the 'individual_t' struct. */
     
      free(ind);
}


/*-------------------------| statemachine functions |-------------------*/

int state1() 
/* Do what needs to be done in state 1.

   pre: The global variable 'paramfile' contains the name of the
        parameter file specified on the commandline.
        The global variable 'alpha' contains the number of indiviuals
        you need to read using 'read_ini()'.
        The global variable 'mu' contains the number of individuals
        you need to select.
        
   post: optionally read parameter specific for the module
         optionally do some initialization
         read_ini() called
         'mu' parents selected
         undesired individuals deleted from the global population
         write_sel() called
         write_arc() called
         return value == 0 if successful,
                      == 1 if unspecified errors happened,
                      == 2 if file operation failed.
*/
{
     int result; /* stores return values of called functions */
     int *sample_identities;
     int *result_identities; /* array of identities returned by read_ini */

     /**** Here you could call a function to read the local parameter
           values from the 'paramfile'. */

     result_identities = (int *) malloc(alpha * sizeof (int));
     if (result_identities == NULL)
     {
          log_to_file(log_file, __FILE__, __LINE__, "selector out of memory");
          return (1);
     }
     
     result = read_ini(result_identities);   /* read ini file */
     if (result == 1)
          return (2); /* reading ini file failed */
    

     sample_identities = (int *) malloc(mu * sizeof (int));
     if (result_identities == NULL)
     {
          log_to_file(log_file, __FILE__, __LINE__, "selector out of memory");
          return (1);
     }
     
     /**** Here comes your code for selecting 'mu' parents out of the
           global population. Put their identities in the
           'sample_identities' array. */


     result = write_sel(sample_identities);     /* write sel file */
     if(result != 0)
     {
          log_to_file(log_file, __FILE__, __LINE__, "failed write_sel()");
          return(1);
     }
     
     /**** Here comes your code for removing the individuals from the
           global population which you don't want to keep anymore.
           Use: remove_individual(identity) */

     free(sample_identities);
     free(result_identities);

     result = write_arc();     /* write arc file
                                  (individuals in global population) */
     if(result != 0)
     {
          log_to_file(log_file, __FILE__, __LINE__, "failed write_arc()");
          return(1);
     }
  
     return (0);   
}  


int state3()
/* Do what needs to be done in state 3.

   pre: The global variable 'lambda' contains the number of indiviuals
        you need to read using 'read_var()'.
        The global variable 'mu' contains the number of individuals
        you need to select and then write to the 'sel' file.
        
   post: read_var() called
         mu parents selected
         undesired individuals deleted from the global population
         write_sel() called
         write_arc() called
         return value == 0 if successful,
                      == 1 if unspecified errors happened,
                      == 2 if file reading failed.
*/
{
     int result; /* stores return values of called functions */
     int *offspring_identities; /* array with IDs filled by read_var() */
     int *parent_identities; /* array with IDs of parents */

     offspring_identities = (int *) malloc(lambda * sizeof(int)); 
     if (offspring_identities == NULL)
     {
          log_to_file(log_file, __FILE__, __LINE__, "selector out of memory");
          return (1);
     }

     parent_identities = (int *) malloc(mu * sizeof(int)); 
     if (parent_identities == NULL)
     {
          log_to_file(log_file, __FILE__, __LINE__, "variator out of memory");
          return (1);
     }
     
     result = read_var(offspring_identities);
     if (result == 1) /* if some file reading error occurs, return 2 */
           return (2);

     /**** Here comes your code for determining the new content of the
           global population by deleting individuals which you don't
           want to as parents ever again.
           Select 'mu' parents and put their identities in
           'parent_identities'. */

     result = write_sel(parent_identities);
     if(result != 0)
     {
          log_to_file(log_file, __FILE__, __LINE__, "failed write_sel()");
          return(1);
     }

     free(parent_identities);
     free(offspring_identities);

     result = write_arc();
     
     if(result != 0)
     {
          log_to_file(log_file, __FILE__, __LINE__, "failed write_arc()");
          return (1);
     }

     return (0);   
}  


int state5()
/* Do what needs to be done in state 5.

   pre: state 5 means the variator has just terminated

   post: you probably don't need to do anything, just return 0
         return value == 0 if successful,
                      == 1 if unspecified errors happened,
                      == 2 if file reading failed.

*/
{
     return(0); 
}


int state6()
/* Do what needs to be done in state 6.

   pre: state 6 means that the selector has to terminate.

   post: free all memory
         return value == 0 if successful,
                      == 1 if unspecified errors happened,
                      == 2 if file reading failed.
*/
{
     int current_id;

     /**** Here comes your code if you need to do anything before
           terminating. */
      
     current_id = get_first();
     while(current_id != -1) /* freeing memory */
     {
          remove_individual(current_id);
          current_id = get_next(current_id);
     }
     return (0);
}


int state9()
/* Do what needs to be done in state 9.

   pre: State 9 means that the variator is reset and ready to start
        again in state 0.

   post: You probably don't have to do anything, just return 0.
         return value == 0 if successful,
                      == 1 if unspecified errors happened,
                      == 2 if file reading failed.
*/
{
     return (0);
}


int state10()
/* Do what needs to be done in state 10.

   pre: State 10 means that the selector need to reset and get ready
        to start again in state 1.

   post: Get ready to start again in state 1, this includes:
         Free all memory.
         return value == 0 if successful,
                      == 1 if unspecified errors happened,
                      == 2 if file reading failed.
*/
{
     int current_id;

     /**** Here comes your code if you need to do anything before
           terminating. */
     
     current_id = get_first();
     while(current_id != -1) /* freeing memory */
     {
          remove_individual(current_id);
          current_id = get_next(current_id);
     }
     return (0);
}



int is_finished() 
/* Tests if ending criterion of your algorithm applies.

   post: return value == 1 if optimization should stop
         return value == 0 if optimization should continue

   remark: Normally the variator decides when to terminate. So
           just return 0.
*/
{
     /**** Replace 'return (0)' if you wish to check some termination
           criterion. */
     
     return (0);
}
