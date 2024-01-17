#include "systemcalls.h"


/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
*/
bool do_system(const char *cmd)
{

/*
 * TODO  add your code here
 *  Call the system() function with the command set in the cmd
 *   and return a boolean true if the system() call completed with success
 *   or false() if it returned a failure
*/
    unsigned int retVal = system(cmd);
    if (-1 == retVal)
    {
        perror("system");
        return false;
    }
    return true;
}

/**
* @param count -The numbers of variables passed to the function. The variables are command to execute.
*   followed by arguments to pass to the command
*   Since exec() does not perform path expansion, the command to execute needs
*   to be an absolute path.
* @param ... - A list of 1 or more arguments after the @param count argument.
*   The first is always the full path to the command to execute with execv()
*   The remaining arguments are a list of arguments to pass to the command in execv()
* @return true if the command @param ... with arguments @param arguments were executed successfully
*   using the execv() call, false if an error occurred, either in invocation of the
*   fork, waitpid, or execv() command, or if a non-zero return value was returned
*   by the command issued in @param arguments with the specified arguments.
*/

bool do_exec(int count, ...) {
    pid_t pid;
    va_list args;
    va_start(args, count);
    char *command[count + 1];
    
    for (int i = 0; i < count; i++) {
        command[i] = va_arg(args, char *);
    }
    
    command[count] = NULL;

    pid = fork();
    if (-1 == pid) {
        perror("fork");
        return false;
    } else if (0 == pid) { // Child process
        execv(command[0], command);
        perror("execv"); // execv only returns if an error occurs
        exit(EXIT_FAILURE);
    } else { // Parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            return (WEXITSTATUS(status) == 0); // Return true if child process succeeded
        }
    }

    va_end(args);
    return false;
}


/**
* @param outputfile - The full path to the file to write with command output.
*   This file will be closed at completion of the function call.
* All other parameters, see do_exec above
*/
bool do_exec_redirect(const char *outputfile, int count, ...)
{
    pid_t pid;
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    // this line is to avoid a compile warning before your implementation is complete
    // and may be removed
    command[count] = command[count];


/*
 * TODO
 *   Call execv, but first using https://stackoverflow.com/a/13784315/1446624 as a refernce,
 *   redirect standard out to a file specified by outputfile.
 *   The rest of the behaviour is same as do_exec()
 *
*/
    int fd = open(outputfile, O_WRONLY|O_TRUNC|O_CREAT, 0644);
    if (-1 == fd)
    {
        perror("open");
        return false;
    } 
    pid = fork();
    if (-1 == pid)
    {
        perror("fork");
        close(fd);
        return false;
    }
    else if(0 == pid)
    {
        
        if (dup2(fd, 1) < 0)
        {
            perror("dup2");
            close(fd);
            return false;
        }
        close(fd);
        execvp(command[0], command);
        perror("execvp");
        return false;
        
    }
    else
    {
        int status;
        close(fd);
        waitpid(pid, &status, 0);
        return WIFEXITED(status) && (WEXITSTATUS(status) == 0);
        close(fd);
    }
    va_end(args);

    return true;
}
