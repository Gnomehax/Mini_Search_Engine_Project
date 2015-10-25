Joshua Crane and Robert Jacobson 

Mini Seach Engine Project

This program does not contain any third party libraries so you can compile straight from the source code.

To exit the program you must type Q or q

The program accepts the following query forms
boolean operators must be in all caps, the program accepts AND or OR for these operators

 - One word with nothing after it. e.g. flow

 - Two words with either AND or OR in between e.g. flow AND stream, flow OR stream

 - Three words with either AND or OR in between each word e.g. the AND boundary AND layer, the OR boundary OR layer

 - One set of grouped words OR another word e.g. flow AND stream OR layer
This format finds documents containing both the first two words or the last word

 - Two sets of grouped words e.g. reynolds AND number OR reynolds AND numbers
This format finds documents containing either the first set of words or the second set of words

 - Another form of the two sets of grouped words e.g. reynolds OR number OR reynolds OR numbers
This format finds documents containing either the first set of words or the second set of words