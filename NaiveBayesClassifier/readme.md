By Denis Mistrik

This program creates an executable bayes which when run with a training file that includes the names of the items and their traits 
can determine the most likely items given another input file which has a bunch of traits on each line, using bayes's theorem and laplacian smoothing. 
It then outputs a text file with each line corresponding to the most likely item for each line of the second classify input file.

Side note, my makefile produces a executable bayes but i named my cpp bayess because my vscode had a weird bug where that specific name caused it to no longer
highlight errors and caused intellisense to not work. 