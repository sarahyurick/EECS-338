# EECS-338
Programming exercises from EECS 338 Introduction to Operating Systems and Concurrent Programming

Instructions for hw2q3.c:
Write a c program that takes the output of a “top -b -n 1” command and prints the lines that correspond to processes belonging to root. And only those lines. You can generate sample input by saying  “top -b -n 1 > top.snapshot.3.c” at the command shell (if for some reason you can’t get that command to work, e.g., on a mac, I put 10 snapshots here, e.g., http://codereserve.us/338/top.snapshot.9). Here is a quick guide to the output of the top command if you care https://tecadmin.net/understanding-linux-top-command-results-uses/ . You will have to choose a way to read the input, but I recommend fscanf. Look at examples online such at this: https://www.tutorialspoint.com/c_standard_library/c_function_fscanf.htm .

Instructions for hw2q4.c: 
Modify the last program (from hw2q3) so it sums each memory amount, %, and time elapsed amount, reporting just the sum for root’s processes. Yes, you have to figure out how to sum minutes and seconds. If you don’t take care of days, or convert minutes into hours, I won’t mind. In fact, you could report the time in total minutes if you want. 

Instructions for hw2q5.c: 
Take two snapshots using top. (Do “top -b -n > top.snapshot.3.c” and “top -b -n > top.snapshot.4.c”.) Modify your program so it reports only the differences for each pid (process id), either because a process is new, an old process is no longer being shown, or because the cpu time or memory use has changed. I don’t care about the other columns. You can do memory-change in terms of % and ignore the other three memory columns. What I recommend here is that you allocate an array float pmem[32768] and an array float pcpu[32768] and initialize values to 0 with a loop. Then read one file, parse, and assign values. Then read the other file, parse, and report differences. 
