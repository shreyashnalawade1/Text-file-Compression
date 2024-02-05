# Text File Compression

    Implemented text file compression using LZW compresion technique.
    The LZW algorithm is a very common compression technique.
    This algorithm is typically used in GIF and optionally 
    in PDF and TIFF. Unix’s ‘compress’ command, among other uses.
    It is lossless, meaning no data is lost when compressing. 
    The algorithm is simple to implement and has the potential 
    for very high throughput in hardware implementations. 
    It is the algorithm of the widely used Unix file 
    compression utility compress, and is used in the GIF image format.

    


## Features
   - Compress and Decompress Text files.
   - Compressed file is binary file with .bin extension.
   - Compress and decompress all the files inside the folder when folder name is given as input.
   - Decompresses only those files that are compressed by this project.
   
   



 
  
## LZW with Dynamic bits size

Here we have tried to implement LZW with dynamic bits size .

The basic algorithm description only mentions "output the index to the result" without specifying how exactly those index values should be written to the result.

Naturally the most space-efficient way of writing them is to write only as many bits for each index as is necessary. If, for example, our maximum bitsize of the dictionary is 16, then the index values should be written as 16-bit integers to the output (thus taking 2 bytes per index).

However, it should be noted that every index value written to the output has a maximum value of the size of the dictionary at that point. In other words, if our dictionary contains eg. only 350 entries so far, the next index written to the output will be between 0 and 350. Thus if we write that value using 16 bits, the highest 7 bits of that value will always be 0. This is, naturally, a waste of space.

Dynamic LZW (which is used eg. in the GIF format) only writes as many bits as the current dictionary size requires. In other words, if the current dictionary size is 350 elements, then the index value will be written as a 9-bit integer (instead of eg. a 16-bit one). When the element with index 511 is added to the dictionary then the output bitsize is incremented by one, ie. all indices will now by written as 10-bit integers.




## Usage
```sh
Clone the repository on your machine. 
```
```sh
 - Open Terminal and change directory to the project directory.
```
```sh
- Type command ' make all' which will compile the required files and generate executable file.
```
```sh
 - project -[cd] -i input file/folder name -o output file/folder name.
    -  -c specifies the option of compression.
    -  -d specifies the option of decompression.
```
  
## Results Obtained

- Using this program we can compress text files upto size 20kB.
- You can refer to results.txt file to get the information about results obtained.

## Authors
- [@Onkar Viralekar](https://github.com/onkar-1432)

  
