#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <csignal>
#include <sys/types.h>
#include <wait.h>
#include <sys/types.h>
#include <dirent.h>

using namespace std;

//QUESTION why does signal print twice??

//FIXME ctrl+c gets overriden but the program skips sleep after command


// printf("parent PiD: %d\n", parent_pid);
// printf("kid PiD: %d\n", kid_pid);

// parent process

// for(;;)
//     sleep(10);

// big loop
//      fork
// parent

// sigint
// try whatever to prevent killing
// override three different signals
// ps -aux tell what programs are running

//command line: "kill -kill PiD"


void overwritesig(int i){
    cout << "Sike, you can't quit the program" << endl;
}

int main(){

    // only able to override ctrl+c, idk what to do about ctrl+z

    cout << "parent pid is " << getpid() << endl;
    // trying to redirect default signal behavior to overwritesig(int i)
    // signal does NOT send signals, it OVERRIDES signals
    signal(SIGINT, overwritesig); // ctrl+c
    //signal(SIGTSTP, overwritesig); // ctrl+z
    // signal(SIGKILL, overwritesig); // impossible to override SIGKILL
    signal(SIGQUIT, overwritesig); // ctrl+\
    // signal(SIGTERM, overwritesig);
    // signal(SIGABRT, overwritesig);
    // signal(SIGSTOP, overwritesig);


    DIR *dir;
    struct dirent *dp;
    if((dir = opendir(".")) == NULL){
        perror("not opening");
        exit(1);
    }


    // in order to send signals can use: keyboard shortcuts (ie ctrl+z) or programmatically using kill
    // kill(pid, signal) // sends signal to specified process
    // kill(getpid(), SIGKILL) // use to kill current program

    // kill the kid and check that parent is respawning

    int pid = fork();
    // printf("here is kid pid %d\n", pidkid);
    if(pid == 0){

            for(int i = 0;;i++){
                sleep(10);
                cout << i << endl;
                cout << "printing files..." << endl;
                while((dp = readdir(dir)) != NULL){
                    cout << "filename: " << dp -> d_name << " , ";
                    if(dp->d_type == DT_REG) cout << "type: file" << endl;
                    else cout << "type: folder" << endl;
                }
                cout << "...done printing" << endl;
                rewinddir(dir);

                
            }
                
            
        return 0;
        
    }
    
    printf("Kid pid %d\n", pid);
    // sleep(5);
    // cout << "done with sleep" << endl;
    // kill(SIGINT, pid); //FIXME Not working, shouldn't this kill child?
    //kill(SIGINT,getpid());

    wait(0);
    cout << "child is done talking" << endl;

    return 0;

}