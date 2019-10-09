#include <fstream>
#ifndef createAndApply_h
#define createAndApply_h

void createDiff(std::istream& fold, std::istream& fnew, std::ostream& fdiff);
/*
 //createDiff: This function takes the contents of two files, A and A', and produces a diff file containing instructions for converting A into A'. Each day, Small-Mart will use this function at their corporate headquarters to create a new diff file that they will then send to all the devices.
 //The diff file that your implementation of createDiff produces must be in this format: A diff file is a sequence of zero or more instructions, where an instruction is either
 //an Add instruction of the form Alen:text in which len is a sequence of one or more digits representing the number of characters to add, and text is a character sequence of length len, the text to add; or
 //a Copy instruction of the form Clen,offset in which len is a sequence of one or more digits representing the number of characters to copy, and offset is a sequence of one or more digits representing the (zero-based) offset in the original file from which to start copying.
 //a Do-nothing instruction consisting of either a single newline character ('\n') or a single carriage return character ('\r').
 //When run under g32fast, your createDiff function must not run for longer than 15 seconds for any file of up to 100 kilobytes.
 */

bool applyDiff(std::istream& fold, std::istream& fdiff, std::ostream& fnew);
/*
 //applyDiff: This function takes the content of a file A and a diff file, and will apply the instructions in the diff file to produce a new file A'. Each day, every device will use this function to update the previous day's inventory file.
 //The applyDifffunction returns true if the operation succeeds. If it fails because the diff file is malformed (e.g., there's a character other than an A or C where an instruction is expected, or an offset or length is invalid), the function returns false. If the function returns false, the caller can make no assumption about what may or may not have been written to the output destination (so you're free to, for example, just return false as soon as you detect an error, without regard to what you may have already written).
 //Your applyDiff function must not run for longer than 5 seconds for any file of up to 100 kilobytes.
 */

#endif /* createAndApply_h */
