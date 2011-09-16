///-----------------------------------------------
// Copyright 2011 Wellcome Trust Sanger Institute
// Written by Jared Simpson (js18@sanger.ac.uk)
// Released under the GPL
//-----------------------------------------------
//
// StdAlnTools - Collection of wrappers around the
// stdaln dynamic programming alignment functions
#ifndef STDALNTOOLS_H
#define STDALNTOOLS_H

#include <string>
#include <inttypes.h>
#include "stdaln.h"

// Parameters object 
struct GlobalAlnParams
{
    GlobalAlnParams() { setDefaults(); }

    void setDefaults()
    {
        gap_open = 5;
        gap_ext = 2;
        mismatch = 3;
        match = 1;
        gap_open_extend = gap_open + gap_ext;
        threshold = 30;
        bandwidth = 50;
    }

    // PacBio specific parameters
    void setPacBio()
    {
        setDefaults();

        gap_open = 2;
        gap_ext = 1;
        mismatch = 5;
        gap_open_extend = gap_open + gap_ext;
    }

    int gap_open;
    int gap_ext;
    int mismatch;
    int match;
    int gap_open_extend;
    int threshold;
    int bandwidth;
};

namespace StdAlnTools
{

    // Perform a global alignment between target and query using stdaln
    // If bPrint is true, the padded alignment is printed // to stdout.
    // The alignment score is returned.
    int globalAlignment(const std::string& target, const std::string& query, bool bPrint = false);

    // Convert a std::string into the stdAln required packed format.
    // This function allocates memory which the caller must free.
    uint8_t* createPacked(const std::string& s, size_t start = 0, size_t length = std::string::npos);

    // Calculate the maximum aligned target length possible for a query of length ql
    // under the scoring scheme given by params
    size_t calculateMaxTargetLength(int ql, const GlobalAlnParams& params);

    // Fill in the stdaln AlnParam data, using GlobalAlnParams
    void setAlnParam(AlnParam& par, int matrix[25], const GlobalAlnParams& params);

    // Convert a stdaln path to a pair of padded strings representing the alignment
    void makePaddedStrings(const std::string& s1, const std::string& s2, 
                           path_t* path, int path_len,
                           std::string& out1, std::string& out2, std::string& outm);
    
    // Make a cigar string from a path
    std::string makeCigar(path_t* path, int path_len);

    // Print the padded aligned strings
    void printPaddedStrings(const std::string& s1, const std::string& s2, const std::string& m, int colSize = 100);
};

#endif