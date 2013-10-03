mit-C
=====

MIT Practical Programming in C. Lessons and exercises

This zip package contains the HTML pages and files associated with the course. 

Some materials - such as videos, java applets, and other special content - are not posted on the OCW server, 
and are therefore not part of this package. This prevents zip packages from becoming too large for download. 
To download these resources to your computer, please read the FAQ at http://ocw.mit.edu/help/faq-technology/ .

Use of the materials in this package are governed by the same Creative Commons license as all other materials 
published on MIT OpenCourseWare. For more information, see http://ocw.mit.edu/terms .

If you have any trouble using this package, please contact us at ocw@mit.edu .

BLOG
====

06/09/13 continue with assignement 5 remember the most common gcc options: gcc -g -Wall ass5.c -o ass5.o -g is 
necessary to keep the symbols table in the object file and then allow debugging. gcc debugging. howto set a 
breakpoint: break source.c:line tutorial simple de gdb: http://www.unknownroad.com/rtfm/gdbtut/gdbtoc.html 
next: I am doing btree. the talloc function is done. before going on, learn the background of the btree.

07/09/13 spent time setting github and git studied binary tree: see wikipedia "search binary tree" addnode is 
done. the preorder function only displays the last item: weak in recursion?

08/09/13 preorder fixed: as usual in recursion, focus on designing the function considering 
that it was already designed. the rest of the exercise is straight forward.

started with assignment 6a. infix_to_postfix function. does not work because not 
understanding p_expr_token (pointer or what?) note that i have modified evaluate to be able 
to test my function, but the display function is not yet created: what a bordel!

11/09/13 I did not learn anything particular about C except how difficult it is to find your 
way through the code. infix_to_postfix looks completed, but the output displays more 0's 
than expected on the postfix (perhaps of the legacy code dealing with spaces: I left this 
for another occasion)

25/09/13 Started with lesson about pointers to functions, hash and assignment 6b. More about 
pointers, or how to make your debugging life difficult by passing void pointers arguments to 
be casted in runtime. C is a nightmare. Programming in C seems to be about doing very small 
functions easy to read and debug. Anything longer than 15 lines exceeds my understanding 
capabilities. Assignment 6b (pointers to functions) is finished. Next: hashes

27/09/13 Hashes. Seg fault during the first try of the lookup function. Troubleshoot 
Pointers, pointers: the origin of all C seg fault. Interesting: the calls to free the memory 
loop through all the linked list and free the pointers AND wp->word. Perhaps because word 
was create by duplicating a string (which is probably a hidden call to malloc?)

29/09/13 Start assiggment 7. First, install sqlite: sudo apt-get install sqlite3 
libsqlite3-dev
In order to build you need to link the library sqlite3: add "-lsqlite3" to the gcc command
(you may automate this in geany, but then remember to modify again the commands if you
use geany for another different project)
a) is completed. I have started b): you have to complete several functions ("find_value"
is the first called by "store_result"

2/10/2013
End of coding part of ass7. Started with the creation of libraries
I have opted for a static library.
I have found a web page that summarizes the process (see pdf)
After following all the steps, I have a large number of cryptic errors.
It is quite impressive the time it takes in C to do pretty straight forward things...

3/10/13
Ended the creation of the library. The pdf is helpful. I found the origin of the cryptic
errors: I tried to link "static" against both "libprob1.a" and "sqlite3" (by setting the
command line option -static). It looks obvious that sqlite3 is not meant to be linked
statically. Solution: remove the "-static" option but, attention: you link statically
against libprob1.a by removing "-lprob1" and giving libprob1.a instead:
"gcc -Wall prob1d.c -L. libprob1.a -lsqlite3 -o prob1d"

