# aryakk2-konda3-prithvi4
Final Project
Link to full dataset: http://snap.stanford.edu/data/amazon0302.html
The above dataset can only be used on a linux terminal. To unzip the file using the command "gzip -d 'filename'" in the command line.
To import the file from Windows, go into the directory of the file in Windows, and use the scp protocol to send it into your linux directory.
# Build
- The project has only been tested on linux, it may not work on Windows.
- To execute a directed and unweighted graph data of your own, switch out the filename in the MakeGraph call in main.cpp and swap with your own.
- To compile the project type "make" in the terminal. This will produce an executable called "finalproj". To run the executable, type "./finalproj" in the terminal. This will create the graph and run the algorithms and finally create the data output files.
- To run tests type "make test" on the terminal. Then run the executable "./test" in the terminal once the compilation is finished.
