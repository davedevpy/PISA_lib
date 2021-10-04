/*========================================================================
  PISA  (www.tik.ee.ethz.ch/pisa/)
 
  ========================================================================
  Computer Engineering (TIK)
  ETH Zurich
 
  ========================================================================
  PISALIB 

  Pisa basic functionality that have to be implemented by the user  
   
  Header file.
  
  file: variator_user.h
  author: Fabian Landis, flandis@ee.ethz.ch

  revision by: Stefan Bleuler, bleuler@tik.ee.ethz.ch
  last change: $date$
  
  ========================================================================
*/

#ifndef VARIATOR_USER_H
#define VARIATOR_USER_H

#define PISA_UNIX /**** replace with PISA_WIN if compiling for Windows */

/* maximal length of filenames */
#define FILE_NAME_LENGTH 128  /**** change the value if you like */

/* maximal length of entries in local cfg file */
#define CFG_NAME_LENGTH 128   /**** change the value if you like */


/*----------------| declaration of global variables |------------------*/

/* defined in variator_user.c */
  
extern char paramfile[]; /* file with local parameters */

extern char *log_file; /* file to log to, defined in variator_user.c */

/*----------------------| individual struct |--------------------------*/

struct individual_t
{
     /* add your members here and make sure you initialize them
     correctly in create_individual */

     /* in variator.h a typedef is used to the define the type
     individual based on the individual_t struct defined here. */
};


/*------------------| functions for individual struct |----------------*/

void free_individual(individual *ind);
/* Frees the memory for one indiviual.

   post: memory for ind is freed
*/


double get_objective_value(int identity, int i); 
/* Gets objective value of an individual.

   pre: 0 <= i <= dim - 1 (dim is the number of objectives)

   post: Return value == the objective value number 'i' in individual '*ind'.
         If no individual with ID 'identity' return value == -1. 
*/   

/*-------------------------| statemachine |-----------------------------*/


int state0(); 
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


int state2();
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


int state4();
/* Do what needs to be done in state 4.

   pre: State 4 means the variator has to terminate.

   post: Free all memory.
         Return value == 0 if successful,
                      == 1 if unspecified errors happened,
                      == 2 if file reading failed.
*/


int state7();
/* Do what needs to be done in state 7.

   pre: State 7 means that the selector has just terminated.

   post: You probably don't need to do anything, just return 0.
         Return value == 0 if successful,
                      == 1 if unspecified errors happened,
                      == 2 if file reading failed.
*/


int state8();
/* Do what needs to be done in state 8.

   pre: State 8 means that the variator needs to reset and get ready to
        start again in state 0.

   post: Get ready to start again in state 0, this includes:
         Free all memory.
         Return value == 0 if successful,
                      == 1 if unspecified errors happened,
                      == 2 if file reading failed.
*/


int state11();
/* Do what needs to be done in state 11.

   pre: State 11 means that the selector has just reset and is ready
        to start again in state 1.

   post: You probably don't need to do anything, just return 0.
         Return value == 0 if successful,
                      == 1 if unspecified errors happened,
                      == 2 if file reading failed.
*/

int is_finished();
/* Tests if ending criterion of your algorithm applies.

   post: return value == 1 if optimization should stop
         return value == 0 if optimization should continue
*/
 
#endif /* VARIATOR_USER.H */
